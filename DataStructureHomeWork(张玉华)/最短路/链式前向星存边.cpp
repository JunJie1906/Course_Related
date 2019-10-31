#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<string.h>

#define ll long long 

using namespace std;

const ll Max=10000;

struct Edge
{
	int val;
	int to; // �����ߵ��յ� 
	int next; //ͬһ����������һ���ߵ�λ�� 
};

Edge E[Max*Max]; //�ߵ���ţ�ͨ��head[i]��������i��������ӵ������ E[head[i]] �ߣ��õ������ߵ��յ㣬Ȩֵ������˱߳�������������һ���� 

int head[Max]; //head[i]��ʾ���i����������������һ���ߵ���� ������һ����ʱ����м�ֵ���飬������ͬһ�����������һ���ߵ���E[]����� 

static int count; //��ʾ�ߵ���ţ�������˳���1 ��ʾ�ߵ���� 

void Init()
{
	memset(head,-1,sizeof(head));
	count = 0;
}

void Add(int i,int j,int val)  //��i������j�ıߣ�ȨֵΪval 
{
	E[count].val = val;
	E[count].next = head[i];
	E[count].to = j;
	head[i] = count++;
}

void ShowEdge(int num) //������ĸ��� 
{
	int cnt = 1; 
	for(int i=0;i<num;i++)
	{
		if(head[i]!=-1)
		{
			int crt = head[i];
			while(E[crt].next != -1)
			{
				cout<<"��"<<cnt++<<"���ߣ��ӽ�� "<<i<<" ����� "<<E[crt].to<<" ȨֵΪ�� "<<E[crt].val<<endl;
				crt = E[crt].next;
			}
			cout<<"��"<<cnt++<<"���ߣ��ӽ�� "<<i<<" ����� "<<E[crt].to<<" ȨֵΪ�� "<<E[crt].val<<endl;
		}
	 } 
	
}



int main()
{
	int len,num;
	cout<<"��������ĸ�����";
	cin>>len;
	cout<<endl;
	cout<<"������ߵĸ�����";
	cin>>num;
	Init();
	for(int i=0;i<num;i++)
	{
		int p,q,val;
		cout<<"�������"<<i+1<<"���ߵ� i, j, val"<<endl;
		cin>>p>>q>>val;
		cout<<endl;
		Add(p,q,val);
		Add(q,p,val);
	}
	
	ShowEdge(num);
	
}

/*
6 
8

1 4 3
1 0 6
4 0 5
0 2 7
0 3 8
2 3 3
0 5 4
3 5 2



*/





