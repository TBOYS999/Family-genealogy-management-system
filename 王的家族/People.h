#pragma once
#include<iostream>
#include<cstring>
using namespace std;
template<class ElemType, class Weight>
struct People//˫�׺��ӱ�ʾ���У����Ա��е�������
{
	ElemType name;//����
	Weight BornTime;//����ʱ��
	Weight DiedTime;//����ʱ��
	ElemType FatherName;//���׵�����
	People();
	People(ElemType n, Weight b, Weight d, ElemType f=nullptr);
	People &operator=(const People&b);
};
template<class ElemType, class Weight>
People<ElemType,Weight>& People<ElemType,Weight>::operator=(const People<ElemType,Weight>& b)
{
	this->name = b.name;
	this->BornTime = b.BornTime;
	this->DiedTime = b.DiedTime;
	this->FatherName = b.FatherName;
	return *this;
}template<class ElemType, class Weight>
People<ElemType,Weight>::People()
{
	name = "";
	BornTime = 0;
	DiedTime = 0;
	FatherName = "";
}template<class ElemType, class Weight>
People<ElemType,Weight>::People(ElemType n, Weight b, Weight d, ElemType f)
{
	name = n;
	BornTime = b;
	DiedTime = d;
	FatherName = f;
}


