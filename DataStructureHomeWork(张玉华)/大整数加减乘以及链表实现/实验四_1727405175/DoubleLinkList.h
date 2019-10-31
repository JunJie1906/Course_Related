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
    void push_back(Temp a);  //在链表尾部添加元素 
    void push_front(Temp a) ;  //在链表首部添加元素 
	Temp front() const;       //得到头节点数据 
	Temp back() const;        //得到尾节点数据 
	void pop_back();		//删除尾节点 
	void pop_front();		//删除首节点 
	void Insert(Temp val,Temp i); //在第i个元素前插入val
	void Remove(int i); 	  // 删除第i个元素 
	void Print_pstv();        //正向遍历链表元素 
	void Print_ngtv();		  //逆向遍历链表元素 
	void chval(int i,Temp val);  //改变第i个元素的值为val
	int find(Temp dest)const ;       //查找值为dest的元素 找得到返回第一个元素的位置 否则返回-1 
	Temp getVal(int i)const ;        //返回第i个元素的值 
    DoubleLink<Temp>& operator=(const DoubleLink<Temp>& s);
	
};





