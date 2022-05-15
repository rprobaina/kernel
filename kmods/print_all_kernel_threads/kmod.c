/*
 *      This is a simple kmod to print all kernel threads.
 *      Notice that kernel threads have a null mm.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/kern_levels.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("Print all kernel threads");
MODULE_VERSION("1.0");

void get_task_state_str(long int state, char *state_str);

int load_func(void)
{
        struct task_struct *task;

        printk("------------------- ALL KERNEL THREADS  -------------------\n");
        for_each_process(task) {
                if(!task->mm) /* if(task->mm) would print all user-space tasks. */
			printk(KERN_INFO "pid: %d, name: %s, is a kernel thread.\n", task->pid, task->comm);
        }   
        printk("-------------------------------------------------\n");

        return 0;
}

void unload_func(void)
{
	/* nothing to do. */
}

module_init(load_func);
module_exit(unload_func);
