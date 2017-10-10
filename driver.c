#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#define ADD 0x1
#define SUB 0X2
#define MUL 0x3

dev_t dev;

struct cdev *my_cdev;

static DECLARE_WAIT_QUEUE_HEAD(wq);
static int flag = 0;

char *ptr;
char *ptr1;

struct foo{
	int a;
	int b;
	int c;

};


static int my_release(struct inode *inode, struct file *file)
{
        kfree(ptr);
        printk("\n Device Released and freed memory \n");
        return 0;
}

static ssize_t my_read(struct file *filp,char *buffer,
                                size_t length,loff_t *offset)
{
	printk("\nprocess going to sleep\n");
	wait_event_interruptible(wq, flag != 0);
	flag = 0;
        copy_to_user(buffer, ptr1, length);
        return 0;
}

static ssize_t my_write(struct file *filp, const char *buffer,
                                size_t length, loff_t *offset)
{
	int i;
        printk("\nReceiced String :%s \n", buffer);
	flag = 1;
	wake_up_interruptible(&wq);
        copy_from_user(ptr, buffer, length);
	printk("\nlength :%zu",length);
	for(i = 0; i < length; i++) {
		ptr1[length-i] = ptr[i];	
		
	}
        return length;
}

static int my_open(struct inode *inode, struct file  *file)
{
        printk("\n Device Major : %d \n", imajor(inode));
        printk("\n Device Minor : %d \n", iminor(inode));
        ptr = kmalloc(15, GFP_KERNEL);
	ptr1 = kmalloc(15,GFP_KERNEL);
        return 0;
}

static struct file_operations fops = {
        .open = my_open,
        .read = my_read,
        .write = my_write,
        .release = my_release
};

static int mymodule_init(void)
{
	int ret_val;
	ret_val = alloc_chrdev_region(&dev,0,1,"mydev_dynamic");
	if(ret_val < 0) {
		printk("\n Error");
		return -1;

	}
	printk("\n Major No: %d %d \n",MAJOR(dev),MINOR(dev));
	my_cdev = cdev_alloc();
	my_cdev->owner = THIS_MODULE;
	my_cdev->ops = &fops;
	cdev_add(my_cdev,dev,1);
	return 0;

}

static void mymodule_exit(void)
{
	unregister_chrdev_region(dev,1);
	cdev_del(my_cdev);
	printk("Unloading my module\n");
	return;

}

module_init(mymodule_init);
module_exit(mymodule_exit);






