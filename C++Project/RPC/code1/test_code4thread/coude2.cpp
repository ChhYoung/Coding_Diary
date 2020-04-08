#include <iostream>
#include <boost/asio.hpp>

int g_count = 0;

void reset_timer(boost::asio::deadline_timer& timer){
    timer.expires_from_now(boost::posix_time::seconds(1));// 重新设置超时时间为 1s
    timer.async_wait([&timer](const boost::system::error_code& ec){ // async_wait() 不会阻塞程序。超时后会调用 lambda 表达式。
        if(ec){
            std::cout<<ec.message()<<std::endl;
            return;
        }

        if(g_count==10){
            return;
        }

        g_count++;

        std::cout<<"timer event"<<std::endl;
        reset_timer(timer);
    });
}

int main()
{
    try{
        boost::asio::io_service io_service;

        boost::asio::deadline_timer timer(io_service);// 初始化 timer，让 timer 作用于上条语句中定义的 io_service。
        timer.expires_from_now(boost::posix_time::seconds(5)); // 超过 5s 后退出，从执行完这句语句开始计时。
        std::cout << "Starting synchronous wait\n";
        timer.wait(); // wait() 函数的作用为阻塞等待。程序会一直卡在本条语句，直到定时器超时。
        std::cout << "Finished synchronous wait\n";

        reset_timer(timer);// 调用上面定义的 reset_timer() 函数。
        io_service.run();// run 函数的作用是阻塞等待 io_service 上所有的时间执行完毕后退出。
                        //在程序执行到这一句的时候，io_service 上只剩下 timer.async_wait() 没有执行完毕，所以此处 run() 的作用为阻塞等待超时。超时之后执行作为 async_wait() 参数的 lambda 表达式。


        std::cout << "Finished asynchronous wait\n";
    }
    catch (std::exception& e){
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}