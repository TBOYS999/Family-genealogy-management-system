#pragma once
#include<iostream>
#include<cstring>
using namespace std;
template<class ElemType, class Weight>
struct People//双亲孩子表示法中，线性表中的数据域
{
	ElemType name;//名字
	Weight BornTime;//出生时间
	Weight DiedTime;//死亡时间
	ElemType FatherName;//父亲的名字
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


