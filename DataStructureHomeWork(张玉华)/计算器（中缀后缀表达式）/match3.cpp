#include "match2.cpp"
#include<vector>
#include<stack>

class MidCal
{
	private:
		stack<char> opt;
		string ans;      
		string inp; 
	public:
		
		
		
		MidCal(string s=" ")  //初始化 
		{
			inp = s;
			ans = "";
			opt.push('%');
		}
		
		int prio(char s)
		{
			if(s=='(')
			{
				return 3;
			}
			if(s=='*'||s=='/')
			{
				return 2;
			}
			if(s=='+'||s=='-')
			{
				return 1;
			}
			if(s==')')
			{
				return 0;
			}
			else
			{
				return -1;
			}
		}
		
		
		void chmod()
		{
			int len = inp.length();
		
			for(int i=0;i<len;i++)
			{
				if(inp[i]=='.')
				{
					ans+=inp[i];		
					
				}
				else
				{
					if(int(inp[i])<=57&&int(inp[i])>=48)
					{
						ans+=inp[i];						
					}
					else
					{

						ans+=' ';
						
						if(opt.top()!='(')
						{
							if(prio(opt.top())<=prio(inp[i]))
							{
								opt.push(inp[i]);
					
							}
							else
							{
								if(inp[i]==')')
								{
									while(opt.top()!='(')
									{
										ans+=opt.top();
										ans+=' ';
										opt.pop();
									}
									opt.pop();
								}
								else
								{
									while(prio(opt.top())>prio(inp[i]))
									{
											ans+=opt.top();
											ans+=' ';
											opt.pop();
									}
	
									opt.push(inp[i]);
								}

							}
							
						}
						else
						{
							if(inp[i]==')')
							{
								opt.pop();
							}
							else
							{
								opt.push(inp[i]);
							}

						}
						
						
						

					}
				}	
			 } 
			 ans+=' ';
			 while(!opt.empty())
			 {
			 	ans+=opt.top();
			 	ans+=' ';
			 	opt.pop();
 	
			 }
			 
			 
			
			ans.erase(--ans.end());
			ans.erase(--ans.end());
			ans.erase(--ans.end());
			
			int le = ans.length();
			
			string ans1(ans);
			ans = "";
			for(int i=0;i<le-1;i++)   //去空格 
			{
				if(ans1[i]==' '&&ans1[i+1]==' ')
				{
					continue;
				}
				else
				{
					ans+=ans1[i];
				}
				
				
			}
			ans+=ans1[le-1];
		}
		
		
		
		
		void Cal()
		{
			chmod();
			DeskCal2 p(ans);
			p.Cal();
			
		}
		
		

};



