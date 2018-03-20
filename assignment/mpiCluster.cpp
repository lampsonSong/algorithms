#include <mpi.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

struct Pixel{
	int x;
	int y;
	int z;
	int index;
};

double dist(Pixel p1,Pixel p2)
{
	return sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2) + pow((p1.z-p2.z),2));
}


int main(int argc, char **argv)
{
	int myid, numprocs,dataNum,averageSize;
	int pointNum = 0;
	struct Pixel *pixel;
	Pixel *centuralPoint;
	Pixel *newCenturalPoint;
	int *clusterCount;
	int k;
	double minDist = -1;
	double d;
	double delta;
	double eps = 50;
	double t_start,t_end,t_dur;

	//define a struct
	MPI_Datatype myPixel;
	MPI_Datatype old_types[1];
	MPI_Aint indices[1];
	int blocklens[1];

	//Init MPI
	MPI_Init(&argc,&argv);

	blocklens[0] = 4;
	old_types[0] = MPI_INT;
	indices[0] = 0;
	MPI_Type_struct(1,blocklens,indices,old_types,&myPixel);
	MPI_Type_commit(&myPixel);

	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	/*	
	if(numprocs<2)
	{
		cout<<"At least 2 processes"<<endl;
		exit(0);
	}
	*/
	
	//master process
	if(myid == 0)
	{
		cout<<"Input K value:"<<endl;
		cin>>k;
	
		pixel = (Pixel*)malloc(sizeof(Pixel));
		
		ifstream fin("sample1.jpg.txt");	
		while(!fin.eof())
		{
			pixel = (Pixel*)realloc( pixel, (pointNum+1)*sizeof(Pixel) );
			fin>>pixel[pointNum].x>>pixel[pointNum].y>>pixel[pointNum].z;
			pixel[pointNum].index = 0;
			pointNum++;
		}
		fin.close();

		//time
		srand(time(NULL));		

		centuralPoint = (Pixel*)malloc(k*sizeof(Pixel));
		newCenturalPoint = (Pixel*)malloc(k*sizeof(Pixel));
		clusterCount = (int*)malloc(k*sizeof(int));
		
		t_start = MPI_Wtime();

		//random select k values	
		for(int i=0; i<k; i++)
		{
			centuralPoint[i] = pixel[rand()%pointNum+1];
		}
		//braodcast the total number of points,each processing data number for each process
		MPI_Bcast(&k,1,MPI_INT,0,MPI_COMM_WORLD);	
		MPI_Bcast(&pointNum,1,MPI_INT,0,MPI_COMM_WORLD);	
		MPI_Bcast(centuralPoint,k,myPixel,0,MPI_COMM_WORLD);	
		
		//the block size for each process, (7,3)->(2,2,3), averageSize = 2
		averageSize = pointNum/numprocs;
		dataNum = averageSize;
		for(int i=1; i<numprocs && numprocs>1; i++)
		{
			if(numprocs-i>1)
				dataNum = averageSize;
			else
				dataNum = pointNum - averageSize*i;
			MPI_Send(pixel+i*averageSize,dataNum,myPixel,i,0,MPI_COMM_WORLD);
		}


		//Begin clustering
		cout<<"Begin clustering"<<endl;
		do
		{		
		

		
		for(int i=0; i<k; i++)
		{
			clusterCount[i] = 0;
		}
		delta = 0;

		//compute 0-dataNum for master process
		for(int i=0; i<averageSize; i++)
		{
			for(int j=0; j<k; j++)
			{
				d = dist(pixel[i],centuralPoint[j]);
				if(j==0)
				{
					minDist = d;
					pixel[i].index = j;
				}
				else
				{
					if(d<minDist)
					{
						minDist = d;
						pixel[i].index = j;
					}
				}
			}
			clusterCount[pixel[i].index]++;
		}
		MPI_Barrier(MPI_COMM_WORLD);
		
		int ide;
		for(int i=0; i<k; i++)
		{
			newCenturalPoint[i].x = 0;
			newCenturalPoint[i].y = 0;
			newCenturalPoint[i].z = 0;
		}
		for(int i=0; i<dataNum; i++)
		{
			ide = pixel[i].index;
			newCenturalPoint[ide].x += pixel[i].x;
			newCenturalPoint[ide].y += pixel[i].y;
			newCenturalPoint[ide].z += pixel[i].z;
		}
		//receive new centural point from other processes
		Pixel *tempSumPoint = (Pixel*)malloc(k*sizeof(Pixel));
		int *tempClusterCount = (int*)malloc(k*sizeof(int));
		for(int i=1; i<numprocs; i++)
		{
			//receive sum of each cluster from different processes
			MPI_Recv(tempSumPoint,k,myPixel,i,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(tempClusterCount,k,MPI_INT,i,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			//for each cluster
			for(int j=0; j<k; j++)
			{
				newCenturalPoint[j].x += tempSumPoint[j].x;
				newCenturalPoint[j].y += tempSumPoint[j].y;
				newCenturalPoint[j].z += tempSumPoint[j].z;
				
				clusterCount[j] += tempClusterCount[j];		
			}
			
		}
		//new center points for each cluster
		for(int j=0; j<k; j++)
		{
			newCenturalPoint[j].x /= clusterCount[j];
			newCenturalPoint[j].y /= clusterCount[j];
			newCenturalPoint[j].z /= clusterCount[j];
		}
		free(tempSumPoint);
		free(tempClusterCount);
		//compute the delta difference between tow centers
		for(int j=0; j<k; j++)
		{
			delta  += dist(centuralPoint[j],newCenturalPoint[j]);
			centuralPoint[j] = newCenturalPoint[j];
		}
		//MPI_Bcast -> send in master process and receive in slave process
		MPI_Bcast(&delta,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
		MPI_Bcast(centuralPoint,k,myPixel,0,MPI_COMM_WORLD);
		
		}while(delta > eps);

		//end of clustering
		t_end = MPI_Wtime();

		t_dur = t_end - t_start;

		//collect data from all processes
		for(int i=1; i<numprocs; i++)
		{
			if(numprocs-i>1)
				dataNum = averageSize;
			else
				dataNum = pointNum - averageSize*i;
			MPI_Recv(pixel+i*averageSize,dataNum,myPixel,i,3,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
		cout<<"Clustering and collecting time is: "<<t_dur<<endl;

		//write into file
		ofstream fout("sample1.cluster.p.txt");
		for(int i=0; i<pointNum; i++)
		{
			fout<<pixel[i].index<<endl;	
		}
		fout.close();
	}
	else
	{
		//get the centural points from master process
		MPI_Bcast(&k,1,MPI_INT,0,MPI_COMM_WORLD);
		MPI_Bcast(&pointNum,1,MPI_INT,0,MPI_COMM_WORLD);	
		
		centuralPoint = new Pixel[k];
		newCenturalPoint = (Pixel*)malloc(k*sizeof(Pixel));
		clusterCount = (int*)malloc(k*sizeof(int));

		MPI_Bcast(centuralPoint,k,myPixel,0,MPI_COMM_WORLD);	
		
		//compute the data number for each process
		averageSize = pointNum/numprocs;
		
		if(numprocs-myid>1)
		{
			dataNum = averageSize;
		}
		else
		{
			dataNum = pointNum - averageSize * myid;
		}
		pixel = (Pixel*) malloc(dataNum*sizeof(Pixel)); 
		MPI_Recv(pixel,dataNum,myPixel,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);	
		
		//begin clustering
		do
		{


		
		for(int i=0; i<k; i++)
		{
			clusterCount[i] = 0;
		}
			
		for(int i=0; i<dataNum; i++)
		{
			for(int j=0; j<k; j++)
			{
				d = dist(pixel[i],centuralPoint[j]);
				if(j==0)
				{
					minDist = d;
					pixel[i].index = j;
				}
				else
				{
					if(d<minDist)
					{
						minDist = d;
						pixel[i].index = j;
					}
				}
			}
			clusterCount[pixel[i].index]++;
		}
		
		MPI_Barrier(MPI_COMM_WORLD);
		//cout<<pixel[206].index<<endl;
		
		int ide;
		for(int i=0; i<k; i++)
		{
			newCenturalPoint[i].x = 0;
			newCenturalPoint[i].y = 0;
			newCenturalPoint[i].z = 0;
		}
		for(int i=0; i<dataNum; i++)
		{
			ide = pixel[i].index;
			newCenturalPoint[ide].x += pixel[i].x;
			newCenturalPoint[ide].y += pixel[i].y;
			newCenturalPoint[ide].z += pixel[i].z;
		}
		MPI_Send(newCenturalPoint,k,myPixel,0,1,MPI_COMM_WORLD);
		MPI_Send(clusterCount,k,MPI_INT,0,2,MPI_COMM_WORLD);
		
		MPI_Bcast(&delta,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
		MPI_Bcast(centuralPoint,k,myPixel,0,MPI_COMM_WORLD);

		
		
		}while(delta > eps);

		//send back data to write into file
		MPI_Send(pixel,dataNum,myPixel,0,3,MPI_COMM_WORLD);
	}


		free(centuralPoint);
		free(newCenturalPoint);
		free(clusterCount);

	MPI_Finalize();
	return 0;
}

