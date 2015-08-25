#include <iostream>

extern "C"
{
	#include <xdrfile_xtc.h>
}

using namespace std;

int main (int argc,char * argv[])
{
	char * filename;
	int natoms,step;
	filename="traj.xtc";
	float time;
	float p;
	matrix box;
	rvec *x;
	XDRFILE *xtc;
	xtc=xdrfile_open(filename,"r");
	int read_return=read_xtc_natoms(filename,&natoms);
	x=(rvec * )calloc(natoms,sizeof(x[0]));
	while(1)
	{
		read_return=read_xtc(xtc,natoms,&step,&time,box,x,&p);
		if(read_return!=0)
		{
			break;
		}
		for(int natom=0;natom<natoms;natom++)
		{
			cout<<step<<"\t"<<time<<"\t"<<natom<<"\t"<<x[natom][0]<<"\t"<<x[natom][1]<<"\t"<<x[natom][2]<<endl;	
			cout<<box[0][0]<<"\t"<<box[1][1]<<"\t"<<box[2][2]<<endl;
		}
	}
	xdrfile_close(xtc);
	return 0;
}

