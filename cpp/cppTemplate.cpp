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

template<typename T> 
T ForAdd(T a,int times)
{
	T returnVal=0;
	for(int i=0; i<times; i++)
	{
		returnVal += a;
		a = a + 1;
	}

	return returnVal;
}

template<typename T> 
T ForAdd_reference(T& a,int times)
{
	T returnVal=0;
	for(int i=0; i<times; i++)
	{
		returnVal += a;
		a = a + 1;
	}

	return returnVal;
}

int main()
{
  int a = 1;
		float b = 3.1;
		std::cout<<"Out is :"<<ForAdd<int>(a,3)<<std::endl;
	 std::cout<<"Out is :"<<ForAdd<float>(b,3)<<std::endl;
		std::cout<<"after calling, a is : "<<a<<std::endl;

		std::cout<<"Out is :"<<ForAdd_reference<int>(a,3)<<std::endl;
		std::cout<<"after calling, a is : "<<a<<std::endl;
}

