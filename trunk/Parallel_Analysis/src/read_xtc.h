#ifndef  READ_XTC_H
#define READ_XTC_H

#include <vector>
#include <fstream>
#include <iomanip>

#include "pdb.h"
#include "matrix.h"
#include "m_f.h"
#include "string_operate.h"

using namespace std;

extern "C"
{
	#include "xdrfile_xtc.h"
	#include "xdrfile_trr.h"
}

void  read_xtc2Rotation_matrix(char * filename,const char * out_file,int base_serial,struct atom * atom_head,int step_frame);
void  read_trr2Rotation_matrix(char * filename,const char * out_file,int base_serial,struct atom * atom_head,int step_frame );
void  Parallel_analysis(char * filename,char * out_file,vector<int> group_1_serial,vector<int> group_2_serial,struct atom * atom_head ,int step_frame);

#endif

