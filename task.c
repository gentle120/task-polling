/*
 * Copyright (c) August 27, 2026 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "task.h"

static task_timer timer = NULL;

static struct task_list *task_head = NULL;

/**
 * @brief   Add new task item to this list
 * 
 * @param   item     new task item
 * 
 * @retval  None
 */
void task_add(struct task_list *item)
{
    if(task_head == NULL)
    {
        task_head = item;
        return;
    }

    struct task_list *cur = task_head;
    
    while(cur->next)
    {
        cur = cur->next;
    }
    item->next = cur->next;
    cur->next = item;
}

/**
 * @brief   Remove task from list
 * 
 * @param   item    removed task
 * 
 * @retval  None
 */
void task_remove(struct task_list *item)
{
    if(task_head == NULL)
    {
        return;
    }

    if(task_head == item)
    {
       task_head = item->next;
       item->next = NULL;

       return; 
    }

    struct task_list *cur = task_head;
    struct task_list *pre = cur;

    while(cur)
    {
        if(cur == item)
        {
            pre->next = cur->next;
            break;    
        }

        pre = cur;
        cur = cur->next;
    }
}

/**
 * @brief   All task traversal 
 * 
 * @retval  None
 */
void task_member(void)
{
    if(task_head == NULL)
    {
        return;
    }

    struct task_list *cur = task_head;

    while(cur)
    {
        printf("task_name:%s\n", cur->name);
        cur = cur->next;
    }
}

/**
 * @brief   Initialize a task item and add it to list
 * 
 * @param   item        a new task item
 * @param   _name       name of task item
 * @param   _deadline   task deadline run time
 * @param   _ob         callback function of task
 * @param   timer       timer source
 * 
 * @note    Must set timer source as tick timer of task
 * 
 * @retval  None
 */
void task_init(struct task_list *item, const char *_name, uint32_t _deadline, task_ob _ob, task_timer _timer)
{
    item->name = _name;
    item->deadline = _deadline;
    item->start = 0;
    item->next = NULL;
    item->ob = _ob;

    task_add(item);

    timer = _timer;
}

/**
 * @brief   Embark on the task polling
 * 
 * @retval  None 
 */
void task_start(void)
{
    struct task_list *cur = task_head;

    while(cur)
    {
        uint32_t cur_time = timer();
        if(cur_time - cur->start >= cur->deadline)
        {
            if(cur->ob)
            {
                cur->ob(cur, cur->user_data);
            }
            cur->start = cur_time;
        }

        cur = cur->next;
    }
}

/** 
 * @brief   End task task and remove entire list
 * 
 * @retval  None
 */
void task_stop(void)
{
    struct task_list *cur = task_head;
    struct task_list *item = task_head;

    while(cur)
    {
        item = cur->next;
        task_remove(cur);
        cur = item;
    }
}

