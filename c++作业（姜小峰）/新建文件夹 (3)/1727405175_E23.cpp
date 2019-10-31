#include<iostream>
#include<string>
#include<cstdio>
#include<cmath>

using namespace std;

const double Pi = 3.1415926;

class Column
{
private:
	double x;
	double y;
	double r;
	double h;
public:
	void set_center(double a, double b) //����Բ�� 
	{
		x = a;
		y = b;
	}

	void set_r(double a)  //���õ���뾶 
	{
		r = a;
	}

	void set_h(double a) // ���ø߶� 
	{
		h = a;
	}


	double cal_S_bottom() //���������� 
	{
		if(r)
		{
			return Pi*r*r;
		}
		else
		{
			cout<<"Please set r first!!"<<endl;
			return 0;
		}
	}

	double cal_L_bottom() //��������ܳ� 
	{
		if(r)
		{
			return 2*Pi*r;
		}
		else
		{
			cout<<"Please set r first!!"<<endl;
			return 0;
		}
	}

	double cal_S_side()  //�������� 
	{
		if(r&&h)
		{
			double L;
			L = cal_L_bottom();
			return L*h;
		}
		else
		{
			cout<<"Please set r and h first!!"<<endl;
			return 0;
		}
	}

	double cal_V()  //������� 
	{
		if(r&&h)  //���û������r��h ����ʾ������� 
		{
			double S_bottom;
			S_bottom = cal_S_bottom();
			return S_bottom*h;
		}
		else
		{
			cout<<"Please set r and h first!!"<<endl;
			return 0;
		}

	}
};

int main()
{
	double S1,S2,V,L;
	Column C1;

	C1.set_center(2,2);
	C1.set_h(6.5);
	C1.set_r(12);

	S1 = C1.cal_S_bottom();
	S2 = C1.cal_S_side();
	V = C1.cal_V();
	L = C1.cal_L_bottom();
	cout<<"Side S = "<<S2<<endl;
	cout<<"Bottom S = "<<S1<<endl;
	cout<<"V = "<<V<<endl;
	cout<<"Bottom L = "<<L<<endl;
}
