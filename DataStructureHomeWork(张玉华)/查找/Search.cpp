#include<cstdio>
#include<iostream>
#include<time.h>
#include<cstdlib>

using namespace std;

const int MAX =10000005;
int Num[MAX];

void InputNum(int N) //�ֶ�����
{
	for(int i=0;i<=N;i++)
	{
		int p;
		cin>>p;
		Num[i] = p;
	}
}

void InputNum_auto(int N)  //�Զ�����10000��(1000+N) ������
{
	for(int i=0;i<N;i++)
	{
		Num[i] = i;
	}
}

int SeqSearch_times(int target,int N)
{
	int count=N;
	
	for(int i=0;i<N;i++)
	{
		if(target==Num[i])
		{
			count = i;
			break;
		}
	}
	return count;
}

void Seq_count(int m,int n)
{
	InputNum_auto(n);

	clock_t start,finish;
	double run_time;
	start = clock();

	long long count1=0,count2 = 0,success = 0;
	for(int i=0;i<m;i++)
	{
		int p = rand();
		int times = SeqSearch_times(p,n);
		if(times==n)  //ʧ��
		{
			count2+=times;
		}
		else
		{
			success++;
			count1+=times;
		}
	}

	finish = clock();
	cout<<"˳����ң�"<<endl;
	cout<<"�ɹ����ҵĴ�����"<<success<<endl;
	run_time = (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"����"<<m<<"�����е���ʱ��Ϊ��"<<run_time<<"��"<<endl;
	if(success==0)
	{
		cout<<"δ�ɹ����ҵ�Ԫ��"<<endl; 
	}
	else 
	{
		cout<<"�ɹ�����ʱ�Ƚϵ�ƽ������: "<<(double)count1/(double)success<<endl;
	}
	if(success==m)
	{
		cout<<"δʧ�ܲ��ҵ�Ԫ��"<<endl; 
	}
	else 
	{
		cout<<"ʧ�ܲ���ʱ�Ƚϵ�ƽ������: "<<(double)count2/(double)(m-success)<<endl;
	}
	
	cout<<"===================="<<endl;

	
}

int bin_search1_rec_times(int target,int l,int r,int count)  //�ҵ�������ֵ���Ҳ������ظ�ֵ
{
	int mid = (l+r)/2;
	if(l==mid||r==mid) 
	{
		count+=1;
		if(target == Num[r]) 
		{
			count++;
			return count;
		}
		else
		{
			count++;
			return -count;
		}
	}
	if(target <= Num[mid] ) 
	{
		count++;
		return bin_search1_rec_times(target,l,mid,count+1);
	}
	else
	{
		count++;
		return bin_search1_rec_times(target,mid,r,count+1);
	}
}

int bin_search2_rec_times(int target,int l,int r,int count)  //�ҵ�������ֵ���Ҳ������ظ�ֵ
{
	int mid = (l+r)/2;
	if(Num[mid]==target) 
	{
		count+=1;
		return count;
	}
	if(l==mid||r==mid) 
	{
		count +=1;
		if(target == Num[mid]) 
		{
			count += 1;
			return count;
		}
		else
		{
			count += 1;
			return -count;
		}
	}
	if(target == Num[mid] ) 
	{
		count += 1;
		return count;
	}
	else
	{
		count += 1; 
		if(target < Num[mid])
		{
			count += 1;
			return bin_search1_rec_times(target,l,mid,count+1);
		}
		else
		{
			count += 1;
			return bin_search1_rec_times(target,mid,r,count+1);
		}
		
	}
}

void bin_search1_rec_count(int m,int n)
{
	InputNum_auto(n);

	clock_t start,finish;
	double run_time;
	start = clock();

	long long count1=0,count2 = 0,success = 0;
	for(int i=0;i<m;i++)
	{
		int p = rand();
		int times = bin_search1_rec_times(p,0,n,0);
		if(times<0)  //ʧ��
		{
			count2+=times;
		}
		else
		{
			success++;
			count1+=times;
		}
	}

	finish = clock();
	count2 = -count2;
	cout<<"���ֲ���1_�ݹ飺"<<endl;
	cout<<"�ɹ����ҵĴ�����"<<success<<endl;
	run_time = (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"����"<<m<<"�����е���ʱ��Ϊ��"<<run_time<<"��"<<endl;
	if(success==0)
	{
		cout<<"δ�ɹ����ҵ�Ԫ��"<<endl; 
	}
	else 
	{
		cout<<"�ɹ�����ʱ�Ƚϵ�ƽ������: "<<(double)count1/(double)success<<endl;
	}
	if(success==m)
	{
		cout<<"δʧ�ܲ��ҵ�Ԫ��"<<endl; 
	}
	else 
	{
		cout<<"ʧ�ܲ���ʱ�Ƚϵ�ƽ������: "<<(double)count2/(double)(m-success)<<endl;
	}
	
	cout<<"===================="<<endl;
}


void bin_search2_rec_count(int m,int n)
{
	InputNum_auto(n);

	clock_t start,finish;
	double run_time;
	start = clock();

	long long count1=0,count2 = 0,success = 0;
	for(int i=0;i<m;i++)
	{
		int p = rand();
		int times = bin_search2_rec_times(p,0,n,0);
		if(times<0)  //ʧ��
		{
			count2+=times;
		}
		else
		{
			success++;
			count1+=times;
		}
	}
	
	finish = clock();
	count2 = -count2;
	cout<<"���ֲ���2_�ݹ飺"<<endl;
	cout<<"�ɹ����ҵĴ�����"<<success<<endl;
	run_time = (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"����"<<m<<"�����е���ʱ��Ϊ��"<<run_time<<"��"<<endl;
	if(success==0)
	{
		cout<<"δ�ɹ����ҵ�Ԫ��"<<endl; 
	}
	else 
	{
		cout<<"�ɹ�����ʱ�Ƚϵ�ƽ������: "<<(double)count1/(double)success<<endl;
	}
	if(success==m)
	{
		cout<<"δʧ�ܲ��ҵ�Ԫ��"<<endl; 
	}
	else 
	{
		cout<<"ʧ�ܲ���ʱ�Ƚϵ�ƽ������: "<<(double)count2/(double)(m-success)<<endl;
	}
	
	cout<<"===================="<<endl;
}

int bin_search1_non_rec_times(int target,int l,int r)  //�ҵ�������ֵ���Ҳ������ظ�ֵ
{
	int count = 0;
	int mid = (l+r)/2;
	while(mid!=l&mid!=r)
	{
		count += 1;
		if(target <= Num[mid] ) 
		{
			count ++;
			r = mid;
		}
		else
		{
			l = mid;
			count ++;
		}
		mid = (l+r)/2;
	}

	if(target == Num[r]) 
	{
		count += 1;
		return count;
	}
	else
	{
		count += 1;
		return -count;
	}
}

int bin_search2_non_rec_times(int target,int l,int r)  //�ҵ�������ֵ���Ҳ������ظ�ֵ
{
	int count = 0;
	int mid = (l+r)/2;
	while(mid!=l&mid!=r)
	{
		count += 1;
		if(Num[mid] == target) 
		{
			count += 1;
			return count;
		}

		if(target < Num[mid] ) 
		{
			count ++;
			r = mid;
		}
		else
		{
			l = mid;
			count ++;
		}
		mid = (l+r)/2;
	}
	count++;
	if(target == Num[mid]) 
	{
		count += 1;
		return count;
	}
	else
	{
		count += 1;
		return -count;
	}
}

void bin_search1_non_rec_count(int m,int n)
{
	InputNum_auto(n);

	clock_t start,finish;
	double run_time;
	start = clock();

	long long count1=0,count2 = 0,success = 0;
	for(int i=0;i<m;i++)
	{
		int p = rand();
		int times = bin_search1_non_rec_times(p,0,n);
		if(times<0)  //ʧ��
		{
			count2+=times;
		}
		else
		{
			success++;
			count1+=times;
		}
	}
	
	finish = clock();
	count2 = -count2;
	cout<<"���ֲ���1_�ǵݹ飺"<<endl;
	cout<<"�ɹ����ҵĴ�����"<<success<<endl;
	run_time = (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"����"<<m<<"�����е���ʱ��Ϊ��"<<run_time<<"��"<<endl;
	if(success==0)
	{
		cout<<"δ�ɹ����ҵ�Ԫ��"<<endl; 
	}
	else 
	{
		cout<<"�ɹ�����ʱ�Ƚϵ�ƽ������: "<<(double)count1/(double)success<<endl;
	}
	if(success==m)
	{
		cout<<"δʧ�ܲ��ҵ�Ԫ��"<<endl; 
	}
	else 
	{
		cout<<"ʧ�ܲ���ʱ�Ƚϵ�ƽ������: "<<(double)count2/(double)(m-success)<<endl;
	}
	
	cout<<"===================="<<endl;
}


void bin_search2_non_rec_count(int m,int n)
{
	InputNum_auto(n);

	clock_t start,finish;
	double run_time;
	start = clock();

	long long count1=0,count2 = 0,success = 0;
	for(int i=0;i<m;i++)
	{
		int p = rand();
		int times = bin_search2_non_rec_times(p,0,n);
		if(times<0)  //ʧ��
		{
			count2+=times;
		}
		else
		{
			success++;
			count1+=times;
		}
	}
	
	finish = clock();
	count2 = -count2;
	cout<<"���ֲ���2_�ǵݹ飺"<<endl;
	cout<<"�ɹ����ҵĴ�����"<<success<<endl;
	run_time = (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"����"<<m<<"�����е���ʱ��Ϊ��"<<run_time<<"��"<<endl;
	if(success==0)
	{
		cout<<"δ�ɹ����ҵ�Ԫ��"<<endl; 
	}
	else 
	{
		cout<<"�ɹ�����ʱ�Ƚϵ�ƽ������: "<<(double)count1/(double)success<<endl;
	}
	if(success==m)
	{
		cout<<"δʧ�ܲ��ҵ�Ԫ��"<<endl; 
	}
	else 
	{
		cout<<"ʧ�ܲ���ʱ�Ƚϵ�ƽ������: "<<(double)count2/(double)(m-success)<<endl;
	}
	
	cout<<"===================="<<endl;
}



int main()
{
	// ����50��Σ������СΪ100 
	Seq_count(500000,100);  
	// ����500��Σ������СΪ100��
	bin_search1_non_rec_count(5000000,1000000);
	bin_search2_non_rec_count(5000000,1000000);
	bin_search1_rec_count(5000000,1000000);
	bin_search2_rec_count(5000000,1000000);
}
