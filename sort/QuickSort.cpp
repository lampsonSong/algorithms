#include <iostream>

using namespace std;

//Input: array, begin index, end index
//Output: Max index of the smaller part
int partition(int a[],int begin, int end)
{
	int median = a[end];
	int maxIndexOfSmaller = begin;
	int temp;

	for(int m = begin; m < end; m++)
	{
		if(a[m] < median)
		{
			//not the same number, convert them
			if(m != maxIndexOfSmaller)
			{
				//Convert a[m] and a[maxIndexOfSmaller]
				temp = a[m];
				a[m] = a[maxIndexOfSmaller];
				a[maxIndexOfSmaller] = temp;
			}
			maxIndexOfSmaller++;
		}
	}
	temp = a[end];
	a[end] = a[maxIndexOfSmaller];
	a[maxIndexOfSmaller] = temp;

	return maxIndexOfSmaller;
}

//input: array, begin, end
//Output: ascending array
void QuickSort(int a[], int begin, int end)
{
	if(begin < end)
	{
		int q = partition(a,begin,end);
		QuickSort(a,begin,q-1);
		QuickSort(a,q+1,end);
	}
}

int main()
{
	int size;
	cout<<"Input Array size:";
	cin>>size;
	
	int array[size];

	cout<<"Input Array data:"<<endl;
	for(int i = 0; i < size; i++)
	{
		cin>>array[i];
	}
	cout<<endl;
	QuickSort(array,0,size-1);
	
	for(int i = 0; i < size; i++)
	{
		cout<<array[i]<<"   ";
	}
	cout<<endl;
}
