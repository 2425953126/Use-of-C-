#pragma once
#include <utility>
#include <iostream>
#include <cassert>
using namespace std;
using std::pair;
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode(const pair<K, V>& x = pair<K, V>())
		: _Left(nullptr)
		, _Right(nullptr)
		, _Parent(nullptr)
		, _data(x)
		, _bf(0)
	{}
	AVLTreeNode<K, V>* _Left;
	AVLTreeNode<K, V>* _Right;
	AVLTreeNode<K, V>* _Parent;
	pair<K, V> _data;
	short int _bf;   // �ڵ��ƽ������
};
 
// AVL: ���������� + ƽ�����ӵ�����
template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree()
		: _Root(nullptr)
	{}
 
    // ��AVL���в���ֵΪdata�Ľڵ�
	bool Insert(const pair<K,V>&data)
	{	
		const auto& key = data.first;
		if (!_Root)
		{
			_Root = new Node(data);
			return true;
		}
		Node* cur = _Root;
		Node* parent = nullptr;
		while (cur)
		{	
			auto& ckey = cur->_data.first;
			if (key < ckey)
				if (cur->_Left)
				{
					parent = cur;
					cur = cur->_Left;
				}
				else
				{
					cur->_Left = new Node(data);
					parent = cur;
					cur = cur->_Left;
					cur->_Parent = parent;
					break;
				}
			else if (key > ckey)
				if (cur->_Right)
				{
					parent = cur;
					cur = cur->_Right;
				}
				else
				{
					cur->_Right = new Node(data);
					parent = cur;
					cur = cur->_Right;
					cur->_Parent = parent;
					break;
				}
			else
				return false;
		}
		//��֤ƽ������
		Node* insertnode = cur;
		while (cur->_Parent)
		{
			if (cur == cur->_Parent->_Left)
			{
				cur = cur->_Parent;
				cur->_bf--;
			}
			else
			{
				cur = cur->_Parent;
				cur->_bf++;
			}
			//���
			if (cur->_bf == 0)
				break;
			else if (cur->_bf == 1 || cur->_bf == -1)
				continue;
			else
			{
				if (cur->_bf == -2 && cur->_Left->_bf == -1)//�ҵ��������
				{
					RotateR(cur);
					break;
				}
				else if (cur->_bf == 2 && cur->_Right->_bf == 1)//���������
				{												//���ݲ���ڵ���ʧ�������������������ĸ�����ʧ����������������������������Һ��ӣ�ƽ�����ӵ��������������ͬ
					RotateL(cur);
					break;
				}
				else if (cur->_bf == -2 && cur->_Left->_bf == 1)//����˫��
				{
					RotateLR(cur);
					if (parent == insertnode->_Left)
						break;//�������,����ڵ��Ϊʧ�������ڵ�,������ڵ���ʧ�������������������ĸ�,����ƽ�������Ѿ������ҵ����б�����Ϊ0
					else if ((parent->_data.first) > (insertnode->_data.first))
					{
						cur->_bf = 1;//�����bfΪ0
						break;
					}
					else if ((parent->_data.first) < (insertnode->_data.first))
					{
						parent->_Left->_bf = -1;//�����bfΪ0
						break;
					}
					else
						assert(false);
				}
				else if (cur->_bf == 2 && cur->_Right->_bf == -1)//����˫��
				{
					RotateRL(cur);
					if (parent == insertnode->_Right)
						break;//�������,����ڵ��Ϊʧ�������ڵ�,������ڵ���ʧ�������������������ĸ�,����ƽ�������Ѿ������ҵ����б�����Ϊ0
					else if ((parent->_data.first) > (insertnode->_data.first))
					{
						insertnode->_Parent->_bf = 1;//�����bfΪ0
						break;
					}
					else if ((parent->_data.first) < (insertnode->_data.first))
					{
						cur->_bf=-1;//�����bfΪ0
						break;
					}
					else
						assert(false);
				}
			}
		}
		return true;
	}
    
    // AVL������֤
	bool IsAVLTree()
	{
		return _IsAVLTree(_Root);
	}
	void inorder()
	{
		return _inorder(_Root);
	}
