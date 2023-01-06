#define _CRT_SECURE_NO_WARNINGS 1
#include "ClassDate.h"
//打印日期
void Date::PrintDate()
{
	cout << _year << "年" << _month << "月" << _day << "日"<<endl;
}
// 全缺省的构造函数
Date::Date(int year, int month, int day)
{	
		_year = year;
		_month = month;
		_day = day;
		if (!(year >= 0 && month > 0 && month < 13 && day>0 && day <= GetMonthDay(year, month)))
			cout << "#错误,输入日期"<< _year << '.' << _month << '.' << _day << "不合法!" << endl;
		if (year == 1582 && month == 10 && day > 4 && day < 15)
			cout << "#警告,公历上不存在此记录,公历1582年10月4号之后为1582年10月15号!" << endl;
}
// 拷贝构造函数
// d2(d1)
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}
// 赋值运算符重载
  // d2 = d3 -> d2.operator=(&d2, d3)
Date& Date::operator=(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}
// 析构函数
Date::~Date()
{

}
// 获取某年某月的天数
int Date::GetMonthDay(int year, int month)
{
	int days[] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
	int day = days[month];
	if (month == 2 && ((year<1582&&year % 4 == 0)||((year>1582&&year%4==0&&year%100!=0)||year%400==0)))//注意了,1582年公历改革,在1582年后才有了百年不闰的规则,之前是没有的
		++day;																          //并且,1582年10月4日到10月15日之间的十天是没有的,星期四10月4日后直接就是星期五10月15日
	return day;
}
// 日期+=天数
Date& Date::operator+=(int day)
{	
	if (day < 0)//防止day为负数
		return *this -= -day;
	int monthday = GetMonthDay(_year, _month);
	if (_year == 1582 && _month == 10&&_day<=4&&_day+day>4)//当日期为1582年10月1日到4日的某一天时,且加上day后将大于4号,需要进行修正,因为没有5号到14号
	{	
		int tmp = 15 - _day;//没有5号,要直接跳到15号,tmp负责记录原日号要加多少天才能达到'5'(15)
		_day = _day + tmp;//把日号升到10月15日
		day = day - tmp+10;//升到10月15日时增加的天数从day中扣除
	}
	_day += day;
	while (_day >monthday)//进行日期进位
	{	
		_day -= monthday;
		_month++;
		if (_year == 1582 && _month == 10 && _day > 4)//1582年10月实际日期为1,2,3,4,15,16...31,实际上只有21天,本应为31天.因此一旦在加的过程中到了该月且大于4号,必须加10天进行修正
			_day += 10;
		if (_month > 12)
		{
			_year++;
			_month = 1;
		}
		monthday = GetMonthDay(_year, _month);
	}
	return *this;
}
// 日期+天数
Date Date::operator+(int day)
{
	Date copy(*this);
	copy += day;
	return copy;
}
// 日期-天数
Date Date::operator-(int day)
{
	Date copy(*this);
	copy -= day;
	return copy;
}
// 日期-=天数
Date& Date:: operator-=(int day)
{	
	if (day < 0)//防止day为负数
		return *this += -day;
	if (_year == 1582 && _month == 10 && _day >= 15 && _day - day < 15)//当日期为1582年10月15日到31日的某一天时,且减去day后将小于15号,需要进行修正,因为没有5号到14号
	{
		int tmp = _day-4;//没有14号,要直接跳到4号,tmp负责记录原日号要减去多少天才能达到'14'(4)
		_day = _day - tmp;//把日号降到10月4日
		day = day-tmp+10;//降到10月4日减去的天数从day中扣除
	}
	_day -= day;
	while (_day < 1)//进行日期借位
	{	
		--_month;
		if (_month < 1)
		{
			--_year;
			_month = 12;
		}
		int monthday = GetMonthDay(_year, _month);
		_day += monthday;
		if (_year == 1582 && _month == 10 && _day < 15)//1582年10月实际日期为1,2,3,4,15,16...31,实际上只有21天,本应为31天.因此一旦在减的过程中到了该月且小于15号,必须加减10天进行修正
			_day -= 10;
	}
	return *this;
}
// 前置++
Date& Date::operator++()
{
	*this += 1;
	return *this;
}
// 后置++
Date Date::operator++(int)
{
	Date copy = *this;
	*this += 1;
	return copy;
}
// 后置--
Date Date::operator--(int)
{
	Date copy = *this;
	*this -= 1;
	return copy;
}
// 前置--
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}
// >运算符重载
bool Date::operator>(const Date& d)
{
	if (_year > d._year)
		return true;
	else if (_year == d._year && _month > d._month)
		return true;
	else if (_year == d._year && _month == d._month && _day > d._day)
		return true;
	else
		return false;
}
// ==运算符重载
bool Date::operator==(const Date& d)
{
	if (_year == d._year && _month == d._month && _day == d._day)
		return true;
	else
		return false;
}
// >=运算符重载
bool Date::operator >= (const Date& d)
{
	if (_year > d._year)
		return true;
	else if (_year == d._year && _month > d._month)
		return true;
	else if (_year == d._year && _month == d._month && _day >= d._day)
		return true;
	else
		return false;
}
// <运算符重载
bool Date::operator < (const Date& d)
{
	return !(*this >= d);
}
// <=运算符重载
bool Date::operator <= (const Date& d)
{
	return !(*this > d);
}
// !=运算符重载
bool Date::operator != (const Date& d)
{
	return !(*this == d);
}

