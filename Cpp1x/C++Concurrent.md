# C++并发编程

## 1.基础

### 1.1 为什么在引用程序中使用并发： 

**关注点分离**：将相关的代码放到一起，无关的分开

**性能**

### 1.2 实践

- 在linux中编译 `g++ -pthread -o run run.cpp`

```c++
#include<iostream>
#include<thread>
void hello(){
    std::cout<<"hello concurrent world\n";
}

int main(){
    std::thread t{hello};
    t.join();
}
```

- 创建一个线程对象 `std::thread t(hello)` 用`hello()`函数来进行构造，对象`t`拥有函数`hello`作为其初始函数
- 初始线程一分为二，初始线程始于`main`,新线程始于`t`，初始线程可能不会等待新线程，所以可能`t`还没有执行，程序就已经退出，所以调用`t.join()`来关联。

## 2. 管理线程

- `std::thread t{hello}` 来声明线程对象
- `join`声明则等待，`detach`则不等待,只能对给定的线程调用一次`join`，一旦调用则这个thread对象不再是可连接的`joinable()`返回`false`

