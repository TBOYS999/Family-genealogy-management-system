#include<iostream>
#include<fstream>
#include<vector>
#include<conio.h>//_getch()���������ͷ�ļ�
#include<string>
#include<graphics.h>
#include<time.h>
#include<iomanip>
#include<algorithm>
#include"button.h"
#include"Genealogy.h"
using namespace std;

void First()//�ʼ��ҳ��չʾ������ÿ��ģ��������ҳ����ɣ��ڶ���ҳ�水���˼����س�ʼҳ�棬
//���ǽ���ʼҳ���װΪһ������
{
	initgraph(1880, 830, SHOWCONSOLE);    // ������ͼ���ڣ���СΪ 1880*830����
	setbkcolor(WHITE);//���ñ�������ɫ
	setbkmode(TRANSPARENT);//���ñ���ģʽΪ͸�����������ʱ�����ƻ�����
	cleardevice();
	TCHAR s[50] = "��ʾ����";
	TCHAR s1[50] = "��ӳ�Ա";
	TCHAR s2[50] = "�޸ĳ�Ա";
	TCHAR s3[50] = "ɾ����Ա";
	TCHAR s4[50] = "��ѯ";
	TCHAR s5[50] = "����";
	TCHAR s6[50] = "�˳�";
	button b0(650, 160, 150, 50, RGB(170, 172, 184), s);
	button b1(650, 230, 150, 50, RGB(164, 168, 180), s1);
	button b2(650, 300, 150, 50, RGB(180, 179, 186), s2);
	button b3(650, 370, 150, 50, RGB(160, 162, 174), s3);
	button b4(650, 440, 150, 50, RGB(209, 198, 194), s4);
	button b5(650, 510, 150, 50, RGB(131, 129, 129), s5);
	button b6(650, 580, 150, 50, RGB(170, 161, 151), s6);//������ҳ�水ť
	IMAGE background;
	loadimage(&background, "Khan.jpg", 1880, 830, 1);//Ϊ��ǰ��������һ��ͼƬ
	putimage(0, 0, &background);
	settextcolor(RGB(247, 171, 0));
	settextstyle(100, 0, "STXINWEI");
	outtextxy(550, 50, "���ļ���");
	b0.drawbutton();
	b1.drawbutton();
	b2.drawbutton();
	b3.drawbutton();
	b4.drawbutton();
	b5.drawbutton();
	b6.drawbutton();//������ť
}template<class ElemType,class Weight>
void Visited(const People<ElemType,Weight>& a)
{
	cout << a.name << " ";
}
void Outtest(int x, int y, string a, int n)//n�����ֵĴ�С
{
	char* str;
	str = new char[a.size() + 1];
	strcpy(str, a.c_str());
	setfillcolor(BLACK);
	settextcolor(RGB(170, 172, 184));//����������ɫ
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "����");//����������ʽ
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = n;
	settextstyle(&f);//��������ĸ߶ȣ��������С�仯
	outtextxy(x, y, str);//��ʾstr�е���
}

