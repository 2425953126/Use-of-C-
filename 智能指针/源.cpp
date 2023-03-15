#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <thread>
#include <mutex>
#include "smart_ptr.h"
#include <memory>
using namespace std;
using namespace smart_ptr;
template <class T>
void test(smart_ptr::shared_ptr<T>&ary,size_t n)
{	
	
	for (int i = 1; i < n; i++)
	{
		/*cout << this_thread::get_id() << endl;*/
		smart_ptr::shared_ptr<T> tmp(ary);
		/*cout<<" count为:"<< tmp.getcount() << endl<<endl;*/
	}
}
class X
{
public:
	X()
	{}
	~X()
	{}
};
int main()
{	
	smart_ptr::shared_ptr<X> a(new X);
	smart_ptr::shared_ptr<X> b(new X[10], [](X* ptr) {delete[] ptr; cout << "[]已析构" << endl; }); 
	return 0;
}
//smart_ptr::shared_ptr<int> a(new int(10));
	///*thread t1(test<int>,ref(a),100000);
	//thread t2(test<int>, ref(a), 100000);
	//t1.join();
	//t2.join();
	//cout << "最终为:" << a.getcount() << endl;*/
	//smart_ptr::weak_ptr<int> w(a);
	//cout << *w << endl;
	//smart_ptr::weak_ptr<int> w1;
	//w1 = a;
	//cout << *w1 << endl;
	//smart_ptr::weak_ptr<int> w2;
	//w2 = w1;
	//*w2 = 100;
	//cout << *w2<< endl;