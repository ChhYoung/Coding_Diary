#include <iostream>
#include <memory>
#include <functional>

class person : public std::enable_shared_from_this<person> {

public:
    void update(){
        name_ = "jack";
        callback_();
    }

    void init_callback(){
        auto self = this->shared_from_this();
        callback_ = [this, self]{
            test();
        };
    }

    void test(){
        auto self = this->shared_from_this();
        std::cout<<name_<<std::endl;
    }

private:
    std::function<void()> callback_;
    std::string name_ = "tom";
};

int main(){
    person* ptr = nullptr;

    {
        std::shared_ptr<person> p = std::make_shared<person>();
        p->init_callback();

        ptr = p.get();
        std::cout<<p.use_count()<<std::endl;
    }

    ptr->update();
}