void SetR(int j, int h, Genealogy<string, int> G, People<string, int>& p1)//�ڲ�ѯʱ��
//���ģ���õ���չʾ������ʾ���ݵ��������꣬����ȣ����ǽ����װΪ����
{
	p1 = G.GetData(j);
	char* str1;
	str1 = new char[p1.name.size() + 1];
	strcpy(str1, p1.name.c_str());
	button b01(150, h + 50, 150, 50, RGB(170, 172, 184), str1);
	b01.drawbutton();
	std::string b1 = std::to_string(p1.BornTime);
	std::string b2 = std::to_string(p1.DiedTime);
	char* str2;
	str2 = new char[b1.size() + 1];
	strcpy(str2, b1.c_str());
	button b02(320, h + 50, 150, 50, RGB(170, 172, 184), str2);
	b02.drawbutton();
	char* str3;
	str3 = new char[b2.size() + 1];
	strcpy(str3, b2.c_str());
	button b03(490, h + 50, 150, 50, RGB(170, 172, 184), str3);
	b03.drawbutton();
	char* str4;
	str4 = new char[p1.FatherName.size() + 1];
	strcpy(str4, p1.FatherName.c_str());
	button b04(660, h + 50, 150, 50, RGB(170, 172, 184), str4);
	b04.drawbutton();
}
template<class ElemType,class Weight>
void GenealogicGraph(Genealogy<ElemType,Weight>G, int x, int y, DateNode<ElemType,Weight>* num,int h,ElemType Name)//����������x��y�������������
//��ʼ���꣬num�����ݳ�Ա���飬h��ÿһ�����䵽�ĸ߶ȣ�Name��Ҫ���ĺ��ӵĸ���
{
	int j = -1;
	G.NameFind(Name, j);
	int count = 0;
	Node* p = num[j].first;
		while (p != nullptr)
		{
			p = p->next;
			count++;
		}//�ȼ��㺢�ӵĸ���
	if (count != 0)
	{
		h = h / count;//Ϊÿ�����ӷ���߶ȿռ�
		if (h < 30)
		{
			h = 30;
		}//��������
		p = num[j].first;//�ӵ�һ�����ӿ�ʼ
		People<string, int>p1;
		if (count >=3)
		{
			y -= 60;
		}
		int d = count;
		count = 0;
		while (p != nullptr)
		{
			p1 = G.GetData(p->No);
			Outtest(x, y + h * count, p1.name,20);//д����ǰ���ӵ�����
			int j = 0;
			if (d >= 3)
			{
				j = 60;
			}
			line(x - 90, y + 10+j, x, y + h * count+10);//�������뵱ǰ����֮������
			GenealogicGraph(G, x +150, y + h * count, num, h, p1.name);//���õݹ麯�����Ե�ǰ���ӽ��еݹ�
			p = p->next;
			count++;//��������ÿһ�����ӵ���ʼ�����꣬���⺢��֮�����ֵ��ص�
		}
	}
}
template<class ElemType,class Weight>
void GenealogicGraph(Genealogy<ElemType,Weight> G)
{
	DateNode<ElemType, Weight>* num;
	num = G.GetNum();
	People<string, int>p1;
	if (G.GetAcSize()!=0)//�жϻ���û��Ԫ��
	{
		p1 = G.GetData(0);
		Outtest(150, 60, p1.name, 20);//����ʼ��
		GenealogicGraph(G, 300, 60, num, 825, p1.name);//���õݹ黭���亢��
	}
}

