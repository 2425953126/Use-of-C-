#pragma once
#include <thread>
#include <mutex>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::mutex;
using std::function;
namespace smart_ptr
{	
	template <class T>//默认删除器
	struct basedeletefunc
	{
		void operator()(T* ptr)
		{
			delete ptr;
			cout << "已成功析构" << endl;
		}
	};

	template <class T,class D= basedeletefunc<T>>
	class auto_ptr
	{	
		typedef auto_ptr<T> Self;
	public:
		auto_ptr(T*ptr=nullptr):_ptr(ptr)
		{}
		~auto_ptr()
		{
			del(_ptr);
			if(_ptr!=nullptr)
				cout <<_ptr<< "已析构" << endl;
		}
		auto_ptr(Self&a)
		{
			std::swap(_ptr, a._ptr);
		}
		Self& operator=(Self&a)
		{
			std::swap(_ptr, a._ptr);
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return &(operator*());
		}
	private:
		T* _ptr;
		D del;
	};

	template<class T,class D= basedeletefunc<T>>
	class unique_ptr
	{
		typedef unique_ptr<T> Self;
	public:
		unique_ptr(T* ptr = nullptr) :_ptr(ptr)
		{}
		~unique_ptr()
		{
			del(_ptr);
			if (_ptr != nullptr)
				cout << _ptr << "已析构" << endl;
		}
		unique_ptr(Self& a) = delete;
		Self& operator=(Self& a) = delete;
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return &(operator*());
		}
	private:
		T* _ptr;
		D del;
	};

	template<class T>
	class shared_ptr
	{
		typedef shared_ptr<T> Self;
	public:
		template <class D = basedeletefunc<T>> shared_ptr(T* ptr = nullptr, D delfunc = basedeletefunc<T>()) :_ptr(ptr),del(delfunc)
		{
			_count = new size_t(1);
			_m = new mutex;
			//*del = D(); 尤其需要注意,这里不能用D来新建一个匿名对象,当D是个lambad表达式类型的时候,它是一个不完整的类型,详情见C++疑难杂解
						//不带捕获的lambda表达式对象可以直接赋值给function类对象
		}
		void clear()
		{
			_m->lock();
			--(*_count);
			_m->unlock();
			if (*_count == 0)
			{
				del(_ptr);
				delete _count;
				delete _m;
				if (_ptr != nullptr)
					cout << _ptr << "已析构" << endl;
			}
		}
		~shared_ptr()
		{
			if (_count != nullptr)
				clear();
		}
		void copy(const Self& a)
		{
			_ptr = a._ptr;
			_count = a._count;
			_m = a._m;
			_m->lock();//临界区
			(*_count)++;
			_m->unlock();

			del = a.del;
		}
		shared_ptr(const Self& a)
		{
			copy(a);
		}
		Self& operator=(const Self& a)
		{
			if (_ptr == a._ptr)
				return *this;
			if (_count != nullptr)
			{
				clear();
			}
			copy(a);
			return *this;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return &(operator*());
		}
		size_t getcount()const
		{
			return *_count;
		}
		T* getptr()const
		{
			return _ptr;
		}
	private:
		T* _ptr;
		size_t* _count;
		mutex* _m;
		function<void(T*)> del;
	};

	template <class T>
	class weak_ptr		//负责封装shared_ptr,拷贝不增加引用计数,处理循环引用情况
	{
		typedef weak_ptr<T> Self;
	public:
		weak_ptr():_ptr( nullptr)
		{}

		weak_ptr(const shared_ptr<T>& sp):_ptr(sp.getptr())
		{}

		Self& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp.getptr();
			return *this;
		}
		Self& operator=(const Self& a)
		{
			_ptr = a._ptr;
			return *this;
		}
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return &(operator*());
		}
	private:
		T* _ptr;
	};
}
