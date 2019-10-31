#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;




void Quick_Sort(int Num[],int l,int r)
{
	if(l>=r) return;
	
	int crt = Num[l];
	
	int i=l,j = r;
	
	while(i<j)
	{
		while(Num[j]>=crt&&i<j)
		{
			j--;
		}
		Num[i] = Num[j];
		
		while(Num[i]<crt&&i<j)
		{
			i++;
		}
		Num[j] = Num[i];
	}
	Num[i] = crt;
	Quick_Sort(Num,l,j-1);
	Quick_Sort(Num,j+1,r);
}


void Merge(int num[],int temp[],int low,int mid,int high)  //合并两个有序数组
{
	int len = high - mid;
	for(int p=0;p<len;p++)
	{
		temp[p] = num[mid+p+1];
	}

	int i=low;
	int j = 0;
	while(i<=mid&&j<len)
	{
		while(num[j] >num[i]&&i<=mid) i++;
		swap(num[i],num[j+mid+1]);
		j++;
	}
}

void Merge_Sort(int num[],int Crt[],int low,int high) // 从low到high 用归并排序从大到小排列
{
	if(low>high)
	{
		int mid = (low+high)/2;
	
		Merge_Sort(num,Crt,low,mid);
		Merge_Sort(num,Crt,mid+1,high);
		Merge(num,Crt,low,mid,high);
	}

}

void MergeSort(int num[],int m,int n)  //只new一次Crt[] 然后重复利用已经new出来的crt，提高空间利用效率，以免重复new，delete()浪费不必要的时间 
{
	int *Crt = new int[n-m+1];

	Merge_Sort(num,Crt,m,n);
	delete(Crt);
}





void SelectionSort(int num[],int low,int high)
{
	int Min,crt;
	crt = low;
	int i = low;
	while(i<=high)
	{
		Min = i;
		for(int p = i;p<=high;p++)
		{
			if(num[Min]>num[p])
			{
				Min = p;
			}
		}
		swap(num[Min],num[crt]);
		i++;
	}
}


 // 1 2 7 3 6  0 6 4 8 0 5

void InsertionSort(int num[],int low,int high)
{
	int i = low;
	while(i<=high)
	{
		for(int p=low;p<i;p++)
		{
			if(num[i]<num[p])
			{
				int crt = num[i];
				for(int m=i;m>p;m--)
				{
					num[m] = num[m-1];
				}
				num[p] = crt;
			}
		}
		i++;
	}
}




void ShallSort(int num[],int low,int high)
{
	int inc = (high-low)/2+1;

	while(inc>=1)
	{
		for(int i=0;i<inc;i++)
		{
			int n=0;
			 //(i+inc*n+low)

			while((i+inc*n+low)<=high)
			{
				for(int p=(i+low);p<=(i+inc*n+low);p+=inc)
				{
					if(num[i+inc*n+low]<num[p])
					{
						int crt = num[i+inc*n+low];
						for(int m=i+inc*n+low;m>p;m-=inc)
						{
							num[m] = num[m-inc];
						}
						num[p] = crt;
					}
				}
				n++;
			}
		}
		inc = inc/3;  //增量
	}
}


  

void MaxHeap(int num[],int i,int j) 
{
	int dad = i,son = dad*2+1;
	while(son<=j)
	{
		if(son+1<=j&&num[son]<num[son+1])
		{
			son++;
		}
		if(num[dad]>=num[son]) return;
		
		swap(num[dad],num[son]);
		dad = son;
		son = dad*2+1;
	}
}


void MinHeap(int num[],int i,int j) 
{
	int dad = i,son = dad*2+1;
	while(son<=j)
	{
		if(son+1<=j&&num[son]>num[son+1])
		{
			son++;
		}
		if(num[dad]<=num[son]) return;
		
		swap(num[dad],num[son]);
		dad = son;
		son = dad*2+1;
	}
}




void HeapSort(int num[],int len,bool iff = true)
{
	if(iff)
	{
		for(int i=len/2-1;i>=0;i--)
		{
			MaxHeap(num,i,len-1);
		}
		
		for(int i=len-1;i>0;i--)
		{
			swap(num[i],num[0]);
			MaxHeap(num,0,i-1);
		}
	}
	else
	{
		for(int i=len/2-1;i>=0;i--)
		{
			MinHeap(num,i,len-1);
		}
		
		for(int i=len-1;i>0;i--)
		{
			swap(num[i],num[0]);
			MinHeap(num,0,i-1);
		}
	}

}








int main()
{

	int num[1000];
	for(int i=10;i>=0;i--)
	{
		num[i] = i;
	}
	
	
	for(int i=0;i<10;i++)
	{
		cout<<num[i]<<" ";
	}
	cout<<endl;
	
	MergeSort(num,0,9);
	
	for(int i=0;i<10;i++)
	{
		cout<<num[i]<<" ";
	}
	
	system("pause");
}
