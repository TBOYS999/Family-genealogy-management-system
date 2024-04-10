#pragma once
#include<iostream>
using namespace std;
template<class ElemType>
struct Nodeone
{
	ElemType date;
	Nodeone<ElemType>* next;
	Nodeone();
	Nodeone(const Nodeone<ElemType>& a);
	Nodeone(const ElemType &a);
	Nodeone<ElemType>& operator=(const Nodeone<ElemType>& a);
};
template<class ElemType>
Nodeone<ElemType>::Nodeone()
{
	next = NULL;
}template<class ElemType>
Nodeone<ElemType>::Nodeone(const Nodeone<ElemType>& a)
{
	next = NULL;
	this->date = a.date;
}
template<class ElemType>
Nodeone<ElemType>::Nodeone(const ElemType &a)
{
	next = NULL;
	this->date = a;
}
template<class ElemType>
Nodeone<ElemType>& Nodeone<ElemType>::operator=(const Nodeone<ElemType>& a)
{
	this->date = a.date;
	this->next = a.next;
	return *this;
}

