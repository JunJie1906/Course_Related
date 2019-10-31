#include <iostream>
#include <cmath>

using namespace std;


class CTime
{
	int m_hour,m_minute,m_second;

public:
	CTime(int hour=0,int minute=0,int second=0):m_hour(hour),m_minute(minute),m_second(second)
	{
		init();
	}
	//����ʱ���Ϸ�������ֵ��������ֵ0 ʱ0 ��0 ��
	int SetTime(int hour=0,int minute=0,int second=0)
	{
		m_hour=hour;
		m_minute=minute;
		m_second = second;

		if(init())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	//����ʱ���Ϸ�������ֵ������1�����򲻸�ֵ��������0
	int getHour();
	int getMinute();
	int getSecond();
	void ShowTime(bool flag);
	int init();
	int ShowMinute()
	{
		return m_minute;
	}
	//flag ΪTrue ����24 Сʱ����ʾʱ�䣬������ AM PM �ķ�ʽ��ʾ
};

class CDate
{
	int m_year,m_month,m_day;
public:
	CDate(int year=2000,int month=1,int day=1):m_year(year),m_month(month),m_day(day)//�������ںϷ�������ֵ��������ֵ2000 ��1 ��1 ��
	{
		init();
	}
	//�������ںϷ�������ֵ��������ֵ2000 ��1 ��1 ��
	int SetDate(int year ,int month,int date); //�������ںϷ�������ֵ������1�����򲻸�ֵ��������0
	//�������ںϷ�������ֵ������1�����򲻸�ֵ��������0
	int GetYear();
	int GetMonth();
	int GetDay();
	void ShowDate(bool flag);
	int init();
	int ShowMonth()
	{
		return m_month;
	}
	//flag ΪTRUE���������ĵķ�ʽ��ʾ���ڣ�������MM/DD/YYYY �ķ�ʽ��ʾ����

};


class CDateTime
{
	CTime m_time;
	CDate m_date;

public:
	CDateTime(int a=2000,int b=1,int c=1,int d=0,int e=0,int f=0):m_date(a,b,c),m_time(d,e,f){}

	int SetDateTime(int a,int b,int c,int d,int e,int f);
	void ShowDateTime(bool flag1,bool falg2);
	int GetMonth()
	{
		return m_date.ShowMonth();
	}

	int GetMinute()
	{
		return m_time.ShowMinute();
	}

};

int CTime::init()
{
	if(m_hour>=0&&m_hour<24&&m_minute>=0&&m_minute<60&&m_second>=0&&m_second<60)
	{
		return 1;
	}
	else
	{
		m_hour=0;
		m_minute=0;
		m_second=0;
		return 0;
	}
}

int CTime::getHour()
{
	return m_hour;
}

int CTime::getMinute()
{
	return m_minute;
}

int CTime::getSecond()
{
	return m_second;
}

void CTime::ShowTime(bool flag)
{
	if(flag)
	{
		cout<<"Time is :   "<<m_hour<<" : "<<m_minute<<" : "<<m_second<<endl;
	}
	else
	{
		int now_h;
		string now_Time;

		if(m_hour<12&&m_hour>=0)
		{
			now_Time = "AM";
			if(m_hour==0)
			{
				now_h = 12;
			}
			else now_h = m_hour;
		}
		else
		{
			now_Time = "PM";
			if(m_hour==12)
			{
				now_h = 12;
			}
			else
			{
				now_h = m_hour-12;
			}
		}

		cout<<"Time is :  "<<m_hour<<" : "<<m_minute<<" : "<<m_second<<" "+now_Time<<endl;
	}
}


int CDate::GetYear()
{
	return m_year;
}

int CDate::GetMonth()
{
	return m_month;
}

int CDate::GetDay()
{
	return m_day;
}

void CDate::ShowDate(bool flag) //flag ΪTRUE���������ĵķ�ʽ��ʾ���ڣ�������MM/DD/YYYY �ķ�ʽ��ʾ����
{
	if(flag)
	{
		cout<<m_year<<"�� "<<m_month<<"�� "<<m_day<<"��"<<endl;
	}
	else
	{
		cout<<m_year<<"\\"<<m_month<<"\\"<<m_day<<"\\"<<endl;
	}

}

int CDate::init()
{
	if(m_year<0||m_month>12||m_month<1||m_day<1||m_day>31)
	{
		m_year=2000;
		m_month = 1;
		m_day = 1;
		return 0;
	}
	else return 1;
}

int CDate::SetDate(int year=2000,int month=1,int day=1) //�������ںϷ�������ֵ������1�����򲻸�ֵ��������0
{
	m_year=year;
	m_month = month;
	m_day=day;
	if(init()) return 1;
	else return 0;
}



int CDateTime::SetDateTime(int a,int b,int c,int d,int e,int f)
{
	int n1 = m_date.SetDate(a,b,c);
	int n2 = m_time.SetTime(d,e,f);

	if(n1&&n2) return 1;
	if(!n1) return -1;
	if(!n2) return -2;
}

void CDateTime::ShowDateTime(bool flag1,bool flag2)
{
	m_date.ShowDate(flag1);
	m_time.ShowTime(flag2);
}


int main()
{
	CDateTime d1(2014, 5, 2, 27, 12, 5);
	d1.ShowDateTime(false, true); //��1 ��������ʾ��Ӣ�ķ�ʽ��ʾ����, ��2 ��������ʾ��24 Сʱ�Ʒ�ʽ��ʾʱ��

	CDateTime d2;
	d2.ShowDateTime(true, false); //��1 ��������ʾ�����ķ�ʽ��ʾ����, ��2 ��������ʾ��AM PM �ķ�ʽ��ʾʱ��

	int iStatus;
	iStatus=d2.SetDateTime(2014, 5, 2, 21, 55, 5);
	switch(iStatus)
	{
	case 1:
			cout<<"���ں�ʱ������������ȷ!"<<endl;
			break;
	case -1:
			cout<<"�����������ò���ȷ!"<<endl;
			break;
	case -2:
			cout<<"ʱ���������ò���ȷ!"<<endl;
			break;
	}
	d2.ShowDateTime(false, false); //��1 ��������ʾ��Ӣ�ķ�ʽ��ʾ����, ��2 ��������ʾ��AM PM �ķ�ʽ��ʾʱ��
	cout<<"��="<<d2.GetMonth()<<endl; //���濼��һ������ʵ�ִ˲�����
	cout<<"����="<<d2.GetMinute()<<endl; //���濼��һ������ʵ�ִ˲�����
}
