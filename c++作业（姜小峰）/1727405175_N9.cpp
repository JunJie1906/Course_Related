#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
    
int main()
{
	for(int k=0;k<100;k++)
	{
		for(int j=0;j<33;j++)
		{
			for(int i=0;i<20;i++)
			{
				if(k*3+j+i==100 )
				{
					if(k+i*5+j*3==100)
					{
						cout<<i<<"  "<<j<<"  "<<k*3<<endl;
						
					}
				}

			}
		}
	}

}
