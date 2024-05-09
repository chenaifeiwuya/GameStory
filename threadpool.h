
#include <pthread.h>
#include <unistd.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
//任务结构体
typedef struct task{
    void *arg;
    void* (*user_job)(void*);
}task_t;
//线程池的结构体
typedef struct pool{
    int thread_max;//线程的最大数量
    int thread_min;//线程的最小数量
    int thread_alive;//线程的当前数量
    int thread_busy;//线程的运行数量

    int thread_shutdown; //线程的退出标志
    int thread_exitcode;  //让指定个数的线程退出

    task_t* queue_task; //任务队列---环形队列--数组--效率高，提高空间利用率
    int  queue_max;  //任务队列的最大值
    int  queue_front; //任务队列的头指针
    int  queue_tail; //任务队列的尾指针
    int  queue_cur; //当前的任务数量

    pthread_t* consume_id; //消费者线程
    pthread_t  manage_id;//管理者线程

    pthread_mutex_t lock; //互斥锁
    pthread_cond_t   product; //生产者条件变量
    pthread_cond_t   consume; //消费者条件变量

}pool_t;
//线程池的接口
pool_t* threadpool_create(int ,int ,int);//线程创建函数
void threadpool_destroy(pool_t*); //线程池销毁函数
int  threadpool_addtask(pool_t*,task_t); //投递任务函数

void* consume(void*);//线程池-消费者线程
void* manage(void*); //管理者线程 --维持线程池的动态平衡



