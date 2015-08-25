/*
	this is a program design for calculating the position of ions in the cavity of 
G-quartets.It's already konw that for the ions of K,the stably place is the middle
state between two G-quartets.In the program,we get the z-axis plumb the 
surface of G-quartets.and get the distribution of ions  along the z-axis.
	I get the least-squares fitted coordinates of base to calculate the z-axis. what
is the same with 3DNA does.
zhuhong
2010.01.25
*/

#include <iostream>
#include <string>

#include "pdb.h"
#include "read_xtc.h"
#include <stdlib.h>

using namespace std;

int main(int argc,char  * argv[])
{
	char * pdb_file;
	char * xtc_file;
	char * out_file;
	int step=1;

	vector<int> serial_quartet_1;
	vector<int> serial_quartet_2;

	switch(argc)
	{
	case 9:
		for(int i=0;i<8;i++)
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

		}
		break;
	default:
		cout<<"Usage: Parallel_Analysis -p *.pdb -f *.xtc -o *.xvg -num step"<<endl;
		exit(0);
	}

	//read pdb file to select the two quartets
	struct chain * chain_head;
	struct atom * atom_head;
	atom_head=  read_pdb_to_atom(pdb_file);
	chain_head=read_pdb_to_chain(atom_head);
	
	print_chain(chain_head);
	while(1)
	{
		cout<<"select a serial number of base for the 1st Group(press -1 to break):";
		int temp_num;
		cin>>temp_num;
		if(temp_num>0)
		{
			serial_quartet_1.push_back(temp_num);
			cout<<"select base: "<<get_base(chain_head,temp_num)<<"\t"<<temp_num<<endl;
		}
		else
		{
			cout<<"Finished choose for group 1."<<endl;
			break;
		}
	}
	while(1)
	{
		cout<<"select a serial number of base for the 2nd Group(press -1 to break):";
		int temp_num;
		cin>>temp_num;
		if(temp_num>0)
		{
			serial_quartet_2.push_back(temp_num);
			cout<<"select base: "<<get_base(chain_head,temp_num)<<"\t"<<temp_num<<endl;
		}
		else
		{
			cout<<"Finished choose for group 2."<<endl;
			break;
		}
	}

//	if(st.find(".xtc")<50)
//	{
		Parallel_analysis(xtc_file,out_file,serial_quartet_1,serial_quartet_2,atom_head,step);
//	}
//	else
//	{
	//	read_trr2structure(xtc_file,out_file,serial,serial_quartet_1,serial_quartet_2,atom_head,step);
//	}

	return 0;
}

