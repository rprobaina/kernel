/*
 *      This is a simple kmod to print all tasks' VMAs.
 *      (a very simple pmap that runs in kernel space)
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/kern_levels.h>
#include <linux/mm_types.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("Print all tasks' VMAs");
MODULE_VERSION("1.0");

int load_func(void)
{
        struct task_struct *task; /* current task */
	struct mm_struct *mm; /* mm of current task */
	struct vm_area_struct *area; /* current VMA */

        for_each_process(task) {
		mm = task->mm;
		printk("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printk(KERN_INFO "pid: %d, name: %s.\n", task->pid, task->comm);
		printk("VMAs:");
                
		/* a kernel thread doen't have memory mapped */
		if(!mm){
			printk(KERN_INFO "no area. it's a kernel thread!");
			printk(KERN_INFO "\n");
			continue;
		}
		
		/* print all VMAs details */		
		area = mm->mmap;
		while(area->vm_next){
			printk(KERN_INFO "start: 0x%lx end: 0x%lx size: %ld (bytes) flags: 0x%lx", 
				area->vm_start, area->vm_end, area->vm_end - area->vm_start, 
				area->vm_flags);
			area = area->vm_next;
		}
		printk(KERN_INFO "\n");
        }   

        return 0;
}

void unload_func(void)
{
	/* nothing to do. */
}

module_init(load_func);
module_exit(unload_func);
