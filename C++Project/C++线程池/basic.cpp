/*
 #include<iostream>
#include<thread>

void foo(){
    std::cout<<"hello world"<<std::endl;
}

int main(){
    std::thread t(foo);
    t.join();
    return 1;
}

*/

#include<iostream>
#include<future>
#include<thread>

int main(){
    //  封装一个返回7的Lambda表达式
    //  std::packaged_task的模板参数为封装函数的类型
    std::packaged_task<int()>  task([](){return 7;});
    //  获取task的future
    std::future<int> result = task.get_future();
    //  在一个线程执行 task
    std::thread(std::move(task)).detach();
    std::cout<<"waiting...";
    result.wait();
    //  输出执行结果
    std::cout<<" Done "<<std::endl<<"Result is "<< result.get()<<"\n";
    
    return 1;
}