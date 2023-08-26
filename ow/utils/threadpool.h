
#pragma once

#include <vector>
#include <mutex>
#include <thread>
#include <functional>
#include <queue>
#include <condition_variable>
#include <future>

namespace ow::utils
{

class ThreadPool
{
public:
    ThreadPool();
    ~ThreadPool();

    void add_job(std::function<void()> job);

    bool has_work() const;

    unsigned int get_remaining() const;

    void join(); 

private:
    void do_work();

    std::vector<std::thread> m_threads;
    std::mutex m_queue_mutex;
    std::queue<std::packaged_task<void()>> m_queue;
    std::condition_variable m_condition;
    bool m_terminate = false;
};

}