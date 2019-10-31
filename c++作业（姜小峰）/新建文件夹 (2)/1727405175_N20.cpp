#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
    
void Calc(int Num1,int Num2,int &GCD,int &LCM)
{
	int max,min;
	if(Num1>=Num2)
	{
		max = Num1;
		min = Num2;
	}
	else
	{
		max = Num2;
		min = Num1;
	 } 
	 if(min==1||max==1)
	 {
	 	GCD = 1;
	 	LCM = max;
	 	return;
	 }
	for(int i=min;i>=2;i--)
	{
		if(Num1%i==0&&Num2%i==0)
		{
			GCD = i;
			break;
		}
	}
	for(int i = max;i;i++)
	{
		if(i%Num1==0&&i%Num2==0)
		{
			LCM = i;
			break;
		}
	}
	
}

int main()
{
	int num1,num2,GCD,LCM;
	cin>>num1>>num2;
	Calc(num1,num2,GCD,LCM);
	cout<<GCD<<" "<<LCM<<endl;
}


