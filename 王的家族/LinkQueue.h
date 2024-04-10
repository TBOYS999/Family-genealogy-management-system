#pragma once
#include"Nodeone.h"
#include"Status.h"
template<class ElemType>
class LinkQueue
{protected:
	Nodeone<ElemType>* top;
	Nodeone<ElemType>* tail;
	int length;
public:
	LinkQueue();
	Status EnQueue(const ElemType a);
	Status DeQueue(ElemType& a);
	void Traverse(void(*visit)(const ElemType&));
	bool IsEmpty();
};
template<class ElemType>
LinkQueue<ElemType>::LinkQueue()
{
	top = tail = new Nodeone<ElemType>();
	length = 0;
}
template<class ElemType>
Status LinkQueue<ElemType>::EnQueue(const ElemType a)
{
	Nodeone<ElemType>* p;
	p = new Nodeone<ElemType>(a);
	if (p)
	{
		tail->next = p;
		length++;
		tail = tail->next;
		return SUCCESS;
	}
	else
	{
		return RANGE_ERROR;
	}
}
template<class ElemType>
Status LinkQueue<ElemType>::DeQueue(ElemType& a)
{
	if (IsEmpty())
	{
		return RANGE_ERROR;
	}
	else
	{
		a = (*(top->next)).date;
		top = top->next;
		length--;
		return SUCCESS;
	}
}template<class ElemType>
void LinkQueue<ElemType>::Traverse(void(*visit)(const ElemType&))
{
	Nodeone<ElemType>* temp = top->next;
	while (temp != NULL)
	{
		(*visit)((*temp).date);
		temp = temp->next;
	}
}
template<class ElemType>
bool LinkQueue<ElemType>::IsEmpty()
{
	if (length == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

