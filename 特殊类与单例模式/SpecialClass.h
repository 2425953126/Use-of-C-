#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <mutex>
using std::mutex;
using std::cout;
using std::endl;

//不能被继承的类 C++11
class noHerit final
{
public:
	noHerit(int x=0):a(x)
	{}
private:
	int a;
};
//C++ 98
class noHerit2
{
public:
	static noHerit2 getObject(int x = 0)
	{	
		return noHerit2(x);
	}
private:
	noHerit2(int x = 0) :a(x)
	{}
	int a;
};

//不能被拷贝,C++11,以下只实现C++11中的方式,C++98,多为将指定函数设为私有,另外处理来完成
class noCopy
{
public:
	noCopy(int x = 0) :a(x)
	{}
	noCopy(const noCopy& nc) = delete;
private:
	int a;
};

//只能在栈
class onlyStack
{
public:
	onlyStack(int x = 0) :a(x)
	{}
	void* operator new(size_t) = delete;
	void operator delete(void*) = delete;
private:
	int a;
};

//只能在堆
class onlyHeap
{
public:
	static onlyHeap* getObject(int x=0)
	{
		return new onlyHeap(x);
	}
	onlyHeap(const onlyHeap& oh) = delete;
private:
	onlyHeap(int x = 0) :a(x)
	{}
	int a;
};

//单例模式:饿汉 
class Singletion_hungry
{
public:
	static Singletion_hungry* getdata()
	{
		return &a;
	}
	void reviseData(int x)
	{
		data = x;
	}
	void hungry()
	{
		cout << data<< endl;
	}
private:
	Singletion_hungry()
	{}
	Singletion_hungry(const Singletion_hungry&) = delete;
	Singletion_hungry operator=(const Singletion_hungry&) = delete;
	static Singletion_hungry a;
	int data=0;
};
Singletion_hungry Singletion_hungry::a;

//单例模式:懒汉 
class Singletion_lazy
{
public:
	static Singletion_lazy* getdata()
	{
		if (ptr == nullptr)
		{
			m.lock();
			if (ptr == nullptr)
			{
				ptr = new Singletion_lazy;
			}
			m.unlock();
		}
		return ptr;
	}
	void reviseData(int x)
	{
		data = x;
	}
	void lazy()
	{
		cout << data << endl;
	}
	class CleanUp
	{
	public:
		~CleanUp()
		{
			if (Singletion_lazy::ptr != nullptr)
				delete Singletion_lazy::ptr;
		}
	};
private:
	Singletion_lazy()
	{}
	Singletion_lazy(const Singletion_lazy&) = delete;
	Singletion_lazy operator=(const Singletion_lazy&) = delete;

	static Singletion_lazy*ptr;
	static mutex m;
	int data = 0;
	static CleanUp clean;
	
};
Singletion_lazy* Singletion_lazy::ptr = nullptr;
mutex  Singletion_lazy::m;
Singletion_lazy::CleanUp Singletion_lazy::clean;

//C++11中支持,C++11以前静态成员初始化不是原子操作,会引发线程安全问题
class Singletion_lazy2
{
public:
	static Singletion_lazy2* getdata()
	{
		static Singletion_lazy2 Sinlazy;
		return &Sinlazy;
	}
	void reviseData(int x)
	{
		data = x;
	}
	void lazy2()
	{
		cout << data << endl;
	}
private:
	Singletion_lazy2()
	{}
	Singletion_lazy2(const Singletion_lazy2&) = delete;
	Singletion_lazy2 operator=(const Singletion_lazy2&) = delete;

	int data = 0;
};
