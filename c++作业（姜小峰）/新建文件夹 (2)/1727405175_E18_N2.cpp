#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;


void isPrime(int num)
{
	cout<<2<<"  ";
	int count = 1;
	
	for(int i=3;i<=num;i++)
	{
		int flag = 1;
		for(int j=2;j<((i/2)+1);j++)
		{
			if(i%j==0)
			{
				flag = 0;
				
			}
		}
		if(flag==1)
		{
			cout<<i<<"  ";
			count++;
			if(count%8==0)
			{
				cout<<endl;
			}
		}

	}
}
int main()
{
	isPrime(1000);
}
