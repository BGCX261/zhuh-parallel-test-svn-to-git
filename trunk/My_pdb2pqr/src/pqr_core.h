#ifndef PQR_CORE_H
#define PQR_CORE_H

#include <iostream>
#include <fstream>
#include <string>

#include "string_operate.h"

using namespace std;

struct pqr
{
	char  name[10];
	double radii;
	double charge;
	struct pqr * next;
};

struct pqr * Read_pqr(char * pqr_file);


#endif