#include"BigInt.h"
#include<iostream>

using namespace std;


void BigInt::Change()
{
	if(op)
	{
		op = false;
	}
	else
	{
		op = true;
	}
	
}

BigInt BigInt::abs()const
{
	
	BigInt ans(inp);
	if(!op)
	{
		ans.Change();
	}
	
	return ans;
}

BigInt::BigInt(string s = "")
{
	inp = s;
	if(!s.empty())
	{
		
		if(s[0] == '-') 
		{
			op = false;
			int len = s.length();
			int i=1;
			while(i<len)
			{
				if((int(s[i])-48)>9||(int(s[i])-48)<0) 
				{
					cout<<"input a wrong number !"<<endl;
					exit(0);
				}
				num.push_front(int(s[i])-48);
				i++;
			}
		}
		else
		{
			op = true;
			int len = s.length();
			int i=0;
			while(i<len)
			{
				if((int(s[i])-48)>9||(int(s[i])-48)<0) 
				{
					cout<<"input a wrong number !"<<endl;
					exit(0);
				}
				num.push_front(int(s[i])-48);
				i++;
			}
		}
	}
}

BigInt& BigInt::operator=(const BigInt &n)
{
	op = n.op;
	num = n.num;
	inp = n.inp;
	return *this;
}
	
bool operator >(const BigInt &p,const BigInt &q)
{
	BigInt a(p),b(q);
	
	if(a.isEmpty()&&b.isEmpty()) return false;
	if(!a.isEmpty()&&b.isEmpty()) return b.op;
	if(a.isEmpty()&&!b.isEmpty()) return a.op;
	int lena = a.num.Length();
	int lenb = b.num.Length();
	if(lena!=lenb)
	{
		return lena>lenb;
	}
	while(!a.num.isEmpty()&&!b.num.isEmpty()&&a.num.back()==b.num.back())
	{
		a.num.pop_back();
		b.num.pop_back();
	}
	if(!a.num.isEmpty())
	{
		return a.num.back()>b.num.back();
	}
	
	return false;
	
}

bool operator ==(const BigInt &p,const BigInt &q)
{
	BigInt a(p),b(q);
	if(a.isEmpty()&&b.isEmpty()) return true;
	if(a.isEmpty()||b.isEmpty()) return false;
	int lena = a.num.Length();
	int lenb = b.num.Length();
	if(lena!=lenb) return false;
	while(!a.num.isEmpty()&&!b.num.isEmpty()&&a.num.back()==b.num.back())
	{
		a.num.pop_back();
		b.num.pop_back();
	}
	if(a.isEmpty()) return true;
	else return false;
	
}

BigInt operator +(const BigInt& a,const BigInt& b)
{
	BigInt ans;
	if(a.isEmpty())
	{
		if(b.isEmpty()) return ans;
		else
		{
			return b;
		}
	}
	else
	{
		if(b.isEmpty())
		{
			return a;
		}
	}
	int lena = a.num.Length();
	int lenb = b.num.Length();
	if(a.op==b.op)
	{
		int i=0,j=0;
		int crt=0,crt_b = 0;
		while(i<lena&&j<lenb)
		{
			crt_b = crt;
			crt = a.num.getVal(i)+b.num.getVal(j)+crt_b/10;
			ans.num.push_back(crt%10);
			i++;
			j++;
		}
		while(i<lena)
		{
			crt_b = crt;
			crt = a.num.getVal(i)+crt_b/10;
			ans.num.push_back(crt%10);
			i++;
		}
		
		while(j<lenb)
		{
			crt_b = crt;
			crt = b.num.getVal(j)+crt_b/10;
			ans.num.push_back(crt%10);
			j++;
		}
	
		if(crt/10!=0)
		{
			ans.num.push_back(crt/10);
		}
		
		ans.op = a.op;
	}
	else
	{
		int i=0,j=0;
		int crt=0,crt_b = 0;
		
		
		if(a.abs()>b.abs())
		{
			
			ans.op = a.op;
			while(j<lenb)
			{
				
				crt = a.num.getVal(i)-b.num.getVal(j)+crt_b;
				if(crt<0)
				{
					crt+=10;
					crt_b = -1;
				}
				else crt_b = 0;
				ans.num.push_back(crt);
				i++;
				j++;
			}
			while(i<lena)
			{
				crt = a.num.getVal(i)+crt_b;
				if(crt<0)
				{
					crt+=10;
					crt_b = -1;
				}
				else crt_b = 0;
				ans.num.push_back(crt);
				i++;
			}
			while(!ans.num.isEmpty())
			{
				if(ans.num.back()==0) ans.num.pop_back();
				else
				{
					break;
				}
			}
		}
		else
		{
			if(a.abs()==b.abs())
			{
				return ans;
			 } 
			ans.op = b.op;
			while(i<lena)
			{
				
				crt = b.num.getVal(j)-a.num.getVal(j)+crt_b;
				if(crt<0)
				{
					crt+=10;
					crt_b = -1;
				}
				else crt_b = 0;
				ans.num.push_back(crt);
				i++;
				j++;
			}
			while(j<lenb)
			{
				
				crt = b.num.getVal(j)+crt_b;
				if(crt<0)
				{
					crt+=10;
					crt_b = -1;
				}
				else crt_b = 0;
				ans.num.push_back(crt);
				j++;
			}
			
			while(!ans.num.isEmpty())
			{
				
				if(ans.num.back()==0)
				{
					ans.num.pop_back();
				}
				else
				{
					break;
				}
			}
			
		}
	}
	
	return ans;
	
}

BigInt operator -(const BigInt& p,const  BigInt& q)
{
	BigInt b(q),a(p);
	b.Change();
	return a+b;
}


BigInt operator *(const BigInt& p, const  BigInt& q)
{
	BigInt a(p),b(q);
	BigInt ans;
	if (p.isEmpty() || q.isEmpty())
	{
		return ans;
	}
	int len1 = a.num.Length();
	int len2 = b.num.Length();
	
	ans.op = a.op == b.op;

	int crt = 0;
	for (int i = 0; i<len1; i++)
	{
		for (int j = 0; j<len2; j++)
		{
			if (crt <= i + j)
			{
				ans.num.push_back(a.num.getVal(i)*b.num.getVal(j));
				crt++;
			}
			else
			{
				ans.num.chval(i + j, ans.num.getVal(i + j) + a.num.getVal(i)*b.num.getVal(j));
			}
		}

	}

	crt = 0;
	int ith = 0;
	int Len = ans.num.Length();
	while (ith<Len)
	{
		int nm = ans.num.getVal(ith) + crt;
		crt = nm / 10;
		ans.num.chval(ith, nm % 10);
		ith++;
	}
	if (crt != 0)
	{
		ans.num.push_back(crt);
	}
	return ans;
}

bool BigInt::isEmpty() const
{
	if (num.isEmpty()) return true;
	else
	{
		for (int i = num.Length() - 1; i >= 0; i--)
		{
			if (num.getVal(i) != 0)
				return false;
		}
		return true;
	}
}

void BigInt::print()
{
	if(num.isEmpty()) 
	{
		cout<<0<<endl;
		return;
	}
	
	if(op==false) cout<<'-';
	
	num.Print_ngtv();
}



int main()
{
	while(1)
	{
		string s1,s2;
		cin>>s1;
		BigInt a(s1);
		cin>>s2;
		BigInt b(s2),c;
		c = a*b;
		cout<<"answer = ";
		c.print();
		cout<<endl;
		cout<<endl;
    }
	
	
	
	
	 
}

