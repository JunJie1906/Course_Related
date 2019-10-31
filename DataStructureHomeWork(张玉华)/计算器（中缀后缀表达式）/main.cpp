#include "match3.cpp"


void FirstType()
{
	DeskCal1 p1;
	p1.Cal();
	
}


void SecondType()
{
	string s2;
	getline(cin,s2);
	DeskCal2 p2(s2);
	p2.Cal();
}

void ThirdType()
{
	string s3;
	getline(cin,s3);
	MidCal p3(s3);
	p3.Cal();
	
}

void menu()
{
	cout<<"菜单："<<endl;
	cout<<"1. 带有提示符的后缀表达式输入"<<endl;
	cout<<"2. 输入后缀表达式"<<endl;
	cout<<"3. 输入中缀表达式"<<endl;
	cout<<"4. 退出"<<endl;
	cout<<"选择输入方式："<<endl;
	int c ;
	cin >>c;
	string crt;
	if(c==1)
	{
		FirstType();
		menu();
	}
	if(c==2)
	{
		getline(cin,crt);
		SecondType();
		menu();
	}
	if(c==3)
	{
		getline(cin,crt);
		ThirdType();
		menu();
	}
	
	
}


int main()
{
	menu();
}


