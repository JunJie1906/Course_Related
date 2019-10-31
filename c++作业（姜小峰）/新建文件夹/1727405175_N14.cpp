#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

void Insert(int arr[10],int num)
{
	if(num>=arr[8])
	{
		arr[9] = num;
		return;
	}
	if(num<=arr[0])
	{
		for(int i=9;i>0;i--)
		{
			arr[i] = arr[i-1];
		}
		arr[0] = num;
		return;
	}
	for(int i=0;i<9;i++)
	{
		if(num>=arr[i]&&num<=arr[i+1])
		{
			for(int j=9;j>i+1;j--)
			{
				arr[j] = arr[j-1];
			}
			arr[i+1] = num;
			return;
		}
	}
}


int main()
{
	int arr[10] = {13,24,35,46,57,35,79,35,93};
	int num;
	cin>>num;
	Insert(arr,num);
	for(int i=0;i<10;i++)
	{
		cout<<arr[i]<<" ";
	}cout<<endl;
	int arr1[10];
	arr1[0] = arr[0];
	for(int i=0;arr[i];i++)
	{
		int flag = 0;
		for(int j=0;arr1[j];j++)
		{
			if(arr[i] == arr1[j])
			{
				flag = 1;
			}
		}
		if(flag == 0)
		{
			arr1[i] = arr[i];
		}
		if(flag==1)
		{
			arr1[i] = -1;
		}
	}
	for(int i=0;i<10;i++)
	{
		if(arr1[i] != -1)
		{
			cout<<arr1[i]<<" ";
		}
	}cout<<endl;
	
}
