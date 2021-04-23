#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/spinlock.h>
static int major = 230;
static int minor = 0;
static dev_t devno;
static struct cdev cdev;
static struct class *cls;
static struct device *test_device;
static spinlock_t lock;
static int flage = 1;
#define DEAD 1
static int hello_open (struct inode *inode, struct file *filep)
{
    spin_lock(&lock);
    if(flage !=1)
    {
         spin_unlock(&lock);
         return -EBUSY;
    }
    flage =0;
    #if DEAD
    #elif
    spin_unlock(&lock);
    #endif
    return 0;
}
static int hello_release (struct inode *inode, struct file *filep)
{
    flage = 1;
    #if DEAD
    spin_unlock(&lock);
    #endif
    return 0;
}
static struct file_operations hello_ops =
{
    .open = hello_open,
    .release = hello_release,
};
static int hello_init(void)
{
    int result;
    int error;    
    printk("hello_init \n");
    result = register_chrdev( major, "hello", &hello_ops);
    if(result < 0)
    {
        printk("register_chrdev fail \n");
        return result;
    }
    devno = MKDEV(major,minor);
    cls = class_create(THIS_MODULE,"helloclass");
    if(IS_ERR(cls))
    {
        unregister_chrdev(major,"hello");
        return result;
    }
    test_device = device_create(cls,NULL,devno,NULL,"test");
    if(IS_ERR(test_device ))
    {
        class_destroy(cls);
        unregister_chrdev(major,"hello");
        return result;
    }
    spin_lock_init(&lock);
    return 0;
}
static void hello_exit(void)
{
    printk("hello_exit \n");
    device_destroy(cls,devno);    
    class_destroy(cls);
    unregister_chrdev(major,"hello");
    return;
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");