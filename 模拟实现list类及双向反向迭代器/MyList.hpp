#pragma once
#include <cassert>
#include <iostream>
#include "MyReverse_iterator.hpp"
namespace mylist
{
	// List的节点类
	template<class T>
	struct ListNode
	{
		ListNode(const T& val = T()):_val(val)
		{}
		ListNode<T>* _pPre=nullptr;
		ListNode<T>* _pNext=nullptr;
		T _val;//如果T是string,vector<>等自定义类型,默认生成的析构函数就会调用对应类的析构函数
	};

	//List的迭代器类
	template<class T, class Ref, class Ptr>
	class ListIterator
	{
	public:
		typedef ListNode<T>* PNode;
		typedef ListIterator<T, Ref, Ptr> Self;
		typedef Ref Ref;
		typedef Ptr Ptr;
	public:
		ListIterator(PNode pNode = nullptr):_pNode(pNode)//同时也是隐式类型转换构造函数
		{}
		/*ListIterator(const Self& l)
		{}*/
		Ref operator*()
		{
			return _pNode->_val;
		}
		Ptr operator->()
		{
			return &(_pNode->_val);
		}
		Self& operator++()
		{
			_pNode = (_pNode->_pNext);
			return *this;
		}
		Self operator++(int)
		{
			Self tmp = *this;
			_pNode = (_pNode->_pNext);
			return tmp;
		}
		Self& operator--()
		{
			_pNode = (_pNode->_pPre);
			return *this;
		}
		Self operator--(int)
		{
			Self tmp = *this;
			_pNode = (_pNode->_pPre);
			return tmp;
		}
		bool operator!=(const Self& l)
		{
			return _pNode != l._pNode;
		}
		bool operator==(const Self& l)
		{
			return _pNode == l._pNode;
		}
		PNode _pNode;//指向链表节点的指针
	};

	//list类
	template<class T>
	class list
	{
		typedef ListNode<T> Node;
		typedef Node* PNode;
	public:
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;
		typedef myreverse_iterator::reverse_bidirectional_iterator<iterator> reverse_iterator;//typename法,注意需要把iterator类中需要取的内嵌类型设为公有
		typedef myreverse_iterator::reverse_bidirectional_iterator<const_iterator> const_reverse_iterator;
		
		/*typedef myreverse_iterator::reverse_bidirectional_iterator<iterator,T&,T*> reverse_iterator;//多参数法
		typedef myreverse_iterator::reverse_bidirectional_iterator<const_iterator,const T&,const T*> const_reverse_iterator;*/
												                  //注意此处不能写成<iterator,const T&,const T*>,这样在反向迭代器类模板中的T															  
																  //就被设为iterator类型的了,但const对象调用的是begin()/end() const 返回的是const_iterator类型
	public:														  //这样在反向迭代器的构造函数中就会出现用const_iterator类型的迭代器给T(iterator)的形参赋值的情况,显然,无法转换,导致错误

		///////////////////////////////////////////////////////////////
		// List的构造
		list()
		{
			CreateHead();
		}
		list(int n, const T& value = T());
		template <class Iterator>
		list(Iterator first, Iterator last)
		{	
			CreateHead();
			Iterator it = first;
			while (it!=last)
			{
				push_back(*it);
				it++;
			}
		}
		list(const list<T>& l)
		{	
			CreateHead();
			list<T> tmp(l.begin(), l.end());
			swap(tmp);
		}
		list<T>& operator=(list<T> l)
		{	
			CreateHead();
			swap(l);
			return *this;
		}
		~list()
		{
			clear();
			delete _pHead;
			_pHead = nullptr;
		}

		///////////////////////////////////////////////////////////////
		// List Iterator
		iterator begin()//ListIterator<T, T&, T*> begin()
		{
			return _pHead->_pNext;
		}
		iterator end()
		{
			return _pHead;
		}
		const_iterator begin()const//给const对象用的迭代器获取函数,因此要设成const类型,但const_iterator迭代器本身并不是const类型的,它可以在定义
		{							//后指向别的对象,只是保证它指向的对象的值不能修改,因此要求该迭代器类模板里的返回值是const类型
			return _pHead->_pNext;
		}
		const_iterator end()const
		{
			return _pHead;
		}
		reverse_iterator rbegin()
		{
			return end();
		}
		reverse_iterator rend()
		{
			return begin();
		}
		const_reverse_iterator rbegin()const
		{
			return end();
		}
		const_reverse_iterator rend()const
		{
			return begin();
		}
		///////////////////////////////////////////////////////////////
		// List Capacity
		size_t size()const
		{	
			if (empty())
				return 0;
			size_t siz = 0;
			for (auto& x : *this)
			{
				siz++;
			}
			return siz;
		}
		bool empty()const
		{
			return _pHead == _pHead->_pNext;
		}

		////////////////////////////////////////////////////////////
		// List Access
		T& front()
		{	
			assert(!empty());
			return _pHead->_pNext->_val;
		}
		const T& front()const
		{	
			assert(!empty());
			return _pHead->_pNext->_val;
		}
		T& back()
		{	
			assert(!empty());
			return _pHead->_pPre->_val;
		}
		const T& back()const
		{	
			assert(!empty());
			return _pHead->_pPre->_val;
		}

		////////////////////////////////////////////////////////////
		// List Modify
		void push_back(const T& val) { insert(end(), val); }
		void pop_back() { erase(--end()); }
		void push_front(const T& val) { insert(begin(), val); }
		void pop_front() { erase(begin()); }
		// 在pos位置前插入值为val的节点,返回插入节点的迭代器
		iterator insert(iterator pos, const T& val)
		{
			PNode newnode = new Node(val);
			newnode->_pPre = pos._pNode->_pPre;
			newnode->_pNext = pos._pNode;
			pos._pNode->_pPre->_pNext = newnode;//注意顺序,后面要用到的值不能在前面就改了
			pos._pNode->_pPre = newnode;
			return newnode;//调用隐式类型转换构造函数,将newnode隐式类型转换位迭代器类型!
		}
		// 删除pos位置的节点，返回该节点的下一个位置
		iterator erase(iterator pos)
		{	
			assert(pos._pNode != _pHead);
			pos._pNode->_pPre->_pNext = pos._pNode->_pNext;
			pos._pNode->_pNext->_pPre = pos._pNode->_pPre;
			iterator tmp = pos;
			pos++;
			delete tmp._pNode;
			return pos;
		}
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				delete (it++)._pNode;
			}
			_pHead->_pPre = _pHead;
			_pHead->_pNext = _pHead;
		}
		void swap(list<T>& l)
		{
			std::swap(_pHead, l._pHead);
		}
	private:
		void CreateHead()
		{
			_pHead = new Node;
			_pHead->_pPre = _pHead;
			_pHead->_pNext = _pHead;
		}
		PNode _pHead;//指向链表头结点 
	};
};