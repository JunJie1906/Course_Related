#include<queue>
using namespace std;

class Cat
{
	private:
		int Play[110];
		
		queue<int> p1;
		
		queue<int> p2;
		
		int i ;
		
	public:
		Cat(); 
		
		void Input();
		
		bool P1Put();
		bool P2Put();
		
		void showP1();
		void showP2();
		
		void showplay();
		
		void play();
};
