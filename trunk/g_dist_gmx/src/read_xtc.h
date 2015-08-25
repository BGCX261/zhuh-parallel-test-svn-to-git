#ifndef  READ_XTC_H
#define READ_XTC_H

#include <vector>
#include <iostream>

#include "function.h"

using namespace std;

extern "C"
{
	#include "xdrfile_xtc.h"
}

vector<double>   read_xtc2dist(char * filename,vector<int> serial_1,vector<int> serial_2,vector<double> mass_1,vector<double> mass_2);


#endif
