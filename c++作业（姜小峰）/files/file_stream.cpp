#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int i,temp,t;

	ifstream fin("abc.txt");							//���ı��ļ�����ʽ�򿪵�ǰĿ¼�µ�abc.txt�ļ������ڶ�ȡ����
	ofstream fout("123.dat", ios::binary);		//�Զ������ļ�����ʽ�򿪵�ǰĿ¼�µ�123.dat�ļ�������д�����
	
	if(fin.good()==true && fout.good()==true)	//�˴����ж����������ļ��򿪲����Ƿ����������κ��쳣��good�����᷵��false
	{
		while(fin.eof()==false)								//��abc.txt�ļ���ȡ��ĩβʱ��eof��������true																
		{
//			fin>>temp;
//			if (fin.bad()==false && fin.fail()==false)	//�ڶ�ȡ�з����κ��쳣��������쳣ԭ����bad��fail��������һ������true����ʾ�������쳣
			if (fin>>temp)	//�ڶ�ȡ�з����κ��쳣��������쳣ԭ����bad��fail��������һ������true����ʾ�������쳣
				fout.write((const char *) &temp,sizeof(int));
		}
	}
	else
	{
		if(fin.good()==false)
			cout<<"Error:cannot open file 'abc.txt' "<<endl;
		if(fout.good()==false)
			cout<<"Error:cannot open file '123.dat' "<<endl;

		return 0;
	}
	fin.close();
	fout.close();

	fin.open("123.dat",ios::binary);		//�Զ������ļ�����ʽ�򿪵�ǰĿ¼�µ�123.dat�ļ������ڶ�ȡ����
	fout.open("new.txt");
	if(fin.good()==true && fout.good()==true)
	{
		i=0;
		while (fin.eof() == false)																							
		{
			fin.read( (char *) &temp, sizeof(int));
			t = fin.gcount();	//�˺����᷵�ض�ȡ�ɹ����ֽ���
			
			if (fin.bad()==false && fin.fail()==false)
			{
				fout<<setw(8)<<left<<temp;			//��ҿ������һ�������cout���ļ�������Ĺ����п�����ʾ��ʽ
			
				i++;
				if( i%10 == 0)
					fout<<endl;
			}
		}
		if( i%10 != 0)
			fout<<endl;
	}
	else
	{
		if(fin.good()==false)
			cout<<"Error:cannot open file '123.dat' "<<endl;
		if(fout.good()==false)
			cout<<"Error:cannot open file 'new.txt' "<<endl;

		return 0;
	}

	fin.close();
	fout.close();
}
