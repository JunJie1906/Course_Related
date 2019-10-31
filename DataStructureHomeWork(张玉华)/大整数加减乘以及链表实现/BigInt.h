#include<cstdio>
#include<cstdlib>
#include<stdio.h> 
#include"DoubleLinkList.cpp"
#include<string>




class BigInt
{
	private:
		DoubleLink<int> num;
		bool op;
		string inp;
	public:
		
		BigInt(string a);
		~BigInt() {}
		BigInt& operator=(const BigInt &n);
		void Change();
		BigInt abs()const;
		bool isEmpty() const;
		friend BigInt operator +(const BigInt& a,const  BigInt& b);
		friend BigInt operator -(const BigInt& a,const  BigInt& b);
		friend BigInt operator *(const BigInt& a,const  BigInt& b);
		friend bool operator >(const BigInt &a,const BigInt &b);
		friend bool operator <(const BigInt &a,const BigInt &b);
		friend bool operator ==(const BigInt &a,const BigInt &b);
		void print(); 
	
		
};







