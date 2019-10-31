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
	//如果时间合法，则赋值，否则赋值0 时0 分0 秒
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
	//如果时间合法，则赋值并返回1，否则不赋值，并返回0
	int getHour();
	int getMinute();
	int getSecond();
	void ShowTime(bool flag);
	int init();
	int ShowMinute()
	{
		return m_minute;
	}
	//flag 为True 则以24 小时制显示时间，否则以 AM PM 的方式显示
};

class CDate
{
	int m_year,m_month,m_day;
public:
	CDate(int year=2000,int month=1,int day=1):m_year(year),m_month(month),m_day(day)//如果日期合法，则赋值，否则赋值2000 年1 月1 日
	{
		init();
	}
	//如果日期合法，则赋值，否则赋值2000 年1 月1 日
	int SetDate(int year=2000,int month=1,int day=1) //如果日期合法，则赋值并返回1，否则不赋值，并返回0
	{
		m_year=year;
		m_month = month;
		m_day=day;
		if(init()) return 1;
		else return 0;
	}
	//如果日期合法，则赋值并返回1，否则不赋值，并返回0
	int GetYear();
	int GetMonth();
	int GetDay();
	void ShowDate(bool flag);
	int init();
	int ShowMonth()
	{
		return m_month;
	}
	//flag 为TRUE，则以中文的方式显示日期，否则以MM/DD/YYYY 的方式显示日期

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

void CDate::ShowDate(bool flag) //flag 为TRUE，则以中文的方式显示日期，否则以MM/DD/YYYY 的方式显示日期
{
	if(flag)
	{
		cout<<m_year<<"年 "<<m_month<<"月 "<<m_day<<"日"<<endl; 
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
	d1.ShowDateTime(false, true); //第1 个参数表示以英文方式显示日期, 第2 个参数表示以24 小时制方式显示时间

	CDateTime d2;
	d2.ShowDateTime(true, false); //第1 个参数表示以中文方式显示日期, 第2 个参数表示以AM PM 的方式显示时间

	int iStatus;
	iStatus=d2.SetDateTime(2014, 5, 2, 21, 55, 5);
	switch(iStatus)
	{
	case 1:
			cout<<"日期和时间数据设置正确!"<<endl;
			break;
	case -1:
			cout<<"日期数据设置不正确!"<<endl;
			break;
	case -2:
			cout<<"时间数据设置不正确!"<<endl;
			break;
	}
	d2.ShowDateTime(false, false); //第1 个参数表示以英文方式显示日期, 第2 个参数表示以AM PM 的方式显示时间
	cout<<"月="<<d2.GetMonth()<<endl; //认真考虑一下如何实现此操作？
	cout<<"分钟="<<d2.GetMinute()<<endl; //认真考虑一下如何实现此操作？
}

