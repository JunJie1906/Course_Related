#include<iostream>
#include<stack>
#include<queue> 
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;


//无向图 求最短路 

const int M = 1000;

const long long INF = 10000;



int Dis[M];      //到达第i个结点的最小的路径 
int V[M];         //已经走过的绝对是最短路的结点 
int Matrix[M][M];  //关系矩阵，存储i到j的边的权值，如果没有边则等于INF 



void InputMatrix(int n)  //n为边数 
{
	memset(Dis,INF,sizeof(Dis));
	memset(Matrix,0,sizeof(Matrix));
	memset(V,0,sizeof(V));
	
	int i,j,weight;
	for(int p=0;p<n;p++)  //输入每条边的 i ，j ， weight 
	{
		cout<<"请输入第 "<<p<<" 条边的i,j,weight"<<endl;
		cin>>i>>j>>weight;
		Matrix[i][j] = weight;
		Matrix[j][i] = weight;
	}
}

/*priority_queue<>自定义用法*/
struct compare 
{
	bool operator()(const int l, const int r) 
	{
		return Dis[l] > Dis[r];
	}
};


void dijkstra(int n,int begin,int end)  // n为点数，begin 为起始点，end 为终点 
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
	cout<<"到"<<end<<"的最短路径为"<<Dis[end]<<endl;
	
	
	
	
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





