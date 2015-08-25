#ifndef READ_PDB_H
#define READ_PDB_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "string_operate.h"
#include "pdb.h"
#include "my_math.h"

using namespace std;

vector<double> read_pdb_2_atom(char * top_file,vector<int > vi);
struct atom *  shift_atom(struct atom * atom_st, double shift_x, double shift_y, double shift_z);
struct atom *  whirl_atom(struct atom * atom_shift, double oren_x, double oren_y, double oren_z);
void write_pdb(struct atom * atom_write, char * file_name);

#endif