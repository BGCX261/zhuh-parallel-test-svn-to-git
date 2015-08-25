#include <stdio.h>
#include <stdlib.h>
#include <xdrfile_xtc.h>

int natoms,step,natom,read_return;
float time,lambda;
matrix box;
rvec *x,*v,*f;
XDRFILE *trr;

int main (int argc, char * argv[])
{
	char * filename = argv[1];
	trr=xdrfile_open (filename,"r");
	read_return=read_trr_natoms (filename,&natoms);
	printf("atom number: %d\n",natoms);

	x = calloc(natoms, sizeof(x[0]));
	while (1)
	{
		read_return=read_trr (trr,natoms,&step,&time,box,lambda,x,v,f);
		//printf("%d\t", step );
		if (read_return!=0)
		{
			break;
		}
	//	printf ("%d %f %d %f %f %f\n",step,time,natom,x[0][0],x[0][1],x[0][2]);
	//	printf ("%d %f %d %f\n",step,time,natom,f[0][0]);

		for (natom=1;natom<=natoms;natom++)
		{
		//	printf ("%d %f %d %f %f %f\n",step,time,natom,x[natom-1][0],x[natom-1][1],x[natom-1][2]);
			printf ("%f %f %f\n",x[natom-1][0],x[natom-1][1],x[natom-1][2]);
		}	
	}
	xdrfile_close (trr);
	return 0;
}
