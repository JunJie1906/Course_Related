#include "match1.cpp"


class DeskCal2
{
	private:
		Stack StoredNumbers;
		string s;
		
	public:
		
		DeskCal2(string s1="  ")  //初始化 
		{
			s = s1;
		}
		
		
		void Cal()
		{
			
			bool point = false;   //判断double小数点是否存在 
			bool caled = false;   //当未计算而输出时，输出wrong input 
			int ti = 1;          //小数的位数 
			bool right = true;  //表达式是否正确 
			int len = s.length(); 
			double num = 0;       //得到的数字 
			
			for(int i=0;i<len;i++)
			{
				if(right==false)
				{
					break;
				}
				
				if(s[i]=='.')
				{
					point = true;
				}
				
				
				if(int(s[i])<=57&&int(s[i])>=48)    //是否为数字字符 
				{
					if(i==len-1)           //最后一个字符为数字，表达式错误 
					{
						right = false;
					}
					
					if(point) //当是数字时候，判断是否有小数点，来得到小数 
					{
						double n = s[i]-48;
						for(int o=0;o<ti;o++) 
						{
							n/=10;
						}
						ti++;
						num+=n;
					}
					else
					{
						num*=10;
						num+=(int(s[i])-48);
					}

				}
				
				
				if(s[i]==' ')
				{
	
					if(s[i-1]==' ')
					{
						right = false;
					}
					if(int(s[i-1])<=57&&int(s[i-1])>=48)
					{
						StoredNumbers.push(num);
						num = 0;
						ti = 1;
						point = false;
					}
	
				}
				
				
				if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')
				{
					
					if(s[i-1]!=' ')
					{
						right = false;
					}
					else
					{
						if(StoredNumbers.empty())
						{
							right = false;
							break;
						}
						
						
						double num1,num2;
						num1 = StoredNumbers.top();
						StoredNumbers.pop();
						
						if(StoredNumbers.empty())
						{
							right = false;
							break;
						}
						num2 = StoredNumbers.top();
						StoredNumbers.pop();
						
						if(s[i]=='+')
						{
							StoredNumbers.push(num2+num1);
							caled=true;
						}
						if(s[i]=='-')
						{
							StoredNumbers.push(num2-num1);
							caled=true;
						}
						if(s[i]=='*')
						{
							StoredNumbers.push(num2*num1);
							caled=true;
						}
						if(s[i]=='/')
						{
							StoredNumbers.push(num2/num1);
							caled=true;
						}
					}

					
				}
				
				
				
			}
			
			if(StoredNumbers.empty())
			{
				cout<<"wrong input"<<endl;
			}
			else
			{
				double tp = StoredNumbers.top();
				StoredNumbers.pop();
				if(StoredNumbers.empty()&&right == true&&caled == true)
				{
					cout<<tp<<endl;
				}
				else
				{
					cout<<"wrong input"<<endl;
				}
			}
		}
};


