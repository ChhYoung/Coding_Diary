#include <iostream>
#include <functional>
#include <thread>
#include <memory>
#include <chrono>

struct timer {
    void start() {
        thd_ptr_ = std::make_shared<std::thread>([this]{
            this->test();
        });
    }

    ~timer(){
        stop_ = true;
        thd_ptr_->join();
    }

    void test(){
        /*
        while(!stop_){
            std::cout<<"hello thread"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }*/
        std::cout<<"dasd\n";
    }

    std::shared_ptr<std::thread> thd_ptr_;
    bool stop_ = false;
};

int main(){

    timer t;
    t.start();
    // t.test();
    std::this_thread::sleep_for(std::chrono::seconds(5));
}