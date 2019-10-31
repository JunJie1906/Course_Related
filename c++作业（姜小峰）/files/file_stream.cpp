#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int i,temp,t;

	ifstream fin("abc.txt");							//以文本文件的形式打开当前目录下的abc.txt文件，用于读取操作
	ofstream fout("123.dat", ios::binary);		//以二进制文件的形式打开当前目录下的123.dat文件，用于写入操作
	
	if(fin.good()==true && fout.good()==true)	//此处是判断上述两个文件打开操作是否正常。如任何异常，good函数会返回false
	{
		while(fin.eof()==false)								//当abc.txt文件读取到末尾时，eof函数返回true																
		{
//			fin>>temp;
//			if (fin.bad()==false && fin.fail()==false)	//在读取中发生任何异常，会根据异常原因导致bad和fail函数至少一个返回true，表示出现了异常
			if (fin>>temp)	//在读取中发生任何异常，会根据异常原因导致bad和fail函数至少一个返回true，表示出现了异常
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

	fin.open("123.dat",ios::binary);		//以二进制文件的形式打开当前目录下的123.dat文件，用于读取操作
	fout.open("new.txt");
	if(fin.good()==true && fout.good()==true)
	{
		i=0;
		while (fin.eof() == false)																							
		{
			fin.read( (char *) &temp, sizeof(int));
			t = fin.gcount();	//此函数会返回读取成功的字节数
			
			if (fin.bad()==false && fin.fail()==false)
			{
				fout<<setw(8)<<left<<temp;			//大家可以体会一下如何在cout和文件流输出的过程中控制显示格式
			
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
