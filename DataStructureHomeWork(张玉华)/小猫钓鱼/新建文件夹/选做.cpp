/*设字符串source，依次进入一个初始为空的栈，在入栈的过程中可以出栈，
得到一个出栈字符串dest。设计程序，给出所有可能的入栈出栈的过程。
假设入栈用i表示，出栈用o表示。
如：
source为：balama
dest为：balama
则输出为：
i o i i i o o i i o o o 
i o i i i o o o i o i o 
i o i o i o i i i o o o 
i o i o i o i o i o i o 

source为：value
dest为：lvaeu
则输出为：
输入错误*/ 



#include <iostream>
#include <stack>
#include <string>
#include<cstring>
 
using namespace std;


class ioStack
{
	private:
		string source,dest,crt;
		stack<char> S;
		int lenS,lenD;
		bool right;
		int ans[10000];
	public:
		ioStack()
		{
			memset(ans,0,sizeof(ans));
			
		}
		
		bool isRight()
		{
			return right;
		}
		
		void input()
		{
			cout<<"please input source : ";
			cin>>source;
			cout<<"please input dest : ";
			cin>>dest;
			crt = dest;
			right = false;
			lenS = source.length();
			lenD = dest.length();
		}
		
		void solve(int i,int j,int k)
		{
			if(j==lenD&&dest == crt)
			{

				right = true;
				for(int i=0;i<lenD*2;i++)
				{
					if(ans[i]==0)
					{
						cout<<"o ";
					}
					if(ans[i]==1)
					{
						cout<<"i ";
					}
				}
				cout<<endl;
				
			}
			
			if(i<lenS)
			{
				S.push(source[i]);
				ans[k] = 1;
				solve(i+1,j,k+1);
				S.pop();
			}
			
			if(!S.empty())
			{
				char tp;
				tp = S.top();
				crt[j] = tp;
				S.pop();
				ans[k] = 0;
				solve(i,j+1,k+1);
				S.push(tp);
			}
			
		}	
		
};

 
int main()
{
	ioStack q;
	q.input();
	q.solve(0,0,0);
	if (!q.isRight())
		cout << "输入错误！" << endl;
	return 0;
}

