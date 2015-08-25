/*
	this is a program design for calculating the helical parameters of G-DNA.As the 
	special of G-DNA,the reading  is set to read two base and choose base-pair or
	base-step to calculation.
	I get the least-squares fitted coordinates of base to calculate which is the same
	with 3DNA does.
zhuhong
2010.02.24
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#include "read_ndx.h"
#include "pdb.h"
#include "read_xtc.h"

using namespace std;

int main(int argc,char  * argv[])
{
	char * pdb_file;
	char * xtc_file;
	char * out_file;
	char * choose;
	int step=1;


	int serial_quartet_1;
	int serial_quartet_2;

	switch(argc)
	{
	case 11:
		for(int i=0;i<10;i++)
		{
			if(string(argv[i])=="-p")
			{
				pdb_file=argv[i+1];
			}
			if(string(argv[i])=="-f")
			{
				xtc_file=argv[i+1];
			}
			if(string(argv[i])=="-o")
			{
				out_file=argv[i+1];
			}
			if(string(argv[i])=="-num")
			{
				step=atoi(argv[i+1]);
			}
			if(string(argv[i])=="-c")
			{
				choose=argv[i+1];
			}

		}
		break;
	default:
		cout<<"Usage: g_pig_gmx -p *.pdb -f *.xtc -o *.xvg -c bs.bp -num skip"<<endl;
		exit(0);
	}

	struct chain * chain_head;
	struct atom * atom_head;
	atom_head=  read_pdb_to_atom(pdb_file);
	chain_head=read_pdb_to_chain(atom_head);

	
	print_chain(chain_head);

		cout<<"select a base:";
		cin>>serial_quartet_1;
		cout<<"select base "<<" : "<<get_base(chain_head,serial_quartet_1)<<"\t"<<serial_quartet_1<<endl;
	
		cout<<"select another base:";
		cin>>serial_quartet_2;
		cout<<"select base "<<"  : "<<get_base(chain_head,serial_quartet_2)<<"\t"<<serial_quartet_2<<endl;

	read_xtc2structure(xtc_file,out_file,choose,serial_quartet_1,serial_quartet_2,atom_head,step);
	
   	return 0;
}

