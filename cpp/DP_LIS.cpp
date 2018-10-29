/*
	* Input  : an int array[]
	* Output : max length of decrease subsequence
	*/

#include <iostream>

using namespace std;

//when the array is passed as a parameter, it would be regarded 
//as a pointer in C++
template <class T>  //Even passed by template, the array is passed by reference

int lis(T& A)
{
		int length = sizeof(A)/sizeof(A[0]);
		int result = 0;

		//pointer storing sub-length
		int* d = new int[length];

		for(int i = 0; i < length; i++)
		{
				if(i == 0)
						d[i] = 1;
				else
				{
						if(A[i] <= A[i-1])
								d[i] = d[i-1] + 1;
						else
								d[i] = 1;
				}

				//pick the biggest length
				if( d[i] > result)
						result = d[i];
		}
		//remember to free what have claimed.
		delete d;

		return result;
}

int main()
{
		//test array data
		int A[] = {2,3,1,4,6,3,1,2,5,7,9};

		cout<<"The longest increasing subsequence length is "<<lis(A)<<endl;
		return 0;

}
