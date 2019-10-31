#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
void Sort(vector<string> months ,vector<string> str)
{
	if(months.empty())
	{
		return;
	}
	string min;
	vector<string>::iterator It,pos;
	min = *months.begin();
	for(pos = months.begin();pos!=months.end();pos++)
	{
		if(*pos<=min)
		{
			It = pos;
			min = *pos;
		}
	}
	str.push_back(min);
	months.erase(It);
	cout<<min<<endl;
	Sort(months,str);
}


int main()
{
	
	vector<string> months,str;
	vector<string>::iterator pos;
	string min;
	months.push_back("January");
	months.push_back("February");
	months.push_back("March");
	months.push_back("April");
	months.push_back("May");
	months.push_back("June");
	months.push_back("July");
	months.push_back("August");
	months.push_back("September");
	months.push_back("Octuber");
	months.push_back("November");
	months.push_back("December");
	Sort(months,str);
}
