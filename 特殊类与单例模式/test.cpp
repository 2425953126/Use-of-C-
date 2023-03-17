#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "SpecialClass.h"
using namespace std;
int main()
{
	Singletion_hungry* p = Singletion_hungry::getdata();
	p->reviseData(50);
	p->hungry();

	Singletion_lazy* p2 = Singletion_lazy::getdata();
	p2->reviseData(100);
	p2->lazy();

	Singletion_lazy2* p3 = Singletion_lazy2::getdata();
	p3->reviseData(150);
	p3->lazy2();
	return 0;
}