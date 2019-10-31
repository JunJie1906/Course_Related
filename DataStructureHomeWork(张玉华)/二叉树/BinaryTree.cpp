#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<string>
#include<queue>
#include<stack>
using namespace std;

template<class T>
struct node
{
	T data;
	node<T>* rc;
	node<T>* lc;
	node()
	{
		lc = NULL;
		rc = NULL;
	}
	
	node(T p)
	{
		data = p;
		lc = NULL;
		rc = NULL;
	}

	
};


template<class T>
class Tree
{
private:
	node<T>* root;

public:
	
	Tree()
	{
		root = NULL;
	}
	node<T>* Copy(node<T>* cur)
	{
		if(cur == NULL)
		{
			return NULL;
		}
		node<T>* tmp = new node<T>;
		//node<T>* tmp = new node(cur->data);
		tmp->data = cur->data;
		tmp->lc = Copy(cur->lc);
		tmp->rc = Copy(cur->rc);
		return tmp;
	}
	
	Tree(const Tree<T>& crt) //拷贝构造函数 
	{
		root = Copy(crt.root);
	
	} 
	
	Tree(const node<T>* & crt) //用已知根节点建树 
	{
		root = crt;
	}
	
	Tree<T>& operator = (const Tree<T>& crt)
	{
		this->root = Copy(crt.root);
		return *this;	
	}

	//

	bool IsEmpty()
	{
		if(root==NULL) return true;
		else return false;
	}

	T GetData(node<T>* crt)
	{
		if(crt!=NULL)
			cout<<crt->data<<' ';
		return crt->data;
	}

	void Clear(node<T>* &crt) //注意：加引用！！！
	{
		if(crt==NULL) return;

		Clear(crt->lc);
		Clear(crt->rc);
		delete crt;
		crt=NULL;
	}

	~Tree()
	{
		Clear(root);
	}

	void Insert(T n)
	{
		if(root == NULL)
		{
			root = new node<T>;
			root->data = n;
			return;
		}
		else
		{
			node<T>* crt = root;
			while(1)
			{
				while(crt->data>n)
				{
					if(crt->lc!=NULL)
						crt = crt->lc;
					else
					{
						node<T>* tmp = new node<T>;
						tmp->data = n;
						crt->lc = tmp;
						return;
					}
				}
				while(crt->data<=n)
				{
					if(crt->rc!=NULL)
						crt = crt->rc;
					else
					{
						node<T>* tmp = new node<T>;
						tmp->data = n;
						crt->rc = tmp;
						return;
					}
				}
			}
		}
	}
	

	void Forward(node<T>* crt) //先序遍历
	{
		if(crt==NULL) return;
		else
		{
			GetData(crt);
			Forward(crt->lc);
			Forward(crt->rc);
		}
	}

	void Midward(node<T>* crt)
	{
		if(crt==NULL) return;
		else
		{
			Midward(crt->lc);
			cout<<crt->data<<' ';
			Midward(crt->rc);
		}
	}

	void Backward(node<T>* crt)
	{
		if(crt==NULL) return;
		else
		{
			Backward(crt->lc);
			Backward(crt->rc);
			cout<<crt->data<<' ';
		}
	
	}

	void Forward_non_rec(node<T>* tmp)
	{
		if(tmp == NULL) return;
		stack<node<T>*> S;
		S.push(tmp);
		while(!S.empty()) 
		{
			node<T>* crt = S.top();
			cout<<crt->data<<' ';
			S.pop();
			if(crt->rc!=NULL)
			{
				S.push(crt->rc);
			}
			if(crt->lc!=NULL)
			{
				S.push(crt->lc);
			}
			
		}
		
	}
	
	void Midward_non_rec(node<T>* tmp)
	{
		if(tmp == NULL) return;
		stack<node<T>*> S;
		S.push(tmp);		
		while(!S.empty())
		{
			while(S.top()->lc!=NULL)
			{
				S.push(S.top()->lc);
			}
			
			while(!S.empty())
			{
				node<T>* crt = S.top();
				S.pop();
				cout<<crt->data<<' ';
				if(crt->rc!=NULL)
				{
					S.push(crt->rc);
					break;
				}
			}
			
			
		}
		
	}
	
	void Backward_non_rec(node<T>* tmp)
	{
		if(tmp == NULL) return;
		stack<node<T>*> S;
		S.push(tmp);
		node<T>* Lastpop = NULL;	
		while(!S.empty())
		{
			while(S.top()->lc!=NULL)
			{
				S.push(S.top()->lc);
			}
			while(!S.empty())
			{
				node<T>* crt = S.top();
				
				
				if(crt->rc==NULL||crt->rc==Lastpop)
				{
					S.pop();
					cout<<crt->data<<' ';
					Lastpop = crt;
				}
				else
				{
								
					if(crt->rc!=NULL)
					{
						S.push(crt->rc);
						break;
					}
				} 

			}
			
			
		}	
		
	}
	
