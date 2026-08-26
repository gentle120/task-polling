#include "task.h"

static task_timer timer = NULL;

static task_list *task_head = NULL;

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

/**
 * @example     In main function
 */
struct task_list task1;
struct task_list task2;

void task1_ob(struct task_list *handle, void *user_data)
{
    (void)handle;
    (void)user_data;

    printf("what can i say\n");
}

void task2_ob(struct task_list *handle, void *user_data)
{
    (void)handle;
    (void)user_data;

    printf("man\n");
}

uint32_t tick(void)
{
    static uint32_t cnt = 0;
    
    return ++cnt;
}

int main(void)
{
    task_init(&task1, "task1", 5, task1_ob, tick);
    task_init(&task2, "task2", 1, task2_ob, tick);

    task_member();

    for(int i = 0; i < 100; i++)
    {
        task_start();
        // task_stop();
    }

}
