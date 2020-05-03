void __noreturn do_exit(long code)
{
	//获取当前要释放的进程
	struct task_struct *tsk = current;
	int group_dead;

	//触发task_exit_nb通知链实例的处理函数
	profile_task_exit(tsk);
	kcov_task_exit(tsk);

	//检查进程的blk_plug是否为空
	//保证task_struct中的plug字段是空的，或者plug字段指向的队列是空的。
	WARN_ON(blk_needs_flush_plug(tsk));

	//中断上下文不能执行do_exit函数, 也不能终止PID为0的进程。
	if (unlikely(in_interrupt()))
		panic("Aiee, killing interrupt handler!");
	if (unlikely(!tsk->pid))
		panic("Attempted to kill the idle task!");

	// 设定进程可以使用的虚拟地址的上限（用户空间）
	/*
	 * If do_exit is called because this processes oopsed, it's possible
	 * that get_fs() was left as KERNEL_DS, so reset it to USER_DS before
	 * continuing. Amongst other possible reasons, this is to prevent
	 * mm_release()->clear_child_tid() from writing to a user-controlled
	 * kernel address.
	 */
	set_fs(USER_DS);

	ptrace_event(PTRACE_EVENT_EXIT, code);

	validate_creds_for_do_exit(tsk);


	//检查并设置进程PF_EXITING标志
	/*
	 * We're taking recursive faults here in do_exit. Safest is to just
	 * leave this task alone and wait for reboot.
	 */

	//检查PF_EXITING标识, 此标识表示进程正在退出
	/*如果此标识已被设置, 则进一步设置PF_EXITPIDONE标识,
	并将进程的状态设置为不可中断状态TASK_UNINTERRUPTIBLE,并进程一次进程调度*/
	if (unlikely(tsk->flags & PF_EXITING)) {
		pr_alert("Fixing recursive fault but reboot is needed!\n");
		/*
		 * We can do this unlocked here. The futex code uses
		 * this flag just to verify whether the pi state
		 * cleanup has been done or not. In the worst case it
		 * loops once more. We pretend that the cleanup was
		 * done as there is no way to return. Either the
		 * OWNER_DIED bit is set by now or we push the blocked
		 * task into the wait for ever nirwana as well.
		 */
		tsk->flags |= PF_EXITPIDONE;
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule(); //调度
	}

	//如果此标识未被设置, 则通过exit_signals来设置
	exit_signals(tsk);  /* sets PF_EXITING */
	/*
	 * Ensure that all new tsk->pi_lock acquisitions must observe
	 * PF_EXITING. Serializes against futex.c:attach_to_pi_owner().
	 */


	//内存屏障，用于确保在它之后的操作开始执行之前，它之前的操作已经完成
	smp_mb();
	/*
	 * Ensure that we must observe the pi_state in exit_mm() ->
	 * mm_release() -> exit_pi_state_list().
	 */
	//获得current->pi_lock锁
	raw_spin_lock_irq(&tsk->pi_lock);
	raw_spin_unlock_irq(&tsk->pi_lock);

	if (unlikely(in_atomic())) {
		pr_info("note: %s[%d] exited with preempt_count %d\n",
			current->comm, task_pid_nr(current),
			preempt_count());
		preempt_count_set(PREEMPT_ENABLED);
	}

	//同步进程的mm的rss_stat
	/* sync mm's RSS info before statistics gathering */
	if (tsk->mm)
		sync_mm_rss(tsk->mm);
	
	//获取进程运行时间
	acct_update_integrals(tsk);

	//清除定时器
	group_dead = atomic_dec_and_test(&tsk->signal->live);
	if (group_dead) {
#ifdef CONFIG_POSIX_TIMERS
		hrtimer_cancel(&tsk->signal->real_timer);
		exit_itimers(tsk->signal);
#endif
		if (tsk->mm)
			setmax_mm_hiwater_rss(&tsk->signal->maxrss, tsk->mm);
	}

	acct_collect(code, group_dead);
	if (group_dead)
		tty_audit_exit();
	audit_free(tsk);

	tsk->exit_code = code;
	taskstats_exit(tsk, group_dead);

	//释放占用的资源
	exit_mm(); //释放内存

	if (group_dead)
		acct_process();
	trace_sched_process_exit(tsk);

	exit_sem(tsk);	//释放用户空间的信号量
	exit_shm(tsk);	//释放锁
	exit_files(tsk);//释放已经打开的文件
	exit_fs(tsk);	//释放fs_struct结构体
	//脱离控制终端
	if (group_dead)
		disassociate_ctty(1);
	//释放namespace
	exit_task_namespaces(tsk);
	exit_task_work(tsk);
	exit_thread(tsk);//释放task_struct中的thread_struct结构

	/*
	 * Flush inherited counters to the parent - before the parent
	 * gets woken up by child-exit notifications.
	 *
	 * because of cgroup mode, must be called before cgroup_exit()
	 */
	perf_event_exit_task(tsk);

	sched_autogroup_exit_task(tsk);
	cgroup_exit(tsk);

	/*
	 * FIXME: do that only when needed, using sched_exit tracepoint
	 */
	flush_ptrace_hw_breakpoint(tsk);

	exit_tasks_rcu_start();

	exit_notify(tsk, group_dead); //更新所有子进程的父进程

	proc_exit_connector(tsk);

	mpol_put_task_policy(tsk);
#ifdef CONFIG_FUTEX
	if (unlikely(current->pi_state_cache))
		kfree(current->pi_state_cache);
#endif
	/*
	 * Make sure we are holding no locks:
	 */
	debug_check_no_locks_held();
	/*
	 * We can do this unlocked here. The futex code uses this flag
	 * just to verify whether the pi state cleanup has been done
	 * or not. In the worst case it loops once more.
	 */
	tsk->flags |= PF_EXITPIDONE;

	if (tsk->io_context)
		exit_io_context(tsk);

	if (tsk->splice_pipe)
		free_pipe_info(tsk->splice_pipe);

	if (tsk->task_frag.page)
		put_page(tsk->task_frag.page);

	validate_creds_for_do_exit(tsk);


	/*检查有多少未使用的进程内核栈*/
	check_stack_usage();

	preempt_disable();
	if (tsk->nr_dirtied)
		__this_cpu_add(dirty_throttle_leaks, tsk->nr_dirtied);
	exit_rcu();
	exit_tasks_rcu_finish();

	lockdep_free_task(tsk);
	//设置进程为TASK_DEAD状态，进程无法再被调度
	do_task_dead();
}
