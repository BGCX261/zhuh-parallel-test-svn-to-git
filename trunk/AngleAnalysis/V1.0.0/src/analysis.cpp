
#include "analysis.h"

struct Filelist *Readlist(char *file)
{
	struct Filelist *head;
	struct Filelist *p1,*p2;
	ifstream infile;
	infile.open(file);
	string s;
	infile>>s;
	int n=0;
	while(!infile.fail())
	{
		p1=(struct Filelist *) malloc(sizeof(struct Filelist));
		ifstream in(s.c_str());

		if(!in.fail())
		{
			strcpy(p1->file,s.c_str());
		}
		n++;
		if(n==1)
		{head=p1;}
		else 
		{p2->next=p1;}
		p2=p1;

		infile>>s;
	}
	p2->next=NULL;
	infile.close();
	return head;			
}

int Getfilelen(struct Filelist *head)
{
	int n=1;
	while(head->next!=NULL)
	{
		n++;
		head=head->next;
	}
	return n;
}

int Getatomlen(struct Atom *head)
{
	int n=1;
	while(head->next!=NULL)
	{
		n++;
		head=head->next;
	}
	return n;
}


void ReadInput(char *inputfile,string &operate,string &output,struct Atom *&atom_A,struct Atom *& atom_B,struct Atom *& atom_C)
{
	ifstream infile(inputfile);
	string temp;
	while(!infile.fail())
	{
		string st;
		getline(infile,st);
		if(Split(st,' ',0)=="begin"||Split(st,' ',0)=="BEGIN")
		{
			operate=Split(st,' ',1);
		}
		if(Split(st,' ',0)=="--A"||Split(st,' ',0)=="--a")
		{
			temp=Split(st,' ',1);
			vector<string> vs=Split_v(temp,'&');
			struct Atom * p1, * p2;
		//	atom_A=NULL;
			for(int i=0; i<vs.size() ; i++)
			{
				p1=(struct Atom *) malloc(sizeof(struct Atom));
				strcpy(p1->chain,Split(vs.at(i),'/',0).c_str());
				p1->reside=atoi(Split(vs.at(i),'/',1).c_str());
				strcpy(p1->atom,Split(vs.at(i),'/',2).c_str());

				if(i==0)
				{atom_A=p1;}
				else
				{p2->next=p1;}
				p2=p1;
			}
			p2->next=NULL;
		}
		if(Split(st,' ',0)=="--B"||Split(st,' ',0)=="--b")
		{
			temp=Split(st,' ',1);
			vector<string> vs=Split_v(temp,'&');
			struct Atom * p1, * p2;
	//		atom_B=NULL;
			for(int i=0; i<vs.size() ; i++)
			{
				p1=(struct Atom *) malloc(sizeof(struct Atom));
				strcpy(p1->chain,Split(vs.at(i),'/',0).c_str());
				p1->reside=atoi(Split(vs.at(i),'/',1).c_str());
				strcpy(p1->atom,Split(vs.at(i),'/',2).c_str());

				if(i==0)
				{atom_B=p1;}
				else
				{p2->next=p1;}
				p2=p1;
			}
			p2->next=NULL;
		}
		if(Split(st,' ',0)=="--C"||Split(st,' ',0)=="--c")
		{
			temp=Split(st,' ',1);
			vector<string> vs=Split_v(temp,'&');
			struct Atom * p1, * p2;
	//		atom_C=NULL;
			for(int i=0; i<vs.size() ; i++)
			{
				p1=(struct Atom *) malloc(sizeof(struct Atom));
				strcpy(p1->chain,Split(vs.at(i),'/',0).c_str());
				p1->reside=atoi(Split(vs.at(i),'/',1).c_str());
				strcpy(p1->atom,Split(vs.at(i),'/',2).c_str());

				if(i==0)
				{atom_C=p1;}
				else
				{p2->next=p1;}
				p2=p1;
			}
			p2->next=NULL;
		}

		if(Split(st,' ',0)=="end"||Split(st,' ',0)=="END")
		{
			break;
		}
		if(Split(st,' ',0)=="--output"||Split(st,' ',0)=="--OUTPUT")
		{
			output=Split(st,' ',1);
		}
	}
	
	if(output==" ")
	{
		output="output.txt";
	}
	infile.close();
}

