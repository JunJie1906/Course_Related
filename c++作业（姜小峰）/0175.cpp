#include "stdafx.h"
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
    
int main()
{
	int a,max,min,sum;
	sum = 0;
	for(int i=0;i<3;i++)
	{
		cin>>a;
		if(i==0)
		{
			max = a;
			min=a;
			
		}
		if(max<a)
		{
			max = a;
		}
		if(min>a)
		{
			min = a;
		}
		sum+=a;
	}
	double aver;
	aver = (double)sum / 3;
	printf("ƽ��ֵΪ��%-8.4f\n",aver);
	printf("���ֵΪ��%6d\n��СֵΪ��%6d\n",max,min);
}
