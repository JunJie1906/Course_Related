typedef double Stack_entry;

class Stack
{
	private:
		Stack_entry s[1000];
		int i;
		
	public:
		Stack(); 
		
		void push(Stack_entry entry);
		
		void pop();
		
		Stack_entry top();
		
		bool empty();
		
};


