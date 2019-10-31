
#include<iostream>
#include<stack>
#include<queue> 
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;

const int M = 1000;

const long long INF = 10000;


int Board[M][M];  // 棋盘

static int Count,COUNT,MIN,MAX;
int V[M][M];         //已经走过的结点 



void Init()
{
	memset(Board,0,sizeof(Board));
	memset(V,0,sizeof(V));
	V[0][0] = 1;
	Count = 0;
	COUNT=0;
	MAX = 0;
	MIN = 100000000;
}

void Input_auto(int len) //矩阵的宽
{
	
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len;j++)
		{
			int a = rand();
			if(a<17600)
			{
				Board[i][j]=1;
			}
		}
	}
	Board[len-1][len-1] = 0;
	Board[0][0] = 0;
}

void InputByPoint()
{
	int n;
	cout<<"请输入1的个数: "<<endl;
	cin>>n;
	cout<<"输入每个边的坐标："<<endl;
	while(n--)
	{
		int a,b;
		cin>>a>>b;
		Board[a][b] = 1;
	}
}

void InPut()
/*
0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  0
0  1  0  1  1  1  1  1  1  0
0  1  1  0  1  1  1  1  1  0
0  1  1  1  0  1  1  1  1  0
0  1  1  1  1  0  1  1  1  0
0  1  1  1  1  1  0  1  1  0
0  1  1  1  1  1  1  0  1  0
0  1  1  1  1  1  1  1  0  0
0  0  0  0  0  0  0  0  0  0
*/ 
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
			Board[i][j] = 1;
	}
	for(int i=0;i<10;i++)
	{
		
		Board[0][i] = 0;
		Board[i][0] = 0;
		Board[i][i] = 0;
		Board[9][i] = 0;
		Board[i][9] = 0;
					
	}

}


void Move(stack<int> &a,stack<int> &b,int target)//坐标为a，b的点 边的长度
{
	
	if(a.top()==(target-1)&&b.top()==(target-1))
	{
		
		COUNT++;
		stack<int> cura,curb;
		while(!a.empty())
		{
			cura.push(a.top());
			curb.push(b.top());
			a.pop();
			b.pop();
			Count++;
		}
	//	cout<<"到达目的地, 长度为 "<<Count<<endl;
		while(!cura.empty())
		{
	//		cout<<" ("<<cura.top()<<" , " <<curb.top()<<")";
			a.push(cura.top());
			b.push(curb.top());
			cura.pop();
			curb.pop();
		}
		if(Count>MAX) MAX = Count;
		if(Count < MIN) MIN = Count;

	//	cout<<endl;
	//	cout<<"========================================================="<<endl;
		Count=0;
		
		return;
	}

	bool Exit = false;

	for(int i=1;i>-2;i--)
	{
		for(int j=1;j>-2;j--)
		{
			if(i==0&&j==0) continue;
			else
			{
				if(i+a.top()>=0&&i+a.top()<target&&j+b.top()>=0&&j+b.top()<target&&Board[i+a.top()][j+b.top()]==0&&V[i+a.top()][j+b.top()]==0)
				{
					Exit = true;
					bool Get = false;
					V[i+a.top()][j+b.top()] = 1;
					a.push(a.top()+i);
					b.push(b.top()+j);
					Move(a,b,target);
					a.pop();
					b.pop();
					V[i+a.top()][j+b.top()] = 0;
				}
			}
		}
	}
	
}














int main()
{
	Init();
	Input_auto(10);
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			cout<<Board[j][i]<<"  ";
		}
		cout<<endl;
	}

	stack<int> a,b;
	a.push(0);
	b.push(0);
	Move(a,b,10);


	

	cout<<"一共有"<<COUNT<<"种走法"<<endl;
	cout<<"最短路径为："<<MIN<<endl;
	cout<<"最长路径为："<<MAX<<endl;
}







