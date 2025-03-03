
#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/irq.h>

#include <asm/uaccess.h>
#include <asm/io.h>
static struct class *leddrv_class;

static volatile unsigned long *gpio_con;
static volatile unsigned long *gpio_dat;
static int pin_start;
static int pin_end;

static int s3c24xx_leds_open(struct inode *inode, struct file *file)
{
	int i;
	//配置为输出模式
	for(i = pin_start; i <= pin_end; i++){
		*gpio_con &= ~(0x3<<(i*2));
		*gpio_con |=   0x1<<(i*2) ;
	}
	return 0;
}

static ssize_t s3c24xx_leds_write(struct file *file, const char __user *buf, size_t count, loff_t * ppos)
{
	int val,i;
	copy_from_user(&val, buf, count);//将用户空间的值获取存在val
	if(1 == val){//点灯
		for(i = pin_start; i <= pin_end; i++)
			*gpio_dat &= ~(1<<i);
	}
	else{//灭灯
		for(i = pin_start; i <= pin_end; i++)
			*gpio_dat |= (1<<i);
	}
	return 0;
}

static struct file_operations led_fops = {
  .owner = THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */ 
  .open  = s3c24xx_leds_open,      	
  .write = s3c24xx_leds_write,	 
};

static int major;
static int led_probe(struct platform_device *pdev)
{
	struct resource *res;
	/* 根据platform_device的资源进行ioremap */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	gpio_con = ioremap(res->start, res->end - res->start + 1);
	gpio_dat = gpio_con + 1;

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	pin_start = res->start;//获取是哪一个按键
	pin_end = res->end;
	
	/* 注册字符设备驱动 */
	printk("led_probe, found led\n");
	major = register_chrdev(0, "s3c2440-led", &led_fops);

	/* 给内核提供 设备信息，用于自动创建设备节点 */	
	leddrv_class = class_create(THIS_MODULE, "s3c2440-led");
	class_device_create(leddrv_class, NULL, MKDEV(major, 0), NULL, "led");/* /dev/led */
	return 0;
}

static int led_remove(struct platform_device *pdev)
{

	/* 卸载字符设备驱动 */
	unregister_chrdev(major,"s3c2440-led");//卸载驱动
	class_device_destroy(leddrv_class, MKDEV(major, 0));
	class_destroy(leddrv_class);

	/* iounmap */
	iounmap(gpio_con);
	printk("led_remove \n");
	return 0;	
}
struct platform_driver led_drv = {
	.probe		= led_probe,
	.remove		= led_remove,
	.driver		= {
		.name	= "s3c2440-led",
	}
};

/* 分配/设置/注册一个platform_drive */

static int led_drv_init(void)
{
	platform_driver_register(&led_drv);
	return 0;
}

static int led_drv_exit(void)
{
	platform_driver_unregister(&led_drv);
	return 0;
}

module_init(led_drv_init);
module_exit(led_drv_exit);
MODULE_LICENSE("GPL");
