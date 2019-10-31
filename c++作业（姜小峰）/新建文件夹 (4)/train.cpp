//真jier坑，

#include<iostream>
#include<string>

using namespace std;

class MyString
{
private:
	char *str;    //   就这玩意最坑
	int len; //字符串实际长度
public:
	MyString();  //开始就坑 得用"\0"大发
	MyString(char*); 
	MyString(const MyString&);  
	MyString& operator=(const MyString&);   //MyString& MyString::operator=(const MyString& n) 得这样写，emmmm
	MyString operator+(MyString&);  //这玩意最坑 char*
	int GetLength();//读取字符串长度

	friend ostream& operator<<(ostream &Out, const MyString &Obj); //ostream& operator<<(ostream &Out, const MyString &Obj) 也得这样写，长知识了

	~MyString()
	{
		
	}
};

MyString::MyString():str("\0"),len(0){}

MyString::MyString(char* name):str(name),len(strlen(name)){}

MyString::MyString(const MyString& n):str(n.str),len(n.len){}

MyString& MyString::operator=(const MyString& n)  //赋值运算符重载
{
	this->str = n.str;
	this->len = n.len;
	return MyString(n);
} 

MyString MyString::operator+(MyString& n)  //
{
	char *m;
	m = new char[strlen(this->str)+strlen(n.str)+1];
	strcpy(m,this->str);
	m = strcat(m,n.str);

	MyString p(m);
	return p;
}
int MyString::GetLength()//读取字符串长度
{
	return len;
}

ostream& operator<<(ostream &Out, const MyString &Obj) //显示输出字符串
{
	Out<<Obj.str<<"\n长度为:  "<<Obj.len<<endl;
	return Out;
}


int main()
{
	MyString Obj1,Obj2("qwe"),Obj3;
	Obj3 = Obj1+Obj2;
	cout<<Obj1<<Obj2<<Obj3<<endl;
	
}
