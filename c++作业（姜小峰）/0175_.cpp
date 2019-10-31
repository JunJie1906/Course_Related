// 0175.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

////////////////////E01

//int main()
//{
//	int a,max,min,sum;
//	sum = 0;
//	for(int i=0;i<3;i++)
//	{
//		cin>>a;
//		if(i==0)
//		{
//			max = a;
//			min=a;
//			
//		}
//		if(max<a)
//		{
//			max = a;
//		}
//		if(min>a)
//		{
//			min = a;
//		}
//		sum+=a;
//	}
//	double aver;
//	aver = (double)sum / 3;
//	printf("平均值为：%-8.4f\n",aver);
//	printf("最大值为：%6d\n最小值为：%6d\n",max,min);
//}
///////////E02

//int main()
//{
//	char a;
//	cin>>a;
//	if(a >='a'&&a<='z')
//	{
//		a-=32;
//		cout<<a<<endl;
//		return 0;
//	}
//	if(a>='A'&&a<='Z')
//	{
//		a += 32;
//		cout<<a<<endl;
//		return 0;
//	}
//	cout<<a<<endl;
//}



///////////////////////////////E03

//int DateNum(int month)
//{
//	switch(month)
//	{
//	case 1:
//	case 3:
//	case 5:
//	case 7:
//	case 8:
//	case 10:
//	case 12:
//		return 31;
//	case 4:
//	case 6:
//	case 9:
//	case 11:
//		return 30;
//	case 2:return 28;
//
//	default :cout<<"error\n"<<endl;
//	}
//}
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//
//	int month,date;  
//	cin>>month>>date;
//
//	int sum = 0;
//	for(int i=2;i<=month;i++)
//	{
//		
//		sum +=DateNum(month);
//	}
//	sum+=date;
//	sum--;
//	sum = sum%7;
//	if(sum==0)
//	{
//		cout<<"今天是周日"<<endl;
//		return 0;
//	}
//	if(sum==1)
//	{
//		cout<<"今天是周一"<<endl;
//		return 0;
//	}
//	if(sum==2)
//	{
//		cout<<"今天是周二"<<endl;
//		return 0;
//	}
//	if(sum==3)
//	{
//		cout<<"今天是周三"<<endl;
//		return 0;
//	}
//	if(sum==4)
//	{
//		cout<<"今天是周四"<<endl;
//		return 0;
//	}
//	if(sum==5)
//	{
//		cout<<"今天是周五"<<endl;
//		return 0;
//	}
//	if(sum==6)
//	{
//		cout<<"今天是周六"<<endl;
//		return 0;
//	}
//
//
//}

////////////////////////E04


//#define PI 3.1415926
//
//int main()
//{
//	int r,h,sum,aver;
//	sum = 20000;
//	cout<<"please input r: ";
//	cin>>r;
//	cout<<endl;
//	cout<<"please input h: ";
//	cin>>h;
//	cout<<endl;
//	aver = (sum/(PI*r*r*h))+1;
//	cout<<"The elephent need : "<<aver<<endl;
//
//	return 0;
//}

///////////E05

//int main()
//{
//	int x,t1;
//	double v1,v2;
//	v1 = 3.0;
//	v2 = 1.2;
//	t1 = 27+23;
//	cin>>x;
//	if((x/v1)+t1>(x/v2))
//	{
//		cout<<"步行快"<<endl;
//		return 0;
//	}
//	cout<<"骑车快"<<endl;
//}



////////////E06

//int main()
//{
//	char a;
//	int count;
//	count = 1;
//	for(int i=32;i<=126;i++)
//	{
//		a = i;
//		cout<<a;
//		if(count %5==0)
//		{
//			cout<<endl;
//		}
//		count++;
//	}
//
//}


///////////E07


