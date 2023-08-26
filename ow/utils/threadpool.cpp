#include "threadpool.h"


namespace ow::utils
{

ThreadPool::ThreadPool()
{
    unsigned int num_threads = std::thread::hardware_concurrency();
    for(auto i = 0; i < num_threads; ++i)
    {
        m_threads.emplace_back([this] { do_work(); });
    }
}

ThreadPool::~ThreadPool()
{
    join();
}

void ThreadPool::add_job(std::function<void()> job)
{
    {
        std::unique_lock<std::mutex> lock(m_queue_mutex);
        std::packaged_task<void()> packaged_job(job);
        m_queue.emplace(std::move(packaged_job));
    }
    
    m_condition.notify_one();
}

void ThreadPool::join()
{

    {
      std::unique_lock<std::mutex> l(m_queue_mutex);
      for(auto&&unused:m_threads){
        m_queue.push({});
      }
    }
    m_condition.notify_all();

    for(auto& t: m_threads)
    {
        if(t.joinable())
        {
            t.join();
        }
    }

}

auto ThreadPool::has_work() const -> bool
{
    return !m_queue.empty();
}

unsigned int ThreadPool::get_remaining() const
{
    return m_queue.size();
}


void ThreadPool::do_work()
{
    while(true)
    {
        std::packaged_task<void()> job;
        {
            std::unique_lock<std::mutex> lock(m_queue_mutex);

            if (m_queue.empty()){
                m_condition.wait(lock,[&]{return !m_queue.empty();});
            }
            
            job = std::move(m_queue.front());
            m_queue.pop();
        }
        if (!job.valid()) 
        {
            return;
        }

        job();
    }
}


}