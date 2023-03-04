#pragma once
#include <string>
#include <vector>
#include <utility>
#include <cassert>
using std::vector;
using std::string;
using std::pair;
using std::make_pair;
namespace OpenHash
{
	template<class T>
	class HashFunc
	{
	public:
		size_t operator()(const T& val)
		{
			return val;
		}
	};

	template<>
	class HashFunc<string>
	{
	public:
		size_t operator()(const string& s)
		{
			const char* str = s.c_str();
			unsigned int seed = 131; // 31 131 1313 13131 131313
			unsigned int hash = 0;
			while (*str)
			{
				hash = hash * seed + (*str++);
			}
			return hash;
		}
	};
	
	template<class K>
	struct equalKey
	{
		bool operator()(const K&x1,const K&x2)const
		{
			return x1 == x2;
		}
	};

	template<class V>
	struct HashBucketNode
	{
		HashBucketNode(const V& data)
			: _pNext(nullptr), data(data)
		{}
		HashBucketNode<V>* _pNext;
		V data;
	};


	// Ϊ��ʵ�ּ򵥣��ڹ�ϣͰ�ĵ�����������Ҫ�õ�hashBucket����
	template<class K,class V,class getKey, class HF, class EquealKey>
	class HashBucket;

	// ע�⣺��Ϊ��ϣͰ�ڵײ��ǵ�����ṹ�����Թ�ϣͰ�ĵ���������Ҫ--����
	template <class K, class V, class Ref, class Ptr, class HT>
	struct HBIterator
	{
		typedef HashBucketNode<V>* PNode;
		typedef HBIterator<K, V, Ref, Ptr, HT> Self;

		HBIterator(PNode pNode = nullptr, HT* pHt = nullptr) :_pNode(pNode), _pHt(pHt)
		{}
		Self& operator++()
		{
			// ��ǰ��������ָ�ڵ���нڵ�ʱֱ��ȡ����һ���ڵ�
			if (_pNode->_pNext)
				_pNode = _pNode->_pNext;
			else
			{
				// ����һ�����յ�Ͱ�����ظ�Ͱ�е�һ���ڵ�
				_pNode = _pHt->nextExist_table(_pNode);
			}
			return *this;
		}
		Self operator++(int)
		{
			Self tmp(*this);
			++* this;
			return tmp;
		}
		Ref operator*()
		{	
			assert(_pNode);
			return _pNode->data;
		}
		Ptr operator->()
		{
			assert(_pNode);
			return &(operator*());
		}
		bool operator==(const Self& it) const
		{
			return _pNode == it._pNode;
		}
		bool operator!=(const Self& it) const
		{
			return _pNode != it._pNode;
		}
		PNode getNode()
		{
			return _pNode;
		}
	protected:
		PNode _pNode;             // ��ǰ�����������Ľڵ�
		 HT* _pHt;         // ��ϣͰ--��Ҫ��Ϊ������һ����Ͱʱ�򷽱�
	};




	template<class K,class V, class getKey,class HF = HashFunc<K>,class EquealKey=equalKey<K>>
	class HashBucket
	{	
	public:
		typedef HashBucketNode<V> Node;
		typedef Node* PNode;
		typedef HashBucket<K,V,getKey, HF,EquealKey> Self;
		typedef HBIterator<K, V, V&, V*,Self> iterator;
		typedef HBIterator<K, V, const V&, const V*,Self> const_iterator;
	public:
		HashBucket(size_t capacity=10)
			: _table(capacity)
			, _size(0)
		{}

		~HashBucket()
		{
			Clear();
		}
		iterator begin()
		{
			Node* tmp =_begin();
			iterator beg(tmp,this);
			return beg;
		}
		iterator end()
		{
			Node* tmp = _end();
			iterator en(tmp,this);
			return en;
		}
		const_iterator cbegin()const
		{	
			Self* thistmp = const_cast<Self*>(this);
			Node* tmp = thistmp->_begin();
			const_iterator beg(tmp, thistmp);
			return beg;
		}
		const_iterator cend()const
		{	
			Self* thistmp = const_cast<Self*>(this);
			Node* tmp = thistmp->_end();
			const_iterator en(tmp,thistmp);
			return en;
		}
		// ��ϣͰ�е�Ԫ�ز����ظ�
		pair<iterator,bool> Insert(const V& data)
		{	
			if ((float)_size/_table.size()>=1)
			{
				expanCapacity();
			}
			iterator solout = Find(getK(data));
			if (solout!=end())
				return make_pair(solout, false);
			Node* newnode = new Node(data);
			_Insert(newnode);
			return make_pair(iterator(newnode,this), true);
		}
		// ɾ����ϣͰ��Ϊdata��Ԫ��(data�����ظ�)
		iterator Erase(iterator position)
		{	
			assert(position!= end());
			K key = getK(*position);
			++position;

			size_t true_key = tranKey(key);
			size_t prodicted_pos = true_key % _table.size();
			Node* cur = _table[prodicted_pos];
			Node* pre=cur;
			while (cur != nullptr)
			{
				if (equ(getK(cur->data),key))//equ
				{	
					if (cur == pre)//ע������_table�ϴ洢��ָ��,����VS��������һ����delete��cur,cur��ֵ�ᷢ���ı�
						_table[prodicted_pos] = nullptr;
					pre->_pNext = cur->_pNext;
					delete cur;
					_size--;
					return position;
				}
				pre = cur;
				cur = cur->_pNext;
			}
			assert(false);
			return position;
		}

