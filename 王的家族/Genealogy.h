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
	vector<int>Count;//��¼ÿһ���ĸ���
public:
	Genealogy();
	Genealogy(DateNode<ElemType,Weight> *n, int A, int maxsize = 1000);
	void Initialize();//�������˫�׺��ӱ�ʾ���ṹ�ĳ�ʼ��
	void Display(void(*visited)(const People<ElemType,Weight>&));//���׳�Ա���ֵ�չʾ
	vector<int>GetCount();//���ÿһ���ĸ���������
	DateNode<ElemType,Weight>* GetNum();//��ȡ���ݳ�ԱNum����
	int GetAcSize();//��ȡ���ݳ�ԱAcSize
	People<ElemType, Weight>GetData(int j);//�����±��ȡ���׳�Ա����Ϣ
	vector<int> GenerationFind(int g);//��������Ĵ�����ȡ�ô���Ա���±�
	vector<int>ChildFind(ElemType Name);//���ݴ�������ֻ�ȡ���ĺ��ӵ��±�
	bool FatherFind(ElemType Name, int& j);//���ݴ�������ֻ�ȡ�����׵��±�j
	bool InsertDataNode(ElemType Name, Weight born, Weight Died, ElemType Father);//����һ�����ݳ�Ա
	bool NameFind(ElemType Name,int &j);//�������֣����Ҹó�Ա���±�j
	bool ChangeName(ElemType PreName, ElemType Name);//������
	bool ChangeBornTime(ElemType Name, Weight AfBornTime);//�ĳ���ʱ��
	bool ChangeDeidTime(ElemType Name, Weight AfDiedTime);//������ʱ��
	bool ChangeFather(ElemType Name, ElemType AfFatherName);//�ĸ�������
	bool DeleteData(ElemType Name);//��������ɾ����Ա
	vector<int>BroFind(ElemType Name);//��������Ѱ�������ֵܣ��������ֵܵ��±�λ�÷���
	bool Save();//���浱ǰ���ݵ�txt�ļ���
};
template<class ElemType,class Weight>
bool Genealogy<ElemType, Weight>::Save()
{
	ofstream outfile("date.txt", ios::app);//�����ļ�date.txt
	if (outfile.good())
	{
		for (int i = 0; i < AcSize; i++)
		{
			outfile << num[i].date.name << " " << num[i].date.BornTime << " " << num[i].date.DiedTime << " " << num[i].date.FatherName << endl;
		}//�������г�Ա����Ϣд���ļ���
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
	NameFind(Name, i);//�������ֲ����±�
	if (i < AcSize)//�������
	{
		Node* p;
		p = num[i].first;
		while (p != nullptr)
		{
			Child.push_back(p->No);
			p = p->next;//�������еĺ��ӵ��±�ѹ��������
		}
	}
	return Child;//��������

}
template<class ElemType,class Weight>
vector<int>Genealogy<ElemType, Weight>::BroFind(ElemType Name)//����ѯ���ֵ��ֵܵ��±����������
{
	int j = -1,i=-1;
	vector<int>Bro;
	NameFind(Name, i);//�������ֲ����±�
	if (i < AcSize)//�������
	{
		if (FatherFind(Name, j))//�������ֲ��ҵ��丸�׵��±�
		{
			Node* p;
			p = num[j].first;
			while (p != nullptr)
			{
				if (p->No != i)
				{
					Bro.push_back(p->No);//���丸�׳���֮��ĺ��ӣ��������ֵܵ��±궼ѹ��������
				}
				p = p->next;
			}
		}
	}return Bro;//��������
	
}
template<class ElemType,class Weight>
vector<int> Genealogy<ElemType, Weight>::GenerationFind(int g)//���ص�g���ĳ�Ա�±�
{
	vector<int>gen;
	LinkQueue<int>link;//����һ������
	link.EnQueue(0);
	int count = 1;
	int count2 = 0;//count,��count2�໥������жϵ�ǰ���Ƿ��Ѿ��������
	if (g == 0&&AcSize!=0)
	{
		gen.push_back(0);
	}
	int count3 = 1;
	while (!link.IsEmpty())//����BFS��������㷨��˼��
	{
		int i;
		link.DeQueue(i);
		Node* p = num[i].first;
		while (p != nullptr)
		{
			if (count3 == g)//����¼�Ĵ����ʹ����g���ʱ������һ��Ԫ���±�ѹ��gen��
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
			count3++;//��¼�ڼ���
			count = count2;
			count2 = 0;
		}
	}
	return gen;
}
template<class ElemType,class Weight>
bool Genealogy<ElemType, Weight>::DeleteData(ElemType Name)//�ڵ�ɾ��ģ��
{
	int i = -1, j = -1;//�ֱ��¼ɾ���ڵ���±��ɾ���ڵ㸸�׵��±�
	if (NameFind(Name, i))//�ҵ���ǰ���ݳ�Ա���±�
	{
				Node* p2;
				p2 = num[i].first;
				while (p2 != nullptr)//����к��ӣ����õݹ��Ƚ���ÿһ�����Ӻ�����ɾ��
				{
					DeleteData(num[p2->No].date.name);
					p2 = p2->next;
					
				}num[i].first = nullptr;
				NameFind(Name, i);//�ں��ӽڵ��ɾ�������У���ǰԪ�ؽڵ���±�λ�ÿ��ܻ���Ϊ
				//ɾ�������µ��±�λ�õ��ƶ����ƶ�����Ҫ���»�ȡ�±�
					if (p2 == nullptr)//��ǰ��Ա�Ѿ�û���˺��ӣ�ɾ����ǰ��Ա
					{
						if (NameFind(num[i].date.FatherName, j))//ɾ�������뺢��֮���ָ��
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
						if (i + 1 == AcSize)//���ɾ�����������һ����ֱ�ӽ���ǰ������һ��ʵ��ɾ��
						{
							AcSize--;
						}
						else//������ǣ������һ���ڵ��ƶ�����ǰɾ���ڵ㴦����������һ
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
	if (j < AcSize)//������ڵĻ�
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
		if (FatherFind(Name, i))//�޸ĳ��ף������޸��˳���ʱ�䣬���ܻᵼ�³���˳�����仯��
			//�Ӷ���Ҫ���¸ı䳤��˳��
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
			}delete p;//��ɾ�����丸����ָ���Ԫ�صĽڵ�
			p = num[i].first;
			pre = num[i].first;
			while (p != NULL)//�½�һ���ڵ㣬���ݳ���ʱ��Ĵ�С�����¶Խڵ���в���
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
	if (NameFind(PreName, j))//�ж��ܲ����ҵ�����
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
	if (AcSize >= MaxSize)//Ԫ������
	{
		return false;
	}
	int j = -1;
	if (born > Died)
	{
		return false;
	}
	if (NameFind(Name, j))//����ĳ�Ա�Ƿ��Ѿ�����
	{
		return false;
	}
	else
	{
		num[AcSize].date.name = Name;
		num[AcSize].date.BornTime = born;
		num[AcSize].date.DiedTime = Died;
		num[AcSize].date.FatherName = Father;
		AcSize++;//������������Ϊ����Ԫ�ؽ�������ǰԪ����Ŀ+1
		int d = -1;
		if (NameFind(Father, d))//�ҵ�����Ԫ�صĸ��ף�����һ�����׺���֮���ϵ�Ľڵ�
			//�������ĳ���ʱ�䣬���ճ��׽��ýڵ����
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
	
	LinkQueue<int>link;//����BFS������������ķ���������Ա�������
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
	for (int i = 0; i < AcSize; i++)//��ÿһλ���׳�ʼ�����ĺ��ӽڵ�
	{
		for (j = AcSize-1; j>i; j--)
		{
			if (num[j].date.FatherName == num[i].date.name)//Ѱ�ҵ�ǰ���׵ĺ��ӽڵ�
			{
				Node* p = num[i].first;
				num[i].first = new Node(j, p);
			}
			//else
			//{
			//	count = j;//��Ϊtxt�ļ������еĺ��Ӷ���������һ��ģ������ǰ���Ӳ��ǵ�ǰ���׵ĺ��ӽڵ㣬
			//	//��ǰ��������һ�����׵ĺ��ӣ�
			//	//��¼��ǰ���ӵ�λ�ã���һ�����״Ӹ�λ�ÿ�ʼ����
			//	break;
			//}
		}
		//if (j == AcSize)//˵���������е����ݶ��Ѿ������꣬��ĳ�ʼ�����
		//{
		//	break;
		//}

	}
}



