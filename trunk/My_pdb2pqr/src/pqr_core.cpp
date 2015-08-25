#include "pqr_core.h"


struct pqr * Read_pqr(char * pqr_file)
{
	struct pqr * head;
	struct pqr * p1;
	struct pqr * p2;

		int n=0;
		head=NULL;

	ifstream in_pqr(pqr_file);

	while(!in_pqr.fail())
	{
		string s_pqr;
		getline(in_pqr,s_pqr);
		if(s_pqr.find("HETATM")<10)
		{
				p1=(struct pqr *) malloc(sizeof(struct pqr));
				strcpy(p1->name,Split(s_pqr,' ',2).c_str());
				p1->charge=atof(Split(s_pqr.substr(55,7),' ',0).c_str());		
				p1->radii=atof(Split(s_pqr.substr(63,6),' ',0).c_str());

				n++;
				if(n==1)
				{head=p1;}
				else
				{p2->next=p1;}
				p2=p1;
		}


	}
	return head;
}