#include <iostream>

using namespace std;

//when the array is passed as a parameter, it would be regarded 
//as a pointer in C++
template <class T>  //Even passed by template, the array is passed by reference

int lis(T& A)
{
	int length = sizeof(A)/sizeof(A[0]);
	int len = 0;
	A[0] = 10;
	//pointer storing sub-length
	int* d = new int[length];

	for(int i = 0; i < length; i++)
	{
		d[i] = 1;
		for(int j = 0; j < i; j++)
		{
			if( A[i] >= A[j] && d[j] + 1 > d[i] )
				d[i] = d[j] + 1;
		}
		//pick the biggest length
		if( d[i] > len)
			len = d[i];
	}
	//remember to free what have claimed.
	free(d);

	return len;
}

int main()
{
	//test array data
	int A[] = {2,1,5,3,6,4,8,9,7};
	
	cout<<"The longest increasing subsequence length is "<<lis(A)<<endl;
	return 0;

}
