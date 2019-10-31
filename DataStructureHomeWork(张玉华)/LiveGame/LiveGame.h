#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
#include<cstdio>

using namespace std;



class LiveGame
{
	private:

		char board[30][30];  //存单位 
		int Board[30][30];  //存neighbors数目 
	
	
	public:
		
		void InputByCoor();//以存活坐标输入 
		void InputByString();  //以字符串输入,当输入-1时候停止输入 
		void InputByFile(string f);  //以文件输入
		void CountNeighbors(int row,int col);  //统计（row，col）处的邻居数目 
		void GetBoard(); //得到现在棋盘各个位置的邻居数目 
		void Config(int i,int j);   //在（i，j）增加或者减少一个元素,如果有则消除，如果没有则添加 
		void Update();   //更新棋盘状态 
		void PrintBoard();    //打印当前棋盘状态 
		void WriteBoard(string s);   //写入文件 
		void menu();  //各个选项 
};
		
void LiveGame::InputByCoor()  //以存活坐标输入 
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

void LiveGame::InputByString()  //以字符串输入,当输入-1时候停止输入 
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

void LiveGame::InputByFile(string f)  //以文件输入 
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

void LiveGame::CountNeighbors(int row,int col)  //统计（row，col）处的邻居数目 
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


void LiveGame::GetBoard() //得到现在棋盘各个位置的邻居数目 
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


void LiveGame::Config(int i,int j)   //在（i，j）增加或者减少一个元素,如果有则消除，如果没有则添加 
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

void LiveGame::Update()   //更新棋盘状态 
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



void LiveGame::PrintBoard()    //打印当前棋盘状态 
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

void LiveGame::WriteBoard(string s)   //写入文件 
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


void LiveGame::menu()  //各个选项 
{
	cout<<"初始输入形式选择: "<<endl;
	cout<<"1.Input Board In Coordinates"<<endl;
	cout<<"2.Input Board In String"<<endl;
	cout<<"3.Input Board In File"<<endl;
	cout<<endl;
	cout<<"config:"<<endl;
	cout<<"4.修改棋盘"<<endl;
	cout<<"5.更新棋盘"<<endl;
	cout<<"6.打印棋盘"<<endl;
	cout<<"7.把当前棋盘状态写入文件"<<endl;
	cout<<"8.退出"<<endl;
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
		
		





