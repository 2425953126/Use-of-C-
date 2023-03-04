#pragma once
#include "OpenHash.hpp"
using namespace OpenHash;
namespace mymap
{
	// unordered_map中存储的是pair<K, V>的键值对，K为key的类型，V为value的类型，HF哈希函数类型
	// unordered_map在实现时，只需将hashbucket中的接口重新封装即可
	template<class K, class V, class HF = HashFunc<K>, class EquealKey = equalKey<K>>
	class unordered_map
	{	
		// 通过key获取value的操作
		struct KeyOfValue
		{
			const K& operator()(const pair<K, V>& data)
			{
				return data.first;
			}
		};
	public:
		typedef pair<K, V> Value;
		typedef HashBucket<K, Value, KeyOfValue, HF,EquealKey> HT;
		typedef HBIterator<K, Value, Value&, Value*, HT> iterator;
		typedef HBIterator<K, Value, const Value&, const Value*, HT> const_iterator;
	public:
		unordered_map() : _ht()
		{}

		iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}
		const_iterator cbegin()const
		{
			return _ht.cbegin();
		}
		const_iterator cend()const
		{
			return _ht.cend();
		}
		
		// capacity
		size_t size()const { return _ht.Size(); }
		bool empty()const { return _ht.Empty(); }

		// lookup
		iterator find(const K& key) { return _ht.Find(key); }
		size_t count(const K& key) { return _ht.Count(key); }

		// modify
		pair<iterator, bool> insert(const Value& valye)
		{
			return _ht.Insert(valye);
		}

		iterator erase(iterator position)
		{
			return _ht.Erase(position);
		}

		// Acess
		V& operator[](const K& key)
		{
			auto it = insert(make_pair(key, V()));
			return it.first->second;
		}
		const V& operator[](const K& key)const
		{
			auto it = insert(make_pair(key, V()));
			return it.first->second;
		}

		// bucket
		size_t bucket_count() { return _ht.BucketCount(); }
		size_t bucket_size(size_t n) { return _ht.BucketSize(n); }
	private:
		HT _ht;
	};
}