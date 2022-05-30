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
#include <asm/types.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/io.h>

struct page *p;			/* Memory Page */

int load_func(void)
{
	unsigned long v_addr; /* virtual addr we want to follow */	
	unsigned long p_addr; /* physical addr found */	

	struct task_struct *ts;	 	/* Task Struct */
	struct mm_struct *ts_mm; 	/* MM Struct   */

	pgd_t *pgd;	/* Page Global Directory: points to pud */
	p4d_t *p4d;	/* 5-level page table			*/
	pud_t *pud;	/* Page Upper Directory:  points to pmd */
	pmd_t *pmd;	/* Page Middle Directory: points to pte */
	pte_t *pte; 	/* Page Table Entry:	  points to the physical address */

	unsigned long _pgd_index, _p4d_index, _pud_index, _pmd_index, _pte_index;

	/* allocating a memory page to follow */
	//	p = alloc_pages(GFP_KERNEL, 0);
	p = kmalloc(1024, GFP_ATOMIC);
	if(!p){
		printk("Memory unavailable!\n");
		return 1;
	}
	
	memset(p, 0, 1024);

	printk("-------------------------------------\n");

	/* finding the virtual address of p */
	v_addr = (unsigned long) p;
	printk("VIR: 0x%lx\n", v_addr);


	/* finding the PGD and its index */
	ts = current;
	ts_mm = ts->mm;

	pgd = pgd_offset(ts_mm, v_addr);	
	_pgd_index = pgd_index(v_addr);
	if (pgd_none(*pgd) || pgd_bad(*pgd)){
		return 0;
	}
	printk("PGD: 0x%lx (index: 0x%lx)", (unsigned long) pgd, _pgd_index);

	/* finding p4d and its index (five-level page table support)*/
	p4d = p4d_offset(pgd, v_addr);
	_p4d_index = p4d_index(v_addr);
	if (p4d_none(*p4d) || p4d_bad(*p4d)){
		return 0;
	}
        printk("P4D: 0x%lx (index: 0x%lx)", (unsigned long) p4d, _p4d_index);

	/* finding PUD and its index */
	pud = pud_offset(p4d, v_addr);
	_pud_index = pud_index(v_addr);
	if (pud_none(*pud) || pud_bad(*pud)){
		return 0;
	}
	printk("PUD: 0x%lx (index: 0x%lx)", (unsigned long) pud, _pud_index);

	/* finding PMD and its index */
	pmd = pmd_offset(pud, v_addr);
	_pmd_index = pmd_index(v_addr);
	if (pmd_none(*pmd) || pmd_bad(*pmd)){
		return 0;
	}
	printk("PMD: 0x%lx (index: 0x%lx)", (unsigned long) pmd, _pmd_index);
	
	/* finding PTE and its index */
	pte = pte_offset_kernel(pmd, v_addr);
	_pte_index = pte_index(v_addr);
	if(!pte_present(*pte)){
		return 0;
	}
	printk("PTE: 0x%lx (index: 0x%lx)", (unsigned long) pte, _pte_index);

	/* finally, finding the physical address */
	p_addr = pte->pte;				/* FIXME not sure if it's accurate*/
	printk("PHY: 0x%lx\n", p_addr);

	/*
		unsigned long api_p_addr = virt_to_phys(p);
		printk("API PHYSICAL ADDR: 0x%lu\n", api_p_addr);
	*/
	
	return 0;
}

void unload_func(void)
{
	/* freeing the allocated page */
	//__free_pages(p, 0);
	kfree(p);
	printk("-------------------------------------\n");
}

module_init(load_func);
module_exit(unload_func);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ricardo Robaina <rrobaina@redhat.com>");
MODULE_DESCRIPTION("This simple page walker.");
MODULE_VERSION("1.0");
