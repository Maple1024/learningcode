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
        cv.notify_one(); //���������������߳�
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
������Ĵ����У�����ʹ�û�����������������ʵ�������̵߳�ͬ����printA �������ڸ��ٵ�ǰӦ�ô�ӡ�ĸ���ĸ��

printAFunction() �� printBFunction() �����ֱ��ӡ��ĸ A �� B�����ڴ�ӡ��ͨ������ printA ������֪ͨ��һ���̡߳�

���������������̣߳����ȴ�������ɡ��������߳̽����ӡ��ĸ A �� B ʱ�����Ӧ������ʾ��
*/