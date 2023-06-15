#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool printA = true;

void printAFunction() {
    std::unique_lock<std::mutex> lock(mtx);
    for (int i = 0; i < 10; i++) {
        while (!printA) {
            cv.wait(lock);
        }
        std::cout << "A" << std::endl;
        printA = false;
        cv.notify_one(); //用来唤醒阻塞的线程
    }
}

void printBFunction() {
    std::unique_lock<std::mutex> lock(mtx);
    for (int i = 0; i < 10; i++) {
        while (printA) {
            cv.wait(lock);
        }
        std::cout << "B" << std::endl;
        printA = true;
        cv.notify_one();
    }
}

int main() {
    std::thread t1(printAFunction);
    std::thread t2(printBFunction);
    t1.join();
    t2.join();
    return 0;
}
/*
在上面的代码中，我们使用互斥锁和条件变量来实现两个线程的同步。printA 变量用于跟踪当前应该打印哪个字母。

printAFunction() 和 printBFunction() 函数分别打印字母 A 和 B，并在打印后通过更改 printA 变量来通知另一个线程。

主函数创建两个线程，并等待它们完成。当两个线程交替打印字母 A 和 B 时，输出应如下所示：
*/