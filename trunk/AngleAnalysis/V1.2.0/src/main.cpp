#include "analysis.h"
#include "m_f.h"
/*
#begin distribution
#--A  chain/segment/atom&&chain/segment/atom
#--B  chain/segment/atom&&chain/segment/atom
#--C  chain/segment/atom&&chain/segment/atom
#--output  ***.txt
#end
2009/12/08 11:26:16
*/

//using namespace std;

int main(int argc,char * argv[])
{
	char* input;
	char* list;
	struct Filelist * fl;
	int filelen;
	double **data;
	double *vect;
	string operate; //定义操作
	string output; //输出文件
	struct Atom * atom_A,* atom_B,* atom_C;
	atom_A=NULL;
    atom_B=NULL;
    atom_C=NULL;
	switch(argc)
	{
	case 5:
		for(int i=0;i<5;i++)
		{
			if(string(argv[i])=="-i")
			{
				input=argv[i+1];
			}
			if(string(argv[i])=="-f")
			{
				list=argv[i+1];
			}
		}
		break;
	default:
		cout<<"Usage:AngleAnalysis -i input -f filelist"<<endl;
		exit(0);
	}

	fl=Readlist(list);
	filelen=Getfilelen(fl);
	data=dmatrix(0,filelen-1,0,8);
	vect=dvector(0,8);

	ReadInput(input,operate,output,atom_A,atom_B,atom_C);



//	cout<<atom_A->atom<<endl;

	for(int i=0;i<filelen;i++)
	{
		GetXYZ(fl->file,atom_A,atom_B,atom_C,vect);
		for(int j=0;j<9;j++)
		{
			data[i][j]=vect[j];
		}
		cout<<"Read File "<<fl->file<<" finished!"<<endl;
		fl=fl->next;

	}

	ofstream out(output.c_str());
	ifstream ifs(input);
	string str;
	getline(ifs,str);
	while(!ifs.fail())
	{
		out<<"#"<<str<<endl;
		getline(ifs,str);
	}
	ifs.close();
	out<<"num"<<"\t"<<"angle"<<"\t\t"<<"a*cos"<<"\t\t"<<"a*sin"<<"\t\t"<<"aa"<<"\t\t"<<"bb"<<"\t\t"<<"cc"<<endl;
	for(int j=0;j<filelen;j++)
	{
		for(int i=0;i<9;i++)
		{
			vect[i]=data[j][i];
		}
			double L=0,H=0; 
			double aa=0,bb=0,cc=0;
			double sset=angle(vect,L,H,aa,bb,cc);
			out<<fixed<<showpoint;
			out<<setprecision(3)<<j+1<<"\t"<<sset<<"\t\t"<<L<<"\t\t"<<H<<"\t\t"<<aa<<"\t\t"<<bb<<"\t\t"<<cc<<endl;
	}
		cout<<"calculate angle finished!"<<endl;
		out.close();
	
	


	return 0;
}