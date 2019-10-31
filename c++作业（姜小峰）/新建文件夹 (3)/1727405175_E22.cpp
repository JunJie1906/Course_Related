#include<iostream>
#include<string>
#include<cstdio>
#include<cmath>

using namespace std;

const double Pi = 3.1415926;

class Circle
{
private:
	double x;
	double y;
	double r;

public:
	void set_center(double a ,double b)  //设置圆心 
	{
		x = a; 
		y = b;
	}

	void set_r(double a)  //设置半径 
	{
		r = a;
	}

	double cal_S()   //计算面积 
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

	double cal_L()   //计算周长 
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
};



int main()
{
	Circle c1;
	double S,L;

	c1.set_center(2.1, 3.4);  
	c1.set_r(5.0);
	S = c1.cal_S();
	L = c1.cal_L();
	cout<<"S = "<<S<<endl;
	cout<<"L = "<<L<<endl;
}