private:
	void _inorder(Node* Root)
	{
		if (!Root)
			return;
		_inorder(Root->_Left);
		cout << Root->_data.first << ':' << Root->_data.second << endl;
		_inorder(Root->_Right);
	}
    // ����AVL���ĸ�����֤pRoot�Ƿ�Ϊ��Ч��AVL��
	bool _IsAVLTree(Node* Root)
	{
		int heightsub = _Height(Root->_Right) - _Height(Root->_Left);
		if (Root->_bf != heightsub)
		{
			cout << Root->_data.first << ':' << Root->_data.second << "ƽ���������ô���" << endl;
			cout << "ӦΪ:" << heightsub << '\t' << "ʵΪ:" << Root->_bf << endl;
			return false;
		}
		else
			cout  << Root->_data.first << ':' << Root->_data.second << "�߶�Ϊ:" << heightsub << "ƽ������Ϊ:" << Root->_bf << endl;
		return true;
	}
	size_t _Height(Node* Root)
	{
		if (!Root)
			return 0;
		int Lheight = _Height(Root->_Left) + 1;
		int Rheight = _Height(Root->_Right) + 1;
		return Lheight > Rheight ? Lheight : Rheight;
	}
    // �ҵ���
	void RotateR(Node* Parent)
	{	
		Node* Lchild = Parent->_Left;
		Node* Rchild = Parent->_Right;//����Ϊ��
		Node* LRgrand = Lchild->_Right;//����Ϊ��
		//���ӵǻ�
		if (Parent == _Root)
		{
			_Root = Lchild;
			Lchild->_Parent = nullptr;
		}
		else
		{
			if (Parent == Parent->_Parent->_Left)
				Parent->_Parent->_Left = Lchild;
			else
				Parent->_Parent->_Right = Lchild;
		}
		Lchild->_Parent = Parent->_Parent;
	//�����ӵ�������̸���λ����ͷ�ӵ�����,ͬʱ��ͷ��Ҫ�϶��ӵ�������
		Parent->_Parent = Lchild;
		Lchild->_Right = Parent;

		Parent->_Left = LRgrand;
		if (LRgrand)
			LRgrand->_Parent = Parent;
		//���µ������ƽ������
		Parent->_bf = 0;
		Lchild->_bf = 0;
	}
    // ����
	void RotateL(Node* Parent)
	{	
		Node* Lchild = Parent->_Left;//����Ϊ��
		Node* Rchild = Parent->_Right;
		Node* RLgrand = Rchild->_Left;//����Ϊ��
		//�ҳ��ӵǻ�
		if (Parent == _Root)
		{
			_Root = Rchild;
			Rchild->_Parent = nullptr;
		}
		else
		{
			if (Parent == Parent->_Parent->_Left)
				Parent->_Parent->_Left = Rchild;
			else
				Parent->_Parent->_Right = Rchild;
		}
		Rchild->_Parent = Parent->_Parent;
		//���ҳ��ӵ�������̸���λ����ͷ�ӵ�����,ͬʱ��ͷ��Ҫ�϶��ӵ�������
		Parent->_Parent = Rchild;
		Rchild->_Left = Parent;

		Parent->_Right = RLgrand;
		if (RLgrand)
			RLgrand->_Parent = Parent;
		//���µ������ƽ������
		Parent->_bf = 0;
		Rchild->_bf = 0;
	}
    // ����˫��
	void RotateRL(Node* Parent)
	{
		RotateR(Parent->_Right);
		RotateL(Parent);
	}
    // ����˫��
	void RotateLR(Node* Parent)
	{
		RotateL(Parent->_Left);
		RotateR(Parent);
	}
 
private:
	Node* _Root;
};