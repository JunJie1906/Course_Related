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
	void set_center(double a, double b) //设置圆心 
	{
		x = a;
		y = b;
	}

	void set_r(double a)  //设置底面半径 
	{
		r = a;
	}

	void set_h(double a) // 设置高度 
	{
		h = a;
	}


	double cal_S_bottom() //计算底面面积 
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

	double cal_L_bottom() //计算底面周长 
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

	double cal_S_side()  //计算侧面积 
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

	double cal_V()  //计算体积 
	{
		if(r&&h)  //如果没有输入r，h ，提示输入错误 
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
