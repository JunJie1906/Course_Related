# 构造函数

## 1，默认拷贝构造函数 ，没有指针的情况下，系统会送给我们一个默认的，不再举栗子了~
## 2，自定义拷贝构造函数

## 这玩意让我搞了半天......先上代码
```
#include<iostream>
#include<cstring>
using namespace std;

class student2
{
private:
	char* name;
public:
	student2(string name1 = "noName")
	{
		name = new char[name1.length()+ 1];
		strcpy(name, name1.c_str());
		cout <<name<< " was created!" << endl;
	}

	~student2()
	{
		cout<< name <<" was destructed!" <<endl;
		delete[] name;
	}

	void showName()
	{
		cout << name << endl;
	}

	student2(const student2& p)
	{
		name = new char[strlen(p.name)+1];
		strcpy(name,p.name);
		cout<<"copy finished!!"<<endl;
	}

};

using namespace std;

int main()
{
	student2 zhang1("zhang");
	student2 wang("wang");
	student2 zhang2(zhang1);
}
```
## so，到底是哪出问题了呢？？(上面的是最终正确的

# 首先是char* 这个玩意，就是一个地址指针罢了，但是那些什么const char* ,char* ,string 转换这些是真的烦，那就总结一下
---
我是分割线~~~~~~~
***
1. string 转const char *
string s ="abc";
const char * c_s = s.c_str();

2. const char * 转string
   直接赋值即可
const char * c_s ="abc";
string s(c_s);

 3. string转char *
string s ="abc";
char * c;
const int len = s.length();
c =new char[len+1];
strcpy(c,s.c_str());

 4. char * 转string
char * c ="abc";
string s(c);

 5. const char * 转char *
const char * cpc ="abc";
char * pc =new char[100];//足够长
strcpy(pc,c）

***
## 代码验证,const char * 与string
# Attention: 只有const char * 可以直接赋值，char * 赋值会警告，非常不友好！！
## 以下只能 string 转 const char *
```
#include<iostream>
#include<cstring>

using namespace std;

int main()
{
	string s("wang!!");
	const char* a,* b;
	a = "aaaaaaaaa";
	b = "bbbbbbbbb";

  cout<<a<<b<<endl;

	b = s.c_str();
	cout<<b<<endl;  //OK
}

```

## 以下只能string 转 char *
```
#include<iostream>
#include<cstring>

using namespace std;

int main()
{
	string s ="wangwang";
	char * c;

	c =new char[s.length()+1];
	strcpy(c,s.c_str());

	delete[] c;
}
```
## string 转 char 就是这么简单粗暴~
```
  const char* a ="ppp";
  string s(a);
```
### or
```
  const char* a ="ppp";
  string s1;
  s1 = a;
```
## const char * 转 char *
```
#include<iostream>
#include<cstring>

using namespace std;

int main()
{
	const char* a = "wawawawwa!!!";
	char* b;

	b = new char[strlen(a)+1];
	strcpy(b,a);
	cout<<a<<" " <<b<<endl;

	delete[] b;
	cout<<&b<<endl;
}
```
### 其中delete[] b 只删除了b new出来的内存，b的地址不变，仍然存在

# 深入理解一下 s.c_str()：
##这个函数返回的是一个临时的指针变量，*`是string类的一个东东，当string对象被destructed以后，这个函数所指向的东西也没有了`*,所以，如果直接char * a = s.c_str(),肯定会报错，只能用 strcpy()来深度copy这个东西，这样就ojbk了~~~
