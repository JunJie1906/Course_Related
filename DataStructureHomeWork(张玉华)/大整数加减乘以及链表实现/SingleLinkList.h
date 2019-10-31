#include<cstdio>
#include<cstdlib>
#include<stdio.h> 


template<class T>
struct node {
    T data;
    node *next;
	node()
	{
		next = NULL;
	}
};

template<class T>
class LinkList
{
private:
    node<T> *head;
public:
    LinkList() {head = NULL;}
    ~LinkList();
    void clear();
    bool isEmpty() { return head == NULL; }
    int Length(); 
    void push_back(T a);  //在链表尾部添加元素 
    void push_front(T a);  //在链表首部添加元素 
	T front();       //得到头节点数据 
	T back();        //得到尾节点数据 
	void pop_back();   //删除尾节点 
	void pop_front();  //删除头节点 
	void Insert(int i,T p); //在第i个元素前插入p
	void Remove(int i); // 删除第i个元素 
	void Print();       //输出链表元素 
	void chval(int i,T val);  //改变第i个元素的值为val 
	int find(T dest);       //查找值为dest的元素 找得到返回元素的位置 否则返回-1 
	T getNum(int i);        //返回第i个元素的值 
};
