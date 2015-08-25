/*
  this file is aim to calculate the center of a group and the distance between two groups.
what important is that the result of this porgram is a little difference with the result 
of g_dist from GROMACS program. I hope to know why?
	zhuhongaaa@gmail.com
	2010.01.14
  
*/
#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <cmath>

using namespace std;

vector<double>  get_center(vector<double> coor_x,vector<double> coor_y,vector<double> coor_z,vector<double> mass);
double get_dist(vector<double> cent_1,vector<double> cent_2);

#endif