string Split(string s,char a,int n)
{
	stack<string> sm;
	int index1=0;
	int index2=0;
	string part=s;
	while(index1<s.length())
	{
		index2+=part.find(a);
		if(index2>index1)
		{
			string temp=s.substr(index1,index2-index1);
        	sm.push(temp);
			part=s.substr(index2+1);
			index2++;
		}
		else if(part.find(a)==-1)
		{
			string temp=s.substr(index1,s.length()-index1);
			sm.push(temp);
			part=s.substr(index2+1);
			break;
		}
		else
		{
			part=s.substr(index2+1);
			index2++;
		}
		index1=index2;
	}
	int si=sm.size();
	for(int i=0;i<si-n-1;i++)
	{
		sm.pop();
	}

	return sm.top();
}

vector<string> Split_v(string s,char a)
{
	vector<string> sm;
	int index1=0;
	int index2=0;
	string part=s;
	while(index1<s.length())
	{
		index2+=part.find(a);
		if(index2>index1)
		{
			string temp=s.substr(index1,index2-index1);
			sm.push_back(temp);
			part=s.substr(index2+1);
			index2++;
		}
		else if(part.find(a)==-1)
		{
			string temp=s.substr(index1,s.length()-index1);
			sm.push_back(temp);
			part=s.substr(index2+1);
			break;
		}
		else
		{
			part=s.substr(index2+1);
			index2++;
		}
		index1=index2;
	}
	return sm;
}

void GetXYZ(char * file, struct Atom * atom_A,struct Atom *atom_B,struct Atom * atom_C,double * vect)
{
		ifstream read(file);
		string in;
		getline(read,in);

		int Len_A=Getatomlen(atom_A);
		int Len_B=Getatomlen(atom_B);
		int Len_C=Getatomlen(atom_C);

		double xa=0,ya=0,za=0;
		double xb=0,yb=0,zb=0;
		double xc=0,yc=0,zc=0;

		while(!read.fail())
		{
			if(in.find("ATOM")<10)
			{	

				GetNum(in,atom_A,xa,ya,za,Len_A);
				GetNum(in,atom_B,xb,yb,zb,Len_B);
				GetNum(in,atom_C,xc,yc,zc,Len_C);
			}
		
			getline(read,in);
		}
		read.close();
		vect[0]=xa/Len_A;
		vect[1]=ya/Len_A;
		vect[2]=za/Len_A;
		vect[3]=xb/Len_B;
		vect[4]=yb/Len_B;
		vect[5]=zb/Len_B;
		vect[6]=xc/Len_C;
		vect[7]=yc/Len_C;
		vect[8]=zc/Len_C;
}

void GetNum(string in,struct Atom * atom_T,double &x,double &y,double &z,int Len)
{
			for(int ia=0;ia<Len;ia++)
			{
				if(string(atom_T->chain).at(0)=='*'&&atoi(Split(in.substr(22,25),' ',0).c_str())==atom_T->reside&&Split(in.substr(12,15),' ',0)==string(atom_T->atom))
				{
						x+=atof(Split(in.substr(30,37),' ',0).c_str());
						y+=atof(Split(in.substr(38,45),' ',0).c_str());
						z+=atof(Split(in.substr(46,53),' ',0).c_str());
			//			cout<<in<<endl;
			//			cout<<atom_T->reside<<endl;
				}
				if(in.at(21)==string(atom_T->chain).at(0)&&atoi(Split(in.substr(17,19),' ',0).c_str())==atom_T->reside&&Split(in.substr(12,15),' ',0)==string(atom_T->atom))
				{
					   x+=atof(Split(in.substr(30,37),' ',0).c_str());
					   y+=atof(Split(in.substr(38,45),' ',0).c_str());
					   z+=atof(Split(in.substr(46,53),' ',0).c_str());
				}
					atom_T=atom_T->next;					
			}
}

double angle(double * vect)
{
	double aa,bb,cc;
	double coss;
	double seita;
	
	aa=sqrt((vect[6]-vect[3])*(vect[6]-vect[3])+(vect[7]-vect[4])*(vect[7]-vect[4])+(vect[8]-vect[5])*(vect[8]-vect[5]));
//	cout<<aa<<endl;
	bb=sqrt((vect[6]-vect[0])*(vect[6]-vect[0])+(vect[7]-vect[1])*(vect[7]-vect[1])+(vect[8]-vect[2])*(vect[8]-vect[2]));
//	cout<<bb<<endl;
	cc=sqrt((vect[3]-vect[0])*(vect[3]-vect[0])+(vect[1]-vect[4])*(vect[1]-vect[4])+(vect[2]-vect[5])*(vect[2]-vect[5]));
//	cout<<cc<<endl;
	coss=(aa*aa-bb*bb+cc*cc)/(2*aa*cc);
	seita=acos(coss)/3.1415*180;

	return seita;
}