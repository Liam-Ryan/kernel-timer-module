#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

static struct timer_list timerlst;

static void timer_callback(struct timer_list *list)
{
	printk("%s called (%ld).\n", __FUNCTION__, jiffies);
}

static int __init onload(void)
{
	int res;
	printk("Timer module loaded\n");

	/*Set up timer with callback*/
	timer_setup(&timerlst, timer_callback, 0);
	printk("Setup timer to fire in 500ms (%ld)\n", jiffies);

	/*mod_timer updates the expires for the timer_list*/
        res = mod_timer(&timerlst, jiffies + msecs_to_jiffies(500));
	if (res) 
		printk("Update timer failed\n");
	return 0;
}

static void __exit onunload(void)
{
	int res;
        res = del_timer(&timerlst);
	if (res)
		printk("Timer is still in use...\n");
	printk("Timer module unloaded\n");
}

module_init(onload);
module_exit(onunload);
MODULE_AUTHOR("Liam Ryan <liamryandev@gmail.com>");
MODULE_LICENSE("GPL");
