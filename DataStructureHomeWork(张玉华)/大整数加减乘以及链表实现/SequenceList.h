#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;

template<class T> 
class SeqList
{
	private:
	    T* Data;
	    int Capacity;  //最大元素的个数
	    int len;      //有效元素  
	public:
		SeqList()
		{
			Data = new T[10];
			Capacity = 10;
			len = 0;
		}
		
		SeqList(const SeqList& s)
		{
			Data = new T[s.len];
			Capacity=s.Capacity;
			len=s.len;
			
			for (int i = 0; i< len; i++)
			Data[i] = s.Data[i];
		}

    ~SeqList()
    {
        if (Data)
        {
            delete[] Data;
            Data = NULL;
            Capacity = 0;
            len = 0;
        }
    }

    void Print()//打印顺序表
    {
        if (len > 0)
        {
            for (int i = 0; i < len; i++)
                cout<<Data[i]<<" ";
            cout<<endl;
        }
        else
            cout << "SeqList is empty " << endl;
    }

    void AddCapacity()
    {
        if (len<Capacity)
        {
            return;
        }
        else
        {
            T* p = new T[len+10];
            for (int i=0;i<len;i++)
                p[i]=Data[i];
            delete[] Data;
            Data = p;
            Capacity = len+10;
            cout << "success in plus Capacity"<<endl;
        }
    }
    void Insert(int x,T num)
    {
        AddCapacity();
        if (x>=0 && x<len)
        {
            for(int i = len-1; i>=x; i--)
                Data[i+1] = Data[i];
            Data[x] = num;
            len++;
        }
        else
        {
            cout << "index is error" << endl;
        }
    }
    
    void push_back(const T num)
    {
        AddCapacity();
        Data[len] = num;
        len ++;
    }

    
    int Find(T x)
    {
        for (int i = 0; i < len; i++)
        {
            if (Data[i] == x)
                return i;
        }
        return -1;
    }

    void RemoveData(T x)
    {
        int index = 0;
        if (len>0)
        {
            index = Find(x);
            if (index != -1)
            {
                for (int i = index; i < len-1; i++)
                    Data[i] = Data[i+1];
                len--;
            }
            else
                cout<<"Data is not in the SeqList"<< endl;
        }
    }	
	
	void Remove(int x)
	{
		if(x>=0&&x<len)
		{
			for(int i=x;i<len-1;i++)
			{
				Data[i] = Data[i+1];
			}
			len--;
	
		}
		else
		{
			cout<<"index out of range "<<endl;
		}
	}
	
	void clear()
	{
		len =0;
	}
};





