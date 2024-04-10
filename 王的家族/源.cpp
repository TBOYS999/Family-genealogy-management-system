#include<iostream>
#include<fstream>
#include<vector>
#include<conio.h>//_getch()函数所需的头文件
#include<string>
#include<graphics.h>
#include<time.h>
#include<iomanip>
#include<algorithm>
#include"button.h"
#include"Genealogy.h"
using namespace std;

void First()//最开始的页面展示，由于每个模块由两个页面组成，第二个页面按回退键返回初始页面，
//于是将初始页面封装为一个函数
{
	initgraph(1880, 830, SHOWCONSOLE);    // 创建绘图窗口，大小为 1880*830像素
	setbkcolor(WHITE);//设置背景板颜色
	setbkmode(TRANSPARENT);//设置背景模式为透明，文字输出时不会破坏背景
	cleardevice();
	TCHAR s[50] = "显示族谱";
	TCHAR s1[50] = "添加成员";
	TCHAR s2[50] = "修改成员";
	TCHAR s3[50] = "删除成员";
	TCHAR s4[50] = "查询";
	TCHAR s5[50] = "保存";
	TCHAR s6[50] = "退出";
	button b0(650, 160, 150, 50, RGB(170, 172, 184), s);
	button b1(650, 230, 150, 50, RGB(164, 168, 180), s1);
	button b2(650, 300, 150, 50, RGB(180, 179, 186), s2);
	button b3(650, 370, 150, 50, RGB(160, 162, 174), s3);
	button b4(650, 440, 150, 50, RGB(209, 198, 194), s4);
	button b5(650, 510, 150, 50, RGB(131, 129, 129), s5);
	button b6(650, 580, 150, 50, RGB(170, 161, 151), s6);//设置主页面按钮
	IMAGE background;
	loadimage(&background, "Khan.jpg", 1880, 830, 1);//为当前背景设置一个图片
	putimage(0, 0, &background);
	settextcolor(RGB(247, 171, 0));
	settextstyle(100, 0, "STXINWEI");
	outtextxy(550, 50, "王的家族");
	b0.drawbutton();
	b1.drawbutton();
	b2.drawbutton();
	b3.drawbutton();
	b4.drawbutton();
	b5.drawbutton();
	b6.drawbutton();//画出按钮
}template<class ElemType,class Weight>
void Visited(const People<ElemType,Weight>& a)
{
	cout << a.name << " ";
}
void Outtest(int x, int y, string a, int n)//n代表字的大小
{
	char* str;
	str = new char[a.size() + 1];
	strcpy(str, a.c_str());
	setfillcolor(BLACK);
	settextcolor(RGB(170, 172, 184));//设置字体颜色
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "楷体");//设置字体样式
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = n;
	settextstyle(&f);//更改字体的高度，让字体大小变化
	outtextxy(x, y, str);//显示str中的字
}

void SetR(int j, int h, Genealogy<string, int> G, People<string, int>& p1)//在查询时，
//多个模块用到该展示，即显示数据的名字生年，卒年等，于是将其封装为函数
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
void GenealogicGraph(Genealogy<ElemType,Weight>G, int x, int y, DateNode<ElemType,Weight>* num,int h,ElemType Name)//辅助函数，x，y代表名字输出的
//起始坐标，num是数据成员数组，h是每一代分配到的高度，Name是要画的孩子的父亲
{
	int j = -1;
	G.NameFind(Name, j);
	int count = 0;
	Node* p = num[j].first;
		while (p != nullptr)
		{
			p = p->next;
			count++;
		}//先计算孩子的个数
	if (count != 0)
	{
		h = h / count;//为每个孩子分配高度空间
		if (h < 30)
		{
			h = 30;
		}//保持美观
		p = num[j].first;//从第一个孩子开始
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
			Outtest(x, y + h * count, p1.name,20);//写出当前孩子的名字
			int j = 0;
			if (d >= 3)
			{
				j = 60;
			}
			line(x - 90, y + 10+j, x, y + h * count+10);//将父亲与当前孩子之间连线
			GenealogicGraph(G, x +150, y + h * count, num, h, p1.name);//调用递归函数，对当前孩子进行递归
			p = p->next;
			count++;//用来控制每一个孩子的起始纵坐标，避免孩子之间名字的重叠
		}
	}
}
template<class ElemType,class Weight>
void GenealogicGraph(Genealogy<ElemType,Weight> G)
{
	DateNode<ElemType, Weight>* num;
	num = G.GetNum();
	People<string, int>p1;
	if (G.GetAcSize()!=0)//判断还有没有元素
	{
		p1 = G.GetData(0);
		Outtest(150, 60, p1.name, 20);//画出始祖
		GenealogicGraph(G, 300, 60, num, 825, p1.name);//调用递归画出其孩子
	}
}

