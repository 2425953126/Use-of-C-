#pragma once
namespace myreverse_iterator
{	
	//template<class T, class Ref, class Ptr>//TΪ���������,RefΪ���ݵ�����,PtrΪ���ݵ�ָ��
	//class reverse_bidirectional_iterator
	//{	
	//	typedef reverse_bidirectional_iterator<T, Ref, Ptr> Self;
	//public:
	//	reverse_bidirectional_iterator(T it=T()):rIterator(it)//ͬʱҲ����ʽ����ת�����캯��
	//	{}
	//	/*ListIterator(const Self& l)
	//	{}*/
	//	Ref operator*() 
	//	{	
	//		T tmp = rIterator;
	//		return *--tmp;//--�������tmp����������
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
	template<class T>//TΪ���������,RefΪ���ݵ�����,PtrΪ���ݵ�ָ��
	class reverse_bidirectional_iterator
	{
		typedef reverse_bidirectional_iterator<T> Self;
		typedef typename T::Ref Ref;
		typedef typename T::Ptr Ptr;
	public:
		reverse_bidirectional_iterator(T it = T()) :rIterator(it)//ͬʱҲ����ʽ����ת�����캯��
		{}
		/*ListIterator(const Self& l)
		{}*/
		Ref operator*()
		{
			T tmp = rIterator;
			return *--tmp;//--�������tmp����������
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