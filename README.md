## task_polling

#### introduction
[task polling](https://github.com/gentle120/task_polling) is a runtime processor to handle multiple task based on software timer.

#### get started 
**intialize a task**
```cpp
void task_init(struct task_list *item, const char *_name, uint32_t _deadline, task_ob _ob, task_timer _timer)
```

**start task** 
```cpp
void task_start(void)
```

**timer source**
```cpp
/* according user define self timer source */
static task_timer timer = NULL
```

#### example
```cpp
cd build

cmake --build . && ./demo 
```