int main()
{
	vector<DateNode<string,int>>num;
	string a, b;
	int c, d;
	ifstream file("Genghis Khan.txt");//读取文件
	if (!file)
	{
		cout << "未找到文件" << endl;
	}
	else
	{
		int i = 1;
		while (!file.eof())//读取文件中的数据，直到所有数据被读完
		{
			if (i == 1)//由于第一个成员没有父亲，特殊读取
			{
				file >> a >> c >> d;
				b = "";
				DateNode<string,int> D(a, c, d, b);
				num.push_back(D);//将读来的数据压入容器
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

	Genealogy<string,int> G(&num[0],num.size());//初始化族谱系统
	G.Display(Visited<string,int>);
	vector<int>Count1;
	Count1 = G.GetCount();
	/*for (int i = 0; i < Count1.size()-1; i++)
	{
		cout << Count1[i] << endl;
	}*/
	First();
	while(true)
	{	ExMessage msg;//设置一个获取鼠标的变量
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)//获取鼠标信息
			{
			case WM_LBUTTONDOWN://按下鼠标左键
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 160 && msg.y <= 160 + 50)//功能一：展示族谱图
				{
					cleardevice();
					TCHAR s[50] = "后退";
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
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 0 && m.y <= 0 + 50)//回到初始界面
								{
									First();
									break;
								}
							}
						}
					}

				}
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 230 && msg.y <= 230 + 50)//模块二，添加成员数据
				{
					cleardevice();
					TCHAR s[50] = "后退";
					button b0(0, 0, 150, 50, RGB(170, 172, 184), s);
					b0.drawbutton();
					setfillcolor(BLACK);
					string a0;
					fillrectangle(150, 0, 1880, 830);
					a0 = "请输入要添加成员的个数";
					Outtest(150, 0, a0, 30);
					string a1;
					cin >> a1;
					Outtest(150, 50, a1, 30);
					int n = atoi(a1.c_str());//用来记录需要添加成员的次数

					int j = 1;
					while (n>0)
					{
						
						string a;
						a = "请输入要添加成员的姓名，出生年，死亡年，成员的父亲";
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
							c = "添加成功!";
							Outtest(150, 50 + (j + 2) * 50, c, 30);
						}
						else
						{
							string c;
							c = "添加失败!,该成员已经存在";
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
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 300 && msg.y <= 300 + 50)//模块三，修改成员数据
				{
					cleardevice();
					TCHAR s[50] = "后退";
					button b0(0, 0, 150, 50, RGB(170, 172, 184), s);
					b0.drawbutton();
					setfillcolor(BLACK);
					string a0;
					fillrectangle(150, 0, 1880, 830);
					a0 = "请输入要修改成员的个数";
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
						a2 = "请输入要修改的成员名字";
						Outtest(150, 100, a2, 30);
						string a3;
						cin >> a3;
						Outtest(150, 150, a3, 30);
						People<string, int> p1;
						int j = -1;
						if (G.NameFind(a3, j))
						{
							SetR(j, 200, G, p1);
							TCHAR s[50] = "完成当前修改";
							button b05(0, 300, 150, 50, RGB(170, 172, 184), s);
							b05.drawbutton();
							ExMessage m;
							while (true)
							{
								if (peekmessage(&m, EM_MOUSE))
								{
									if (m.message == WM_LBUTTONDOWN)
									{
										if (m.x >= 150 && m.x <= 150 + 150 && m.y >= 250 && m.y <= 250 + 50)//功能1：修改名字
										{
											setfillcolor(BLACK);
											fillrectangle(150, 300, 1730, 780);
											string c1;
											c1 = "请输入修改后的名字";
											Outtest(150, 300, c1, 30);
											string c12;
											cin >> c12;
											Outtest(150, 350, c12, 30);
											if (G.ChangeName(p1.name, c12))
											{
												string c13;
												c13 = "修改成功!";
												Outtest(150, 400, c13, 30);
												p1.name = c12;
											}
											else
											{
												string c13;
												c13 = "修改失败，未找到该人!";
												Outtest(150, 400, c13, 30);
											}
										}
										if (m.x >= 320 && m.x <= 320 + 150 && m.y >= 250 && m.y <= 250 + 50)//模块二，修改出生年份
										{
											setfillcolor(BLACK);
											fillrectangle(150, 300, 1730, 780);
											string c1;
											c1 = "请输入修改后的生年";
											Outtest(150, 300, c1, 30);
											string c12;
											cin >> c12;
											Outtest(150, 350, c12, 30);
											if (G.ChangeBornTime(p1.name, atoi(c12.c_str())))
											{
												string c13;
												c13 = "修改成功!";
												Outtest(150, 400, c13, 30);
											}
											else
											{
												string c13;
												c13 = "修改失败，未找到该人!";
												Outtest(150, 400, c13, 30);
											}
										}
										if (m.x >= 490 && m.x <= 490 + 150 && m.y >= 250 && m.y <= 250 + 50)//模块三：修改去世年份
										{
											setfillcolor(BLACK);
											fillrectangle(150, 300, 1730, 780);
											string c1;
											c1 = "请输入修改后的卒年";
											Outtest(150, 300, c1, 30);
											string c12;
											cin >> c12;
											Outtest(150, 350, c12, 30);
											if (G.ChangeDeidTime(p1.name, atoi(c12.c_str())))
											{
												string c13;
												c13 = "修改成功!";
												Outtest(150, 400, c13, 30);
											}
											else
											{
												string c13;
												c13 = "修改失败，未找到该人!";
												Outtest(150, 400, c13, 30);
											}
										}
										if (m.x >= 660 && m.x <= 660 + 150 && m.y >= 250 && m.y <= 250 + 50)//模块四：修改父亲名字
										{
											setfillcolor(BLACK);
											fillrectangle(150, 300, 1730, 780);
											string c1;
											c1 = "请输入修改后的父亲名字";
											Outtest(150, 300, c1, 30);
											string c12;
											cin >> c12;
											Outtest(150, 350, c12, 30);
											if (G.ChangeFather(p1.name, c12))
											{
												string c13;
												c13 = "修改成功!";
												Outtest(150, 400, c13, 30);
											}
											else
											{
												string c13;
												c13 = "修改失败，未找到该人!";
												Outtest(150, 400, c13, 30);
											}
										}
										if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 300 && m.y <= 300 + 50)//修改后的展示
										{
											setfillcolor(BLACK);
											fillrectangle(150, 300, 1730, 780);
											string c13;
											c13 = "修改后为：";
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
											c1 = "按1完成展示，继续下面操作";
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
						string a55 = "修改失败，未找到该人";
						Outtest(150, 300, a55, 30);
						string c1;
						c1 = "按1继续，按其他键退出！";
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
							a22 = "全部修改已完成！";
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
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 370 && msg.y <= 370 + 50)//模块三：删除成员
				{
					cleardevice();
					TCHAR s[50] = "后退";
					button b0(0, 0, 150, 50, RGB(170, 172, 184), s);
					b0.drawbutton();
					setfillcolor(BLACK);
					string a0;
					fillrectangle(150, 0, 1880, 830);
						a0 = "请输入要删除成员的个数";
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
							a2 = "请输入要删除的成员名字";
							Outtest(150, 100, a2, 30);
							string a3;
							cin >> a3;
							Outtest(150, 150, a3, 30);
							People<string, int> p1;
							int j = -1;
							if (G.NameFind(a3, j))
							{
								string k;
								k = "名字";
								Outtest(180, 200, k, 30);
								k = "生年";
								Outtest(360, 200, k, 30);
								k = "卒年";
								Outtest(530, 200, k, 30);
								k = "父亲";
								Outtest(670, 200, k, 30);
								SetR(j, 200, G, p1);
								TCHAR s[50] = "确认删除";
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
													string a44 = "删除成功！";
													Outtest(150, 300, a44, 30);
													string c1;
													c1 = "按1完成展示，继续下面操作";
													Outtest(150, 400, c1, 30);
													int n;
													cin >> n;
													if (n == 1)
														break;
												}
												else
												{
													string a55 = "删除失败，未找到该人";
													Outtest(150, 300, a55, 30);
													string c1;
													c1 = "按1完成展示，继续下面操作";
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
								string a55 = "删除失败，未找到该人";
								Outtest(150, 300, a55, 30);
								string c1;
								c1 = "按1继续，按其他键退出！";
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
						a22 = "全部删除已完成！";
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
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 440 && msg.y <= 440 + 50)//模块五，查询成员
				{
					cleardevice();
					TCHAR s[50] = "后退";
					setfillcolor(BLACK);
					fillrectangle(150, 0, 1880, 830);
					button b0(0, 0, 150, 50, RGB(170, 172, 184), s);
					b0.drawbutton();
					TCHAR s1[50] = "名字查询";
					button b01(0, 70, 150, 50, RGB(170, 172, 184), s1);
					b01.drawbutton();
					TCHAR s2[50] = "按代查询";
					button b02(0, 140, 150, 50, RGB(170, 172, 184), s2);
					b02.drawbutton();
					TCHAR s3[50] = "查询兄弟";
					button b03(0, 210, 150, 50, RGB(170, 172, 184), s3);
					b03.drawbutton();
					TCHAR s4[50] = "查询父亲";
					button b04(0, 280, 150, 50, RGB(170, 172, 184), s4);
					b04.drawbutton();
					TCHAR s5[50] = "查询孩子";
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
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 70 && m.y <= 70 + 50)//名字查询
								{
									setfillcolor(BLACK);
									fillrectangle(150, 0, 1880, 830);
									string c1;
									c1 = "请输入要查询的名字";
									Outtest(150, 0, c1, 30);
									string c12;
									cin >> c12;
									Outtest(150, 50, c12, 30);
									People<string, int> p1;
									int j = -1;
									if (G.NameFind(c12, j))
									{
										string k;
										k = "名字";
										Outtest(180, 200, k, 30);
										k = "生年";
										Outtest(360, 200, k, 30);
										k = "卒年";
										Outtest(530, 200, k, 30);
										k = "父亲";
										Outtest(670, 200, k, 30);
										SetR(j, 200, G, p1);
									}
									else
									{
										string d11 = "查无此人!";
										Outtest(150, 100, d11, 30);
									}
								}
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 140 && m.y <= 140 + 50)//代数查询
								{
									setfillcolor(BLACK);
									fillrectangle(150, 0, 1880, 830);
									string c1;
									c1 = "请输入要查询的代数";
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
										k = "名字";
										Outtest(180, 100, k, 30);
										k = "生年";
										Outtest(360, 100, k, 30);
										k = "卒年";
										Outtest(530, 100, k, 30);
										k = "父亲";
										Outtest(670, 100, k, 30);
										SetR(n[i], 100+i*50, G, p1);
										i++;
									}
									if (n.size() == 0)
									{
										string c1;
										c1 = "族谱中没有该代的记录！";
										Outtest(150, 100, c1, 30);
									}
								}
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 210 && m.y <= 210 + 50)//查询父亲
								{
									setfillcolor(BLACK);
									fillrectangle(150, 0, 1880, 830);
									string c1;
									c1 = "请输入要查询的名字";
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
										k = "名字";
										Outtest(180, 100, k, 30);
										k = "生年";
										Outtest(360, 100, k, 30);
										k = "卒年";
										Outtest(530, 100, k, 30);
										k = "父亲";
										Outtest(670, 100, k, 30);
										SetR(n[i], 100 + i * 50, G, p1);
										i++;
									}int w = -1;
									if (n.size() == 0)
									{
										if (!G.NameFind(c12, w))
										{
											string c1;
											c1 = "族谱中没有该人的记载！";
											Outtest(150, 100, c1, 30);
										}
									
										else
										{
											string c1;
											c1 = "族谱中没有该人兄弟的记载！";
											Outtest(150, 100, c1, 30);
										}
									}
								}
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 280 && m.y <= 280 + 50)//查询兄弟
								{
									setfillcolor(BLACK);
									fillrectangle(150, 0, 1880, 830);
									string c1;
									c1 = "请输入要查询的名字";
									Outtest(150, 0, c1, 30);
									string c12;
									cin >> c12;
									Outtest(150, 50, c12, 30);
									People<string, int> p1;
									int j = -1;
									if (G.FatherFind(c12,j))
									{
										string f = c12 + "的父亲为:";
										Outtest(180, 100, f, 30);
										string k;
										k = "名字";
										Outtest(180, 200, k, 30);
										k = "生年";
										Outtest(360, 200, k, 30);
										k = "卒年";
										Outtest(530, 200, k, 30);
										k = "父亲";
										Outtest(670, 200, k, 30);
										SetR(j, 200, G, p1);
									}
									else if (G.NameFind(c12, j))
									{
										string d11 = "族谱中未记载其父亲！";
										Outtest(150, 100, d11, 30);
									}
									else
									{
										string d11 = "查无此人!";
										Outtest(150, 100, d11, 30);
									}
								}
								if (m.x >= 0 && m.x <= 0 + 150 && m.y >= 350 && m.y <= 350 + 50)//查询孩子
								{
									setfillcolor(BLACK);
									fillrectangle(150, 0, 1880, 830);
									string c1;
									c1 = "请输入要查询的名字";
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
										k = "名字";
										Outtest(180, 100, k, 30);
										k = "生年";
										Outtest(360, 100, k, 30);
										k = "卒年";
										Outtest(530, 100, k, 30);
										k = "父亲";
										Outtest(670, 100, k, 30);
										SetR(n[i], 100 + i * 50, G, p1);
										i++;
									}int w = -1;
									if (n.size() == 0)
									{
										if (!G.NameFind(c12, w))
										{
											string c1;
											c1 = "族谱中没有该人的记载！";
											Outtest(150, 100, c1, 30);
										}

										else
										{
											string c1;
											c1 = "族谱中没有该人孩子的记载！";
											Outtest(150, 100, c1, 30);
										}
									}
								}
							}
						}
					}
				}
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 510 && msg.y <= 510 + 50)//保存模块
				{
					cleardevice();
					setfillcolor(BLACK);
					fillrectangle(150, 0, 1880, 830);
					TCHAR s[50] = "后退";
					button b0(0, 0, 150, 50, RGB(170, 172, 184), s);
					b0.drawbutton();
					if (G.Save())
					{
						string a1 = "保存成功！";
						Outtest(550, 350, a1, 100);
					}
					else
					{
						string a1 = "保存失败！";
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
				if (msg.x >= 650 && msg.x <= 650 + 150 && msg.y >= 580 && msg.y <= 580 + 50)//退出系统功能
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
