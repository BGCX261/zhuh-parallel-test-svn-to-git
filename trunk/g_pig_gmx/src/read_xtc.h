#ifndef  READ_XTC_H
#define READ_XTC_H

#include <vector>
#include <fstream>
#include <iomanip>

#include "pdb.h"
#include "matrix.h"
#include "m_f.h"

using namespace std;

extern "C"
{
	#include "xdrfile_xtc.h"
}


void  read_xtc2structure(char * filename,char * out_file, int ion_position,vector<int> quartet_1_serial,vector<int> quartet_2_serial,struct atom * atom_head ,int step_frame);

#endif

