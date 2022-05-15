/*
 *	This is a simple kmod to print 
 *	every task on the system.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/kern_levels.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("Print all tasks");
MODULE_VERSION("1.0");

int load_func(void)
{
	struct task_struct *task;

	printk("------------------- ALL TASKS -------------------\n");
	for_each_process(task) {
		printk(KERN_INFO "pid: %d, name: %s, state: %ld\n", task->pid, task->comm, task->state);
	}
	printk("-------------------------------------------------\n");

	return 0;
}

void unload_func(void)
{

}

module_init(load_func);
module_exit(unload_func);
