#include<condition_variable>
#include<mutex>
#include<thread>
#include<iostream>
#include<queue>
#include<chrono>

int main(){
    // 生产者数量
    std::queue<int> produced_nums;
    // 互斥锁
    std::mutex m;
    // 条件变量
    std::condition_variable cond_var;
    // 结束标志
    bool done = false;
    // 通知标志
    bool notified = false;

    // 生产者线程
    std::thread producer([&](){
        for(int i=0;i<5;++i){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            // 互斥锁
            // 进入临界区 P
            std::unique_lock<std::mutex> lock(m);
            std::cout<<" producing "<<i<<"\n";
            produced_nums.push(i);
            notified = true;
            // 通知一个线程
            // 出临界区 V
            cond_var.notify_one();
        }
        done = true;
        cond_var.notify_all();
    }
    );

    // 消费者线程
    std::thread consumer([&](){
        std::unique_lock<std::mutex> lock(m);
        while(!done){
            while(!notified){
                cond_var.wait(lock);
            }
            while(!produced_nums.empty()){
                std::cout<<" consuming "<<produced_nums.front()<<"\n";
                produced_nums.pop();
            }
            notified = false;
        }
    }
    );

    producer.join();
    consumer.join();

}