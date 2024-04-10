#pragma once
#include"People.h"
#include"Node.h"
template<class ElemType,class Weight>
struct DateNode
{
	People<ElemType,Weight> date;
	Node* first;
	DateNode();
	DateNode(ElemType name, Weight b, Weight d, ElemType f);
};
template<class ElemType, class Weight>
DateNode<ElemType, Weight>::DateNode()
{
	first = nullptr;
	date.name = "";
	date.DiedTime = 0;
	date.BornTime = 0;
	date.FatherName = "";
}template<class ElemType, class Weight>
DateNode<ElemType, Weight>::DateNode(ElemType name, Weight b, Weight d, ElemType f) :date(name, b, d, f)
{
	first = nullptr;
}
