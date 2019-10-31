
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

struct Node
{
	int a;
	int b;
	Node(){a=0;b=0;}
};

const long long INF = 10000;

int Board[M][M];  // 棋盘

Node* LastNode[M][M];
int V[M][M];         //已经走过的结点 



void Init()
{
	memset(Board,0,sizeof(Board));
	memset(V,0,sizeof(V));
	memset(LastNode,0,sizeof(LastNode));
	V[0][0] = 1;
}

void InPut()
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

void Input_auto(int len) //矩阵的宽
{
	
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len;j++)
		{
			int a = rand();
			if(a<15000)
			{
				Board[i][j]=1;
			}
		}
	}
	Board[len-1][len-1] = 0;
}

bool Move(queue<Node*>& q,int len)
{
	bool Get = false;
	
	while(!q.empty())
	{
		if(q.front()->a==len-1&&q.front()->b==len-1)
		{
			Get = true;
			Node* p = q.front();
			cout<<" ("<<q.front()->a<<" , " <<q.front()->b<<")";
			q.pop();
			delete p;
		Node* crt = LastNode[len-1][len-1];
		while(crt->a!=0&&crt->b!=0)
		{
			cout<<",  ("<<crt->a<<" , " <<crt->b<<") ";
			crt = LastNode[crt->a][crt->b];
		}

			return true;
		}
		Node* tmp = q.front();
		for(int i=1;i>-1;i--)
		{
			for(int j=1;j>-1;j--)
			{
				if(i==0&&j==0) continue;
				else
				{
					if(i+ tmp->a>=0&&i+tmp->a<len&&j+tmp->b>=0&&j+tmp->b<len&&Board[i+tmp->a][j+tmp->b]==0&&V[i+tmp->a][j+tmp->b]==0)
					{
						Node* NewNode = new Node;
						NewNode->a = tmp->a;
						NewNode->b = tmp->b;
						LastNode[ i+ tmp->a][j+tmp->b] = NewNode;
						Node* cur = new Node;
						cur->a = i+ tmp->a;
						cur->b = j+tmp->b;
						q.push(cur);
						V[ i+ tmp->a][j+tmp->b] = 1;
					}
				}
			}
		}
		
		q.pop();
		delete tmp;
	}


	return false;
	




}



int main()
{
	 Init();
	 InPut();
	 Node* a = new Node;
	 queue<Node*> q;
	 q.push(a);
	 Move(q,10);


}
