//
//
//
//		Date 		: 		2016-11-30
//		Objective 	: 		give an example of template in CPP
//		Author 		: 		lampson
//
//
//

#include <iostream>

using namespace std;

template<typename T> 
T ForAdd(T a,int times)
{
	T returnVal=0;
	for(int i=0; i<times; i++)
	{
		returnVal += a;
	}

	return returnVal;
}

int main()
{
	cout<<"Out is :"<<ForAdd(1,3)<<endl;
	cout<<"Out is :"<<ForAdd(3.1,3)<<endl;
}

