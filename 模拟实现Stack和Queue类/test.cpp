#define _CRT_SECURE_NO_WARNINGS 1
#include "MyStack_and_Queue.hpp"
#include <iostream>
using namespace std;
int main()
{
	MyStack_and_Queue::stack<int> a;
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(4);
	a.push(5);
	while (!a.empty())
	{
		cout << a.top() << ' ';
		a.pop();
	}
	cout << endl;
	MyStack_and_Queue::queue<int> b;
	b.push(1);
	b.push(2);
	b.push(3);
	b.push(4);
	b.push(5);
	while (!b.empty())
	{
		cout << b.front() << ' ';
		b.pop();
	}
	cout << endl;
}