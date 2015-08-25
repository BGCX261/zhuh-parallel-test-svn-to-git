#include "function.h"

vector<double> get_center(vector<double> coor_x,vector<double> coor_y,vector<double> coor_z,vector<double> mass)
{
	vector<double> center; 
	int N_x=coor_x.size();
	int N_y=coor_y.size();
	int N_z=coor_z.size();
	int N_m=mass.size();
	if(N_x=N_y=N_z=N_m)
	{
		double temp_x=0;
		double temp_y=0;
		double temp_z=0;
		double temp_m=0;

		for(int i=0;i<N_m;i++)
		{
			temp_x+=coor_x.at(i)*mass.at(i);
			temp_y+=coor_y.at(i)*mass.at(i);
			temp_z+=coor_z.at(i)*mass.at(i);
			temp_m+=mass.at(i);
		}

		center.push_back(temp_x/temp_m);
		center.push_back(temp_y/temp_m);
		center.push_back(temp_z/temp_m);

	}
	return  center;
}

double get_dist(vector<double> cent_1,vector<double> cent_2)
{
	double result=0;
	for(int i=0;i<3;i++)
	{
		result+=(cent_1.at(i)-cent_2.at(i))*(cent_1.at(i)-cent_2.at(i));
	}
	result=sqrt(result);
	return result;
}
