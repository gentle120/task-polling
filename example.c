#include "task.h"

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
    }
}
