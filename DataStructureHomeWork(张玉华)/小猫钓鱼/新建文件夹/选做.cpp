/*���ַ���source�����ν���һ����ʼΪ�յ�ջ������ջ�Ĺ����п��Գ�ջ��
�õ�һ����ջ�ַ���dest����Ƴ��򣬸������п��ܵ���ջ��ջ�Ĺ��̡�
������ջ��i��ʾ����ջ��o��ʾ��
�磺
sourceΪ��balama
destΪ��balama
�����Ϊ��
i o i i i o o i i o o o 
i o i i i o o o i o i o 
i o i o i o i i i o o o 
i o i o i o i o i o i o 

sourceΪ��value
destΪ��lvaeu
�����Ϊ��
�������*/ 



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
		cout << "�������" << endl;
	return 0;
}

