#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "string_operate.h"
#include "read_pdb.h"
#include "pdb.h"
#include "my_math.h"

using namespace std;

void Print_usage();

int main(int argc,char * argv[])
{
	char * in_file;
	
	switch(argc)
	{
		case 3:
			in_file=argv[2];
		break;

		case 2:
			Print_usage();
		exit(0);

	default:
		cout<<"usage: "<<argv[0] <<" -i move.in"<<endl;
		cout<<argv[0]<<" -h to see more information."<<endl;
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


void Print_usage()
{
	cout<<"\t\t"<<":-)  Move_pdb  (-:"<<endl;
	cout<<"------------------------------------------------"<<endl;
	cout<<"This is is a program design to move and rotate "<<endl;
	cout<<"the pdb file system. All the parameters are write"<<endl;
	cout<<"in the <move.in> file"<<endl;
	cout<<"------------------------------------------------"<<endl;
	cout<<endl;
	cout<<"      Option   Value  Description"<<endl;
	cout<<"------------------------------------------------"<<endl;
	cout<<"      -h       no     Print help info and quit. "<<endl;
	cout<<"      -i       <file> Set the input parameters. "<<endl;
	cout<<"------------------------------------------------"<<endl;
	cout<<endl;
	cout<<"Sample input file:"<<endl;
	cout<<"------------------------------------------------"<<endl;
	cout<<"<input file name>            # a file in pdb format"<<endl;
	cout<<"shift_x  shift_y  shift_z    #all in angstrom"<<endl;
	cout<<"rotate_x  rotate_y  rotate_z # all in degree"<<endl;
	cout<<"<output file name>"<<endl;
	cout<<"------------------------------------------------"<<endl;
	cout<<endl;
	cout<<"Program Move_pdb, VERSION 1.1.0"<<endl;
	cout<<"Written by Zhu H."<<endl;
	cout<<endl;
}

