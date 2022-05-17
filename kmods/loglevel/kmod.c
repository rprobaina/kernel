/*
 *	This is a simple kmod to print all kernel log levels
 *	defined in "include/linux/kern_levels.h".
 *
 *	It's useful to test rsyslog.conf and dmesg.
 */

#include <linux/init.h>
#include <linux/module.h>

int load_func(void)
{
	printk(KERN_DEBUG "----------------------------- LOG LEVELS -----------------------------"); 
	
	printk("log: KERN_DEFAULT value: %d  \t definition: default (or last) loglevel", LOGLEVEL_DEFAULT);
	printk(KERN_EMERG "log: KERN_EMERG\t value: %d  \t definition: system is unusable", LOGLEVEL_EMERG);
	printk(KERN_ALERT "log: KERN_ALERT\t value: %d  \t definition: action must be taken immediately", LOGLEVEL_ALERT);
	printk(KERN_CRIT "log: KERN_CRIT\t value: %d   \t definition: critical conditions", LOGLEVEL_CRIT);
	printk(KERN_ERR "log: KERN_ERR\t value: %d  \t definition: error conditions", LOGLEVEL_ERR);
	printk(KERN_WARNING "log: KERN_WARNING value: %d  \t definition: warning conditions", LOGLEVEL_WARNING);
	printk(KERN_NOTICE "log: KERN_NOTICE\t value: %d  \t definition: normal but significant condition", LOGLEVEL_NOTICE);
	printk(KERN_INFO "log: KERN_INFO\t value: %d  \t definition: informational", LOGLEVEL_INFO);
	printk(KERN_DEBUG "log: KERN_DEBUG\t value: %d  \t definition: debug-level messages", LOGLEVEL_DEBUG);
	
	printk(KERN_DEBUG "---------------------------------------------------------------------"); 
	return 0;
}

void unload_func(void)
{
	/* nothing to do. */
}

module_init(load_func);
module_exit(unload_func);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("TODO");
MODULE_VERSION("0.1");
