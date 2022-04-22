/*
 *	This is a simple kmod to reproduce a self-deadlock, by
 *	trying to acquire a spinlock twice.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <asm/spinlock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("TODO");
MODULE_VERSION("0.1");

DEFINE_SPINLOCK(deadlock_lock); /* Define a spinlock statically */

int load_func(void)
{
	printk("Acquiring the lock\n");
	spin_lock(&deadlock_lock);	

	printk("Acquiring the lock again\n"); /* deadlock */
	spin_lock(&deadlock_lock);	

	printk("Releasing the lock\n");
	spin_unlock(&deadlock_lock);

	return 0;
}

void unload_func(void)
{
	/* Nothing to do. */	
}

module_init(load_func);
module_exit(unload_func);
