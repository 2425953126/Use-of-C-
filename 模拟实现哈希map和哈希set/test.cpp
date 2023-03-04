#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "myunordered_set.h"
#include "myunordered_map.h"
#include <string>
using namespace std;
template<class K, class V>
struct getKey
{
	K operator()(const V& data)
	{
		return data.first;
	}
};
int main()
{
	/*OpenHash::HashBucket<int,pair<int,int>, getKey<int, pair<int, int>>> a;
	for (int i = 0; i < 40; i++)
	{
		if (i == 7)
			i = i;
		a.Insert(make_pair(i*17, 10));
	}
	OpenHash::HashBucket<int, pair<int, int>, getKey<int, pair<int, int>>>::Node* p;
	p = a.Find(27);
	a.Erase(374);*/

	/*myset::unordered_set<int> a;
	auto x=a.insert(100);
	a.insert(78);
	myset::unordered_set<int>::iterator it = x.first;
	cout << *it << endl;
	cout << *(++it) << endl;
	for (int i = 0; i < 40; i++)
	{
		a.insert(i);
	}
	for (auto& y : a)
	{
		cout << y<<' ';
	}
	cout << endl;
	cout << *a.find(78) << endl;
	cout << a.empty() << endl;
	cout << a.size() << endl;
	myset::unordered_set<int>::iterator it2 = a.find(18);
	a.erase(it2);
	for (auto& y : a)
	{
		cout << y << ' ';
	}
	cout << endl;
	cout << a.count(178) << endl;
	cout << a.bucket_count() << endl;
	a.insert(80);
	cout << a.bucket_size(0) << endl;*/

	mymap::unordered_map<int, string> b;
	for (int i = 0; i < 40; i++)
		b[i] = "shabi";
	for (auto& y : b)
	{
		cout << y.first<<y.second << ' ';
	}
	cout << endl;
	auto it3 = b.find(18);
	b.erase(it3);
	for (auto& y : b)
	{
		cout << y.first << y.second << ' ';
	}
	cout << endl;
	mymap::unordered_map<int, string>::const_iterator ct4 = b.cbegin();
	/*ct4->second = 1000;*/
	cout << ct4->first << ct4->second << endl;

	myset::unordered_set<int> a;
	auto x=a.insert(100);
	a.insert(78);
	myset::unordered_set<int>::iterator it = x.first;
	cout << *it << endl;
	cout << *(++it) << endl;
	for (int i = 0; i < 40; i++)
	{
		a.insert(i);
	}
	myset::unordered_set<int>::const_iterator ct5 = a.cbegin();
	cout << *ct5 << endl;
	return 0;
}