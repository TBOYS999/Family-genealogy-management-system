#pragma once
struct Node//双亲孩子表示法中的代表孩子的节点
{
	int No;//孩子在线性表中的下标
	Node* next;
	Node();
	Node(int n, Node* N=nullptr);
};


