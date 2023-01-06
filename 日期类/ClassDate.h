#pragma once
#include <iostream>
using namespace std;
class Date
{
public:
	//打印日期
	void PrintDate();
	// 获取某年某月的天数
	int GetMonthDay(int year, int month);
	// 全缺省的构造函数
	Date(int year = 1900, int month = 1, int day = 1);
	// 拷贝构造函数
  // d2(d1)
	Date(const Date& d);

	// 赋值运算符重载
  // d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d);
	// 析构函数
	~Date();
	// 日期+=天数
	Date& operator+=(int day);
	// 日期+天数
	Date operator+(int day);
	// 日期-天数
	Date operator-(int day);
	// 日期-=天数
	Date& operator-=(int day);
	// 前置++
	Date& operator++();
	// 后置++
	Date operator++(int);
	// 后置--
	Date operator--(int);
	// 前置--
	Date& operator--();
	// >运算符重载
	bool operator>(const Date& d);
	// ==运算符重载
	bool operator==(const Date& d);
	// >=运算符重载
	bool operator >= (const Date& d);

	// <运算符重载
	bool operator < (const Date& d);
	// <=运算符重载
	bool operator <= (const Date& d);
	// !=运算符重载
	bool operator != (const Date& d);
	// 日期-日期 返回天数
	int operator-(const Date& d);//蠢比方法,聪明方法是通过把较大日期不断--,减到跟较小日期相等时,--了多少次就是相差的天数
	int dateIncludeDays() const;
	//算出星期几
	string getweek();
	//重载<<与>>用于进行类的输入输出
	friend ostream& operator<<(ostream& cout, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
private:
	int _year;
	int _month;
	int _day;
};