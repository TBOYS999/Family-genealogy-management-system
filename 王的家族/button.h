#pragma once
#pragma warning(disable:4996) // ���strcpy����ȫ����
#include<graphics.h>
#include<string>
class button
{
public:
	int x;
	int y;//(x,y)�������Ͻǵ�λ��
	int width;//�������
	int height;//�����߶�
	COLORREF color;//��������ɫ����ɫȫ�����Ǵ�д��Ӣ�ĵ���
	char* str;//�����ϵ���
	button(int x_, int y_, int width_, int height_, COLORREF color_, const char* str_) //�԰������г�ʼ��������Ҳ����ֱ���ù��캯��
	{
		x = x_;
		y = y_;
		width = width_;
		height = height_;
		color = color_;
		str = new char[strlen(str_) + 1];//�ַ�ָ����ҪԤ�ȷ����ڴ�
		strcpy(str, str_);//�����ַ���
	}
	void drawbutton()//��������
	{
		setfillcolor(color);//����������ɫΪ��������ɫ
		settextstyle(20, 0, "����");//�����������ԣ����20���߶�0������Ӧ�������忬��
		//setlinecolor(BLACK);//���ñ߿�������ɫ
		settextcolor(BLACK);//����������ɫ
		setbkmode(TRANSPARENT);//�������屳��Ϊ͸��treansparent
		fillrectangle(x, y, x + width, y + height);//����һ�����Σ�����Ϊ�þ��ε����Ϻ����µ����꣬��ɫΪ���������õ���ɫĬ��Ϊ��ɫ
		int w = (width - (13 * (lstrlen(str)-1))) / 2;
		int h = (height - 20) / 2;
		outtextxy(x+w, y+h, str);//��x+20,y+10λ��������úõ���������str

	}
	bool mouseInButton(MOUSEMSG m)//�����ж�����Ƿ��ڰ����ķ�Χ��
	{
		//m.x,m.y��ʾ�����ĺ�������
		if (m.x >= x && m.x <= x + width && m.y >= y && m.y <= y + height)
		{
			color = RED;//����ھͽ�������ɫ�ı�
			return true;
		}
		else
		{
			//color = YELLOW;//�����
			return false;
		}
	}
	~button() {//��������
		delete[]str;
	}
};

