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
	int to; // 这条边的终点 
	int next; //同一个起点的另外一条边的位置 
};

Edge E[Max*Max]; //边的序号，通过head[i]索引到第i个结点连接的最近的 E[head[i]] 边，得到这条边的终点，权值，和与此边出发点相连的下一条边 

int head[Max]; //head[i]表示与第i个结点相连的最近的一条边的序号 当加入一条边时候的中间值数组，索引到同一个起点的最近的一条边的在E[]的序号 

static int count; //表示边的序号，按输入顺序加1 表示边的序号 

void Init()
{
	memset(head,-1,sizeof(head));
	count = 0;
}

void Add(int i,int j,int val)  //从i出发到j的边，权值为val 
{
	E[count].val = val;
	E[count].next = head[i];
	E[count].to = j;
	head[i] = count++;
}

void ShowEdge(int num) //输入结点的个数 
{
	int cnt = 1; 
	for(int i=0;i<num;i++)
	{
		if(head[i]!=-1)
		{
			int crt = head[i];
			while(E[crt].next != -1)
			{
				cout<<"第"<<cnt++<<"条边：从结点 "<<i<<" 到结点 "<<E[crt].to<<" 权值为： "<<E[crt].val<<endl;
				crt = E[crt].next;
			}
			cout<<"第"<<cnt++<<"条边：从结点 "<<i<<" 到结点 "<<E[crt].to<<" 权值为： "<<E[crt].val<<endl;
		}
	 } 
	
}



int main()
{
	int len,num;
	cout<<"请输入结点的个数：";
	cin>>len;
	cout<<endl;
	cout<<"请输入边的个数：";
	cin>>num;
	Init();
	for(int i=0;i<num;i++)
	{
		int p,q,val;
		cout<<"请输入第"<<i+1<<"条边的 i, j, val"<<endl;
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





