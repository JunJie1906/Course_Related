#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
    
#define MAXN 100
int main()
{
	int n,sum,count;
	cin>>n;
	sum = 0;
	count = 0;
	for(int i=1;i<MAXN;i++)
	{
		for(int j=0;j<i;j++)
		{
			sum+=i;
			count++;
			if(count==n)
			{
				cout<<sum<<endl;
				return 0;
			}
		}
	}
}
