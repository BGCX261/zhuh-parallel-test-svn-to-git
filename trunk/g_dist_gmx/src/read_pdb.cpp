#include "read_pdb.h"



vector<double>  read_pdb_2_atom(char * pdb_file,vector<int > vi)
{
	vector<double> vd;
	string s;
	int num=0;
	ifstream in(pdb_file);
	getline(in,s);
	while(!in.fail())
	{
		while(s.find("ATOM")<20&&!in.fail())
			 {			  
				 if(num<vi.size()&&atoi(Split(s.substr(6,5),' ',0).c_str())==vi.at(num))
						{
							vd.push_back(atof(Split(s.substr(60,6),' ',0).c_str()));
							num++;
						}
						getline(in,s);
			}
			getline(in,s);
	}
	in.close();
	return vd;
}	