	void bfs(node<T>* crt)
	{
		queue<node<T>*> q;
		if(crt==NULL) return;

		q.push(crt);

		while(!q.empty())
		{
			node<T>* tmp = q.front();
			q.pop();
			cout<<tmp->data<<' ';
			if(tmp->lc!=NULL)
				q.push(tmp->lc);
			if(tmp->rc!=NULL)
				q.push(tmp->rc);
		}
	}

	bool FindOne(const T & crt,node<T>* tmp)
	{

		while(tmp!=NULL&&tmp->data!=crt)
		{
			if(tmp->data>crt)
			{
				tmp = tmp->lc;
			}
			else
			{
				if(tmp->data<crt)
				{
					tmp = tmp->rc;
				}
			}
		}
		if(tmp==NULL) return false;
		else return true;
		
	} 
	
	bool Find(const T & crt)
	{
		return FindOne(crt,root);
	}
	
	bool DeleteOne(const T & crt,node<T>* tmp)
	{
		int left = 0;
		bool lastmv = true; //true为左false为右 
		
		node<T>* cur = tmp; //找到目标值的前一个结点
		 
		while(tmp!=NULL&&tmp->data!=crt)
		{
			
			if(tmp->data>crt)
			{
				tmp = tmp->lc;
				
				if(left!=0)
				{
					if(lastmv) cur = cur->lc;
					else cur = cur->rc;
				} 
				left = 1;
				lastmv = true;
			}
			else
			{
				if(tmp->data<crt)
				{
					tmp = tmp->rc;
					
					if(left!=0)
					{
						if(lastmv) cur = cur->lc;
						else cur = cur->rc;
					} 
					
					left = 2;
					lastmv = false;
				}
			}
		}
		
		
		if(tmp==NULL) return false;
		else
		{
			if(tmp->data == crt)
			{
				if(tmp->lc==NULL&&tmp->rc==NULL)
				{
					delete tmp;
					
					if(left==1) cur->lc = NULL;
					else
					{
						if(left==2) cur->rc = NULL;
						else
						{
							if(left==0)
							tmp = NULL;
						}
					}
					return true;
				}
				if(tmp->lc==NULL&&tmp->rc!=NULL)
				{
					node<T>* TMP = tmp;
					if(left==1)
					{
						cur->lc = tmp->rc;
						delete TMP;	
						return true;
					}
					else
					{
						if(left==2)
						{
							cur->rc = tmp->rc;
							delete TMP;
							return true;
							
						}
						if(left==0)
						{	
							root = tmp->rc;
							delete tmp;
							return true;
						} 
					}					
				}
				else
				{
					node<T>* TMP = tmp;
					if(tmp->lc!=NULL&&tmp->rc==NULL)
					{
						if(left==1)
						{
							cur->lc = tmp->lc;	
							delete TMP;
							return true;
						}
						else
						{
							if(left==2)
							{
								cur->rc = tmp->lc;
								delete TMP;
								return true;
							}
							if(left==0)
							{
								root = tmp->lc;
								delete tmp;
								return true;
							}
						}
					}
				}
				if(tmp->lc!=NULL&&tmp->rc!=NULL)
				{
					node<T>* TMP = tmp->lc;    //左子树最大的结点 
					node<T>* TMP1 = tmp;       //TMP前面结点 
					bool caled = false;
					while(TMP->rc!=NULL)
					{
						if(caled) TMP1 = TMP1->rc;
						else TMP1 = TMP1->lc;
						TMP = TMP->rc;
						caled = true;
					}
					
					tmp->data = TMP->data;
					delete TMP;
					if(caled) TMP1->rc = NULL;
					else TMP1->lc = NULL;
					
					return true;
					
					
					
					
					
				}
			}
		}
		
		
		
	}
	
	bool Delete(const T & crt)
	{
		return DeleteOne(crt,root);
	}
	
	
	void dfs(node<T>* crt)
	{
		stack<node<T>*> s;
		if(crt==NULL) return;
		s.push(crt);
		while(!s.empty())
		{
			node<T>* tmp = s.top();
			s.pop();
			cout<<tmp->data<<' ';
			if(tmp->rc!=NULL)
				s.push(tmp->rc);
			if(tmp->lc!=NULL)
				s.push(tmp->lc);

		}
	}
	
	int GetTreeDepth(int dpth, node<T>* crt)
	{
		if(crt==NULL) return dpth;
		int a=dpth,b=dpth;
		if(crt->lc!=NULL)
			a = GetTreeDepth(dpth+1,crt->lc);
		if(crt->rc!=NULL)
			b = GetTreeDepth(dpth+1,crt->rc);
		if(a>b)
			return a;
		else
			return b;
	}

