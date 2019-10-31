#include<fstream>
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	int i, temp, t;
	ifstream fin("Data.txt");
	ofstream fout("Res.dat",ios::binary);
	if (fin.good() == true && fout.good() == true)
	{
		while(fin.eof()==false)
		{
			fin >> temp;
			if (temp)
			{
				fout.write((const char*)&temp, sizeof(int));
			}
		}
	}
	fin.close();
	fout.close();
	
	ifstream in("Res.dat", ios::binary);
	ofstream out("Res.txt");

	if (in.good() == true && out.good() == true)
	{
		i = 0;
		while(in.eof()==false)
		{
			in.read((char*)&temp,4);
		
			t = in.gcount();
			if(in.bad() == false && in.fail() == false) 
			{
				out<<setw(10)<<setfill('C')<<right<<temp;
			}
			i++;
			if (i % 2 == 0) 
			{
				out << endl; 
			}
		}

	}
	in.close();
	out.close();

}
