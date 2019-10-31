#include"DoubleLinkList.h"
#include<iostream>
using namespace std;

template<class Temp>
DoubleLink<Temp>::~DoubleLink()
{
	Node<Temp>*crt;
	
	while(head!=NULL)
	{
		crt = head;
		head = head->next;
		delete(crt);
	}
}

template<class Temp>
void DoubleLink<Temp>::clear()
{
	Node<Temp>*crt;
	
	while(head!=NULL)
	{
		crt = head;
		head = head->next;
		delete(crt);
	}
}

template<class Temp>
DoubleLink<Temp>::DoubleLink(const DoubleLink<Temp> &p)
{
	if(p.isEmpty()) 
	{
		head = NULL;
	}
	else
	{
		Node<Temp> *p1 = p.head;
		Node<Temp>* p2;
		if(p1->next != NULL)
		{
			head = new Node<Temp>;
			head->data = p1->data;
			p2 = head;
			p1 = p1->next;
			while (p1 != NULL)
			{
				Node<Temp> *nd = new Node<Temp>;
				nd->data = p1->data;
				nd->prev = p2;
				p2->next = nd;
				p2 = nd;
				p1 = p1->next;
			}
		}
		else
		{
			head = p.head;
		}
	}
}

template<class Temp>
int DoubleLink<Temp>::Length() const 
{
	Node<Temp> *p;
	int count = 0;
	p = head;
	while(p!=NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}

template<class Temp>
void DoubleLink<Temp>::push_back(Temp a) 
{
	if(head==NULL)
	{
		head = new Node<Temp>;
		head->data = a;
		return;
	}
	Node<Temp>*p,*nd;
	p =head;
	while(p->next!=NULL)
	{
		p = p->next;
	}
	nd = new Node<Temp>;
	nd->data = a;
	nd->prev = p; 
	p->next = nd;
}

template<class Temp>
void DoubleLink<Temp>::push_front(Temp a)
{
	if(head==NULL)
	{
		head = new Node<Temp>;
		head->data = a;
		return;
	}
	Node<Temp>*p,*nd;
	p =head;
	nd = new Node<Temp>;
	nd->data = a;
	nd->next = p; 
	p->prev = nd;
	head = nd;
}

template<class Temp>
void DoubleLink<Temp>::Print_pstv()
{
	Node<Temp>*p;
	p = head;
	while(p!=NULL)
	{
		cout<<p->data;
		p = p->next;
	}
	cout<<endl;
}

template<class Temp>
void DoubleLink<Temp>::Print_ngtv()
{
	if(head==NULL)
	{
		cout<<"an empty list"<<endl;
		return;
	}
	Node<Temp>*p;
	p = head;
	while(p->next!=NULL)
	{
		p = p->next;
	}

	while(p!=NULL)
	{
		cout<<p->data;
		p = p->prev;
	}
}

template<class Temp>
Temp DoubleLink<Temp>::back()const
{
	if(head==NULL)
	{
		cout<<"List is empty !"<<endl;
		return 0;
	}
	Node<Temp>*p;
	p = head;
	while(p->next!=NULL)
	{
		p = p->next;
	}
	return p->data;
}

template<class Temp>
Temp DoubleLink<Temp>::front()const
{
	if(head==NULL)
	{
		cout<<"List is empty !"<<endl;
		return 0;
	}
	return head->data;
}

template<class Temp>
void DoubleLink<Temp>::pop_back()
{
	Node<Temp> *p,*crt;
	p = head;
	if(head==NULL)
	{
		cout<<"List is empty !"<<endl;
		return ;
	}
	if(head->next==NULL)
	{
		delete(p);
		head = NULL;
		return;
		
	}
	while(p->next!=NULL)
	{
		p = p->next;
	}
	crt = p->prev;
	crt->next = NULL;
	delete(p);
}

template<class Temp>
void DoubleLink<Temp>::pop_front()
{
	Node<Temp> *p;
	
	p = head;
	head = head->next;
	head->prev = NULL;
	delete(p);
}

template<class Temp>
void DoubleLink<Temp>::Insert(Temp val,Temp i)
{
	int len = Length();
	if(i>len)
	{
		cout<<"input error !"<<endl;
		return;
	}
	if(head==NULL)
	{
		if(i!=0)
		{
			cout<<"input error !"<<endl;
			return;
		}
		head = new Node<Temp>;
		head ->data = val;
	}
	else
	{
		if(i==0)
		{
			push_front(val);
		}
		else
		{
			if(i==len)
			{
				push_back(val);
			}
			else
			{
				Node<Temp> *nd = new Node<Temp>;
				Node<Temp> *p,*crt;
				p = head;
				while(--i)
				{
					p = p->next;
				}
				crt = p->next;
				nd->data = val;
				nd->prev = p;
				nd->next = crt;
				p->next = nd;
				crt->prev = nd;
			}
		}
	}
}

template<class Temp>
void DoubleLink<Temp>::Remove(int i)
{
	int len = Length();
	if(i>=len)
	{
		cout<<"input error !"<<endl;
		return;
	}
	if(i==len-1)
	{
		pop_back();
		return;
	}
	if(i==0)
	{
		pop_front();
		return ;
	}
	Node<Temp>* p=head;
	while(i--)
	{
		p = p->next;
	}
	Node<Temp> *crt;
	crt = p;
	p = p->prev;
	p->next = crt->next;
	crt->next->prev = p;
	delete(crt);
	
}

template<class Temp>
void DoubleLink<Temp>::chval(int i,Temp val)
{
	int len = Length();
	if(i>=len)
	{
		cout<<"input error !"<<endl;
		return;
	}
	
	if(head==NULL)
	{
		cout<<"List is empty !"<<endl;
		return;
	}
	
	Node<Temp> *p = head;
	while(i--)
	{
		p=p->next;
	}
	p->data = val;
	
}

template<class Temp>
int DoubleLink<Temp>::find(Temp dest) const 
{
	Node<Temp> *p = head;
	int count = 0;
	while(p!=NULL)
	{
		if(p->data==dest)
		{
			return count;
		}
		p = p->next;
		count++;
	}
	return -1;
}

template<class Temp>
Temp DoubleLink<Temp>::getVal(int i)const 
{
	int len = Length();
	if(i>=len||i<0)
	{
		cout<<"input error !"<<endl;
		return 0;
	}
	
	Node<Temp> *p = head;
	while(i--)
	{
		p = p->next;
	}
	return p->data;
} 

template<class Temp>
DoubleLink<Temp>& DoubleLink<Temp>::operator=(const DoubleLink<Temp>& p)
{
	if (this != &p)
	{
		Node<Temp> *p1 = p.head;
		Node<Temp>* p2;
		if (p.head == NULL)
		{
			this->head = NULL;
			return *this;
		}
		if (p1->next != NULL)
		{
			this->head = new Node<Temp>;
			this->head->data = p1->data;
			p2 = this->head;
			p1 = p1->next;
			while (p1 != NULL)
			{
				Node<Temp> *nd = new Node<Temp>;
				nd->data = p1->data;
				nd->prev = p2;
				p2->next = nd;
				p2 = nd;
				p1 = p1->next;
			}
		}
		else
		{
			this->head = p.head;
		}
		return *this;
	}
	else
	{
		return *this;
	}

}






