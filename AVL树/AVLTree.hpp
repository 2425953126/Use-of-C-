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
	short int _bf;   // 节点的平衡因子
};
 
// AVL: 二叉搜索树 + 平衡因子的限制
template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree()
		: _Root(nullptr)
	{}
 
    // 在AVL树中插入值为data的节点
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
		//验证平衡因子
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
			//检测
			if (cur->_bf == 0)
				break;
			else if (cur->_bf == 1 || cur->_bf == -1)
				continue;
			else
			{
				if (cur->_bf == -2 && cur->_Left->_bf == -1)//右单旋的情况
				{
					RotateR(cur);
					break;
				}
				else if (cur->_bf == 2 && cur->_Right->_bf == 1)//左单旋的情况
				{												//根据插入节点是失衡点的左子树的右子树的根、是失衡点的左子树的右子树的左孩子亦或右孩子，平衡因子的修正情况有所不同
					RotateL(cur);
					break;
				}
				else if (cur->_bf == -2 && cur->_Left->_bf == 1)//左右双旋
				{
					RotateLR(cur);
					if (parent == insertnode->_Left)
						break;//特殊情况,插入节点成为失衡树根节点,即插入节点是失衡点的左子树的右子树的根,各点平衡因子已经在左右单旋中被调整为0
					else if ((parent->_data.first) > (insertnode->_data.first))
					{
						cur->_bf = 1;//其余点bf为0
						break;
					}
					else if ((parent->_data.first) < (insertnode->_data.first))
					{
						parent->_Left->_bf = -1;//其余点bf为0
						break;
					}
					else
						assert(false);
				}
				else if (cur->_bf == 2 && cur->_Right->_bf == -1)//右左双旋
				{
					RotateRL(cur);
					if (parent == insertnode->_Right)
						break;//特殊情况,插入节点成为失衡树根节点,即插入节点是失衡点的左子树的右子树的根,各点平衡因子已经在左右单旋中被调整为0
					else if ((parent->_data.first) > (insertnode->_data.first))
					{
						insertnode->_Parent->_bf = 1;//其余点bf为0
						break;
					}
					else if ((parent->_data.first) < (insertnode->_data.first))
					{
						cur->_bf=-1;//其余点bf为0
						break;
					}
					else
						assert(false);
				}
			}
		}
		return true;
	}
    
    // AVL树的验证
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
    // 根据AVL树的概念验证pRoot是否为有效的AVL树
	bool _IsAVLTree(Node* Root)
	{
		int heightsub = _Height(Root->_Right) - _Height(Root->_Left);
		if (Root->_bf != heightsub)
		{
			cout << Root->_data.first << ':' << Root->_data.second << "平衡因子设置错误" << endl;
			cout << "应为:" << heightsub << '\t' << "实为:" << Root->_bf << endl;
			return false;
		}
		else
			cout  << Root->_data.first << ':' << Root->_data.second << "高度为:" << heightsub << "平衡因子为:" << Root->_bf << endl;
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
    // 右单旋
	void RotateR(Node* Parent)
	{	
		Node* Lchild = Parent->_Left;
		Node* Rchild = Parent->_Right;//可能为空
		Node* LRgrand = Lchild->_Right;//可能为空
		//左长子登基
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
	//将左长子的右翼过继给退位的老头子的左翼,同时老头子要认儿子当老子了
		Parent->_Parent = Lchild;
		Lchild->_Right = Parent;

		Parent->_Left = LRgrand;
		if (LRgrand)
			LRgrand->_Parent = Parent;
		//更新调整后的平衡因子
		Parent->_bf = 0;
		Lchild->_bf = 0;
	}
    // 左单旋
	void RotateL(Node* Parent)
	{	
		Node* Lchild = Parent->_Left;//可能为空
		Node* Rchild = Parent->_Right;
		Node* RLgrand = Rchild->_Left;//可能为空
		//右长子登基
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
		//将右长子的左翼过继给退位的老头子的右翼,同时老头子要认儿子当老子了
		Parent->_Parent = Rchild;
		Rchild->_Left = Parent;

		Parent->_Right = RLgrand;
		if (RLgrand)
			RLgrand->_Parent = Parent;
		//更新调整后的平衡因子
		Parent->_bf = 0;
		Rchild->_bf = 0;
	}
    // 右左双旋
	void RotateRL(Node* Parent)
	{
		RotateR(Parent->_Right);
		RotateL(Parent);
	}
    // 左右双旋
	void RotateLR(Node* Parent)
	{
		RotateL(Parent->_Left);
		RotateR(Parent);
	}
 
private:
	Node* _Root;
};