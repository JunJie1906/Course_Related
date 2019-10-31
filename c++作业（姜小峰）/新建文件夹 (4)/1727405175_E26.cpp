#include<iostream>
#include<string>
#include<cstdio>
#include<cmath>

using namespace std;

class CAount
{
	double m_Money;
	int year,month,date;
	static double m_InterestRate;
public:
	static void SetInterestRate(double m) //��̬���������� static double m_InterestRate
	{
		m_InterestRate =m;
	}
	double GetInterestRate()             
	{
		return m_InterestRate;
	}

	void SaveMoney(double m,int y,int mo,int d)  //��Ǯ 
	{
		year = y;
		month = mo;
		date = d;
		if(m_Money>0)
		{
			m_Money += m;
		}
		else
		{
			m_Money = m;
		}
	}

	double LendMoney(double m,int y,int mo,int d)  //ȡǮ���ж��Ƿ����ȡ���� 
	{
		if(m_Money>=m)
		{
			m_Money -= m;
			cout<<"���𹻣�ȡ������";
			return m+m*m_InterestRate*((y-year)*360+(mo-month)*30+(d-date))/360;
		}
		else
		{
			cout<<"���𲻹���ȡ���� ";
			return 0;
		}
	}
	void SaveInterest(int y,int mo,int d) //���� 
	{
		m_Money += m_Money* m_InterestRate*((y-year)*360+(mo-month)*30+(d-date))/360;
		year = y;
		month = mo;
		date = d;
	}

};

double CAount::m_InterestRate=0;        //��ʼ��m_InterestRate

int main()
{
	CAount a,b;
	CAount::SetInterestRate(0.001);
	a.SaveMoney(200000,2017,12,2);
	a.SaveInterest(2018,5,4);
	cout<<a.LendMoney(300000,2019,1,1)<<endl;
	cout<<a.LendMoney(200001,2019,1,1)<<endl;
	cout<<"InterestRate is: "<<a.GetInterestRate()<<endl; 
	CAount::SetInterestRate(0.01);
	b.SaveMoney(200000,2017,12,2);
	b.SaveInterest(2018,5,4);
	cout<<b.LendMoney(300000,2019,1,1)<<endl;
	cout<<b.LendMoney(200001,2019,1,1)<<endl;
}
