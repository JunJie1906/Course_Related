#include"SequenceList.h"
#include<iostream>
using namespace std;


int main()
{
	SeqList<int> a;
	a.push_back(0);
	a.Print();
	a.push_back(1);
	a.push_back(2);
	a.Print();
	a.Remove(1);
	a.Print();
	a.Insert(1,999);
	a.Print();
	a.RemoveData(0);
	a.Print();
	a.clear();
	a.Print();
}


