#include "ThreadPool.h"
#include <mutex>
ThreadPool::ThreadPool(size_t num)
{
    for (size_t i = 0; i < num; i++)
    {
        workers.emplace_back([this]()
                             {
                                 while (true)
                                 {
                                     std::function<void()> task;
                                     {
                                         std::unique_lock<std::mutex> lock(queueMtx);
                                         condition.wait(lock, [this]()
                                                        {
                                                            return stop || tasks.empty();
                                                        });
                                        if (stop&&tasks.empty()) return;
                                        task = std::move(tasks.front());
                                        tasks.pop();
                                     }
                                     task();
                                 } });
    }
}

void ThreadPool::enqueue(std::function<void()> task)
{
    {
        std::lock_guard<std::mutex> lock(queueMtx);
        tasks.push(task);
    }
    condition.notify_one();
}

ThreadPool::~ThreadPool()
{
    {
        std::lock_guard<std::mutex> lock(queueMtx);
        stop = true;
    }
    condition.notify_all(); // 唤醒所有线程
    for (auto &worker : workers)
    {
        if (worker.joinable())
            worker.join();
    }
}