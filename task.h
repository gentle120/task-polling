#ifndef __TASK_H__
#define __TASK_H__

#include <stdio.h>
#include <stdint.h>

struct task_list;

/* timer source */
typedef uint32_t(*task_timer)(void);

/* task object */
typedef void(*task_ob)(struct task_list *handle, void *user_data);

struct task_list
{
    /* set user needed data */
    const char *name;
    void *user_data;

    /* task last time */
    uint32_t deadline;
    uint32_t start;

    /* task node and object */
    struct task_list *next;
    task_ob ob;
};

/* task process */
void task_add(struct task_list *item);
void task_remove(struct task_list *item);
void task_member(void);

/* initialize task polling and operate polling */
void task_init(struct task_list *item, const char *_name, uint32_t _deadline, task_ob ob, task_timer _timer);
void task_start(void);
void task_stop(void);


#endif