		iterator Find(const K& key)
		{	
			size_t true_key = tranKey(key);
			size_t prodicted_pos = true_key % _table.size();
			Node* tmp = _table[prodicted_pos];
			while (tmp != nullptr && !equ(getK(tmp->data),key))//��Ӧ�ñȽ�true_key��Ӧ�ñȽ�ԭ����key
			{															  //��ͬ��keyֵ����ת��Ϊ��ͬ��true_key
				tmp = tmp->_pNext;
			}
			iterator solout(tmp, this);
			return solout;
		}

		size_t Size()const
		{
			return _size;
		}

		bool Empty()const
		{
			return 0 == _size;
		}

		void Clear()
		{
			for (int i = 0; i < _table.size(); i++)
			{
				Node* cur = _table[i];
				Node* next = nullptr;
				while (cur != nullptr)
				{
					next = cur->_pNext;
					delete cur;
					cur = next;
				}
			}
		}

		size_t BucketCount()const
		{
			return _table.size();
		}

		void Swap(Self& ht)
		{
			std::swap(_table, ht._table);
			std::swap(_size, ht._size);
			std::swap(tranKey, ht.tranKey);
			std::swap(getK, ht.getK);
		}

		size_t Count(const K& key)
		{
			size_t true_key = tranKey(key);
			size_t prodicted_pos = true_key % _table.size();
			Node* cur = _table[prodicted_pos];
			size_t count = 0;
			while (cur != nullptr)
			{
				if (getK(cur->data) == key)
					count++;
				cur = cur->_pNext;
			}
			return count;
		}
	private:
		/*size_t HashFunc(const V& data)//ͨ����ʱ������÷º���
		{
			return HF()(data) % _table.size();
		}*/

		void expanCapacity()
		{
			Self tmptable(2 * _table.size());
			for (int i = 0; i < _table.size(); i++)
			{	
				Node* cur = _table[i];
				Node* next = nullptr;
				while (cur != nullptr)
				{	
					next = cur->_pNext; 
					tmptable._Insert(cur);
					cur = next;
				}
			}
			_table.clear();//ע��ԭvector�еĸ�Ԫ����Ȼ�ǵýڵ�ĵ�ַ,���������������,��Ҫclear
			Swap(tmptable);
		}

		void _Insert(Node*insertNode)//��ʵ�Ǹ�����ڵ㰲����ȷ��λ��,ͷ��
		{
			size_t truekey = tranKey(getK(insertNode->data));
			insertNode->_pNext = _table[truekey % _table.size()];
			_table[truekey % _table.size()] = insertNode;
			_size++;
		}
	public:
		HF tranKey;
		getKey getK;
		EquealKey equ;
		size_t true_pos(Node* p)//����һ���ڵ�Ӧ�����ڵ�Ͱ
		{
			size_t truekey = tranKey(getK(p->data));
			return truekey % _table.size();
		}
		Node* nextExist_table(Node* p)
		{
			size_t nowPos = true_pos(p);
			for (int i = nowPos+1; i < _table.size(); i++)
			{
				Node* cur = _table[i];
				if (cur != nullptr)
					return cur;
			}
			return nullptr;
		}

		Node* _begin()
		{
			if (_table[0])
				return _table[0];
			else
				return nextExist_table(_table[0]);
		}
		Node* _end()
		{
			return nullptr;
		}
		size_t BucketCount()
		{
			return _table.size();
		}
		size_t BucketSize(size_t n)
		{
			Node* cur = _table[n];
			size_t count = 0;
			while (cur != nullptr)
			{
				count++;
				cur = cur->_pNext;
			}
			return count;
		}
	private:
		vector<Node*> _table;
		size_t _size;      // ��ϣ������ЧԪ�صĸ���
	};
}