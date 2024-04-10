#include "Node.h"
Node::Node()
{
	No = 0;
	next = nullptr;
}
Node::Node(int n, Node* N)
{
	No = n;
	next = N;
}