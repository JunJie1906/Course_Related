#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
    
int InverseBits(int Num)
{
	int i,final;
	i=0;
	final = 0;
	int result[100];
	while(Num)
	{
		result[i] = Num%10;
		Num/=10;
		i++;
	}
	for(int j =0;j!=i;j++)
	{
		final = final*10+result[j];
	}
	return final;
}

int main()
{
	int Num;
	cin>>Num;
	cout<<InverseBits(Num)<<endl;;

}
