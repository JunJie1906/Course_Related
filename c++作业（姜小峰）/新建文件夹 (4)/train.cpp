//��jier�ӣ�

#include<iostream>
#include<string>

using namespace std;

class MyString
{
private:
	char *str;    //   �����������
	int len; //�ַ���ʵ�ʳ���
public:
	MyString();  //��ʼ�Ϳ� ����"\0"��
	MyString(char*); 
	MyString(const MyString&);  
	MyString& operator=(const MyString&);   //MyString& MyString::operator=(const MyString& n) ������д��emmmm
	MyString operator+(MyString&);  //��������� char*
	int GetLength();//��ȡ�ַ�������

	friend ostream& operator<<(ostream &Out, const MyString &Obj); //ostream& operator<<(ostream &Out, const MyString &Obj) Ҳ������д����֪ʶ��

	~MyString()
	{
		
	}
};

MyString::MyString():str("\0"),len(0){}

MyString::MyString(char* name):str(name),len(strlen(name)){}

MyString::MyString(const MyString& n):str(n.str),len(n.len){}

MyString& MyString::operator=(const MyString& n)  //��ֵ���������
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
int MyString::GetLength()//��ȡ�ַ�������
{
	return len;
}

ostream& operator<<(ostream &Out, const MyString &Obj) //��ʾ����ַ���
{
	Out<<Obj.str<<"\n����Ϊ:  "<<Obj.len<<endl;
	return Out;
}


int main()
{
	MyString Obj1,Obj2("qwe"),Obj3;
	Obj3 = Obj1+Obj2;
	cout<<Obj1<<Obj2<<Obj3<<endl;
	
}
