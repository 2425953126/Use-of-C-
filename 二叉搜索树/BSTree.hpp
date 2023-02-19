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
			else//����ɾ����֧
			{
				if (tmp == _root)//�����ɾ���Ľڵ��Ǹ��ڵ��Ҵ˸�ֻ�в�����һ������,��Ҫ�������⴦��
				{
					if (!_root->left && _root->right)
						_root = _root->right;
					else if (_root->left && !_root->right)
						_root = _root->left;
					else if (!_root->left && !_root->right)
						_root = nullptr;
				}//�����ڵ��������Ӷ�����,������������⴦��,�����滻��,��Ϊ��ͨ�ڵ�㴦����
				if (tmp->left == nullptr)//�����ɾ���Ľڵ�û������
					if (parent->left == tmp)      //�����ɾ���Ľڵ���ү�ڵ������
						parent->left = tmp->right;//��ɾ���Ľڵ���Һ��ӱ�Ϊү�ڵ������
					else						  //�����ɾ���Ľڵ���ү�ڵ���Һ���
						parent->right = tmp->right;//��ɾ���Ľڵ���Һ��ӱ�Ϊү�ڵ���Һ���
				else if (tmp->right == nullptr)//�����ɾ���Ľڵ�û���Һ���
					if (parent->left == tmp)      //�����ɾ���Ľڵ���ү�ڵ������
						parent->left = tmp->left;//��ɾ���Ľڵ�����ӱ�Ϊү�ڵ������
					else						  //�����ɾ���Ľڵ���ү�ڵ���Һ���
						parent->right = tmp->left;//��ɾ���Ľڵ�����ӱ�Ϊү�ڵ���Һ���
				else//�����ɾ���Ľڵ�����������,��Ҫʹ���滻��
				{	
					Node* rmin = tmp->right, * rminpar = tmp;//�ұ�ɾ���ڵ���������е���С�ڵ�
					while (rmin->left)						 //����ڵ��Ȼ����,��Ϊ�˷�֧�±�ɾ���ڵ�������һ��������
					{
						rminpar = rmin;
						rmin = rmin->left;//ע����left,�������е�����ڵ�
					}
					tmp->key = rmin->key;//�滻
					tmp->value = rmin->value;
					if (rmin == rminpar->left)//����rmin�����½ڵ�,ע��,�ýڵ�����Ϊԭ��ɾ���ڵ������������ڵ�,�����������������
						rminpar->left = rmin->right;
					else
						rminpar->right = rmin->right;
					 tmp = rmin;//����ɾ���ڵ��Ϊ�����滻���Ǹ��ڵ�
				}
				delete tmp;
				return true;//ɾ�����
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
//�ݹ����Һ�ɾ��
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
				root = root->right;//ע��root����һ��root->left��root->right������
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