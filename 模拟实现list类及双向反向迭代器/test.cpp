#define _CRT_SECURE_NO_WARNINGS 1
#include "MyList.hpp"
#include <vector>
#include <string>
using namespace std;
int main()
{
	mylist::list<int> a;
	a.push_back(10);
	a.push_back(10);
	a.push_back(10);
	a.push_back(10);
	a.push_back(10);

	mylist::list<int>::iterator it = a.begin();
	for (auto& x : a)
	{
		cout << x << ' ';
	}
	cout << endl;
	cout <<a.size()<< endl;
	cout <<a.empty()<< endl;

	string shili[] = { "hello","hello","shabi" };
	
	const mylist:: list<string>  b(begin(shili),end(shili));
	mylist::list<string>::const_iterator it2 = b.begin();
	for (auto& x : b)
	{
		cout << x << ' ';
	}
	cout << endl;

	mylist::list<string> c;
	c = b;
	cout <<"c:"<< endl;
	for (auto& x : c)
	{
		cout <<x<< ' ';
	}
	cout << endl;
	mylist::list<string>::iterator it3 = c.begin();
	c.erase(it3);
	for (auto& x : c)
	{
		cout << x << ' ';
	}
	cout << endl;
	cout << c.back() << endl;
	c.push_back("nihao");
	c.push_front("nihao");
	for (auto& x : c)
	{
		cout << x << ' ';
	}
	cout << endl;
	c.pop_back();
	c.pop_front();
	for (auto& x : c)
	{
		cout << x << ' ';
	}
	cout << endl;
	mylist::list<int> s;
	s.push_back(100);
	s.push_back(101);
	s.push_back(102);
	s.push_back(103);
	s.push_back(104);
	mylist::list<int>::reverse_iterator rit = s.rbegin();
	while (rit != s.rend())
	{
		cout << *rit << ' ';
		++rit;
	}
	cout << endl;
	const mylist::list<int> cs(s);
	mylist::list<int>::const_reverse_iterator crit = cs.rbegin();
	while (crit != cs.rend())
	{
		cout << *crit << ' ';
		++crit;
	}
	cout << endl;
	while (crit != cs.rbegin())
	{	
		--crit;
		cout << *crit << ' ';
	}
	cout << endl;
	return 0;
}