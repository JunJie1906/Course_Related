#include<stack>
#include<queue>
#include<iostream>
#include<string.h>

using namespace std;


class Cat
{
	private:
		int Play[110];
		queue<int> p1;
		queue<int> p2;
		int i ;
		
	public:
		Cat()
		{
			i=0;
			memset(Play,0,sizeof(Play));
		}
		
		
		void Input()
		{
			int a;
			int n;
			cout<<"输入手牌数目："<<endl;
			cin>>n;
			cout<<"输入第一个的牌："<<endl;
			for(int i =0;i<n;i++)
			{
				
				cin>>a;
				p1.push(a);
			}
			cout<<"输入第二个的牌："<<endl;
			for(int i =0;i<n;i++)
			{
				cin>>a;
				p2.push(a);
			}

			
		}

		void showP1()
		{
			queue<int> crt;
			cout<<"p1: ";
			while(!p1.empty())
			{
				crt.push(p1.front());
				cout<<p1.front()<<"  ";
				p1.pop();
				
			}
			cout<<endl;
			while(!crt.empty())
			{
				p1.push(crt.front());
				crt.pop();
				
			}
		}


		void showP2()
		{
			queue<int> crt;
			cout<<"p2: ";
			while(!p2.empty())
			{
				crt.push(p2.front());
				cout<<p2.front()<<"  ";
				p2.pop();
				
			}
			cout<<endl;
			while(!crt.empty())
			{
				p2.push(crt.front());
				crt.pop();
				
			}
		}
		
		
		bool P1Put()
		{
			cout<<endl;
			cout<<"Player 1 Play: "<<endl;
			showplay();
			showP1();
			showP2();
			
			int j = i-1;
			int front;
			if(!p1.empty())
			{
				front = p1.front();
				p1.pop();
			}
			else
			{
				cout<<"p1 lose "<<endl;
				return false;
			}
			
			if(i==0)        //栈空 
			{
			
				Play[0]=front;
				i++;
				return true;
			}
			else
			{
				while(Play[j]!=front&&j>=0)
				{
					j--;
				}
				if(j>=0)
				{
					for(int u = j;u<i;u++)
					{
						p1.push(Play[u]);
						i--;
					}
					p1.push(front);
					P1Put();
				}
				else
				{
					Play[i]=front;
					i++;
					return true;
				}
			}
		}
		
		
		
		bool P2Put()
		{
			cout<<endl;
			cout<<"Player 2 Play: "<<endl;
			showplay();
			showP1();
			showP2();
			int j = i-1;
			int front ;
			if(!p2.empty())
			{
				front = p2.front();
				p2.pop();
			}
			else
			{
				cout<<"p2 lose "<<endl;
				return false;
			}
			
			if(i==0)        //栈空 
			{
			
				Play[0]=front;
				i++;
				return true;
			}
			else
			{
				while(Play[j]!=front&&j>=0)
				{
					j--;
				}
				if(j>=0)
				{
					for(int u = j;u<i;u++)
					{
						p2.push(Play[u]);
						i--;
					}
					
					p2.push(front);
					P2Put();
					
				}
				else
				{
					Play[i]=front;
					i++;
					return true;
				}
			}
		}
		
		
		void play()
		{
			cout<<"again"<<endl;
			Input();
			bool flag = true;
			while(flag)
			{
				flag = P1Put();
				if(!flag)
				{
					break;
				}
				flag = P2Put();
			}
		}
		
		void showplay()
		{
			cout<<"Play: ";
			for(int q=0;q<i;q++)
			{
				cout<<Play[q]<<" ";
			}
			cout<<endl;
		}
		
		
};


int main()
{
	Cat p;
	p.play();
}




 
