#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
    
int main()
{
	int N,k;
	int NowMoney,NowHouse;
	cin>>N>>k;
	NowHouse = 200;
	NowMoney = 0;
	for(int i=0;i<20;i++)
	{
		NowMoney+=N;
		NowHouse*=(1+k/100);
		if(NowMoney>=NowHouse)
		{
			cout<<i+1<<endl;
			return 0;
		}
	}
	cout<<"Impossible"<<endl;
}
