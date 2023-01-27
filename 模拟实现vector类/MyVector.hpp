#pragma once
#include <iostream>
#include <cassert>
namespace myvector
{
	template<class T>
	class vector
	{
	public:
		// Vector的迭代器是一个原生指针
		typedef T* iterator;
		typedef const T* const_iterator;
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator cbegin()const
		{
			return _start;
		}
		const_iterator cend() const
		{
			return _finish;
		}
		// construct and destroy
		vector() :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
		{}
		vector(int n, const T& value = T()) :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
		{
			assert(n >= 0);
			reserve(n);
			_finish = _start + n;
			_endOfStorage = _finish;
			for (auto& x : *this)
			{
				x = value;
			}
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last) :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
		{
			int size = last - first;
			reserve(size);
			iterator it = begin();
			while (first != last)
			{
				*it = *first;
				it++;
				first++;
			}
			_finish = _start + size;
			_endOfStorage = _finish;
		}
		vector(const vector<T>& v) :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
		{
			vector<T> tmp(v.cbegin(), v.cend());
			swap(tmp);
		}
		vector<T>& operator= (vector<T> v)
		{
			swap(v);
			return *this;
		}
		~vector()
		{
			delete[] _start;
			_start = nullptr;
			_finish = nullptr;
			_endOfStorage = nullptr;
		}
		// capacity
		size_t size() const
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _endOfStorage - _start;
		}
		void reserve(size_t n)
		{
			if (n <= capacity())
				return;
			T* tmp = new T[n];
			for (int i = 0; i < size(); i++)
				tmp[i] = (*this)[i];
			delete[] _start;
			_finish = tmp + size();
			_start = tmp;
			_endOfStorage = tmp + n;
		}
		void resize(size_t n, const T& value = T())
		{
			if (capacity() < n)
				reserve(n);
			if (_finish > _start + n)
			{
				_finish = _start + n;
				return;
			}
			while (_finish < _start + n)
			{
				*_finish = value;
				_finish++;
			}
		}
		/////////////////access///////////////////////////////
		T& operator[](size_t pos)
		{
			return *(_start + pos);
		}
		const T& operator[](size_t pos)const
		{
			return *(_start + pos);
		}
		///////////////modify/////////////////////////////
		void push_back(const T& x)
		{
			if (_finish == _endOfStorage)
				reserve(_start == nullptr ? 10 : 1.5 * capacity());
			*_finish = x;
			_finish++;
		}
		void pop_back()
		{
			_finish--;
		}
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endOfStorage, v._endOfStorage);
		}
		iterator insert(iterator pos, const T& x)//注意一旦本函数内发生扩容，则原本pos迭代器就失效了，需要重新设置
		{	
			assert(pos >= _start && pos <= _finish);
			int ipos = pos - _start;
			if (_finish == _endOfStorage)
			{
				reserve(_start == nullptr ? 10 : 1.5 * capacity());
				pos = _start + ipos;
			}
			iterator it = end();
			_finish++;
			while (it != pos)
			{
				*it = *(it - 1);
				it--;
			}
			*pos = x;
			return pos;
		}
		iterator erase(iterator pos)
		{	
			assert(pos >= _start && pos <= _finish);
			iterator it = pos + 1;
			while (it != end())
			{
				*(it - 1) = *it;
				it++;
			}
			_finish--;
			return pos;
		}
	private:
		iterator _start; // 指向数据块的开始
		iterator _finish; // 指向有效数据的尾的下一个
		iterator _endOfStorage; // 指向存储容量的尾
	};
	void shilihua()
	{
		vector<int> a;
	}
}