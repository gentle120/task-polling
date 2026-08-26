#ifndef __TASK_H__
#define __TASK_H__

#include <iostream>
#include <stdint.h>

struct task_list;

/* timer source */
typedef uint32_t(*task_timer)(void);

/* task object */
typedef void(*task_ob)(task_list *handle, void *user_data);

struct task_list
{
    /* set user needed data */
    const char *name;
    void *user_data;

    /* task last time */
    uint32_t deadline;
    uint32_t start;

    /* task node and object */
    task_list *next;
    task_ob ob;
};



#endif
