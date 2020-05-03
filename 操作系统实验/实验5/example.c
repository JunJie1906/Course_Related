#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/proc_fs.h> 
#include <linux/sched.h> 
#include <asm/uaccess.h>
#include <linux/uaccess.h>

#define MODULE_VERS "1.0" 
#define MODULE_NAME "procfs_example" 
#define FOOBAR_LEN 8

/*文件私有数据结构*/ 
struct fb_data_t { 
    char name[FOOBAR_LEN + 1]; 
    char value[FOOBAR_LEN + 1]; 
};

static struct proc_dir_entry *example_dir, *foo_file, *bar_file, *jiffies_file, *symlink; 
struct fb_data_t foo_data, bar_data;

/*读取内核jiffies*/ 
static int proc_read_jiffies(char *page, char **start, off_t off, int count, int *eof, void *data) 
{ 
    int len;

    len = sprintf(page, "jiffies = %ld\n", jiffies);

    return len; 
}

/*读取foo和bar文件*/ 
static int proc_read_foobar(char *page, char **start, off_t off, int count, int *eof, void *data) 
{ 
    int len; 
    struct fb_data_t *fb_data = (struct fb_data_t *)data;

    len = sprintf(page, "%s = '%s'\n", fb_data->name, fb_data->value);
    return len; 
}

/*写入foo和bar文件*/ 
static int proc_write_foobar(struct file *file, const char *buffer, unsigned long count, void *data) 
{
    int len; 
    struct fb_data_t *fb_data = (struct fb_data_t *)data;

    if(count > FOOBAR_LEN) 
        len = FOOBAR_LEN; 
    else 
        len = count; 
    if(copy_from_user(fb_data->value, buffer, len))
        return -EFAULT;

    fb_data->value[len] = '\0';

    return len; 
}

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
    jiffies_file = create_proc_read_entry("jiffies", 0444, example_dir, proc_read_jiffies, NULL);
    //error!!create_proc_read_entry
    if(jiffies_file == NULL) { 
        rv = -ENOMEM; 
        goto no_jiffies; 
    }











    /* 创建foo和bar文件，使用同一读写回调函数 */ 
    foo_file = create_proc_entry("foo", 0644, example_dir); //error!!!!!!!!!create_proc_entry
    if(foo_file == NULL) { 
        rv = -ENOMEM; 
        goto no_foo; 
    } 
    /*设置foo文件的私有数据和读写回调函数*/ 
    strcpy(foo_data.name, "foo"); 
    strcpy(foo_data.value, "foo"); 
    foo_file->data = &foo_data; 
    foo_file->read_proc = proc_read_foobar; 
    foo_file->write_proc = proc_write_foobar; 
    foo_file->owner = THIS_MODULE;
    /* 创建bar文件 */ 
    bar_file = create_proc_entry("bar", 0644, example_dir); //error!!!!!!!!!!!!create_proc_entry
    if(bar_file == NULL) { 
        rv = -ENOMEM; 
        goto no_bar; 
    }

    /*设置bar私有数据和读写回调函数*/ 
    strcpy(bar_data.name, "bar"); 
    strcpy(bar_data.value, "bar"); 
    bar_file->data = &bar_data; 
    bar_file->read_proc = proc_read_foobar; 
    bar_file->write_proc = proc_write_foobar;
    bar_file->owner = THIS_MODULE;









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