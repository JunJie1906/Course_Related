#include<iostream>
#include<cmath>
using namespace std;

class CPoint
{
	int m_x;
	int m_y;
public:
	CPoint(int x=0,int y=0):m_x(x),m_y(y){}

	int getx()
	{
		return m_x;
	}
	int gety()
	{
		return m_y;
	}
	void showPoint()
	{
		cout<<"("<<this->m_x<<","<<this->m_y<<")"<<endl;
	}
};

class CLine
{
	CPoint m_point1;
	CPoint m_point2;

public:
	CLine(int a,int b,int c,int d):m_point1(a,b),m_point2(c,d){}

	CLine():m_point1(),m_point2(){}

	void ShowLine()
	{
		cout<<"Point 1 is:("<<m_point1.getx()<<m_point1.gety()<<")"<<endl;
		cout<<"Point 2 is:("<<m_point2.getx()<<m_point2.gety()<<")"<<endl;
	}

	double distance()
	{
		double dis = (m_point1.getx()-m_point2.getx())*(m_point1.getx()-m_point2.getx())+(m_point1.gety()-m_point2.gety())*(m_point1.gety()-m_point2.gety());
		double ans = sqrt(dis);
		return ans;
	}
};

void main()
{
	CLine line1;
	line1.ShowLine();
	cout<<"Length="<<line1.distance()<<endl;

	CLine line2(1,1,5,5);
	line2.ShowLine();
	cout<<"Length="<<line2.distance()<<endl;
}

