#include <iostream>
using namespace std;
//Input:  an any orderd array
//Output: ascending ordered array
void bubble(int temp[],int size)
{
	int tempInt;
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size-i-1; j++)
		{
			if(temp[j] > temp[j+1])
			{
				tempInt = temp[j];
				temp[j] = temp[j+1];
				temp[j+1] = tempInt;
			}
		}

	for(int i = 0; i < size; i++)
		printf("%d   ", temp[i]);
	printf("\n");
}

int main()
{
	int size;
	cout<<"Input an array size"<<endl;
	cin>>size;
	int array[size];
	cout<<"Input the array:"<<endl;
	
	for(int i = 0; i < size; i++)
	{
		cin>>array[i];
	}
	bubble(array,size);
}
