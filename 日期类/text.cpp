#define _CRT_SECURE_NO_WARNINGS 1
#include "ClassDate.h"
int main()
{
	Date d1(1583,10,15);
	Date d2(1583,10,15);
	Date d3(2023, 1, 5);
	d1 -= 365;
	d2 -= 366;
	d1.PrintDate();
	d2.PrintDate();
	d3.PrintDate();
	cout <<"是" << d3.getweek() << endl;
	cout << d1<<endl;
	int xx;
	cin >> d1;
	cout << d1;
	return 0;
}