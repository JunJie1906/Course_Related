#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
    
int main()
{
	int arr[12] = {35,146,57,13,224,35,99,68,113,79,88,46};
	int sum =0;
	for(int i=0;i<12;i++)
	{
		sum+=arr[i]/70+1;
	}
	cout<<sum/10<<endl;
}
