函数实现

sys.c

![image-20200403101515824](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200403101515824.png)

![image-20200403085800571](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200403085800571.png)





函数声明

![image-20200403090048678](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200403090048678.png)

是64位的



![image-20200403090931446](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200403090931446.png)



添加系统调用333 mycall

![image-20200403091101882](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200403091101882.png)

![image-20200403091026564](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200403091026564.png)



重复试验二，重新编译内核。。。

成功进入新的内核

![image-20200403201542651](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200403201542651.png)



函数调用测试



![image-20200403203125896](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200403203125896.png)

![image-20200403203201038](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200403203201038.png)

![image-20200403203252240](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200403203252240.png)







get_cur_time.c

```c
#include <linux/module.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/rtc.h>

MODULE_LICENSE("Dual BSD/GPL");

#define SYS_CALL_TABLE_ADDRESS 0xffffffffb1c002a0  //sys_call_table对应的地址
#define NUM 334  //系统调用号为334
int orig_cr0;  //用来存储cr0寄存器原来的值
unsigned long *sys_call_table_my= 0;

static int(*anything_saved)(void);  //定义一个函数指针，用来保存一个系统调用

static int clear_cr0(void) //使cr0寄存器的第17位设置为0（内核空间可写）
{
    unsigned int cr0=0;
    unsigned int ret;
    asm volatile("movq %%cr0,%%rax":"=a"(cr0));//将cr0寄存器的值移动到eax寄存器中，同时输出到cr0变量中
    ret=cr0;
    cr0&=0xfffffffffffeffff;//将cr0变量值中的第17位清0,将修改后的值写入cr0寄存器
    asm volatile("movq %%rax,%%cr0"::"a"(cr0));//将cr0变量的值作为输入，输入到寄存器eax中，同时移动到寄存器cr0中
    return ret;
}

static void setback_cr0(int val) //使cr0寄存器设置为内核不可写
{
    asm volatile("movq %%rax,%%cr0"::"a"(val));
}


asmlinkage long sys_mycall(void )
{
        struct rtc_time tt;

        rtc_time_to_tm(get_seconds(),&tt);
        printk("current time: %d-%d-%d %d:%d:%d\n",tt.tm_year+1900,tt.tm_mon+1,tt.tm_mday,tt.tm_hour+8,tt.tm_min,tt.tm_sec);
        return 0;
}


static int __init call_init(void)
{
    sys_call_table_my=(unsigned long*)(SYS_CALL_TABLE_ADDRESS);
    printk("call_init......\n");
    anything_saved=(int(*)(void))(sys_call_table_my[NUM]);//保存系统调用表中的NUM位置上的系统调用
    orig_cr0=clear_cr0();//使内核地址空间可写
    sys_call_table_my[NUM]=(unsigned long) &sys_mycall;//用自己的系统调用替换NUM位置上的系统调用
    setback_cr0(orig_cr0);//使内核地址空间不可写
    return 0;
}

static void __exit call_exit(void)
{
    printk("call_exit......\n");
    orig_cr0=clear_cr0();
    sys_call_table_my[NUM]=(unsigned long)anything_saved;//将系统调用恢复
    setback_cr0(orig_cr0);
}

module_init(call_init);
module_exit(call_exit);
```



Makefile

```c
obj-m:=get_cur_time.o
CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL_PATH:=/usr/src/linux-headers-5.3.0-28-generic
all:
        make -C  $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
        make -C  $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean

```



make 

![image-20200410114226572](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200410114226572.png)



sudo insmod get_cur_time.ko 

查看sys_call_table，能看到刚才添加的get_cur_time系统调用

sudo cat /proc/kallsyms | grep sys_call_table

![image-20200410114554553](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200410114554553.png)

编写测试

```c
#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>

int main()
{
        printf("call get_cur_time...\n");
        syscall(334);        //测试334号系统调用
        return 0;
}
```



![image-20200410115239085](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200410115239085.png)

删除添加的系统调用

sudo rmmod get_cur_time

再运行

![image-20200410115506839](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200410115506839.png)

![image-20200410115542710](E:\github\Course_Related\操作系统实验\实验3\a.assets\image-20200410115542710.png)

