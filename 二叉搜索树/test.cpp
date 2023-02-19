#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include "BSTree.hpp"
using namespace std;
void TestBSTree2()
{
	BSTree<string, string> dict;
	dict.Insert("insert", "插入");
	dict.Insert("erase", "删除");
	dict.Insert("left", "左边");
	dict.Insert("string", "字符串");

	string str;
	while (cin >> str)
	{	
		if (str == "-1")
			break;
		auto ret = dict.Find(str);
		if (ret)
		{
			cout << str << ":" << ret->value << endl;
		}
		else
		{
			cout << "单词拼写错误" << endl;
		}
	}

	string strs[] = { "苹果", "西瓜", "苹果", "樱桃", "苹果", "樱桃", "苹果", "樱桃", "苹果" };
	// 统计水果出现的次
	BSTree<string, int> countTree;
	for (auto str : strs)
	{
		auto ret = countTree.Find(str);
		if (ret == NULL)
		{
			countTree.Insert(str, 1);
		}
		else
		{
			ret->value++;
		}
	}
	countTree.InOrder();
}
void TestBSTree1()
{
	BSTree<int,int> t;
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9, 5, 5 };
	for (auto e : a)
	{
		t.Insert(e,e);
	}
	// 排序+去重
	t.InOrder();

	t.reErase(7);
	t.InOrder();

	t.Erase(5);
	t.InOrder();

	t.Erase(0);
	t.InOrder();

	t.Erase(1);
	t.InOrder();

	for (auto e : a)
	{
		t.Erase(e);
		t.InOrder();
	}
	t.InOrder();
}
int main()
{
	TestBSTree1();
	TestBSTree2();
	return 0;
}