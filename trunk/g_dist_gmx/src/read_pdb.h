#ifndef READ_PDB_H
#define READ_PDB_H

#include <vector>
#include <iostream>
#include <fstream>

#include "string_operate.h"

using namespace std;

vector<double> read_pdb_2_atom(char * top_file,vector<int > vi);

#endif