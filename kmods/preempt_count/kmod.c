/*
 *	This is a simple to reproduce the issue "scheduling while atomic."
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/kern_levels.h>
#include <asm/preempt.h>
#include <linux/preempt.h>

int load_func(void)
{
	printk(KERN_ERR "KMOD: preempt_count: 0x%08x(initial state)\n", preempt_count());
	_local_bh_enable();
	printk(KERN_ERR "KMOD: preempt_count: 0x%08x(final state)\n", preempt_count());

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
MODULE_DESCRIPTION("Reproducer preempt_count");
MODULE_VERSION("1.0");
