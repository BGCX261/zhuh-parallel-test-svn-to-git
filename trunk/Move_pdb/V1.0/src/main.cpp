#include <iostream>
#include <fstream>
#include <string>

#include "string_operate.h"
#include "read_pdb.h"
#include "pdb.h"
#include "my_math.h"

using namespace std;

int main(int argc,char * argv[])
{
	char * in_file;
	
	switch(argc)
	{
		case 3:
			in_file=argv[2];
		break;
	default:
		cout<<"usage: move_pdb -i move.in"<<endl;
		exit(0);
	}

	string pdb_file;
	string pdb_out_file;

	double cent_x=0;
	double cent_y=0;
	double cent_z=0;
	double oren_x=0;
	double oren_y=0;
	double oren_z=0;

   ifstream read_in(in_file);
  
   string temp_s;

   getline(read_in,temp_s);
   pdb_file=temp_s;

   getline(read_in,temp_s);
   cent_x=atof(Split(temp_s,' ',0).c_str());
   cent_y=atof(Split(temp_s,' ',1).c_str());
   cent_z=atof(Split(temp_s,' ',2).c_str());

    getline(read_in,temp_s);
	oren_x=atof(Split(temp_s,' ',0).c_str())/180*PI;
	oren_y=atof(Split(temp_s,' ',1).c_str())/180*PI;
	oren_z=atof(Split(temp_s,' ',2).c_str())/180*PI;

	getline(read_in,temp_s);
	pdb_out_file=temp_s;

	read_in.close();

	struct atom * atom_struct;
	atom_struct=read_pdb_to_atom((char *)pdb_file.c_str());
	struct atom * atom_shift=shift_atom(atom_struct, cent_x, cent_y, cent_z);
	struct atom * atom_whirl=whirl_atom(atom_shift,oren_x,oren_y,oren_z);

	write_pdb(atom_whirl, (char *)pdb_out_file.c_str());

}



