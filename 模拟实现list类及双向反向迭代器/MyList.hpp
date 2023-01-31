#pragma once
#include <cassert>
#include <iostream>
#include "MyReverse_iterator.hpp"
namespace mylist
{
	// List�Ľڵ���
	template<class T>
	struct ListNode
	{
		ListNode(const T& val = T()):_val(val)
		{}
		ListNode<T>* _pPre=nullptr;
		ListNode<T>* _pNext=nullptr;
		T _val;//���T��string,vector<>���Զ�������,Ĭ�����ɵ����������ͻ���ö�Ӧ�����������
	};

	//List�ĵ�������
	template<class T, class Ref, class Ptr>
	class ListIterator
	{
	public:
		typedef ListNode<T>* PNode;
		typedef ListIterator<T, Ref, Ptr> Self;
		typedef Ref Ref;
		typedef Ptr Ptr;
	public:
		ListIterator(PNode pNode = nullptr):_pNode(pNode)//ͬʱҲ����ʽ����ת�����캯��
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
		PNode _pNode;//ָ������ڵ��ָ��
	};

	//list��
	template<class T>
	class list
	{
		typedef ListNode<T> Node;
		typedef Node* PNode;
	public:
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;
		typedef myreverse_iterator::reverse_bidirectional_iterator<iterator> reverse_iterator;//typename��,ע����Ҫ��iterator������Ҫȡ����Ƕ������Ϊ����
		typedef myreverse_iterator::reverse_bidirectional_iterator<const_iterator> const_reverse_iterator;
		
		/*typedef myreverse_iterator::reverse_bidirectional_iterator<iterator,T&,T*> reverse_iterator;//�������
		typedef myreverse_iterator::reverse_bidirectional_iterator<const_iterator,const T&,const T*> const_reverse_iterator;*/
												                  //ע��˴�����д��<iterator,const T&,const T*>,�����ڷ����������ģ���е�T															  
																  //�ͱ���Ϊiterator���͵���,��const������õ���begin()/end() const ���ص���const_iterator����
	public:														  //�����ڷ���������Ĺ��캯���оͻ������const_iterator���͵ĵ�������T(iterator)���βθ�ֵ�����,��Ȼ,�޷�ת��,���´���

		///////////////////////////////////////////////////////////////
		// List�Ĺ���
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
		const_iterator begin()const//��const�����õĵ�������ȡ����,���Ҫ���const����,��const_iterator��������������const���͵�,�������ڶ���
		{							//��ָ���Ķ���,ֻ�Ǳ�֤��ָ��Ķ����ֵ�����޸�,���Ҫ��õ�������ģ����ķ���ֵ��const����
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
		// ��posλ��ǰ����ֵΪval�Ľڵ�,���ز���ڵ�ĵ�����
		iterator insert(iterator pos, const T& val)
		{
			PNode newnode = new Node(val);
			newnode->_pPre = pos._pNode->_pPre;
			newnode->_pNext = pos._pNode;
			pos._pNode->_pPre->_pNext = newnode;//ע��˳��,����Ҫ�õ���ֵ������ǰ��͸���
			pos._pNode->_pPre = newnode;
			return newnode;//������ʽ����ת�����캯��,��newnode��ʽ����ת��λ����������!
		}
		// ɾ��posλ�õĽڵ㣬���ظýڵ����һ��λ��
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
		PNode _pHead;//ָ������ͷ��� 
	};
};