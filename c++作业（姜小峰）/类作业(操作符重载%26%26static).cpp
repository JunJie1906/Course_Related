//////////////////////////////// E22

//#include<iostream>
//#include<string>
//#include<cstdio>
//#include<cmath>
//
//using namespace std;
//
//const double Pi = 3.1415926;
//
//class Circle
//{
//private:
//	double x;
//	double y;
//	double r;
//
//public:
//	void set_center(double a ,double b)
//	{
//		x = a; 
//		y = b;
//	}
//
//	void set_r(double a)
//	{
//		r = a;
//	}
//
//	double cal_S()
//	{
//		if(r)
//		{
//			return Pi*r*r;
//		}
//		else
//		{
//			cout<<"Please set r first!!"<<endl;
//			return 0;
//		}
//	}
//
//	double cal_L()
//	{
//		if(r)
//		{
//			return 2*Pi*r;
//		}
//		else
//		{
//			cout<<"Please set r first!!"<<endl;
//			return 0;
//		}
//	}
//};


//
//int main()
//{
//	Circle c1;
//	double S,L;
//
//	c1.set_center(2.1, 3.4);
//	c1.set_r(5.0);
//	S = c1.cal_S();
//	L = c1.cal_L();
//	cout<<"S = "<<S<<endl;
//	cout<<"L = "<<L<<endl;
//}


//#include<iostream>
//#include<string>
//#include<cstdio>
//#include<cmath>
//
//using namespace std;
//
//const double Pi = 3.1415926;
//
//class Column
//{
//private:
//	double x;
//	double y;
//	double r;
//	double h;
//public:
//	void set_center(double a, double b)
//	{
//		x = a;
//		y = b;
//	}
//
//	void set_r(double a)
//	{
//		r = a;
//	}
//
//	void set_h(double a)
//	{
//		h = a;
//	}
//
//
//	double cal_S_bottom()
//	{
//		if(r)
//		{
//			return Pi*r*r;
//		}
//		else
//		{
//			cout<<"Please set r first!!"<<endl;
//			return 0;
//		}
//	}
//
//	double cal_L_bottom()
//	{
//		if(r)
//		{
//			return 2*Pi*r;
//		}
//		else
//		{
//			cout<<"Please set r first!!"<<endl;
//			return 0;
//		}
//	}
//
//	double cal_S_side()
//	{
//		if(r&&h)
//		{
//			double L;
//			L = cal_L_bottom();
//			return L*h;
//		}
//		else
//		{
//			cout<<"Please set r and h first!!"<<endl;
//			return 0;
//		}
//	}
//
//	double cal_V()
//	{
//		if(r&&h)
//		{
//			double S_bottom;
//			S_bottom = cal_S_bottom();
//			return S_bottom*h;
//		}
//		else
//		{
//			cout<<"Please set r and h first!!"<<endl;
//			return 0;
//		}
//
//	}
//};
//
//int main()
//{
//	double S1,S2,V,L;
//	Column C1;
//
//	C1.set_center(2,2);
//	C1.set_h(6.5);
//	C1.set_r(3.3);
//
//	S1 = C1.cal_S_bottom();
//	S2 = C1.cal_S_side();
//	V = C1.cal_V();
//	L = C1.cal_L_bottom();
//	cout<<"Side S = "<<S2<<endl;
//	cout<<"Bottom S = "<<S1<<endl;
//	cout<<"V = "<<V<<endl;
//	cout<<"Bottom L = "<<L<<endl;
//}



////////////////////E24


