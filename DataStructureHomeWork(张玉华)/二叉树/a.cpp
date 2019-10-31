#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<string>
#include<queue>
#include<stack>
using namespace std;

template<class T>
struct node
{
	T data;
	node<T>* rc;
	node<T>* lc;
	node()
	{
		lc = NULL;
		rc = NULL;
	}
	
	node(T p)
	{
		data = p;
		lc = NULL;
		rc = NULL;
	}

	
};


int main()
{
	node<int>* a = new node<int>;
	a->data = 10;
	cout<<a->data<<endl;
		delete a;
	
	cout<<a->data;
	
}
