/* 
 Author: Song Yuhao/lampson
 Date  : 2015-4-22
 Input : A dataset that contains training data, income && profit
	________________________________
  price per share	|   income   |  profit
	________________________________
	 0.09    		|  5811.89   |  723.73		(2010-06-30)
	________________________________
   	 0.33     		|  14421.93  |  2766.96		(2010-12-31)
	________________________________
	 0.047   		|  6565.74   |  591.51		(2011-06-30)
	_________________________________
	 0.22	    	| 15808.84   |  2748.51		(2011-12-31)
	_________________________________
	 0.034		    |  6816.92   |  427.39		(2012-06-30)
	_________________________________
	 0.096	    	|  15446.51  |  1605.50		(2012-12-31)
	_________________________________
	 0.04		    |  6002.91   |  496.79		(2013-06-30)
	_________________________________
	 0.53	 	    |  46342.22  |  16708.62	(2013-12-31)
	_________________________________
 Output : Predict profit in 2014
		The ground-truth value is
			_________________________
	-0.032		| 6002.91  |  -458.09
			_________________________
	0.59		| 47952.72 |  20162.84
			_________________________
*/

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	float trainData[8][3] = {		  
							  {0.09,  5811.89,  723.73},
							  {0.33,  14421.93, 2766.96},
							  {0.047, 6565.74,  591.51},
							  {0.22,  15808.84, 2748.51},
							  {0.034, 6816.92,  427.39},
							  {0.096, 15446.51, 1605.5},
							  {0.04,  6002.91,  496.79},
							  {0.53,  46342.22, 16708.62}
							 };
	
	//hypothesis result     profit = h(x) = theta_0 + theta_1*x_1 + theta_2*x_2
	//inititial state theta_0 = theta_1 = theta_2 = 0
	float theta_0 = 0;
	float theta_1 = 0;
	float theta_2 = 0;
	float E = 0;
	float alpha = 0.01;

	float theta_0_new;
	float theta_1_new;
	float theta_2_new;

	//record the step length
	float delta[3] = {0,0,0};
	float eps = 0.1;
	int count = 1;
	bool flag;
	/*
	   train theta
	*/
	do
	{
			for(int i = 0; i < 8; i++)
			{	
				E = theta_0 + theta_1 * trainData[i][0] + theta_2 * trainData[i][1] - trainData[i][2];
			

				theta_0_new = theta_0 - alpha * E * trainData[i][0];
				theta_1_new = theta_1 - alpha * E * trainData[i][1];
				theta_2_new = theta_2 - alpha * E * trainData[i][2];
					
			}
			cout<<"The "<<count<<" time"<<endl;
			cout<<theta_0_new<<endl;
			cout<<theta_1_new<<endl;
			cout<<theta_2_new<<endl;
			cout<<" "<<endl;

			//test the step length
			delta[0] = fabs(theta_0_new - theta_0);
			delta[1] = fabs(theta_1_new - theta_1);
			delta[2] = fabs(theta_2_new - theta_2);

			if(delta[0] > eps || delta[1] > eps || delta[2] > eps)
			{
				flag = true;
				theta_0 = theta_0_new;
				theta_1 = theta_1_new;
				theta_2 = theta_2_new;
				count++;
			}
			else
				flag = false;
	}while(flag);

	return 0;
}