//#include<iostream>
//#include<string>
//#include<cstdio>
//#include<cmath>
//
//using namespace std;
//
//const double Pi = 3.1415926;
//
//class Circle
//{
//private:
//	double x;
//	double y;
//	double r;
//
//public:
//	void set_center(double a ,double b);
//
//	void set_r(double a);
//
//	double cal_S();
//
//	double cal_L();
//
//	friend Circle operator+(const Circle &a,const Circle &b); //  overload  operator +
//	friend Circle operator-(const Circle &a,const Circle &b);  //  overload  operator -
//
//	friend Circle operator++(Circle &a,int);  //a++
//	friend Circle &operator++(Circle &a);  //++a
//
//	friend Circle operator--(Circle &a,int);  //a--
//	friend Circle &operator--(Circle &a);  //--a
//
//	friend bool operator>(const Circle &a,const Circle &b);   //  overload  operator >
//	friend bool operator<(const Circle &a,const Circle &b); //  overload  operator <
//
//	friend bool operator==(const Circle &a,const Circle &b); //  overload  operator ==
//	friend bool operator!=(const Circle &a,const Circle &b); //  overload  operator !=
//
//	friend bool operator&(const Circle &a,const Circle &b); //  overload  operator &
//
//	friend void operator|(const Circle &a,const Circle &b); //  overload  operator |
//
//
//};
//
//void Circle::set_center(double a ,double b)   // set (x,y)
//{
//	x = a; 
//	y = b;
//}
//
//void Circle::set_r(double a)    //set r
//{
//	r = a;
//}
//
//double Circle::cal_S() //cal S
//{
//	if(r)
//	{
//		return Pi*r*r;
//	}
//	else
//	{
//		cout<<"Please set r first!!"<<endl;
//		return 0;
//	}
//}
//
//double Circle::cal_L()       // cal L
//{
//	if(r)
//	{
//		return 2*Pi*r;
//	}
//	else
//	{
//		cout<<"Please set r first!!"<<endl;
//		return 0;
//	}
//}
//Circle operator+(const Circle &a,const Circle &b) //  overload  operator +
//{
//	Circle s;
//	s.set_center(a.x,a.y);
//	s.set_r(a.r+b.r);
//	return s;
//}
//
//Circle operator-(const Circle &a,const Circle &b)   //  overload  operator -
//{
//	Circle s;
//	s.set_center(a.x,a.y);
//	s.set_r(sqrt(abs(a.r*a.r-b.r*b.r)));
//	return s;
//}
//
//Circle operator++(Circle &a,int)   //a++
//{
//	Circle t(a);
//	a.r+=1;
//	return t;
//}
//
//Circle &operator++(Circle &a)  //++a
//{
//	a.r+=1;
//	return a;
//}
//
//Circle operator--(Circle &a,int)  //a--
//{
//	Circle t(a);
//	a.r-=1;
//	return t;
//}
//
//Circle &operator--(Circle &a)  //--a
//{
//	a.r-=1;
//	return a;
//}
//
//bool operator>(const Circle &a,const Circle &b)  //  overload  operator >
//{
//	return a.r>b.r;
//}
//
//bool operator<(const Circle &a,const Circle &b) //  overload  operator <
//{
//	return a.r<b.r;
//}
//
//bool operator==(const Circle &a,const Circle &b) //  overload  operator ==
//{
//	return a.r==b.r&&a.x==b.x&&a.y==b.y;
//}
//
//bool operator!=(const Circle &a,const Circle &b) //  overload  operator !=
//{
//	return a.r!=b.r||a.x!=b.x||a.y!=b.y;
//}
//
//bool operator&(const Circle &a,const Circle &b) //  overload  operator &
//{
//	return a.x==b.x&&a.y==b.y;
//}
//
//void operator|(const Circle &a,const Circle &b) //  overload  operator |
//{
//	int distr = a.r+b.r;
//	int distr2 = abs(a.r-b.r);
//	int distcenter = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
//	if(a==b)
//	{
//		 cout<<"相同"<<endl;
//		 return;
//	}
//	if(distr2>distcenter)
//	{
//		cout<<"包含"<<endl;
//		return;
//	}
//
//	if(distr==distcenter||distr2==distcenter) 
//	{
//		cout<<"相切"<<endl;
//		return;
//	}
//
//	if(distr<distcenter&&distcenter>distr2) 
//	{
//		cout<<"相离"<<endl;
//		return;
//	}
//
//	cout<<"相交"<<endl;
//}
//
//
//int main()
//{
//	Circle a,b,c,d;
//	a.set_center(1,2);
//	a.set_r(8);
//	b.set_r(6);
//	b.set_center(3,6);
//	c = a+b;
//	d = a-b;
//	cout<<d.cal_S()<<endl;
//	if(a>b) cout<<"a>b"<<endl;
//	else cout<<"a<=b"<<endl;
//
//	if(a<b) cout<<"a<b"<<endl;
//	else cout<<"a>=b"<<endl;
//
//	if(a==b) cout<<"a==b"<<endl;
//	else cout<<"a!=b"<<endl;
//
//	if(a!=b) cout<<"a!=b"<<endl;
//	else cout<<"a==b"<<endl;
//
//	if(a&b) cout<<"a, b have the same center"<<endl;
//	else cout<<"a, b don't have the same center"<<endl;
//
//	a|b;
//
//}


