#include <iomanip>
#include "read_ndx.h"
#include "read_pdb.h"
#include "read_xtc.h"

int main(int argc,char * argv[])
{
	char * pdb_file;
	char * xtc_file;
	char * xvg_file;
	char * index_file;

	switch(argc)
	{
	case 9:
		for(int i=0;i<9;i++)
		{
			if(string(argv[i])=="-p" )
			{
				pdb_file=argv[i+1];
			}
			if(string(argv[i])=="-f" )
			{
				xtc_file=argv[i+1];
			}
			if(string(argv[i])=="-n" )
			{
				index_file=argv[i+1];
			}
			if(string(argv[i])=="-o" )
			{
				xvg_file=argv[i+1];
			}
		}
		break;
	default:
		cout<<"Usage: g_dist_gmx -p *.pdb -f *.xtc/trr -n *.ndx -o *.xvg"<<endl;
		exit(0);
	}

   vector<string>  vs=read_2_group(index_file);
   vector<int>  vi= read_2_group_n(index_file);
   for(int i=0;i<vs.size();i++)
   {
	   if(vs.at(i).size()<8)
	   {
			cout<<i<<"\t"<<vs.at(i)<<"\t\t"<<vi.at(i)<<endl;
	   }
	   else
	   {
			cout<<i<<"\t"<<vs.at(i)<<"\t"<<vi.at(i)<<endl;
	   }
   }

 cout<<"select a group:";
  int group_1=1;
  cin>>group_1;
 cout<<"select group "<<vs.at(group_1)<<endl;
 cout<<"select a group:";
  int group_2=1;
  cin>>group_2;
 cout<<"select group "<<vs.at(group_2)<<endl;

  vector<int> serial_1=read_group_2_serial(index_file, vs.at(group_1));
  vector<int>  serial_2=read_group_2_serial(index_file, vs.at(group_2));
  vector<double> mass_1=read_pdb_2_atom(pdb_file,serial_1);
  vector<double> mass_2=read_pdb_2_atom(pdb_file,serial_2);

  vector<double>   result=read_xtc2dist(xtc_file, serial_1, serial_2, mass_1, mass_2);
  ofstream out(xvg_file);

  out<<"# The distence between group "<<vs.at(group_1)<<" and group "<<vs.at(group_2)<<endl;
  for(int i=0;i<result.size();i=i+2)
  {	
	  out<<fixed<<showpoint;
	  out<<result.at(i)<<"\t"<<setprecision(4)<<result.at(i+1)<<endl;
  }
  out.close();


	return 0;
}
