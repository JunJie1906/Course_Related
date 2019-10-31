#include"SingleLinkList.h"
#include<iostream>

using namespace std;

template<class T>
LinkList<T>::~LinkList()
{
    node<T> *p;
    while (head)
    {
        p = head;
        head = head->next;
        delete(p);
    }
}

template<class T>
int LinkList<T>::Length()
{
	node<T> *p = head;

	if(head!=NULL)
	{
		int len = 1;
		while (p->next != NULL)
		{
			len++;
			p = p->next;
		}
		return len;
	}
	else return 0;

}

template<class T>
void LinkList<T>::push_back(T a)
{
	if(head==NULL)
	{
		head = new node<T>;
		head->data = a;
	}
	else
	{
		node<T>* p = head;
		while(p->next != NULL)
		{
			p = p->next;
		}
		
		node<T>* d = new node<T>;

		d->data = a;

		p->next = d;

	}
}

template<class T>
void LinkList<T>::push_front(T a)
{
	if(head==NULL)
	{
		head = new node<T>;
		head->data = a;
	}
	else
	{
		node<T>* p = head;
		node<T>* nd = new node<T>;
		nd->data = a;
		nd->next = p;
		head = nd;
	}
	
}


template<class T>
T LinkList<T>::front()
{
	if(head!=NULL)
	{
		return head->data;
	}
	else
	{
		cout<<"error"<<endl;
		return 0;
	}
	
}

template<class T>
T LinkList<T>::back()
{
	node<T>* p;
	p = head;
	while(p->next!=NULL)
	{
		p = p->next;
	}
	return p->data;
}

template<class T>
void LinkList<T>::pop_front()
{
	node<T> * p;
	p = head;
	head = head->next;
	delete(p);
}


template<class T>
void LinkList<T>::pop_back()
{
	node<T> * p;

	if(head==NULL)
	{
		cout<<"List is empty !"<<endl;
		return;
	}
	if(head->next==NULL)
	{
		p = head;
		
		delete(p);
		head = NULL;
		return;
	}
	
	p = head;
	while(p->next->next!=NULL)
	{
		p = p->next;
	}
	delete(p->next);
	p ->next = NULL;
}


template<class T>
void LinkList<T>::Insert(int i,T p)
{

	if(head == NULL)
	{
		if(i!=0)
		{
			cout<<"input error !"<<endl;
			return;
		}
		else
		{
			head = new node<T>;
			head->data = p;
			return;
		}
	}
	else
	{
		node<T>* nd = new node<T>;
		node<T>* crt;
		nd->data = p;
		
		crt = head;
		if(i==0)
		{
			head = nd;
			head->next = crt;
		}
		else
		{
			while(--i)
			{
				if(crt->next==NULL)
				{
					cout<<"input error !"<<endl;
					return;
				}
				crt = head->next;
			}
			node<T> *crt1;
			crt1 = crt->next;
			crt->next = nd;
			crt->next->next = crt1;
		}
	}
}

template<class T>
void LinkList<T>::Print()
{
	if(head == NULL)
	{
		cout<<"List is empty !"<<endl;
		return;
	}
	node<T>*p;
	p = head;
	while(p!=NULL)
	{
		cout<<p->data<<' ';
		p = p->next; 
	}
	cout<<endl;
	
}

template<class T>
void LinkList<T>::Remove(int i)
{
	node<T> *p;
	p = head;
	if(i==0)
	{
		head = head->next;
		delete(p);
		return;
	}
	else
	{
		while(--i)
		{
			p = p->next;
			if(p->next==NULL)
			{
				cout<<"input error!"<<endl;
				return;
			}
		}
		node<T>* crt;
		crt = p->next;
		p->next = p->next->next;
		delete(crt);
	}
	
}

template<class T>
void LinkList<T>::chval(int i,T val)
{
	node<T> *p;
	p = head;
	if(head == NULL)
	{
		cout<<"input error !"<<endl;
		return;
	}
	while(i--)
	{
		p = p->next;
		if(p==NULL)
		{
			cout<<"input error !"<<endl;
			return;
		}
	}
	p->data = val;
}





int main()
{

	LinkList<int> p;
	p.push_back(999);
	p.push_front(-100);
	p.push_front(200);
	p.Insert(2,0);
	p.Print();
	
	LinkList<int> q(p),r;
	q.Print();
	r = p;
	r.Print();
	
	cout<<p.Length()<<endl;
}







