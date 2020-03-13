#ifndef ThreadPool_hpp
#define ThreadPool_hpp
#include <vector>               // std::vector
#include <queue>                // std::queue
#include <memory>               // std::make_shared
#include <stdexcept>            // std::runtime_error
#include <thread>               // std::thread
#include <mutex>                // std::mutex,        std::unique_lock
#include <condition_variable>   // std::condition_variable
#include <future>               // std::future,       std::packaged_task
#include <functional>           // std::function,     std::bind
#include <utility>              // std::move,         std::forward


class ThreadPool{
public: 
    // 在线程池中创建 threads 个工作线程
    ThreadPool(size_t threads);
    // 项线程池中增加线程，其中由->后的推断返回类型
    template<typename F,typename... Args>
    auto enqueue(F&& f, Args&&... args)
        ->std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();

private:
    // 需要持续追踪线程来保证可以使用 join
    // 线程
    std::vector<std::thread> workers;

    // 任务队列
    std::queue<std::function<void()>> tasks;

    //--------------------同步相关
    // 互斥锁
    std::mutex queue_mutex; 
    // 互斥条件变量
    std::condition_variable condition;

    //--------------------停止相关
    bool stop;
};

inline ThreadPool::ThreadPool(size_t threads):stop(false){
    // 启动 threads 数量的工作线程 worker
    for(size_t i=0;i<threads;++i){
        workers.emplace_back(
            // 用Lambda来捕获this,即线程实例
            [this]{
                // 循环避免虚假唤醒
                for(;;){
                    // 定义函数对象的容器，存储任意返回类型为void,参数列表为空的函数
                    std::function<void()> task;
                    // 临界区
                    {
                        // 创建互斥量
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        // 阻塞当前线程，直到 condition_variable被唤醒，当前结束或任务队列非空时
                        // 唤醒
                        this->condition.wait(lock,
                            [this]{return this->stop || !this->tasks.empty();});
                        // 如果当前线程池已经结束且等待队列为空，则直接返回
                        if(this->stop && this->tasks.empty())
                            return ;
                        // 否则运行任务队列队首
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    // 执行任务
                    task();
                }
            }
        );
    }
}

// 销毁线程池中的创建的所有线程
inline ThreadPool::~ThreadPool(){
    // 临界区中改变 stop
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    // 通知所有等待线程
    condition.notify_all();
    // 使所有异步线程转成同步执行
    for(std::thread &worker: workers)
        worker.join();
}

// 添加一个新的线程到线程池
template<typename F,typename...Args>
auto ThreadPool::enqueue(F&& f,Args&&... args)
    ->std::future<typename std::result_of<F(Args...)>::type>{
        using return_type = typename std::result_of<F(Args...)>::type;
        // 获取当前任务
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f),std::forward<Args>(args)...)
        );
        // 获取std::future对象以便实施同步
        std::future<return_type> res = task->get_future();
        // 临界区
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            // 禁止在线程池停止后加入新的线程
            if(stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");
            // 将线程添加到执行任务对了中
            tasks.emplace([task]{(*task)();});
        }
        // 通知一个在等待的线程，相当于V操作
        condition.notify_one();
        return res;
}

#endif 