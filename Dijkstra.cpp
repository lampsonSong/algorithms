#include <iostream>

using namespace std;

void dijks(int* list,int* state,int currentIndex,int count);

	const int MAX = 100000;
	// initialize graph,there are 0,1,2,3,4,5 six points
	int graph[6][6] = {{MAX,  7,  9,MAX,MAX, 14},
		  	  {   7,MAX, 10, 15,MAX,MAX},
			  {   9, 10,MAX, 11,MAX,  2},
			  { MAX, 15, 11,MAX,  6,MAX},
			  { MAX,MAX,MAX,  6,MAX,  9},
			  {  14,MAX,  2,MAX,  9,MAX}};

int main()
{
	//shortest path points
	int list[6] = {-1,-1,-1,-1,-1,-1};
	//whether the point is visited, 0 -> no, 1 -> yes
	int state[6] = {0,0,0,0,0,0};
	//start point index
	int currentIndex = 0;
	state[currentIndex] = 1;

	//iterate all numbers
	int count = 0;

	list[0] = currentIndex;
	
	dijks(list,state,currentIndex,count);	

	return 0;
}

//recursive
void dijks(int* list,int* state,int currentIndex,int count)
{
	int temp;
	int minD = graph[currentIndex][currentIndex];
	int minID = currentIndex;;
	
	cout<<currentIndex<<endl;
	for(int i=0; i<6; i++)
	{
		temp = graph[currentIndex][i];
	        if(temp < minD && state[i] == 0)
		{
			minD = temp;
			minID = i;
		}	
	}
	currentIndex = minID;
	//change the visited state to 1
	state[currentIndex] = 1;
	count = count + 1;
	
	if(count < 6)
	{
		list[count] = currentIndex;
		dijks(list,state,currentIndex,count);
	}
}
