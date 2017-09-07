#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#define ADD 0x1
#define SUB 0X2
#define MUL 0x3

dev_t dev;

struct cdev *my_cdev;

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

/*static const char    g_s_Hello_World_string[] = "Hello world from kernel mode!\n\0";
static const ssize_t g_s_Hello_World_size = sizeof(g_s_Hello_World_string);
static ssize_t my_read(
                       struct file *file_ptr
                       , char __user *user_buffer
                       , size_t count
                       ,loff_t *position)
{
    printk( KERN_NOTICE "Simple-driver: Device file is read at offset = %i, read bytes count = %u"
                , (int)*position
                , (unsigned int)count );
     If position is behind the end of a file we have nothing to read */
   // if( *position >= g_s_Hello_World_size )
        //return 0;
//     If a user tries to read more than we have, read only as many bytes as we have */
    //if( *position + count > g_s_Hello_World_size )
      //  count = g_s_Hello_World_size - *position;
    //if( copy_to_user(user_buffer, g_s_Hello_World_string + *position, count) != 0 )
      //  return -EFAULT;
    /* Move reading position 
    *position += count;
    return count;
}*/

static ssize_t my_read(struct file *filp,char *buffer,
                                size_t length,loff_t *offset)
{
        copy_to_user(buffer, ptr1, length);
        return 0;
}


static ssize_t my_write(struct file *filp, const char *buffer,
                                size_t length, loff_t *offset)
{
	int i;
        printk("\nReceiced String :%s \n", buffer);
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






