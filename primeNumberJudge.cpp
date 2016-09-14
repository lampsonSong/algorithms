//
//
// 	Date 	: 		2016-9-16
//	Author 	: 		lampson
//	Input 	: 		A random integer number
//	Output 	: 		Whether it is a prime number
//
//
//


#include <iostream>
#include <math.h>
using namespace std;

int judge(int num)
{
	int last_i = 1;
	int result=1;
	for(int i=2; i<=ceil(num/last_i); i++)
	{
		if(num%i==0)
		{
			result = 0;
			break;
		}
		else
			last_i ++;
	}
	return result;
}

int main()
{
	int num;
	cout<<"Input one random number: "<< endl;
	cin>>num;

	if(judge(num))
		cout<<"Yes, it is!"<<endl;
	else
		cout<<"No, it is not"<<endl;

	return 0;
}
