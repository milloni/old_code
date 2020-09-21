#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/init_task.h>

const char *statestr(long state) {
    if (state < 0) {
        return "unrunnable";
    } else if (state == 0) {
        return "runnable";
    } else {
        return "stopped";
    }
}

int listing_tasks_init(void)
{
    struct task_struct *task;
    struct list_head *list;

    list_for_each(list, &(init_task.children)) {
        task = list_entry(list, struct task_struct, sibling);
        printk(KERN_INFO "pid: %u, comm: %s, state: %s\n", task->pid,
                task->comm, statestr(task->state));
    }

    return 0;
}

void listing_tasks_exit(void)
{

}

module_init(listing_tasks_init);
module_exit(listing_tasks_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Listing tasks module");
MODULE_AUTHOR("milloni");

