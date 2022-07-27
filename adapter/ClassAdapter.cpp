#include <iostream>

/**
 * @brief  对象， 负责定义所需要的方法
 *  使用适配器模型，对象与我们的被适配类所使用的方法有相近之处。
 */
class Target {
public:
    virtual ~Target() {}
    virtual void request() = 0;
};

/**
 * @brief 被适配器
 *  扮演持有既定方法的角色
 */
class Adaptee {
public:
    Adaptee() {}
    void special_request() {
        std::cout << "special request" << std::endl;
    }
};

/**
 * @brief 适配器
 * 使用Adaptee的方法来满足Target的请求
 */
class Adapter : public Target, private Adaptee{
public:
    virtual void request() {
        special_request();
    }
};

int main(int argc, char const *argv[])
{
    Target *t = new Adapter();
    t->request();
    delete t;
    return 0;
}