/////////////////////////E25

//#include<iostream>
//#include<string>
//#include<cstdio>
//#include<cmath>
//
//using namespace std;
//
//class CComplex
//{
//	double m_real;
//	double m_image;
//public:
//	void setValue(double real,double image)
//	{
//		m_real = real;
//		m_image = image;
//	}
//
//	friend ostream &operator<<(ostream &o,const CComplex &c)   // overload  operator  <<
//	{
//		return o<<c.m_real<<"+"<<c.m_image<<"*i";
//	}
//
//	friend CComplex operator+(const CComplex &a,const CComplex &b) // overload  operator  a+b
//	{
//		CComplex s;
//		s.setValue(a.m_real+b.m_real,a.m_image+b.m_image);
//		return s;
//	}
//
//	friend CComplex operator+(const int a,const CComplex &b) // int + complex
//	{
//		CComplex s;
//		s.setValue(a+b.m_real,b.m_image);
//		return s;
//	}
//
//	friend CComplex operator+(const CComplex &a,const int b)  // complex + int 
//	{
//		CComplex s;
//		s.setValue(a.m_real+b,a.m_image);
//		return s;
//	}
//
//	friend CComplex operator++(CComplex &a,int) // overload  operator  a++
//	{
//		CComplex t(a);
//		a.m_real++;
//		a.m_image++;
//		return t;
//	}
//
//	friend CComplex &operator++(CComplex &a) // overload  operator  ++a
//	{
//		a.m_real++;
//		a.m_image++;
//		return a;
//	}
//
//
//};
//
//
//int main()
//{
//	CComplex p,q;
//	p.setValue(10,9);
//	q.setValue(33,44);
//	cout<<"p: "<<p<<endl;
//	cout<<"q: "<<q<<endl;
//	cout<<"p+100 : "<<p+100<<endl;
//	cout<<"p+q : "<<p+q<<endl;
//
//	cout<<"++p: "<<++p<<endl;
//	cout<<"p++: "<<p++<<endl;
//	cout<<"p: "<<p<<endl;
//}



/////////////////E26

#include<iostream>
#include<string>
#include<cstdio>
#include<cmath>

using namespace std;

class CAount
{
	double m_Money;
	int year,month,date;
	static double m_InterestRate;
public:
	static void SetInterestRate(double m)
	{
		m_InterestRate =m;
	}
	double GetInterestRate()
	{
		return m_InterestRate;
	}

	void SaveMoney(double m,int y,int mo,int d)
	{
		year = y;
		month = mo;
		date = d;
		if(m_Money>0)
		{
			m_Money += m;
		}
		else
		{
			m_Money = m;
		}
	}

	double LendMoney(double m,int y,int mo,int d)
	{
		if(m_Money>=m)
		{
			m_Money -= m;
			cout<<"本金够，取出来了";
			return m+m*m_InterestRate*((y-year)*360+(mo-month)*30+(d-date))/360;
		}
		else
		{
			cout<<"本金不够，取出来 ";
			return 0;
		}
	}
	void SaveInterest(int y,int mo,int d)
	{
		m_Money += m_Money* m_InterestRate*((y-year)*360+(mo-month)*30+(d-date))/360;
		year = y;
		month = mo;
		date = d;
	}

};

double CAount::m_InterestRate=0;        //初始化m_InterestRate

int main()
{
	CAount a,b;
	CAount::SetInterestRate(0.001);
	a.SaveMoney(200000,2017,12,2);
	a.SaveInterest(2018,5,4);
	cout<<a.LendMoney(300000,2019,1,1)<<endl;
	cout<<a.LendMoney(200001,2019,1,1)<<endl;
	cout<<"InterestRate is: "<<a.GetInterestRate()<<endl; 
	CAount::SetInterestRate(0.01);
	b.SaveMoney(200000,2017,12,2);
	b.SaveInterest(2018,5,4);
	cout<<b.LendMoney(300000,2019,1,1)<<endl;
	cout<<b.LendMoney(200001,2019,1,1)<<endl;
}
