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
	void set_center(double a ,double b)  //����Բ�� 
	{
		x = a; 
		y = b;
	}

	void set_r(double a)  //���ð뾶 
	{
		r = a;
	}

	double cal_S()   //������� 
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

	double cal_L()   //�����ܳ� 
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
