#include<iostream>
#include<string>
#include<cstdio>
#include<cmath>

using namespace std;

class CComplex
{
	double m_real;
	double m_image;
public:
	void setValue(double real,double image)
	{
		m_real = real;
		m_image = image;
	}

	friend ostream &operator<<(ostream &o,const CComplex &c)   // overload  operator  <<
	{
		return o<<c.m_real<<"+"<<c.m_image<<"*i";
	}

	friend CComplex operator+(const CComplex &a,const CComplex &b) // overload  operator  a+b
	{
		CComplex s;
		s.setValue(a.m_real+b.m_real,a.m_image+b.m_image);
		return s;
	}

	friend CComplex operator+(const int a,const CComplex &b) // int + complex
	{
		CComplex s;
		s.setValue(a+b.m_real,b.m_image);
		return s;
	}

	friend CComplex operator+(const CComplex &a,const int b)  // complex + int 
	{
		CComplex s;
		s.setValue(a.m_real+b,a.m_image);
		return s;
	}

	friend CComplex operator++(CComplex &a,int) // overload  operator  a++
	{
		CComplex t(a);
		a.m_real++;
		a.m_image++;
		return t;
	}

	friend CComplex &operator++(CComplex &a) // overload  operator  ++a
	{
		a.m_real++;
		a.m_image++;
		return a;
	}


};


int main()
{
	CComplex p,q;
	p.setValue(10,9);
	q.setValue(33,44);
	cout<<"p: "<<p<<endl;
	cout<<"q: "<<q<<endl;
	cout<<"p+100 : "<<p+100<<endl;
	cout<<"p+q : "<<p+q<<endl;

	cout<<"++p: "<<++p<<endl;
	cout<<"p++: "<<p++<<endl;
	cout<<"p: "<<p<<endl;
}
