#pragma once
#pragma warning(disable:4996) // 解决strcpy不安全问题
#include<graphics.h>
#include<string>
class button
{
public:
	int x;
	int y;//(x,y)按键左上角的位置
	int width;//按键宽度
	int height;//按键高度
	COLORREF color;//按键的颜色，颜色全部都是大写的英文单词
	char* str;//按键上的字
	button(int x_, int y_, int width_, int height_, COLORREF color_, const char* str_) //对按键进行初始化，这里也可以直接用构造函数
	{
		x = x_;
		y = y_;
		width = width_;
		height = height_;
		color = color_;
		str = new char[strlen(str_) + 1];//字符指针需要预先分配内存
		strcpy(str, str_);//复制字符串
	}
	void drawbutton()//画出按键
	{
		setfillcolor(color);//设置填充的颜色为按键的颜色
		settextstyle(20, 0, "楷体");//设置字体属性，宽度20，高度0（自适应），字体楷体
		//setlinecolor(BLACK);//设置边框线条颜色
		settextcolor(BLACK);//设置字体颜色
		setbkmode(TRANSPARENT);//设置字体背景为透明treansparent
		fillrectangle(x, y, x + width, y + height);//填充出一个矩形，参数为该矩形的左上和右下的坐标，颜色为上面所设置的颜色默认为黑色
		int w = (width - (13 * (lstrlen(str)-1))) / 2;
		int h = (height - 20) / 2;
		outtextxy(x+w, y+h, str);//在x+20,y+10位置输出设置好的字体文字str

	}
	bool mouseInButton(MOUSEMSG m)//用于判断鼠标是否在按键的范围内
	{
		//m.x,m.y表示该鼠标的横纵坐标
		if (m.x >= x && m.x <= x + width && m.y >= y && m.y <= y + height)
		{
			color = RED;//如果在就将按键颜色改变
			return true;
		}
		else
		{
			//color = YELLOW;//变回来
			return false;
		}
	}
	~button() {//析构函数
		delete[]str;
	}
};

