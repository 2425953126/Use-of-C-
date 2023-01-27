#define _CRT_SECURE_NO_WARNINGS 1
#include "MyVector.hpp"
using namespace std;
int main()
{
	int y[5] = { 1,2,3,4,5 };
	myvector::vector<int> a(y, y + 5);
	myvector::vector<int> b(a);
	myvector::vector<int> c;
	c = b;
	/*a.push_back(10);
	a.push_back(20);
	a.push_back(30);
	a.push_back(40);
	a.push_back(50);
	a.push_back(60);*/

	for (auto x : a)
	{
		cout << x << ' ';
	}
	cout << endl;
	for (auto x : b)
	{
		cout << x << ' ';
	}
	cout << endl;
	c.resize(3, 99);
	for (auto x : c)
	{
		cout << x << ' ';
	}
	cout << endl;
	c.pop_back();
	for (auto x : c)
	{
		cout << x << ' ';
	}
	cout << endl;
	a.insert(a.begin() + 5, 888);
	for (auto x : a)
	{
		cout << x << ' ';
	}
	cout << endl;
	int _douint[] = { 1,2,4,5,6,8,8 };
	myvector::vector<int> douint(_douint, _douint + 7);
	myvector::vector<int>::iterator it = douint.begin();
	while (it != douint.end())
	{
		if (*it % 2 == 0)
			it = douint.erase(it);
		else
			it++;
	}
	for (auto x : douint)
	{
		cout << x << ' ';
	}
	cout << endl;
	return 0;
}