//int Get(int num,int count,int sum,int a)
//{
//	
//	if(count==1)
//	{
//		return sum;
//	}
//	count--;
//	num=num*10+a;
//	sum+=num;
//	Get(num,count,sum,a);
//}
//
//
//int main()
//{
//	int sum,a,n;
//	cin>>a>>n;
//	sum = 0;
//	cout<<Get(a,n,0,a)+a<<endl;
//	return 0;
//}


//////////E08


//int main()
//{
//	int N,k;
//	int NowMoney,NowHouse;
//	cin>>N>>k;
//	NowHouse = 200;
//	NowMoney = 0;
//	for(int i=0;i<20;i++)
//	{
//		NowMoney+=N;
//		NowHouse*=(1+k/100);
//		if(NowMoney>=NowHouse)
//		{
//			cout<<i+1<<endl;
//			return 0;
//		}
//	}
//	cout<<"Impossible"<<endl;
//}


//////////////E09


//int main()
//{
//	for(int k=0;k<100;k++)
//	{
//		for(int j=0;j<33;j++)
//		{
//			for(int i=0;i<20;i++)
//			{
//				if(k*3+j+i==100 )
//				{
//					if(k+i*5+j*3==100)
//					{
//						cout<<i<<"  "<<j<<"  "<<k*3<<endl;
//						
//					}
//				}
//
//			}
//		}
//	}
//
//}

/////////////E10
//#define MAXN 100
//int main()
//{
//	int n,sum,count;
//	cin>>n;
//	sum = 0;
//	count = 0;
//	for(int i=1;i<MAXN;i++)
//	{
//		for(int j=0;j<i;j++)
//		{
//			sum+=i;
//			count++;
//			if(count==n)
//			{
//				cout<<sum<<endl;
//				return 0;
//			}
//		}
//	}
//}

//////////E11



//int main()
//{
//	int max,min,sum;
//	sum =0;
//	int a[10];
//	for(int i=0;i<10;i++)
//	{
//		int ran;
//		ran = (rand()%(100-10))+10;
//		a[i]=ran;
//		if(i==0)
//		{
//			max = ran;
//			min=ran;
//		}
//		if(max<ran)
//		{
//			max = ran;
//		}
//		if(min>ran)
//		{
//			min = ran;
//		}
//		sum+=ran;
//	}
//	
//	cout<<max<<"  "<<min<<"  "<<sum/10<<endl;
//	
//
//}


////////E12
//void Print(int count[26],char alpha1[26])
//{
//	int n =0;
//	int max = count[0];
//	for(int j=0;j<26;j++)
//	{
//		if(max<count[j])
//		{
//			max = count[j];
//			n = j;
//		}
//	}
//	if(max==0)
//	{
//		return;
//	}
//
//	count[n] = 0;
//	cout<<alpha1[n]<<max<<endl;
//	Print(count,alpha1);
//
//}
//
//
//
//int main()
//{
//	int count[26] ={0};
//	char s[200];
//	cin>>s;
//	char alpha[26];
//	int i = 0;
//	int ct = 26;
//	char a = 'z';
//	while(ct)
//	{
//		alpha[ct-1] = a;
//		a--;
//		ct--;
//	}
//	while(s[i])
//	{
//
//		if(s[i]>='A'&&s[i]<='Z')
//		{
//			s[i]=s[i]+32;
//		}
//		for(int k =0;k<26;k++)
//		{
//			if(s[i]==alpha[k])
//			{
//				count[k]+=1;
//			}
//		}
//		i++;
//	}
//	Print(count,alpha);
//	return 0;
//}

//////////////E13

//int main()
//{
//	int arr[12] = {35,146,57,13,224,35,99,68,113,79,88,46};
//	int sum =0;
//	for(int i=0;i<12;i++)
//	{
//		sum+=arr[i]/70+1;
//	}
//	cout<<sum/10<<endl;
//}

////////////E14

int main()
{
	int arr[10] = {13,24,35,46,57,35,79,35,93};
	int num;
	cin>>num;
}









