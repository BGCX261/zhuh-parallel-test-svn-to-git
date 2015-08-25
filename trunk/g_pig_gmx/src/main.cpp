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

#include "read_ndx.h"
#include "pdb.h"
#include "read_xtc.h"
#include "read_trr.h"

using namespace std;

int main(int argc,char  * argv[])
{
	char * pdb_file;
	char * xtc_file;
	char * ndx_file;
	char * out_file;
	int step=1;

	int num_ion;

	vector<int> serial_quartet_1;
	vector<int> serial_quartet_2;

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
			if(string(argv[i])=="-n")
			{
				ndx_file=argv[i+1];
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
		cout<<"Usage: g_pig_gmx -p *.pdb -f *.xtc -n *.ndx -o *.xvg -num step"<<endl;
		exit(0);
	}
	//select  the ions serial.
	vector<string>  vs_temp=read_2_group(ndx_file);
	vector<int> vi_temp=read_2_group_n(ndx_file);
	for(int i=0;i<vs_temp.size();i++)
	{
		cout<<i<<"\t"<<vs_temp.at(i)<<"\t"<<vi_temp.at(i)<<endl;
	}
	cout<<"Select the ion:";
	cin>>num_ion;
	cout<<"Select the ion:"<<vs_temp.at(num_ion)<<endl;;
	vector<int>  vi_serial =read_group_2_serial(ndx_file, vs_temp.at(num_ion));

	//read pdb file to select the two quartets
	struct chain * chain_head;
	struct atom * atom_head;
	atom_head=  read_pdb_to_atom(pdb_file);
	chain_head=read_pdb_to_chain(atom_head);

	
	print_chain(chain_head);
	for(int i=0;i<4;i++)
	{
		cout<<"select a serial number of guanine for the 1st G-quartet:";
		int temp_num;
		cin>>temp_num;
		serial_quartet_1.push_back(temp_num);
		cout<<"select base "<<i+1<<" : "<<get_base(chain_head,temp_num)<<"\t"<<temp_num<<endl;
	}
	for(int i=0;i<4;i++)
	{
		cout<<"select a serial number of guanine for the 2nd G-quartet:";
		int temp_num;
		cin>>temp_num;
		serial_quartet_2.push_back(temp_num);
		cout<<"select base "<<i+1<<"  : "<<get_base(chain_head,temp_num)<<"\t"<<temp_num<<endl;
	}

	int serial=vi_serial.at(0);
	string st=string(xtc_file);
	if(st.find(".xtc")<50)
	{
		read_xtc2structure(xtc_file,out_file,serial,serial_quartet_1,serial_quartet_2,atom_head,step);
	}
	else
	{
		read_trr2structure(xtc_file,out_file,serial,serial_quartet_1,serial_quartet_2,atom_head,step);
	}




	return 0;
}

