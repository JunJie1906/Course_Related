#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
#include<string>
using namespace std;

void printOut(int num)
{
	printf("%10d\n",num);
}

void printOut(double num)
{
	printf("%10.4f\n",num);
}

void printOut(string str)
{
	cout<<fixed<<setw(10)<<str<<endl;
}

int main()
{
	int num1 = 12345;
	double num2 = 123.45;
	string s = "Hello";
	
	printOut(num1);
	printOut(num2);
	printOut(s);
}
