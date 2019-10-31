#include<iostream>
#include<stack>
#include<queue> 
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;


//����ͼ �����· 

const int M = 1000;

const long long INF = 10000;



int Dis[M];      //�����i��������С��·�� 
int V[M];         //�Ѿ��߹��ľ��������·�Ľ�� 
int Matrix[M][M];  //��ϵ���󣬴洢i��j�ıߵ�Ȩֵ�����û�б������INF 



void InputMatrix(int n)  //nΪ���� 
{
	memset(Dis,INF,sizeof(Dis));
	memset(Matrix,0,sizeof(Matrix));
	memset(V,0,sizeof(V));
	
	int i,j,weight;
	for(int p=0;p<n;p++)  //����ÿ���ߵ� i ��j �� weight 
	{
		cout<<"������� "<<p<<" ���ߵ�i,j,weight"<<endl;
		cin>>i>>j>>weight;
		Matrix[i][j] = weight;
		Matrix[j][i] = weight;
	}
}

/*priority_queue<>�Զ����÷�*/
struct compare 
{
	bool operator()(const int l, const int r) 
	{
		return Dis[l] > Dis[r];
	}
};


void dijkstra(int n,int begin,int end)  // nΪ������begin Ϊ��ʼ�㣬end Ϊ�յ� 
{
	
	priority_queue<int,vector<int>,compare> q; 
	
	q.push(begin);
	V[begin] = 1;
	Dis[begin] = 0;
	while(!q.empty())
	{
		int tmp = q.top();
		V[tmp] = 1;
		q.pop();   
		for(int i=0;i<n;i++)
		{
			if(Matrix[tmp][i]!=0&&V[i]==0)
			{
				q.push(i);
				if(Dis[i] > Matrix[tmp][i] + Dis[tmp])
				{
					Dis[i] = Matrix[tmp][i] + Dis[tmp];
				}
				
			}
			
		}
	}
	cout<<"��"<<end<<"�����·��Ϊ"<<Dis[end]<<endl;
	
	
	
	
}


int main()
{
	InputMatrix(9); 
	dijkstra(5,0,3);
}



/*
2 3 1
0 2 20
0 4 20
0 1 5
5 4 3
4 2 1
1 2 1
3 1 8
5 3 6
*/





