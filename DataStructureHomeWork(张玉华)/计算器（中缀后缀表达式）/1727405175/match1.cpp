#include "Stack.cpp"


/*
	带有提示符的输入 


*/




class DeskCal1
{
	private:
		Stack StoredNumbers;
		
	public:
		void Input(char s)
		{
			if(s=='?')
			{
				double num;
				cin>>num;
				StoredNumbers.push(num);
			}
			if(s=='=')
			{
				
				cout<<StoredNumbers.top()<<endl;
				StoredNumbers.pop();
			}
			if(s=='+'||s=='-'||s=='*'||s=='/')
			{
				double num1,num2;
				num1 = StoredNumbers.top();
				StoredNumbers.pop();
				num2 = StoredNumbers.top();
				StoredNumbers.pop();
				if(s=='+')
				{
					StoredNumbers.push(num2+num1);
				}
				if(s=='-')
				{
					StoredNumbers.push(num2-num1);
				}
				if(s=='*')
				{
					StoredNumbers.push(num2*num1);
				}
				if(s=='/')
				{
					StoredNumbers.push(num2/num1);
				}
			}
			
		}
		
		void Cal()
		{
			char p;
			
			while(cin>>p)
			{
				
				Input(p);
				if(p=='=')
				{
					break;
				}
			}
		}
};