int main()
{
	vector<DateNode<string,int>>num;
	string a, b;
	int c, d;
	ifstream file("Genghis Khan.txt");//��ȡ�ļ�
	if (!file)
	{
		cout << "δ�ҵ��ļ�" << endl;
	}
	else
	{
		int i = 1;
		while (!file.eof())//��ȡ�ļ��е����ݣ�ֱ���������ݱ�����
		{
			if (i == 1)//���ڵ�һ����Աû�и��ף������ȡ
			{
				file >> a >> c >> d;
				b = "";
				DateNode<string,int> D(a, c, d, b);
				num.push_back(D);//������������ѹ������
				i++;
			}
			else
			{

				file >> a >> c >> d >> b;
				DateNode<string, int> D(a, c, d, b);
				num.push_back(D);
			}
		}
		file.close();
	}

	Genealogy<string,int> G(&num[0],num.size());//��ʼ������ϵͳ
	G.Display(Visited<string,int>);
	vector<int>Count1;
	Count1 = G.GetCount();
	/*for (int i = 0; i < Count1.size()-1; i++)
	{
		cout << Count1[i] << endl;
	}*/
	First();
	while(true)
	{	ExMessage msg;//����һ����ȡ���ı���
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)//��ȡ�����Ϣ
			{
			case WM_LBUTTONDOWN://����������
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 160 && msg.y <= 160 + 50)//����һ��չʾ����ͼ
				{
					cleardevice();
					TCHAR s[50] = "����";
					button b0(0, 0 ,150, 50, RGB(170, 172, 184), s);
					b0.drawbutton();
					setfillcolor(BLACK);
					fillrectangle(150, 0, 1880, 830);
					GenealogicGraph(G);
					ExMessage m;
					while (true)
					{
						if (peekmessage(&m, EM_MOUSE))
						{
							if (m.message == WM_LBUTTONDOWN)
							{
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 0 && m.y <= 0 + 50)//�ص���ʼ����
								{
									First();
									break;
								}
							}
						}
					}

				}
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 230 && msg.y <= 230 + 50)//ģ�������ӳ�Ա����
				{
					cleardevice();
					TCHAR s[50] = "����";
					button b0(0, 0, 150, 50, RGB(170, 172, 184), s);
					b0.drawbutton();
					setfillcolor(BLACK);
					string a0;
					fillrectangle(150, 0, 1880, 830);
					a0 = "������Ҫ��ӳ�Ա�ĸ���";
					Outtest(150, 0, a0, 30);
					string a1;
					cin >> a1;
					Outtest(150, 50, a1, 30);
					int n = atoi(a1.c_str());//������¼��Ҫ��ӳ�Ա�Ĵ���

					int j = 1;
					while (n>0)
					{
						
						string a;
						a = "������Ҫ��ӳ�Ա�������������꣬�����꣬��Ա�ĸ���";
						Outtest(150, 50+j*50, a, 30);
						string b1, b2, b3, b4;
						cin >> b1;
						Outtest(150, 50 + (j + 1) * 50, b1, 30);
						cin >> b2;
						Outtest(350, 50 + (j + 1) * 50, b2, 30);
						cin >> b3;
						Outtest(450, 50 + (j + 1) * 50, b3, 30);
						cin >> b4;
						Outtest(550, 50 + (j + 1) * 50, b4, 30);
						if (G.InsertDataNode(b1, atoi(b2.c_str()), atoi(b3.c_str()), b4))
						{
							string c;
							c = "��ӳɹ�!";
							Outtest(150, 50 + (j + 2) * 50, c, 30);
						}
						else
						{
							string c;
							c = "���ʧ��!,�ó�Ա�Ѿ�����";
							Outtest(150, 50 + (j + 2) * 50, c, 30);
						}
						j += j + 3;
						n--;
					}
					ExMessage m;
					while (true)
					{
						if (peekmessage(&m, EM_MOUSE))
						{
							if (m.message == WM_LBUTTONDOWN)
							{
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 0 && m.y <= 0 + 50)
								{
									First();
									break;
								}
							}
						}
					}
				}
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 300 && msg.y <= 300 + 50)//ģ�������޸ĳ�Ա����
				{
					cleardevice();
					TCHAR s[50] = "����";
					button b0(0, 0, 150, 50, RGB(170, 172, 184), s);
					b0.drawbutton();
					setfillcolor(BLACK);
					string a0;
					fillrectangle(150, 0, 1880, 830);
					a0 = "������Ҫ�޸ĳ�Ա�ĸ���";
					Outtest(150, 0, a0, 30);
					string a1;
					cin >> a1;
					Outtest(150, 50, a1, 30);
					int n = atoi(a1.c_str());
					while (n > 0)
					{
						setfillcolor(BLACK);
						fillrectangle(150, 100, 1880, 830);
						string a2;
						a2 = "������Ҫ�޸ĵĳ�Ա����";
						Outtest(150, 100, a2, 30);
						string a3;
						cin >> a3;
						Outtest(150, 150, a3, 30);
						People<string, int> p1;
						int j = -1;
						if (G.NameFind(a3, j))
						{
							SetR(j, 200, G, p1);
							TCHAR s[50] = "��ɵ�ǰ�޸�";
							button b05(0, 300, 150, 50, RGB(170, 172, 184), s);
							b05.drawbutton();
							ExMessage m;
							while (true)
							{
								if (peekmessage(&m, EM_MOUSE))
								{
									if (m.message == WM_LBUTTONDOWN)
									{
										if (m.x >= 150 && m.x <= 150 + 150 && m.y >= 250 && m.y <= 250 + 50)//����1���޸�����
										{
											setfillcolor(BLACK);
											fillrectangle(150, 300, 1730, 780);
											string c1;
											c1 = "�������޸ĺ������";
											Outtest(150, 300, c1, 30);
											string c12;
											cin >> c12;
											Outtest(150, 350, c12, 30);
											if (G.ChangeName(p1.name, c12))
											{
												string c13;
												c13 = "�޸ĳɹ�!";
												Outtest(150, 400, c13, 30);
												p1.name = c12;
											}
											else
											{
												string c13;
												c13 = "�޸�ʧ�ܣ�δ�ҵ�����!";
												Outtest(150, 400, c13, 30);
											}
										}
										if (m.x >= 320 && m.x <= 320 + 150 && m.y >= 250 && m.y <= 250 + 50)//ģ������޸ĳ������
										{
											setfillcolor(BLACK);
											fillrectangle(150, 300, 1730, 780);
											string c1;
											c1 = "�������޸ĺ������";
											Outtest(150, 300, c1, 30);
											string c12;
											cin >> c12;
											Outtest(150, 350, c12, 30);
											if (G.ChangeBornTime(p1.name, atoi(c12.c_str())))
											{
												string c13;
												c13 = "�޸ĳɹ�!";
												Outtest(150, 400, c13, 30);
											}
											else
											{
												string c13;
												c13 = "�޸�ʧ�ܣ�δ�ҵ�����!";
												Outtest(150, 400, c13, 30);
											}
										}
										if (m.x >= 490 && m.x <= 490 + 150 && m.y >= 250 && m.y <= 250 + 50)//ģ�������޸�ȥ�����
										{
											setfillcolor(BLACK);
											fillrectangle(150, 300, 1730, 780);
											string c1;
											c1 = "�������޸ĺ������";
											Outtest(150, 300, c1, 30);
											string c12;
											cin >> c12;
											Outtest(150, 350, c12, 30);
											if (G.ChangeDeidTime(p1.name, atoi(c12.c_str())))
											{
												string c13;
												c13 = "�޸ĳɹ�!";
												Outtest(150, 400, c13, 30);
											}
											else
											{
												string c13;
												c13 = "�޸�ʧ�ܣ�δ�ҵ�����!";
												Outtest(150, 400, c13, 30);
											}
										}
										if (m.x >= 660 && m.x <= 660 + 150 && m.y >= 250 && m.y <= 250 + 50)//ģ���ģ��޸ĸ�������
										{
											setfillcolor(BLACK);
											fillrectangle(150, 300, 1730, 780);
											string c1;
											c1 = "�������޸ĺ�ĸ�������";
											Outtest(150, 300, c1, 30);
											string c12;
											cin >> c12;
											Outtest(150, 350, c12, 30);
											if (G.ChangeFather(p1.name, c12))
											{
												string c13;
												c13 = "�޸ĳɹ�!";
												Outtest(150, 400, c13, 30);
											}
											else
											{
												string c13;
												c13 = "�޸�ʧ�ܣ�δ�ҵ�����!";
												Outtest(150, 400, c13, 30);
											}
										}
										if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 300 && m.y <= 300 + 50)//�޸ĺ��չʾ
										{
											setfillcolor(BLACK);
											fillrectangle(150, 300, 1730, 780);
											string c13;
											c13 = "�޸ĺ�Ϊ��";
											Outtest(150, 300, c13, 30);
											p1 = G.GetData(j);
											char* str1;
											str1 = new char[p1.name.size() + 1];
											strcpy(str1, p1.name.c_str());
											button b01(150, 350, 150, 50, RGB(170, 172, 184), str1);
											b01.drawbutton();
											std::string b1 = std::to_string(p1.BornTime);
											std::string b2 = std::to_string(p1.DiedTime);
											char* str2;
											str2 = new char[b1.size() + 1];
											strcpy(str2, b1.c_str());
											button b02(320, 350, 150, 50, RGB(170, 172, 184), str2);
											b02.drawbutton();
											char* str3;
											str3 = new char[b2.size() + 1];
											strcpy(str3, b2.c_str());
											button b03(490, 350, 150, 50, RGB(170, 172, 184), str3);
											b03.drawbutton();
											char* str4;
											str4 = new char[p1.FatherName.size() + 1];
											strcpy(str4, p1.FatherName.c_str());
											button b04(660, 350, 150, 50, RGB(170, 172, 184), str4);
											b04.drawbutton();
											string c1;
											c1 = "��1���չʾ�������������";
											Outtest(150, 400, c1, 30);
											int n;
											cin >> n;
											if (n == 1)
												break;
										}
									}
								}
							}
						}
						else
						{
						string a55 = "�޸�ʧ�ܣ�δ�ҵ�����";
						Outtest(150, 300, a55, 30);
						string c1;
						c1 = "��1���������������˳���";
						Outtest(150, 400, c1, 30);
						int n;
						cin >> n;
						if (n != 1)
							break;

						}
						n--;
					}
							setfillcolor(BLACK);
							fillrectangle(150, 0, 1880, 830);
							string a22;
							a22 = "ȫ���޸�����ɣ�";
							Outtest(350, 350, a22, 80);
						
					ExMessage m;
					while (true)
					{
						if (peekmessage(&m, EM_MOUSE))
						{
							if (m.message == WM_LBUTTONDOWN)
							{
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 0 && m.y <= 0 + 50)
								{
									First();
									break;
								}
							}
						}
					}
				}
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 370 && msg.y <= 370 + 50)//ģ������ɾ����Ա
				{
					cleardevice();
					TCHAR s[50] = "����";
					button b0(0, 0, 150, 50, RGB(170, 172, 184), s);
					b0.drawbutton();
					setfillcolor(BLACK);
					string a0;
					fillrectangle(150, 0, 1880, 830);
						a0 = "������Ҫɾ����Ա�ĸ���";
						Outtest(150, 0, a0, 30);
						string a1;
						cin >> a1;
						Outtest(150, 50, a1, 30);
						int n = atoi(a1.c_str());
						while (n > 0)
						{
							setfillcolor(BLACK);
							fillrectangle(150, 100, 1880, 830);
								string a2;
							a2 = "������Ҫɾ���ĳ�Ա����";
							Outtest(150, 100, a2, 30);
							string a3;
							cin >> a3;
							Outtest(150, 150, a3, 30);
							People<string, int> p1;
							int j = -1;
							if (G.NameFind(a3, j))
							{
								string k;
								k = "����";
								Outtest(180, 200, k, 30);
								k = "����";
								Outtest(360, 200, k, 30);
								k = "����";
								Outtest(530, 200, k, 30);
								k = "����";
								Outtest(670, 200, k, 30);
								SetR(j, 200, G, p1);
								TCHAR s[50] = "ȷ��ɾ��";
								button b05(0, 300, 150, 50, RGB(170, 172, 184), s);
								b05.drawbutton();
								ExMessage m;
								while (true)
								{
									if (peekmessage(&m, EM_MOUSE))
									{
										if (m.message == WM_LBUTTONDOWN)
										{
											if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 300 && m.y <= 300 + 50)
											{
												if (G.DeleteData(p1.name))
												{
													string a44 = "ɾ���ɹ���";
													Outtest(150, 300, a44, 30);
													string c1;
													c1 = "��1���չʾ�������������";
													Outtest(150, 400, c1, 30);
													int n;
													cin >> n;
													if (n == 1)
														break;
												}
												else
												{
													string a55 = "ɾ��ʧ�ܣ�δ�ҵ�����";
													Outtest(150, 300, a55, 30);
													string c1;
													c1 = "��1���չʾ�������������";
													Outtest(150, 400, c1, 30);
													int n;
													cin >> n;
													if (n == 1)
														break;
												}
											}

										}
									}
								}

							}
							else
							{
								string a55 = "ɾ��ʧ�ܣ�δ�ҵ�����";
								Outtest(150, 300, a55, 30);
								string c1;
								c1 = "��1���������������˳���";
								Outtest(150, 400, c1, 30);
								int n;
								cin >> n;
								if (n != 1)
									break;

							}
							n--;
						}
						setfillcolor(BLACK);
						fillrectangle(150, 0, 1880, 830);
						string a22;
						a22 = "ȫ��ɾ������ɣ�";
						Outtest(500, 350, a22, 80);


					ExMessage m;
					while (true)
					{
						if (peekmessage(&m, EM_MOUSE))
						{
							if (m.message == WM_LBUTTONDOWN)
							{
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 0 && m.y <= 0 + 50)
								{
									First();
									break;
								}
							}
						}
					}
				}
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 440 && msg.y <= 440 + 50)//ģ���壬��ѯ��Ա
				{
					cleardevice();
					TCHAR s[50] = "����";
					setfillcolor(BLACK);
					fillrectangle(150, 0, 1880, 830);
					button b0(0, 0, 150, 50, RGB(170, 172, 184), s);
					b0.drawbutton();
					TCHAR s1[50] = "���ֲ�ѯ";
					button b01(0, 70, 150, 50, RGB(170, 172, 184), s1);
					b01.drawbutton();
					TCHAR s2[50] = "������ѯ";
					button b02(0, 140, 150, 50, RGB(170, 172, 184), s2);
					b02.drawbutton();
					TCHAR s3[50] = "��ѯ�ֵ�";
					button b03(0, 210, 150, 50, RGB(170, 172, 184), s3);
					b03.drawbutton();
					TCHAR s4[50] = "��ѯ����";
					button b04(0, 280, 150, 50, RGB(170, 172, 184), s4);
					b04.drawbutton();
					TCHAR s5[50] = "��ѯ����";
					button b05(0, 350, 150, 50, RGB(170, 172, 184), s5);
					b05.drawbutton();
					ExMessage m;
					while (true)
					{
						if (peekmessage(&m, EM_MOUSE))
						{
							if (m.message == WM_LBUTTONDOWN)
							{
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 0 && m.y <= 0 + 50)
								{
									First();
									break;
								}
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 70 && m.y <= 70 + 50)//���ֲ�ѯ
								{
									setfillcolor(BLACK);
									fillrectangle(150, 0, 1880, 830);
									string c1;
									c1 = "������Ҫ��ѯ������";
									Outtest(150, 0, c1, 30);
									string c12;
									cin >> c12;
									Outtest(150, 50, c12, 30);
									People<string, int> p1;
									int j = -1;
									if (G.NameFind(c12, j))
									{
										string k;
										k = "����";
										Outtest(180, 200, k, 30);
										k = "����";
										Outtest(360, 200, k, 30);
										k = "����";
										Outtest(530, 200, k, 30);
										k = "����";
										Outtest(670, 200, k, 30);
										SetR(j, 200, G, p1);
									}
									else
									{
										string d11 = "���޴���!";
										Outtest(150, 100, d11, 30);
									}
								}
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 140 && m.y <= 140 + 50)//������ѯ
								{
									setfillcolor(BLACK);
									fillrectangle(150, 0, 1880, 830);
									string c1;
									c1 = "������Ҫ��ѯ�Ĵ���";
									Outtest(150, 0, c1, 30);
									string c12;
									cin >> c12;
									Outtest(150, 50, c12, 30);
									People<string, int> p1;
									int j = -1;
									vector<int>n;
									n=G.GenerationFind(atoi(c12.c_str())-1);
									int i = 0;
									while (i<n.size())
									{
										string k;
										k = "����";
										Outtest(180, 100, k, 30);
										k = "����";
										Outtest(360, 100, k, 30);
										k = "����";
										Outtest(530, 100, k, 30);
										k = "����";
										Outtest(670, 100, k, 30);
										SetR(n[i], 100+i*50, G, p1);
										i++;
									}
									if (n.size() == 0)
									{
										string c1;
										c1 = "������û�иô��ļ�¼��";
										Outtest(150, 100, c1, 30);
									}
								}
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 210 && m.y <= 210 + 50)//��ѯ����
								{
									setfillcolor(BLACK);
									fillrectangle(150, 0, 1880, 830);
									string c1;
									c1 = "������Ҫ��ѯ������";
									Outtest(150, 0, c1, 30);
									string c12;
									cin >> c12;
									Outtest(150, 50, c12, 30);
									People<string, int> p1;
									int j = -1;
									vector<int>n;
									n = G.BroFind(c12);
									int i = 0;
									while (i < n.size())
									{
										string k;
										k = "����";
										Outtest(180, 100, k, 30);
										k = "����";
										Outtest(360, 100, k, 30);
										k = "����";
										Outtest(530, 100, k, 30);
										k = "����";
										Outtest(670, 100, k, 30);
										SetR(n[i], 100 + i * 50, G, p1);
										i++;
									}int w = -1;
									if (n.size() == 0)
									{
										if (!G.NameFind(c12, w))
										{
											string c1;
											c1 = "������û�и��˵ļ��أ�";
											Outtest(150, 100, c1, 30);
										}
									
										else
										{
											string c1;
											c1 = "������û�и����ֵܵļ��أ�";
											Outtest(150, 100, c1, 30);
										}
									}
								}
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 280 && m.y <= 280 + 50)//��ѯ�ֵ�
								{
									setfillcolor(BLACK);
									fillrectangle(150, 0, 1880, 830);
									string c1;
									c1 = "������Ҫ��ѯ������";
									Outtest(150, 0, c1, 30);
									string c12;
									cin >> c12;
									Outtest(150, 50, c12, 30);
									People<string, int> p1;
									int j = -1;
									if (G.FatherFind(c12,j))
									{
										string f = c12 + "�ĸ���Ϊ:";
										Outtest(180, 100, f, 30);
										string k;
										k = "����";
										Outtest(180, 200, k, 30);
										k = "����";
										Outtest(360, 200, k, 30);
										k = "����";
										Outtest(530, 200, k, 30);
										k = "����";
										Outtest(670, 200, k, 30);
										SetR(j, 200, G, p1);
									}
									else if (G.NameFind(c12, j))
									{
										string d11 = "������δ�����丸�ף�";
										Outtest(150, 100, d11, 30);
									}
									else
									{
										string d11 = "���޴���!";
										Outtest(150, 100, d11, 30);
									}
								}
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 350 && m.y <= 350 + 50)//��ѯ����
								{
									setfillcolor(BLACK);
									fillrectangle(150, 0, 1880, 830);
									string c1;
									c1 = "������Ҫ��ѯ������";
									Outtest(150, 0, c1, 30);
									string c12;
									cin >> c12;
									Outtest(150, 50, c12, 30);
									People<string, int> p1;
									int j = -1;
									vector<int>n;
									n = G.ChildFind(c12);
									int i = 0;
									while (i < n.size())
									{
										string k;
										k = "����";
										Outtest(180, 100, k, 30);
										k = "����";
										Outtest(360, 100, k, 30);
										k = "����";
										Outtest(530, 100, k, 30);
										k = "����";
										Outtest(670, 100, k, 30);
										SetR(n[i], 100 + i * 50, G, p1);
										i++;
									}int w = -1;
									if (n.size() == 0)
									{
										if (!G.NameFind(c12, w))
										{
											string c1;
											c1 = "������û�и��˵ļ��أ�";
											Outtest(150, 100, c1, 30);
										}

										else
										{
											string c1;
											c1 = "������û�и��˺��ӵļ��أ�";
											Outtest(150, 100, c1, 30);
										}
									}
								}
							}
						}
					}
				}
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 510 && msg.y <= 510 + 50)//����ģ��
				{
					cleardevice();
					setfillcolor(BLACK);
					fillrectangle(150, 0, 1880, 830);
					TCHAR s[50] = "����";
					button b0(0, 0, 150, 50, RGB(170, 172, 184), s);
					b0.drawbutton();
					if (G.Save())
					{
						string a1 = "����ɹ���";
						Outtest(550, 350, a1, 100);
					}
					else
					{
						string a1 = "����ʧ�ܣ�";
						Outtest(550, 350, a1, 100);
					}
					ExMessage m;
					while (true)
					{
						if (peekmessage(&m, EM_MOUSE))
						{
							if (m.message == WM_LBUTTONDOWN)
							{
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 0 && m.y <= 0 + 50)
								{
									First();
									break;
								}
							}
						}
					}
				}
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 580 && msg.y <= 580 + 50)//�˳�ϵͳ����
				{
					return 0;
				}
				break;
			default:
				break;
			}

		}
	}
	system("pause");
	return 0;
}
