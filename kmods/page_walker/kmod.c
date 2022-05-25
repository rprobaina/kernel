/*
 *	This simple kmod will walk through the page tables, in order to
 *	show the process of virtual to physical address conversion.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mm_types.h>
#include <linux/sched/signal.h>
#include <linux/kern_levels.h>

struct page *p;			/* Memory Page */
struct task_struct *ts;	 	/* Task Struct */
struct mm_struct *ts_mm; 	/* MM Struct   */

pgd_t *pgd;	/* Page Global Directory: points to pud */
pud_t *pud;	/* Page Upper Directory:  points to pmd */
pmd_t *pmd;	/* Page Middle Directory: points to pte */
pgtable_t *pte; /* Page Table Entry:	  points to the physical address */

unsigned long pgd_index, pud_index, pmd_index, pte_index;	

int load_func(void)
{
	unsigned long va; /* virtual addr we want to follow */	
	unsigned long pa; /* physical addr found */	

	p = alloc_pages(GFP_KERNEL, 0);
	if(!p){
		printk("Memory unavailable!\n");
		return 1;
	}
	
	printk("-------------------------------------\n");

	va = (unsigned long) p;
	printk("VIR:\t%lx\n", va);

	ts = current;
	ts_mm = ts->mm;

	pgd = ts_mm->pgd;
	pgd_index = (va >> PGDIR_SHIFT);	
	printk("PGD:\t%lx (index: %lx)", (unsigned long) pgd, pgd_index);

	/* TODO */	
	printk("PUD:\t%lx (index: %lx)", (unsigned long) pud, pud_index);
	
	/* TODO */	
	printk("PMD:\t%lx (index: %lx)", (unsigned long) pmd, pmd_index);

	/* TODO */	
	printk("PTE:\t%lx (index: %lx)", (unsigned long) pte, pte_index);
	
	/* TODO */	
	printk("PHY:\t%lx\n", pa);

	return 0;
}

void unload_func(void)
{
	__free_pages(p, 0);
	printk("-------------------------------------\n");
}

module_init(load_func);
module_exit(unload_func);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("This simple page walker.");
MODULE_VERSION("1.0");
