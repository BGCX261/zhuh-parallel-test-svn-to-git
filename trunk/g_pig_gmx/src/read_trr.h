#ifndef  READ_TRR_H
#define READ_TRR_H

#include <vector>
#include <fstream>
#include <iomanip>

#include "pdb.h"
#include "matrix.h"
#include "m_f.h"

using namespace std;

extern "C"
{
	#include "xdrfile_trr.h"
}


void  read_trr2structure(char * filename,char * out_file, int ion_position,vector<int> quartet_1_serial,vector<int> quartet_2_serial,struct atom * atom_head ,int step_frame);

#endif

