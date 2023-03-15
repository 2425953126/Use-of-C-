#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;
class A {
public:
    // ���캯��
    A(int n) {
        size = n;
        data = new int[n];
        cout << "��ͨ���캯��" << endl;
    }

    // �������캯��
    A(const A& other) {
        size = other.size;
        data = new int[size];
        std::copy(other.data, other.data + size, data);
        cout << "�������캯��" << endl;
    }

    // �ƶ����캯��
    A(A&& other) {
        size = other.size;
        data = other.data;
        other.data = nullptr; // �ñ��ƶ��Ķ�����ָ��ԭ��������
        cout << "�ƶ����캯��" << endl;
    }

    // ��������
    ~A() {
        delete[] data; // �ͷŶ�̬���������
    }
private:
    int size; // �����С
    int* data; // ����ָ��
};
A foo() {
    A a(10); // ����һ����СΪ10��A����
    return a; // �����������
}
int main() {
    A a1(10);
    A x(A(10));
    A y(move(a1));
    return 0;
}