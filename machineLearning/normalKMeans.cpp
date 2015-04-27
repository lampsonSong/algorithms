/*
Input	:	a file with lot of 3d points
Output	:	K clusters
2014-12-8
lampson	
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <math.h>

#include <time.h>

using namespace std;


struct Pixel
{
	int x;
	int y;
	int z;	
};


//compute the Euclidean distance of two points, the method name can not be named as distance
double dist(Pixel p1, Pixel p2)
{
	return sqrt( pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2) + pow((p1.z-p2.z),2) ); 
}

int main()
{
	clock_t t_start,t_end;
	vector<Pixel> points;
	Pixel pixel;
	int k;
	int pointNum = 0;
	double deltCenter = 0; // difference between old center and new center

	cout<<"Input K value:"<<endl;
	cin>>k;
	Pixel *centuralPoint = new Pixel[k];
	Pixel *newCentural = new Pixel[k];
	int *clusterCount = new int[k];

	for(int i=0; i<k; i++)
		clusterCount[i] = 0;
	
	cout<<"Loading data from file"<<endl;
	//read points from file
	ifstream fin("sample1.jpg.txt");
	string line;

	while(!fin.eof())
	{
		//assign number to points
		fin>>pixel.x>>pixel.y>>pixel.z;
		points.push_back(pixel);
		pointNum++;	
	}
	fin.close();
	
	cout<<"Begin clustering"<<endl;

	t_start = clock();

	int *cluster = new int[pointNum];
	//randomly select K points as the initial state
	for(int i=0; i<k; i++)
	{
		centuralPoint[i] = points[rand()%pointNum+1];
	}
	//delete(i);
	//double d = dist(points[initialState[0]],points[initialState[1]]);
	//clustering
		double d,minDist=-1; // distance

	do{
		deltCenter = 0;

		for(int i=0; i<pointNum; i++)
		{
			for(int j=0; j<k; j++)
			{
				d = dist(points[i],centuralPoint[j]);
				if(j == 0)
				{
					minDist = d;
					cluster[i] = j;
				}
				else
				{
					if(d<minDist)
					{
						minDist = d;
						cluster[i] = j;
					}
				}
			}
			clusterCount[cluster[i]]++;
		}
	//stop for loop, centural points are stable
		for(int j=0; j<k; j++)
		{
			newCentural[j].x = 0;
			newCentural[j].y = 0;
			newCentural[j].z = 0;	
		}
		for(int i=0; i<pointNum; i++)
		{
			int ide = cluster[i];
			pixel = points[i];
			
			newCentural[ide].x += pixel.x;
			newCentural[ide].y += pixel.y;
			newCentural[ide].z += pixel.z;				
		}
		for(int j=0; j<k; j++)
		{
			newCentural[j].x /= clusterCount[j];
			newCentural[j].y /= clusterCount[j];
			newCentural[j].z /= clusterCount[j];
			
			deltCenter += dist(centuralPoint[j],newCentural[j]);
			
			centuralPoint[j] = newCentural[j];	
		}
	}while(deltCenter > 50);

	t_end = clock();
	double t_dur = t_end - t_start;
	cout<<"Time consuming is: "<<t_dur/CLOCKS_PER_SEC<<endl;

	//write the cluster results into a file
	ofstream fout("sample1.cluster.txt");
	for(int i=0; i<pointNum; i++)
	{
		fout<<cluster[i]<<endl;	
	}
	fout.close();
	return 0;	
}
