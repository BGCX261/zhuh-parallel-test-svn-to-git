#ifndef  READ_XTC_H
#define READ_XTC_H

#include <vector>
#include <fstream>
#include <iomanip>

#include "pdb.h"
#include "matrix.h"
#include "m_f.h"
#include "structure.h"
using namespace std;
/*
#define DEBUG
*/
extern "C"
{
	#include "xdrfile_xtc.h"
}


void  read_xtc2structure(char * filename,char * out_file, char * choose,int base_1_serial,int base_2_serial,struct atom * atom_head,int step_frame );

#endif
