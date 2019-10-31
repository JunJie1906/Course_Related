#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
	char a;
	int count;
	count = 1;
	for(int i=32;i<=126;i++)
	{
		a = i;
		cout<<a;
		if(count %5==0)
		{
			cout<<endl;
		}
		count++;
	}

}
