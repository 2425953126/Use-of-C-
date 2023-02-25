#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "AVLTree.hpp"
using namespace std;
int main()
{
	AVLTree<int, int> B;
	int example1[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < sizeof(example1) / sizeof(int); i++)
	{	
		B.Insert(make_pair( example1[i], 1));
		B.IsAVLTree();
	}
	B.inorder();
	AVLTree<int, int> A;
	int example2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14};
	for (int i = 0; i < sizeof(example2) / sizeof(int); i++)
	{
		A.Insert(make_pair(example2[i], 1));
		A.IsAVLTree();
	}
	A.inorder();
	return 0;
}