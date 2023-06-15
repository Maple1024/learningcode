#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t thread_count) : stop(false) {
        for (size_t i = 0; i < thread_count; ++i)
            workers.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex);
                    this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                    if (this->stop && this->tasks.empty())
                        return;
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task();
            }
                });
    }
    template<class F>
    void enqueue(F&& f) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace(std::forward<F>(f));
        }
        condition.notify_one();
    }
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers)
            worker.join();
    }
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

int main() {
    ThreadPool pool(4);
    for (int i = 0; i < 8; ++i) {
        pool.enqueue([i] {
            std::cout << "hello " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "world " << i << std::endl;
            });
    }
    return 0;
}

/*
该线程池使用了std::function来存储任务，支持传递任意可调用对象。
实现了一个enqueue方法来添加任务，该方法使用了一个std::unique_lock来保证线程安全。
当添加任务时，线程池会通知一个等待中的线程去执行任务。
线程池的析构函数会等待所有线程执行完任务后再退出。

*/