	int CountLeaf(node<T>* crt)
	{
		if(crt==NULL) return 0;
		int a=0,b=0;
		if(crt->lc==NULL&&crt->rc==NULL)
		{
			return 1;
		}
		a = CountLeaf(crt->lc);
		b = CountLeaf(crt->rc);
		
		return a+b;
	}

	
	node<T>* GetTreeRootNodeBySeq1(T *a, T *b,int len)  // 中 前 
	{
		if(len==0) return NULL;
		if(len == 1) 
		{
			node<T>* crt = new node<T>;
			crt->data = *b;
			return crt;
		}
		
		node<T>* crt = new node<T>;
		crt->data = *b;
		int p = 0;
		for(;p<len;p++)
		{
			if(*(a+p)==*b) break;
			
		}
		
		crt->lc = GetTreeRootNodeBySeq1(a,b+1,p);
		crt->rc = GetTreeRootNodeBySeq1(a+p+1,b+1+p,len-p-1);
		return crt;
	}
	
	node<T>* GetTreeRootNodeBySeq2(T *a, T *b ,int len)   // 中  后 b为最后一个元素 
	{
		if(len==0) return NULL;
		if(len == 1) 
		{
			node<T>* crt = new node<T>;
			crt->data = *b;
			return crt;
		}
		
		node<T>* crt = new node<T>;
		crt->data = *b;
		int p = 0;
		for(;p<len;p++)
		{
			if(*(a+p)==*b) break;
			
		}
		
		crt->lc = GetTreeRootNodeBySeq2(a,b-len+p,p);
		crt->rc = GetTreeRootNodeBySeq2(a+p+1,b-1,len-p-1);
		return crt;
	}
	
	void menu()
	{
		int a,p;
		T b;
		cout<<"\n请输入数字选择功能：\n0. 退出程序 \n1. 插入一个元素"<<endl;
		cout<<"2. 遍历树\n3. 得到树的深度\n4. 得到叶子结点数\n5. 清空二叉树"<<endl;
		cout<<"6. 判断是否为空树\n7. 用前序遍历和中序遍历得到树\n8. 用后序遍历和中序遍历得到树"<<endl;
		cout<<"9. 查找指定元素\n10. 删除指定键元素"<<endl;
		cin>>a;

		if(a==0)
				exit(0);
		if(a==1)
		{
			cout<<"\n请输入要插入的元素： "<<endl;
			cin>>b;
			Insert(b);
		}
		if(a==2)
		{
			cout<<"\n请输入遍历类型：\n1. 先序遍历\n2.中序遍历\n3.后序遍历\n4.BFS"<<endl;
			cin>>p;
			if(p==1) {cout<<"先序遍历: ";Forward(root);}
			if(p==2) {cout<<"中序遍历: ";Midward(root);}
			if(p==3) {cout<<"后序遍历: ";Backward(root);}
			if(p==4) {cout<<"层序遍历: ";bfs(root);}
			cout<<endl;
		}
		if(a==3)
		{
			if(root==NULL) cout<<0<<endl;
			else
				cout<<GetTreeDepth(1,root)<<endl;
		}
		if(a ==4)
		{
			cout<<CountLeaf(root)<<endl;
		}
		if(a == 5 )
		{
			Clear(root);
		}
		if(a==6)
		{
			if(IsEmpty()) cout<<"树为空 "<<endl;
			else
				cout<<"树为非空"<<endl;
		}
		if(a==7)
		{
			T a[1000];
			T b[1000];
			int len;
			cout<<"请输入长度："<<endl;
			cin>>len;
			cout<<"请输入前序序列："<<endl;
			for(int i=0;i<len;i++)
			{
				cin>>b[i];
			}
			cout<<"请输入中序序列："<<endl;
			for(int i=0;i<len;i++)
			{
				cin>>a[i];
			}
			
			root = GetTreeRootNodeBySeq1(a, b,len);
		}
		
		if(a==8)
		{
			T a[1000];
			T b[1000];
			int len;
			cout<<"请输入长度："<<endl;
			cin>>len;
			cout<<"请输入后序序列："<<endl;
			for(int i=0;i<len;i++)
			{
				cin>>b[i];
			}
			cout<<"请输入中序序列："<<endl;
			for(int i=0;i<len;i++)
			{
				cin>>a[i];
			}
			
			root = GetTreeRootNodeBySeq2(a, b+len-1,len);
		}
		
		if(a==9)
		{
			T a;
			cout<<"请输入需要查找的元素："<<endl;
			cin>>a;
			if(Find(a))
			{
				cout<<"存在元素"<<a<<endl;
			}
			else
			{
				cout<<"不存在元素"<<a<<endl;
			}
		}
		
		if(a==10)
		{
			T a;
			cout<<"请输入要删除的元素: "<<endl;
			cin>>a;
			if(Delete(a))
			{
				cout<<"成功删除元素"<<a<<endl;
			}
			else
			{
				cout<<"不存在元素"<<a<<endl;
			}
		}
		cout<<"===================="<<endl;
		menu();
	
		
	}




};

int main()
{
	Tree<int> t,t2;

	t.Insert(1);
	t.Insert(-123);
	t.Insert(123);
	t.Insert(66);
	t.Insert(23);
	t.Insert(128037);
	t.Insert(3);
	t.Insert(68);
	Tree<int> t1(t);
	t2 = t;
	t2.menu();

}






