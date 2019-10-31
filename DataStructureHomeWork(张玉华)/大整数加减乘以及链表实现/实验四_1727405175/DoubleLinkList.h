#include<cstdio>
#include<cstdlib>
#include<stdio.h> 


template<class Temp>
struct Node {
   	Temp data;
    Node *next,*prev;
	Node()
	{
		next = NULL;
		prev = NULL;
	}
};

template<class Temp>
class DoubleLink
{
private:
    Node<Temp> *head;
public:
	
    DoubleLink() {head = NULL;}
    ~DoubleLink();
	DoubleLink(const DoubleLink<Temp> &p);
    bool isEmpty()const  { return head == NULL; }
    int Length() const ;
	Node<Temp> * GetHead(){return head;}
    void clear();
    void push_back(Temp a);  //������β�����Ԫ�� 
    void push_front(Temp a) ;  //�������ײ����Ԫ�� 
	Temp front() const;       //�õ�ͷ�ڵ����� 
	Temp back() const;        //�õ�β�ڵ����� 
	void pop_back();		//ɾ��β�ڵ� 
	void pop_front();		//ɾ���׽ڵ� 
	void Insert(Temp val,Temp i); //�ڵ�i��Ԫ��ǰ����val
	void Remove(int i); 	  // ɾ����i��Ԫ�� 
	void Print_pstv();        //�����������Ԫ�� 
	void Print_ngtv();		  //�����������Ԫ�� 
	void chval(int i,Temp val);  //�ı��i��Ԫ�ص�ֵΪval
	int find(Temp dest)const ;       //����ֵΪdest��Ԫ�� �ҵõ����ص�һ��Ԫ�ص�λ�� ���򷵻�-1 
	Temp getVal(int i)const ;        //���ص�i��Ԫ�ص�ֵ 
    DoubleLink<Temp>& operator=(const DoubleLink<Temp>& s);
	
};





