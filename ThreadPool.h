#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool {
private:
    int numThreads;                                   // 线程数量
    std::vector<std::thread> workers;                 // 工作线程集合
    std::queue<std::function<void()>> tasks;          // 任务队列

    std::mutex queueMtx;                              // 队列锁
    std::condition_variable condition;                // 条件变量
    std::atomic<bool> stop;                           // 是否关闭线程池

public:
    ThreadPool(size_t num);
    // 提交任务：把一个任务放进任务队列
    void enqueue(std::function<void()> task);
    ~ThreadPool(); // 析构函数：关闭线程池并等待线程退出
};

#endif // THREADPOOL_H
