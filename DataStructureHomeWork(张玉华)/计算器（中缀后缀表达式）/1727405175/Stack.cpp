#include "Stack.h" 

#include<iostream>
#include<cstring>
#include<string>

using namespace std;

Stack::Stack()
{
	i = 0;
	memset(s,0,sizeof(s));
}


void Stack::push(Stack_entry entry)
{
	i++;
	if(i<1000)
	{
		s[i] = entry;
	}
	else
	{
		if(i>=1000)
		{
			cout<<"Stack is full"<<endl;
		}
	}
}

void Stack::pop()
{
	if(i<1000&&i>0)
	{
		s[i] = 0;
		i--;
	}
	else
	{
		cout<<"Stack is empty"<<endl;
		
	}
}


Stack_entry Stack::top()
{
	return s[i];
}

bool Stack::empty()
{
	if(i==0)
	{
		return true;
	}
	return false;
}









