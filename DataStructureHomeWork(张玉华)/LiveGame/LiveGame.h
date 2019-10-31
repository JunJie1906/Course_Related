#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
#include<cstdio>

using namespace std;



class LiveGame
{
	private:

		char board[30][30];  //�浥λ 
		int Board[30][30];  //��neighbors��Ŀ 
	
	
	public:
		
		void InputByCoor();//�Դ���������� 
		void InputByString();  //���ַ�������,������-1ʱ��ֹͣ���� 
		void InputByFile(string f);  //���ļ�����
		void CountNeighbors(int row,int col);  //ͳ�ƣ�row��col�������ھ���Ŀ 
		void GetBoard(); //�õ��������̸���λ�õ��ھ���Ŀ 
		void Config(int i,int j);   //�ڣ�i��j�����ӻ��߼���һ��Ԫ��,����������������û������� 
		void Update();   //��������״̬ 
		void PrintBoard();    //��ӡ��ǰ����״̬ 
		void WriteBoard(string s);   //д���ļ� 
		void menu();  //����ѡ�� 
};
		
void LiveGame::InputByCoor()  //�Դ���������� 
{
	memset(board,' ',sizeof(board));
	int a,b;
	cin>>a>>b;
	while(a!=-1&&b!=-1)
	{
		
		board[a][b] = 'X';
		cin>>a>>b;
	}
}

void LiveGame::InputByString()  //���ַ�������,������-1ʱ��ֹͣ���� 
{
	memset(board,' ',sizeof(board));
	string s;
	int j=0;
	while(getline(cin,s)&&s!="-1")
	{
		int i=s.length();
		for(int p = 0;p<i;p++)
		{
			board[j][i] = 'X';
		}
		j++;
	}
	
	
}

void LiveGame::InputByFile(string f)  //���ļ����� 
{
	memset(board,' ',sizeof(board));
	ifstream fin;
	fin.open(f.data());
	 if(fin.is_open())
	 {
	 	cout<<"GOOD"<<endl;

		string s;
		int j = 0;
		while(getline(fin,s))
		{
			int len = s.length();
			for(int i =0;i<len;i++)
			{
				board[j][i] = s[i];
				
			}
			j++;
		}
		fin.close();
	} 
	else
	{
		cout<<"file open error!"<<endl;
	} 
	
	
	
}

void LiveGame::CountNeighbors(int row,int col)  //ͳ�ƣ�row��col�������ھ���Ŀ 
{
	int count =0;
	for(int i=row-1;i<=row+1;i++)
	{
		for(int j = col-1;j<=col+1;j++)
		{
			if(i==row&&j==col)
			{
				continue;
			}
			
			if(board[i][j]=='X')
			{
				count++;
			}
		}
	}
	Board[row][col] = count;
	
}


void LiveGame::GetBoard() //�õ��������̸���λ�õ��ھ���Ŀ 
{
	memset(Board,0,sizeof(Board));
	for(int i=1;i<30;i++)
	{
		for(int j=1;j<30;j++)
		{
			if(board[i][j]!=' ')
			{
				for(int p = i-1;p<=i+1;p++)
				{
					for(int q = j-1;q<=j+1;q++)
					{
						CountNeighbors(p,q);
					}
				}
			}
		}
	}
}


void LiveGame::Config(int i,int j)   //�ڣ�i��j�����ӻ��߼���һ��Ԫ��,����������������û������� 
{
	if (board[i][j] = ' ')
	{
		board[i][j] = 'X';
	}
	else
	{
		board[i][j] = ' ';
	}
}

void LiveGame::Update()   //��������״̬ 
{
	GetBoard(); 
    for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			if(Board[i][j] <= 1||Board[i][j]>=4)
			{
				board[i][j] = ' ';
			}
			if(Board[i][j]==3||Board[i][j]==2)
			{
				if(Board[i][j]==3)
				{
					board[i][j] = 'X';

				}
				if(Board[i][j]==2&&board[i][j]=='X')
				{

					board[i][j] = 'X';

				}
			}
		}
	}
	
	
	
	
	
}



void LiveGame::PrintBoard()    //��ӡ��ǰ����״̬ 
{
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			cout<<board[i][j];
		}
		cout<<endl;
	}
	
}	

void LiveGame::WriteBoard(string s)   //д���ļ� 
{
	ofstream fout(s.data());
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			fout<<board[i][j];
		}
		fout<<endl;
	}
}


void LiveGame::menu()  //����ѡ�� 
{
	cout<<"��ʼ������ʽѡ��: "<<endl;
	cout<<"1.Input Board In Coordinates"<<endl;
	cout<<"2.Input Board In String"<<endl;
	cout<<"3.Input Board In File"<<endl;
	cout<<endl;
	cout<<"config:"<<endl;
	cout<<"4.�޸�����"<<endl;
	cout<<"5.��������"<<endl;
	cout<<"6.��ӡ����"<<endl;
	cout<<"7.�ѵ�ǰ����״̬д���ļ�"<<endl;
	cout<<"8.�˳�"<<endl;
	cout<<"Input a number:"; 	
    
	int n;
	cin>>n;
	if(n==1)
	{
		InputByCoor();
		menu();
	}
	if(n==2)
	{
		InputByString();
		menu();
	}
	if(n == 3)
	{
		cout<<"Input File Location:";
		string filename;
		cin>>filename;
		InputByFile(filename);
		menu();
	}

	if(n == 4)
	{
		cout<<"Input (i,j):";
		int i,j;
		cin>>i>>j;
		Config(i, j);
		menu();
	}
	if(n==5)
	{
		Update();
		menu();
	}
	if(n==6)
	{
		PrintBoard();
		menu();
	}
	if(n == 7)
	{
		string f;
		cout<<"Input File Location:";
		cin>>f;
		WriteBoard(f);
		menu();
	}
	if(n==8)
	{
		cout<<"over"<<endl;
	}
} 
		
		





