#include "diaoyu.h"
#include<stack>
#include<queue>
#include<iostream>
#include<string.h>

using namespace std;


Cat::Cat()
{
	i=0;
	memset(Play,0,sizeof(Play));
}


void Cat::Input()
{
	int a;
	int n;
	cout<<"����������Ŀ��"<<endl;
	cin>>n;
	cout<<"�����һ�����ƣ�"<<endl;
	for(int i =0;i<n;i++)
	{
		
		cin>>a;
		p1.push(a);
	}
	cout<<"����ڶ������ƣ�"<<endl;
	for(int i =0;i<n;i++)
	{
		cin>>a;
		p2.push(a);
	}

	
}


bool Cat::P1Put()
{
	int j = i-1;
	int front;
	if(!p2.empty()&&!p1.empty())
	{
		front = p1.front();
		p1.pop();
	}
	else
	{
		if(!p1.empty())
		{
			cout<<"ʤ��ΪA��Aʣ�µ��ƴ��ϵ�������Ϊ";
			while(!p1.empty())
			{
				cout<<p1.front()<<" ";
				p1.pop();
			}
		}
		else
		{
			cout<<"ʤ��ΪB��Bʣ�µ��ƴ��ϵ�������Ϊ";
			while(!p2.empty())
			{
				cout<<p2.front()<<" ";
				p2.pop();
			}
			cout<<endl;
		}
		return false;
	}
	
	if(i==0)        //ջ�� 
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
			p1.push(front);
			int cnt=0;
			for(int u = i-1;u>=j;u--)
			{
				p1.push(Play[u]);
				cnt++;
			}
			i-=cnt;
			return true;
			
		}
		else
		{
			Play[i]=front;
			i++;
			return true;
		}
	}
}



bool Cat::P2Put()
{


	int j = i-1;
	int front ;
	if(!p2.empty()&&!p1.empty())
	{
		front = p2.front();
		p2.pop();
	}
	else
	{
		if(!p1.empty())
		{
			cout<<"ʤ��ΪA��Aʣ�µ��ƴ��ϵ�������Ϊ";
			while(!p1.empty())
			{
				cout<<p1.front()<<" ";
				p1.pop();
			}
		}
		else
		{
			cout<<"ʤ��ΪB��Bʣ�µ��ƴ��ϵ�������Ϊ";
			while(!p2.empty())
			{
				cout<<p2.front()<<" ";
				p2.pop();
			}
			cout<<endl;
		}
		return false;
	}
	
	if(i==0)        //ջ�� 
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
			p2.push(front);
			int cnt=0;
			for(int u = i-1;u>=j;u--)
			{
				p2.push(Play[u]);
				cnt++;
			}
			i-=cnt;
			return true;
			
			
		}
		else
		{
			Play[i]=front;
			i++;
			return true;
		}
	}
}

void Cat::showP1()
{
	queue<int> crt;
	cout<<"the cards in A's hand :";
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


void Cat::showP2()
{
	queue<int> crt;
	cout<<"the cards in B's hand : ";
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

void Cat::showplay()
{
	cout<<"the cards on the desk:";
	for(int q=0;q<i;q++)
	{
		cout<<Play[q]<<" ";
	}
	cout<<endl;
}

void Cat::play()
{
	Input();
	bool flag = true;

	while(flag)
	{

		showplay();
		showP1();
		showP2();
		cout<<"************************"<<endl;

		flag = P1Put();
		if(!flag)
		{
			break;
		}
		flag = P2Put();
		cout<<endl;
	


	}
}







 
