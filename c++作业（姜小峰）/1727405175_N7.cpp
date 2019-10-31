#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
    
int Get(int num,int count,int sum,int a)
{
	
	if(count==1)
	{
		return sum;
	}
	count--;
	num=num*10+a;
	sum+=num;
	Get(num,count,sum,a);
}


int main()
{
	int sum,a,n;
	cin>>a>>n;
	sum = 0;
	cout<<Get(a,n,0,a)+a<<endl;
	return 0;
}
