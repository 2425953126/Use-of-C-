#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;
class A {
public:
    // 构造函数
    A(int n) {
        size = n;
        data = new int[n];
        cout << "普通构造函数" << endl;
    }

    // 拷贝构造函数
    A(const A& other) {
        size = other.size;
        data = new int[size];
        std::copy(other.data, other.data + size, data);
        cout << "拷贝构造函数" << endl;
    }

    // 移动构造函数
    A(A&& other) {
        size = other.size;
        data = other.data;
        other.data = nullptr; // 让被移动的对象不再指向原来的数据
        cout << "移动构造函数" << endl;
    }

    // 析构函数
    ~A() {
        delete[] data; // 释放动态分配的数组
    }
private:
    int size; // 数组大小
    int* data; // 数组指针
};
A foo() {
    A a(10); // 创建一个大小为10的A对象
    return a; // 返回这个对象
}
int main() {
    A a1(10);
    A x(A(10));
    A y(move(a1));
    return 0;
}