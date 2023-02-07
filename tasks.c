#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#define BUFSIZE  10


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Young");

static struct proc_dir_entry *ent;
static struct proc_dir_entry *dir;

static int tasks(struct seq_file *m, void *v) {
    int num_threads = get_nr_threads(current);
    seq_printf(m, "%d\n", num_threads);
    return 0;
}

static int tasks_init(void) {
    dir = proc_mkdir("tasks", NULL);
    if(!dir) {
        printk(KERN_INFO "Error creating proc entry");
        return -ENOMEM;
    }
    ent = proc_create_single("tasks", 0444, dir, tasks);
    if(!ent) {
        printk(KERN_INFO "Error creating proc entry");
        return -ENOMEM;
    }
    return 0;
}

static void tasks_cleanup(void) {
    proc_remove(ent);
    proc_remove(dir);
}

module_init(tasks_init);
module_exit(tasks_cleanup);
