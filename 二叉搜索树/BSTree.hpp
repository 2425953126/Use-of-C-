#pragma once
#include <iostream>
template<class K, class V>
class BSTree
{	
	public:
	struct BSTreeNode
	{
		BSTreeNode(K x = K(), V y = V()) :key(x), value(y), left(nullptr), right(nullptr)
		{}
		BSTreeNode * left;
		BSTreeNode * right;
		K key;
		V value;
	};
	typedef BSTreeNode Node;
public:
	bool Insert(const K& key, const V& value)
	{
		if (!_root)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* tmp = _root,*parent = _root;
		while (1)
		{
			if (key < tmp->key)
				if (tmp->left)
				{
					parent = tmp;
					tmp = tmp->left;
				}
				else
				{
					parent = tmp;
					tmp = new Node(key, value);
					parent->left = tmp;
					return true;
				}
			else if (key > tmp->key)
				if (tmp->right)
				{
					parent = tmp;
					tmp = tmp->right;
				}
				else
				{
					parent = tmp;
					tmp = new Node(key, value);
					parent->right = tmp;
					return true;
				}
			else
				return false;
		}
	}
	Node* Find(const K& key)
	{
		Node* tmp = _root;
		while (tmp)
		{
			if (key < tmp->key)
				tmp = tmp->left;
			else if (key > tmp->key)
				tmp = tmp->right;
			else
				return tmp;
		}
		return nullptr;
	}

	bool Erase(const K& key)
	{
		if (!_root)
			return false;
		Node* parent = _root, * tmp = _root;
		while (tmp)
		{
			if (key < tmp->key)
			{
				parent = tmp;
				tmp = tmp->left;
			}
			else if (key > tmp->key)
			{
				parent = tmp;
				tmp = tmp->right;
			}
			else//进入删除分支
			{
				if (tmp == _root)//如果被删除的节点是根节点且此根只有不超过一个孩子,需要进行特殊处理
				{
					if (!_root->left && _root->right)
						_root = _root->right;
					else if (_root->left && !_root->right)
						_root = _root->left;
					else if (!_root->left && !_root->right)
						_root = nullptr;
				}//若根节点两个孩子都存在,则无需进行特殊处理,交由替换法,视为普通节点般处理即可
				if (tmp->left == nullptr)//如果被删除的节点没有左孩子
					if (parent->left == tmp)      //如果被删除的节点是爷节点的左孩子
						parent->left = tmp->right;//被删除的节点的右孩子变为爷节点的左孩子
					else						  //如果被删除的节点是爷节点的右孩子
						parent->right = tmp->right;//被删除的节点的右孩子变为爷节点的右孩子
				else if (tmp->right == nullptr)//如果被删除的节点没有右孩子
					if (parent->left == tmp)      //如果被删除的节点是爷节点的左孩子
						parent->left = tmp->left;//被删除的节点的左孩子变为爷节点的左孩子
					else						  //如果被删除的节点是爷节点的右孩子
						parent->right = tmp->left;//被删除的节点的左孩子变为爷节点的右孩子
				else//如果被删除的节点有两个孩子,需要使用替换法
				{	
					Node* rmin = tmp->right, * rminpar = tmp;//找被删除节点的右子树中的最小节点
					while (rmin->left)						 //这个节点必然存在,因为此分支下被删除节点至少有一个右子孙
					{
						rminpar = rmin;
						rmin = rmin->left;//注意是left,右子树中的最左节点
					}
					tmp->key = rmin->key;//替换
					tmp->value = rmin->value;
					if (rmin == rminpar->left)//连接rmin的上下节点,注意,该节点由于为原被删除节点的右子树最左节点,因此它不可能有左孩子
						rminpar->left = rmin->right;
					else
						rminpar->right = rmin->right;
					 tmp = rmin;//将被删除节点改为用来替换的那个节点
				}
				delete tmp;
				return true;//删除完毕
			}
		}
		return false;
	}
	void InOrder()
	{	
		int i = 1;
		_InOrder(_root,i);
		std::cout <<std::endl;
	}
//递归版查找和删除
	Node* refind(const K& key)
	{
		return _refind(_root,key);
	}
	bool reErase(const K& key)
	{
		return _reErase(_root, key);
	}
private:
	Node* _root = nullptr;
	void _InOrder(Node* root,int&i)
	{
		if (!root)
			return;
		_InOrder(root->left,i);
		if (i % 11==0)
			std::cout <<std:: endl;
		std::cout << root->key << ':' << root->value << '\t';
		i++;
		_InOrder(root->right, i);
	}
	Node* _refind(Node*root,const K& key)
	{
		if (!root)
			return nullptr;
		if (key < root->key)
			return _refind(root->left,key);
		else if (key > root->key)
			return _refind(root->right,key);
		else
			return root;
	}
	bool _reErase(Node*&root, const K& key)
	{
		if (!root)
			return false;
		if (key < root->key)
			return _reErase(root->left, key);
		else if (key > root->key)
			return _reErase(root->right, key);
		else
		{	
			Node* tmp = root;
			if (!root->left)
				root = root->right;//注意root是上一层root->left或root->right的引用
			else if(!root->right)
				root = root->left;
			else
			{	
				Node* rmin = tmp->right, * rparent = tmp;
				while (rmin->left)
				{
					rparent = rmin;
					rmin = rmin->left;
				}
				tmp->key = rmin->key;
				tmp->value = rmin->value;
				if (rmin == rparent->right)
					rparent->right = rmin->right;
				else
					rparent->left = rmin->right;
				tmp = rmin;
			}
			delete tmp;
			return true;
		}
	}
};