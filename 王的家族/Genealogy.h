#pragma once
#include"DateNode.h"
#include"LinkQueue.h"
#include<vector>
#include<fstream>
#include"button.h"
#include<string>
using namespace std;
template<class ElemType,class Weight>
class Genealogy
{protected:
	DateNode<ElemType,Weight>* num;
	int MaxSize;
	int AcSize;
	vector<int>Count;//记录每一代的个数
public:
	Genealogy();
	Genealogy(DateNode<ElemType,Weight> *n, int A, int maxsize = 1000);
	void Initialize();//完成树的双亲孩子表示法结构的初始化
	void Display(void(*visited)(const People<ElemType,Weight>&));//族谱成员名字的展示
	vector<int>GetCount();//获得每一代的个数的数组
	DateNode<ElemType,Weight>* GetNum();//获取数据成员Num数组
	int GetAcSize();//获取数据成员AcSize
	People<ElemType, Weight>GetData(int j);//根据下标获取族谱成员的信息
	vector<int> GenerationFind(int g);//根据输入的代数获取该代成员的下标
	vector<int>ChildFind(ElemType Name);//根据传入的名字获取他的孩子的下标
	bool FatherFind(ElemType Name, int& j);//根据传入的名字获取他父亲的下标j
	bool InsertDataNode(ElemType Name, Weight born, Weight Died, ElemType Father);//插入一个数据成员
	bool NameFind(ElemType Name,int &j);//根据名字，查找该成员的下标j
	bool ChangeName(ElemType PreName, ElemType Name);//改名字
	bool ChangeBornTime(ElemType Name, Weight AfBornTime);//改出生时间
	bool ChangeDeidTime(ElemType Name, Weight AfDiedTime);//改死亡时间
	bool ChangeFather(ElemType Name, ElemType AfFatherName);//改父亲名字
	bool DeleteData(ElemType Name);//根据名字删除成员
	vector<int>BroFind(ElemType Name);//根据名字寻找他的兄弟，并将其兄弟的下标位置返回
	bool Save();//保存当前数据到txt文件中
};
template<class ElemType,class Weight>
bool Genealogy<ElemType, Weight>::Save()
{
	ofstream outfile("date.txt", ios::app);//创建文件date.txt
	if (outfile.good())
	{
		for (int i = 0; i < AcSize; i++)
		{
			outfile << num[i].date.name << " " << num[i].date.BornTime << " " << num[i].date.DiedTime << " " << num[i].date.FatherName << endl;
		}//将数组中成员的信息写入文件中
		outfile.close();
		return true;
	}
	return false;
}
template<class ElemType,class Weight>
vector<int>Genealogy<ElemType, Weight>::ChildFind(ElemType Name)
{
	int i = -1;
	vector<int>Child;
	NameFind(Name, i);//根据名字查找下标
	if (i < AcSize)//如果存在
	{
		Node* p;
		p = num[i].first;
		while (p != nullptr)
		{
			Child.push_back(p->No);
			p = p->next;//将其所有的孩子的下标压入容器中
		}
	}
	return Child;//返回容器

}
template<class ElemType,class Weight>
vector<int>Genealogy<ElemType, Weight>::BroFind(ElemType Name)//将查询名字的兄弟的下标存入容器中
{
	int j = -1,i=-1;
	vector<int>Bro;
	NameFind(Name, i);//根据名字查找下标
	if (i < AcSize)//如果存在
	{
		if (FatherFind(Name, j))//根据名字查找到其父亲的下标
		{
			Node* p;
			p = num[j].first;
			while (p != nullptr)
			{
				if (p->No != i)
				{
					Bro.push_back(p->No);//将其父亲除他之外的孩子，即他的兄弟的下标都压入容器中
				}
				p = p->next;
			}
		}
	}return Bro;//返回容器
	
}
template<class ElemType,class Weight>
vector<int> Genealogy<ElemType, Weight>::GenerationFind(int g)//返回第g代的成员下标
{
	vector<int>gen;
	LinkQueue<int>link;//创建一个队列
	link.EnQueue(0);
	int count = 1;
	int count2 = 0;//count,和count2相互配合来判断当前代是否已经遍历完成
	if (g == 0&&AcSize!=0)
	{
		gen.push_back(0);
	}
	int count3 = 1;
	while (!link.IsEmpty())//利用BFS广度优先算法的思想
	{
		int i;
		link.DeQueue(i);
		Node* p = num[i].first;
		while (p != nullptr)
		{
			if (count3 == g)//当记录的代数和传入的g相等时，将这一代元素下标压入gen中
			{
				gen.push_back(p->No);
		}
			link.EnQueue(p->No);
			p = p->next;
			count2++;
		}
		count--;
		if (count == 0)
		{
			count3++;//记录第几代
			count = count2;
			count2 = 0;
		}
	}
	return gen;
}
template<class ElemType,class Weight>
bool Genealogy<ElemType, Weight>::DeleteData(ElemType Name)//节点删除模块
{
	int i = -1, j = -1;//分别记录删除节点的下标和删除节点父亲的下标
	if (NameFind(Name, i))//找到当前数据成员的下标
	{
				Node* p2;
				p2 = num[i].first;
				while (p2 != nullptr)//如果有孩子，利用递归先将其每一个孩子和其后代删除
				{
					DeleteData(num[p2->No].date.name);
					p2 = p2->next;
					
				}num[i].first = nullptr;
				NameFind(Name, i);//在孩子节点的删除过程中，当前元素节点的下标位置可能会因为
				//删除而导致的下标位置的移动而移动，需要重新获取下标
					if (p2 == nullptr)//当前成员已经没有了孩子，删除当前成员
					{
						if (NameFind(num[i].date.FatherName, j))//删除父亲与孩子之间的指针
						{
							if (j == 4)
							{
								int w = 1;
							}
							Node* p, * pre;
							p = pre = num[j].first;
							while (p->No != i && p != nullptr)
							{
								pre = p;
								p = p->next;
							}
							if (p == num[j].first)
							{
								num[j].first = num[j].first->next;
							}
							else
							{
								pre->next = p->next;
								delete p;
							}

						}
						if (i + 1 == AcSize)//如果删除孩子是最后一个，直接将当前容量减一来实现删除
						{
							AcSize--;
						}
						else//如果不是，将最后一个节点移动到当前删除节点处，将容量减一
						{
							num[i].date = num[AcSize - 1].date;
							num[i].first = num[AcSize - 1].first;
							int k = -1;
							if (NameFind(num[AcSize - 1].date.FatherName, k))
							{
								Node* p;
								p = num[k].first;
								while (p->No != AcSize - 1 && p != nullptr)
								{
									p = p->next;
								}
								p->No = i;
							}
							AcSize--;
						}
					}
				
			
			return true;
	}
	return false;
}
template<class ElemType,class Weight>
People<ElemType, Weight> Genealogy<ElemType, Weight>::GetData(int j)
{
	People<ElemType, Weight>p;
	if (j < AcSize)//如果存在的话
	{
		p = num[j].date;
	}
	return p;
}
template<class ElemType,class Weight>
bool Genealogy<ElemType, Weight>::ChangeFather(ElemType Name, ElemType AfFatherName)
{

	int j = -1;
	if (NameFind(Name, j))
	{
		num[j].date.FatherName = AfFatherName;
		return true;
	}
	return false;
}
template<class ElemType,class Weight>
bool Genealogy<ElemType, Weight>::ChangeDeidTime(ElemType Name, Weight AfDiedTime)
{
	
	int j = -1;
	if (AfDiedTime < num[j].date.BornTime)
	{
		return false;
	}
	if (NameFind(Name, j))
	{
		num[j].date.DiedTime = AfDiedTime;
		return true;
	}
	return false;
}
template<class ElemType,class Weight>
bool Genealogy<ElemType, Weight>::ChangeBornTime(ElemType Name, Weight AfBornTime)
{
	int j = -1,i=-1;
	if (AfBornTime > num[j].date.DiedTime)
	{
		return false;
	}
	if (NameFind(Name, j))
	{
		num[j].date.BornTime = AfBornTime;
		if (FatherFind(Name, i))//修改长幼，由于修改了出生时间，可能会导致长幼顺序发生变化，
			//从而需要重新改变长幼顺序
		{
			Node* P;
			Node* p = num[i].first;
			Node* pre = num[i].first;
			while (p->No != j)
			{
				pre = p;
				p = p->next;
			}
			if (p == pre)
			{
				num[i].first = num[i].first->next;
			}
			else
			{
				pre->next = p->next;
			}delete p;//先删除在其父亲那指向该元素的节点
			p = num[i].first;
			pre = num[i].first;
			while (p != NULL)//新建一个节点，根据出生时间的大小，重新对节点进行插入
			{
				if (num[p->No].date.BornTime <= num[j].date.BornTime)
				{
					pre = p;
					p = p->next;

				}
				else
				{
					break;
				}
			}
			if (pre == p)
			{
				P = new Node();
				P->No = j;
				P->next = num[i].first;
				num[i].first = P;
			}
			else
			{
				P = new Node();
				P->No = j;
				P->next = pre->next;
				pre->next = P;
			}
		}
		return true;
	}
	return false;

}
template<class ElemType,class Weight>
bool Genealogy<ElemType, Weight>::ChangeName(ElemType PreName, ElemType Name)
{
	int j = -1;
	if (NameFind(PreName, j))//判断能不能找到该人
	{
		num[j].date.name = Name;
		return true;
	}
	return false;
}
template<class ElemType,class Weight>
bool Genealogy<ElemType, Weight>::FatherFind(ElemType Name, int& j)
{
	int i;
	if (NameFind(Name, i))
	{
		if (NameFind(num[i].date.FatherName, j))
		{
			return true;
		}
	}return false;
}
template<class ElemType,class Weight>
bool Genealogy<ElemType, Weight>::NameFind(ElemType Name,int &j)
{
	for (int i = 0; i < AcSize; i++)
	{
		if (num[i].date.name == Name)
		{
			j = i;
			return true;
		}
	}
	return false;
}
template<class ElemType,class Weight>
bool Genealogy<ElemType, Weight>::InsertDataNode(ElemType Name, Weight born, Weight Died, ElemType Father)
{
	if (AcSize >= MaxSize)//元素已满
	{
		return false;
	}
	int j = -1;
	if (born > Died)
	{
		return false;
	}
	if (NameFind(Name, j))//插入的成员是否已经存在
	{
		return false;
	}
	else
	{
		num[AcSize].date.name = Name;
		num[AcSize].date.BornTime = born;
		num[AcSize].date.DiedTime = Died;
		num[AcSize].date.FatherName = Father;
		AcSize++;//在数据数组中为插入元素建立，当前元素数目+1
		int d = -1;
		if (NameFind(Father, d))//找到插入元素的父亲，建立一个父亲孩子之间关系的节点
			//根据他的出生时间，按照长幼将该节点插入
		{
			Node* P;
			Node* p = num[d].first;
			Node* pre = num[d].first;
			while (p != NULL)
			{
				if (num[p->No].date.BornTime <= num[AcSize-1].date.BornTime)
				{
					pre = p;
					p = p->next;
					
				}
				else
				{
					break;
				}
			}
			if (pre == p)
			{
				P = new Node();
				P->No = AcSize-1;
				P->next = num[d].first;
				num[d].first = P;
			}
			else
			{
				P = new Node();
				P->No = AcSize-1;
				P->next = pre->next;
				pre->next = P;
			}
			return true;
		}
		return false;
	}
}
template<class ElemType, class Weight>
int Genealogy<ElemType, Weight>::GetAcSize()
{
	return this->AcSize;
}
template<class ElemType, class Weight>
DateNode<ElemType, Weight>* Genealogy<ElemType, Weight>::GetNum()
{
	return this->num;
}
template<class ElemType, class Weight>
vector<int>Genealogy<ElemType, Weight>::GetCount()
{
	return Count;
}
template<class ElemType, class Weight>
void Genealogy<ElemType, Weight>::Display(void(*visited)(const People<ElemType, Weight>&))
{
	
	LinkQueue<int>link;//利用BFS广度优先搜索的方法，将成员按代输出
	link.EnQueue(0);
	int count = 1;
	int count2 = 0;
	while (!link.IsEmpty())
	{
		int i;
		link.DeQueue(i);
		Node* p = num[i].first;
		while (p != nullptr)
		{
			link.EnQueue(p->No);
			p = p->next;
			count2++;
		}
		count--;
		(*visited)(num[i].date);
		if (count == 0)
		{
			Count.push_back(count2);
			count = count2;
			count2 = 0;
			cout << endl;
		}
	}
}
template<class ElemType, class Weight>
Genealogy<ElemType, Weight>::Genealogy()
{
	num = nullptr;
	MaxSize = 0;
	AcSize = 0;
}
template<class ElemType, class Weight>
Genealogy<ElemType, Weight>::Genealogy(DateNode<ElemType, Weight>* n, int A, int maxsize)
{
	AcSize = A;
	MaxSize = maxsize;
	num = new DateNode<ElemType, Weight>[MaxSize];
	for (int i = 0; i < A; i++)
	{
		num[i].date = n[i].date;
		num[i].first = nullptr;
	}
	Count.push_back(1);

	Initialize();
}
template<class ElemType, class Weight>
void Genealogy<ElemType, Weight>::Initialize()
{
	int count = 1;
	int j;
	for (int i = 0; i < AcSize; i++)//对每一位父亲初始化他的孩子节点
	{
		for (j = AcSize-1; j>i; j--)
		{
			if (num[j].date.FatherName == num[i].date.name)//寻找当前父亲的孩子节点
			{
				Node* p = num[i].first;
				num[i].first = new Node(j, p);
			}
			//else
			//{
			//	count = j;//因为txt文件中所有的孩子都是在排在一起的，如果当前孩子不是当前父亲的孩子节点，
			//	//则当前孩子是下一个父亲的孩子，
			//	//记录当前孩子的位置，下一个父亲从该位置开始查找
			//	break;
			//}
		}
		//if (j == AcSize)//说明表中所有的数据都已经遍历完，表的初始化完成
		//{
		//	break;
		//}

	}
}



