#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/proc_fs.h> 
#include <linux/sched.h> 
#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include<linux/seq_file.h>


#define MODULE_VERS "1.0" 
#define MODULE_NAME "procfs_example" 
#define FOOBAR_LEN 8

bool mytest_flag = false;

/*文件私有数据结构*/ 
struct fb_data_t { 
    char name[FOOBAR_LEN + 1]; 
    char value[FOOBAR_LEN + 1]; 
};

static struct proc_dir_entry *example_dir, *foo_file, *bar_file, *jiffies_file, *symlink; 
struct fb_data_t foo_data, bar_data;



// ssize_t file_read(struct file *file, char __user * page, size_t count, loff_t * eof)
// {
//     printk("jiffies = %ld\n", jiffies);
//     return 0; 
// }

static ssize_t proc_write(struct file *file,const char __user *buffer,size_t count,loff_t *pos)
{
	char mode;

	if(count > 0)
	{
		if(get_user(mode,buffer))
		  return -EFAULT;
	}
	return count;
}


// static int proc_show_jiffies(struct seq_file *file, void *v)
// {
//     int cnt = 0;
//     seq_printf(file, "jiffies = %ld\n", jiffies);
//     return cnt;
// }

// static int proc_jiffies_open(struct inode *inode, struct file *file)
// {
//     single_open(file, proc_show_jiffies, NULL);
//     return 0;
// }

static int proc_show_foobar(struct seq_file *file, void * data)
{
    int cnt = 0;

    struct fb_data_t *fb_data = (struct fb_data_t *)data;
    seq_printf(file, "%s = '%s'\n", fb_data->name, fb_data->value);
    return cnt;
}

static int proc_foobar_open(struct inode *inode, struct file *file)
{
    single_open(file, proc_show_foobar, NULL);
    return 0;
}


struct file_operations proc_fops =
{
	.owner = THIS_MODULE,
    .open = proc_foobar_open,
    .read = seq_read,
    .write = proc_write,
    .llseek  = seq_lseek,
    .release = single_release,
};


static ssize_t read_jiffies_proc(struct file *filp,char __user *buf,size_t count,loff_t *offp ){
	printk(KERN_INFO"count=%d  jiff_temp=%d\n", count, jiff_temp);
	char tempstring[100]="";
	if (jiff_temp!=0)
		jiff_temp=sprintf(tempstring, "jiffies=%ld\n", jiffies);	//jiffies为系统启动后经过的时间戳
	if (count>jiff_temp)
		count=jiff_temp;
	jiff_temp=jiff_temp-count;

	printk(KERN_INFO"count=%d  jiff_temp=%d\n", count, jiff_temp);
	copy_to_user(buf, tempstring, count);
	if (count==0)
		jiff_temp=-1;	//读取结束后temp变回-1
	return count;
}

struct file_operations jiff_fops = 
{
	.owner = THIS_MODULE,
    .read = read_jiffies_proc,
    .write = proc_write,
};




/*模块初始化函数*/ 
static int __init init_procfs_example(void) 
{ 
    int rv = 0; 
    /* 在/proc下创建一个父目录 */ 
    example_dir = proc_mkdir(MODULE_NAME, NULL); 
    if(example_dir == NULL) { 
        rv = -ENOMEM; 
        goto out; 
    }

    /* 创建读取jiffies的proc文件 */ 
    jiffies_file = proc_create("jiffies", 0444, example_dir, &jiff_fops);

    if(jiffies_file == NULL) { 
        rv = -ENOMEM; 
        goto no_jiffies; 
    }

    /* 创建foo和bar文件，使用同一读写回调函数 */ 
    foo_file = proc_create("foo", 0644, example_dir, &proc_fops);
    if(foo_file == NULL) { 
        rv = -ENOMEM; 
        goto no_foo; 
    } 

    /* 创建bar文件 */ 
    bar_file = proc_create("bar", 0644, example_dir, &proc_fops);
    if(bar_file == NULL) { 
        rv = -ENOMEM; 
        goto no_bar; 
    }

    /* 创建符号链接 */ 
    symlink = proc_symlink("jiffies_too", example_dir, "jiffies"); 
    if(symlink == NULL) { 
        rv = -ENOMEM; 
        goto no_symlink; 
    }

    printk(KERN_INFO "%s %s initialised\n", MODULE_NAME, MODULE_VERS); 
    return 0;

no_symlink: 
    remove_proc_entry("bar", example_dir); 
no_bar: 
    remove_proc_entry("foo", example_dir); 
no_foo: 
    remove_proc_entry("jiffies", example_dir); 
no_jiffies: 
    remove_proc_entry(MODULE_NAME, NULL); 
out: 
    return rv; 
}

/*模块卸载函数*/ 
static void __exit cleanup_procfs_example(void) 
{ 
    remove_proc_entry("jiffies_too", example_dir); 
    remove_proc_entry("bar", example_dir); 
    remove_proc_entry("foo", example_dir); 
    remove_proc_entry("jiffies", example_dir); 
    remove_proc_entry(MODULE_NAME, NULL); 
    printk(KERN_INFO "%s %s removed\n", 
    MODULE_NAME, MODULE_VERS); 
}

module_init(init_procfs_example); 
module_exit(cleanup_procfs_example); 
MODULE_AUTHOR("Erik Mouw"); 
MODULE_DESCRIPTION("procfs examples");