// 日期-日期 返回天数
int Date::dateIncludeDays() const
{
	int normalyears = 0, leapyears = 0,year=1;
	while (year < _year)//公元元年为公元一年,因此从公元1年开始算起
	{
		if (((year < 1582 && year % 4 == 0) || ((year > 1582 && year % 4 == 0 && year % 100 != 0) || year % 400 == 0)))
			leapyears++;
		else
			normalyears++;
		year++;
	}
	int monthsIndays[] = {-1,0,31,59,90,120,151,181,212,243,273,301,334};//用来给出到月份包含从今年开始的总天数,注意12月只包含前是十一个月的天数,一月包含0天
	int days = leapyears * 366 + normalyears * 365+monthsIndays[_month]+_day;
	if (_month>2&& ((year < 1582 && year % 4 == 0) || ((year > 1582 && year % 4 == 0 && year % 100 != 0) || year % 400 == 0)))//如果已经过了2月,且今年为闰年则加一天
		days++;
	if (_year> 1582 ||( _year==1582&&_month > 10)||(_year==1582&&_month==10 && _day > 4))//1582年10月只有21天需要减去,因此凡是1582年10月4日后的日期都多算了十天,要修正
		days -= 10;
	return days;
}
int Date::operator-(const Date& d)
{
	if (this == &d)
		return 0;
	return dateIncludeDays() - d.dateIncludeDays();//不需要用(*this).dateIncludeDays(d)这样的方式,因为在类中的成员函数中使用到本类的函数和变量时,	编译器会自动在类前面加上this->;
}
//求出星期几
string Date::getweek()
{	
	string yearoneweek[] = { "星期六", "星期日", "星期一", "星期二", "星期三", "星期四","星期五", };//公元元年一月一日实际上为星期六
	Date yearone(1, 1, 1);
	return yearoneweek[(*this - yearone) % 7];
	//由于星期四1582年10月4日后直接是星期五10月15日,因此特别注意要在dateIncludeDays()函数中,把1582年10月的天数修正到21天,不然当日期超过1582年10月4日后
	//算出来的总天数就比实际总天数多出来十天,用这个错误的总天数来%7,自然得不到正确的星期几
}
//重载<<与>>用于进行类的输入输出
ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << '/' << d._month << '/' << d._day;
	return out;
}
istream& operator>>(istream& in,Date& d)
{
	in >>d._year>>d._month>> d._day;
	return in;
}