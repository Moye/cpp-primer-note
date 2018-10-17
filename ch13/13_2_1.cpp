#include <iostream>
#include <string>

using namespace std;

// 行为像值的类
class HasPtr {
public:
    HasPtr(const string& s = string())
        : ps(new string(s))
        , i(0){}; // 构造函数

    // 对ps指向的string，每个HasPtr对象都有自己的拷贝
    HasPtr(const HasPtr& p)
        : ps(new string(*p.ps))
        , i(p.i){}; // 拷贝构造函数

    HasPtr& operator=(const HasPtr&);
    ~HasPtr() { delete ps; };

private:
    string* ps;
    int i;
};

HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    /*
     * 编写赋值运算符的两点注意：
     * 1.如果将一个对象赋值给它自身，赋值运算符必须能正确工作；
     * 2.大多数赋值运算符组合了析构函数和拷贝构造函数的工作。
     * 一个好的模式是：先将右侧运算对象拷贝到一个局部临时对象中。当
     * 拷贝完成后，销毁左侧运算对象的现有成员就是安全的了。然后将数
     * 据从临时变量拷贝到左侧运算对象的成员中。
     */
    auto newp = new string(*rhs.ps); // 拷贝底层string
    delete ps;                       // 释放旧内存
    ps = newp;                       // 从右侧运算对象拷贝数据到本对象
    i = rhs.i;
    return *this;
}
