/*
this program is design for create pqr file for ligand file.
It's base on the pqr file of ligand .
*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "string_operate.h"
#include "pqr_core.h"


using namespace std;

int main( int argc,char * argv[] )
{
	char * ligand_pqr;
	char * result_pqr;
	char * read_pdb;
	switch (argc)
	{
	case 7:
		for(int i=0;i<7;i++)
		{
			if(string(argv[i])=="-i")
			{
				read_pdb=argv[i+1];
			}
			if(string(argv[i])=="-f")
			{
				ligand_pqr=argv[i+1];
			}
			if(string(argv[i])=="-o")
			{
				result_pqr=argv[i+1];
			}

		}
		break;
	default:
		cout<<"Usage : my_pdb2pqr -f ligand.pqr -i pdb_input.pdb -o out.pqr"<<endl;
		exit(0);
	}


	struct pqr * pqr_resu= Read_pqr(ligand_pqr);

	ifstream in_pdb(read_pdb);
	ofstream out_pqr(result_pqr);

	string s_pdb;
	
	while(!in_pdb.fail())
	{
		getline(in_pdb,s_pdb);
		if(s_pdb.find("ATOM")<10||s_pdb.find("HETATM")<10)
		{
			if(string(pqr_resu->name)==Split(s_pdb.substr(12,4),' ',0))
			{
				out_pqr<<s_pdb.substr(0,56)<<setiosflags(ios::right)<<setw(7)<<setprecision(4)<<pqr_resu->charge<<setiosflags(ios::right)<<setw(7)<<setprecision(4)<<pqr_resu->radii<<endl;
			}
			else
			{
				cout<<"Segment error!"<<endl;
				exit(0);
			}	
			pqr_resu=pqr_resu->next;
		}


	}
	out_pqr.close();
	cout<<"write pqr file "<< result_pqr<<endl;

}
