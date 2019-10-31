#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
	int max,min,sum;
	sum =0;
	int a[10];
	for(int i=0;i<10;i++)
	{
		int ran;
		ran = (rand()%(100-10))+10;
		a[i]=ran;
		if(i==0)
		{
			max = ran;
			min=ran;
		}
		if(max<ran)
		{
			max = ran;
		}
		if(min>ran)
		{
			min = ran;
		}
		sum+=ran;
	}

	cout<<max<<"  "<<min<<"  "<<sum/10<<endl;


}
