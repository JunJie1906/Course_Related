#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
    
void Print(int count[26],char alpha1[26])
{
	int n =0;
	int max = count[0];
	for(int j=0;j<26;j++)
	{
		if(max<count[j])
		{
			max = count[j];
			n = j;
		}
	}
	if(max==0)
	{
		return;
	}

	count[n] = 0;
	cout<<alpha1[n]<<max<<endl;
	Print(count,alpha1);

}



int main()
{
	int count[26] ={0};
	char s[200];
	cin>>s;
	char alpha[26];
	int i = 0;
	int ct = 26;
	char a = 'z';
	while(ct)
	{
		alpha[ct-1] = a;
		a--;
		ct--;
	}
	while(s[i])
	{

		if(s[i]>='A'&&s[i]<='Z')
		{
			s[i]=s[i]+32;
		}
		for(int k =0;k<26;k++)
		{
			if(s[i]==alpha[k])
			{
				count[k]+=1;
			}
		}
		i++;
	}
	Print(count,alpha);
	return 0;
}
