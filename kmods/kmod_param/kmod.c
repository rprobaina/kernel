/*
 *	This is a simple kmod that has one paramter.
 */

#include <linux/init.h>
#include <linux/module.h>

static int kmod_param_enable = 0;
module_param(kmod_param_enable, int, 0644); /* defines a module parameter */

int load_func(void)
{
	if(kmod_param_enable)
		printk(KERN_INFO "kmod_param enabled!");	
	return 0;
}

void unload_func(void)
{
	printk(KERN_DEBUG "kmod_param_enable: %d", kmod_param_enable);
}

module_init(load_func);
module_exit(unload_func);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("TODO");
MODULE_VERSION("0.1");
MODULE_PARM_DESC(kmod_param_enable, "It enables enables this module."); /* informational only */
