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
    void push_back(T a);  //������β�����Ԫ�� 
    void push_front(T a);  //�������ײ����Ԫ�� 
	T front();       //�õ�ͷ�ڵ����� 
	T back();        //�õ�β�ڵ����� 
	void pop_back();   //ɾ��β�ڵ� 
	void pop_front();  //ɾ��ͷ�ڵ� 
	void Insert(int i,T p); //�ڵ�i��Ԫ��ǰ����p
	void Remove(int i); // ɾ����i��Ԫ�� 
	void Print();       //�������Ԫ�� 
	void chval(int i,T val);  //�ı��i��Ԫ�ص�ֵΪval 
	int find(T dest);       //����ֵΪdest��Ԫ�� �ҵõ�����Ԫ�ص�λ�� ���򷵻�-1 
	T getNum(int i);        //���ص�i��Ԫ�ص�ֵ 
};
