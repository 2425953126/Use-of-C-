#pragma once
namespace myreverse_iterator
{	
	//template<class T, class Ref, class Ptr>//T为正向迭代器,Ref为数据的引用,Ptr为数据的指针
	//class reverse_bidirectional_iterator
	//{	
	//	typedef reverse_bidirectional_iterator<T, Ref, Ptr> Self;
	//public:
	//	reverse_bidirectional_iterator(T it=T()):rIterator(it)//同时也是隐式类型转换构造函数
	//	{}
	//	/*ListIterator(const Self& l)
	//	{}*/
	//	Ref operator*() 
	//	{	
	//		T tmp = rIterator;
	//		return *--tmp;//--运算符离tmp操作数更近
	//	}
	//	Ptr operator->()
	//	{
	//		return &(operator*());
	//	}
	//	Self& operator++()
	//	{	
	//		--rIterator;
	//		return *this;
	//	}
	//	Self operator++(int)
	//	{
	//		Self tmp = *this;
	//		--rIterator;
	//		return tmp;
	//	}
	//	Self& operator--()
	//	{	
	//		++rIterator;
	//		return *this;
	//	}
	//	Self operator--(int)
	//	{
	//		Self tmp = *this;
	//		++rIterator;
	//		return tmp;
	//	}
	//	bool operator!=(const Self& l)
	//	{
	//		return rIterator!=l.rIterator;
	//	}
	//	bool operator==(const Self& l)
	//	{
	//		return rIterator==l.rIterator;
	//	}
	//	T rIterator;
	//};
	template<class T>//T为正向迭代器,Ref为数据的引用,Ptr为数据的指针
	class reverse_bidirectional_iterator
	{
		typedef reverse_bidirectional_iterator<T> Self;
		typedef typename T::Ref Ref;
		typedef typename T::Ptr Ptr;
	public:
		reverse_bidirectional_iterator(T it = T()) :rIterator(it)//同时也是隐式类型转换构造函数
		{}
		/*ListIterator(const Self& l)
		{}*/
		Ref operator*()
		{
			T tmp = rIterator;
			return *--tmp;//--运算符离tmp操作数更近
		}
		Ptr operator->()
		{
			return &(operator*());
		}
		Self& operator++()
		{
			--rIterator;
			return *this;
		}
		Self operator++(int)
		{
			Self tmp = *this;
			--rIterator;
			return tmp;
		}
		Self& operator--()
		{
			++rIterator;
			return *this;
		}
		Self operator--(int)
		{
			Self tmp = *this;
			++rIterator;
			return tmp;
		}
		bool operator!=(const Self& l)
		{
			return rIterator != l.rIterator;
		}
		bool operator==(const Self& l)
		{
			return rIterator == l.rIterator;
		}
		T rIterator;
	};
}