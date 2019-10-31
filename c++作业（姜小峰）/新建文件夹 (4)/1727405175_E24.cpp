#include<iostream>
#include<string>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<time.h>
#include<stdlib.h>
#include<vector>

using namespace std;

const double Pi = 3.1415926;

class Circle
{
private:
	double x;
	double y;
	double r;

public:
	void set_center(double a ,double b);

	void set_r(double a);

	double cal_S();

	double cal_L();

	friend Circle operator+(const Circle &a,const Circle &b); //  overload  operator +
	friend Circle operator-(const Circle &a,const Circle &b);  //  overload  operator -

	friend Circle operator++(Circle &a,int);  //a++
	friend Circle &operator++(Circle &a);  //++a

	friend Circle operator--(Circle &a,int);  //a--
	friend Circle &operator--(Circle &a);  //--a

	friend bool operator>(const Circle &a,const Circle &b);   //  overload  operator >
	friend bool operator<(const Circle &a,const Circle &b); //  overload  operator <

	friend bool operator==(const Circle &a,const Circle &b); //  overload  operator ==
	friend bool operator!=(const Circle &a,const Circle &b); //  overload  operator !=

	friend bool operator&(const Circle &a,const Circle &b); //  overload  operator &

	friend void operator|(const Circle &a,const Circle &b); //  overload  operator |


};

void Circle::set_center(double a ,double b)   // set (x,y)
{
	x = a; 
	y = b;
}

void Circle::set_r(double a)    //set r
{
	r = a;
}

double Circle::cal_S() //cal S
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

double Circle::cal_L()                // cal L
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
Circle operator+(const Circle &a,const Circle &b) //  overload  operator +
{
	Circle s;
	s.set_center(a.x,a.y);
	s.set_r(a.r+b.r);
	return s;
}

Circle operator-(const Circle &a,const Circle &b)   //  overload  operator -
{
	Circle s;
	s.set_center(a.x,a.y);
	s.set_r(sqrt(abs(a.r*a.r-b.r*b.r)));
	return s;
}

Circle operator++(Circle &a,int)   //a++
{
	Circle t(a);
	a.r+=1;
	return t;
}

Circle &operator++(Circle &a)  //++a
{
	a.r+=1;
	return a;
}

Circle operator--(Circle &a,int)  //a--
{
	Circle t(a);
	a.r-=1;
	return t;
}

Circle &operator--(Circle &a)  //--a
{
	a.r-=1;
	return a;
}

bool operator>(const Circle &a,const Circle &b)  //  overload  operator >
{
	return a.r>b.r;
}

bool operator<(const Circle &a,const Circle &b) //  overload  operator <
{
	return a.r<b.r;
}

bool operator==(const Circle &a,const Circle &b) //  overload  operator ==
{
	return a.r==b.r&&a.x==b.x&&a.y==b.y;
}

bool operator!=(const Circle &a,const Circle &b) //  overload  operator !=
{
	return a.r!=b.r||a.x!=b.x||a.y!=b.y;
}

bool operator&(const Circle &a,const Circle &b) //  overload  operator &
{
	return a.x==b.x&&a.y==b.y;
}

void operator|(const Circle &a,const Circle &b) //  overload  operator |
{
	int distr = a.r+b.r;
	int distr2 = abs(a.r-b.r);
	int distcenter = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	if(a==b)
	{
		 cout<<"相同"<<endl;
		 return;
	}
	if(distr2>distcenter)
	{
		cout<<"包含"<<endl;
		return;
	}

	if(distr==distcenter||distr2==distcenter) 
	{
		cout<<"相切"<<endl;
		return;
	}

	if(distr<distcenter&&distcenter>distr2) 
	{
		cout<<"相离"<<endl;
		return;
	}

	cout<<"相交"<<endl;
}


int main()
{
	Circle a,b,c,d;
	int r1,r2,x1,y1,x2,y2; 
	srand((int)time(0));
	
	r1 = rand()%100;
	r2 = rand()%100;
	x1 = rand()%100;
	x2 = rand()%100;
	y1 = rand()%100;
	y2 = rand()%100;
	
	a.set_center(x1,y1);
	a.set_r(r1);
	b.set_r(r2);
	b.set_center(x2,y2);
	c = a+b;
	d = a-b;
	
	cout<<"r1= "<<r1<<endl;
	cout<<"r2= "<<r2<<endl;
	cout<<"S = "<<d.cal_S()<<endl;
	if(a>b) cout<<"a>b"<<endl;
	else cout<<"a<=b"<<endl;

	if(a<b) cout<<"a<b"<<endl;
	else cout<<"a>=b"<<endl;

	if(a==b) cout<<"a==b"<<endl;
	else cout<<"a!=b"<<endl;

	if(a!=b) cout<<"a!=b"<<endl;
	else cout<<"a==b"<<endl;

	if(a&b) cout<<"a, b have the same center"<<endl;
	else cout<<"a, b don't have the same center"<<endl;

	a|b;

}
