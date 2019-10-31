#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
    
#include<vector>
#include<algorithm>
typedef vector<int> Vi;
typedef Vi::iterator It;

int main()
{
	Vi L1,L2;
	It pos;
	int n,num;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>num;
		L1.push_back(num);
	}

	
	for(pos = L1.end();pos!=L1.begin();pos--)
	{
		if(pos==L1.end())
		{continue;}
		L2.push_back(*pos);
	}
	L2.push_back(*L1.begin());

	for(pos=L2.begin();pos!=L2.end();pos++)
	{
		cout<<*pos<<" ";
	}cout<<endl;
}
