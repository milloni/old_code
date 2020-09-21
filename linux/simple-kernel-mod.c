#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

int simple_init(void)
{
    LIST_HEAD(birthday_list);
    struct birthday *p1, *p2, *p3;
    struct birthday *ptr;
    int _cnt = 0;

    printk(KERN_INFO "Loading Module\n");

    
    p1 = kmalloc(sizeof(*p1), GFP_KERNEL);
    p1->day = 2;
    p1->month = 8;
    p1->year = 1995;
    INIT_LIST_HEAD(&p1->list);
    list_add_tail(&p1->list, &birthday_list);

    p2 = kmalloc(sizeof(*p2), GFP_KERNEL);
    p2->day = 9;
    p2->month = 5;
    p2->year = 1997;
    INIT_LIST_HEAD(&p2->list);
    list_add_tail(&p2->list, &birthday_list);

    p3 = kmalloc(sizeof(*p3), GFP_KERNEL);
    p3->day = 29;
    p3->month = 9;
    p3->year = 1997;
    INIT_LIST_HEAD(&p3->list);
    list_add_tail(&p3->list, &birthday_list);

    list_for_each_entry(ptr, &birthday_list, list) {
        printk("List element %d: day=%d,month=%d,year=%d\n", _cnt,
            ptr->day, ptr->month, ptr->year);
        _cnt++;
    }
    
    kfree(p1);
    kfree(p2);
    kfree(p3);
    return 0;
}

void simple_exit(void)
{
    printk(KERN_INFO "Removing Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("milloni");

