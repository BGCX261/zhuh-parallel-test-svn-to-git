#include <iomanip>

#include "curves.h"
/*这是一个处理cur52结果的程序。主要是可以对curves的结果进行求取平均值，求取数据的分布，以及部分
参数的方差，这这里成为螺旋参数的刚性，通过这些分析可以得到一些DNA体系的柔顺性的动力学信息。
目前可以完成的操作和存在的问题：
可以完成的操作：

暂时没有解决的问题：
1.如何处理segment的多样式输入！
version：1.1.0

*/


void ReadInput(char *inputfile,string &operate,char &choose,string &output,double &temperature,string &segment,int &segment_b,int &segment_e);
void Printversion();
void Printhelp();

int main(int argc,char *argv[])
{
	char *listfile,*inputfile;
	char choose= ' ';
	string operate=" ";
	double temperature=300;
	string output=" ";
	string segment="all";
	int segment_b=0;
	int segment_e=0;
//  读取当前的时间
	time_t t = time( 0 ); 
    char TIME[64]; 
    strftime( TIME, sizeof(TIME), "%Y/%m/%d %X ",localtime(&t) ); 
    
//

	switch(argc)
	{
	case 1:
		cout<<"Usage:CurvesTest -f listfile.txt -i inputfile.txt"<<endl;
		cout<<"Usage:'CurvesTest -a' to know something about the program!"<<endl;
		cout<<"Usage:'CurvesTest -h' for help!"<<endl;
		exit(0);
	case 2:
		if(string(argv[1])=="-a")
		{
			Printversion();
			exit(0);
		}
		if(string(argv[1])=="-h")
		{
			Printhelp();
			exit(0);
		}
	case 5:
		if(string(argv[1])=="-f"&&string(argv[3])=="-i")
		{
			listfile=argv[2];
			inputfile=argv[4];
		}
		break;

	default:
		cout<<"Usage:CurAnalysis -f listfile.txt -i inputfile.txt"<<endl;
		exit(0);

	}

	ReadInput(inputfile,operate,choose,output,temperature,segment,segment_b,segment_e);
/*
average部分已经完成，经测试可以使用，主要的问题是读文件的异常
比如说文件残缺，文件丢失等的情况的处理的过程没有完成。
*/
	if(operate=="average")
	{
		if(choose=='E'||choose=='F'||choose=='G'||choose=='H')
		{
			double ***totaldata;
			struct	Filelist *fl;
			struct Paramater *spt;
	//		struct Information inf;
			int N=0;
			ofstream outfile(output.c_str(),ios::app);
			fl=Readlist(listfile,choose);
			
			switch(choose)
			{
			case 'E':
				spt=E_part(fl->file);
				break;
			case 'F':
				spt=F_part(fl->file);
				break;
			case 'G':
				spt=G_part(fl->file);
				break;
			case 'H':
				spt=H_part(fl->file);
				break;
			}
			int filesize=Getfilelen(fl);	
			int size=GetParamaterlen(spt);
			if(segment!="all")
			{
				size=segment_e - segment_b+1;
			}
			if(segment=="all")
			{
				segment_b=1;
				segment_e=size;
			}
			totaldata=f3tensor(0,5,0,size-1,0,filesize-1);
outfile<<"******************************************************************"<<endl;
//output the input file!
	ifstream infile(inputfile);
	string s;
    getline(infile,s);
   while(!infile.fail())
	{
		outfile<<"#"<<s<<endl;
		getline(infile,s);
	}
    outfile<<TIME<<endl;  //输出当前时间
	infile.close();

//
			while(fl!=NULL)
			{
				struct Paramater *sp; 
				switch(choose)
				{
					case 'E':
						sp=E_part(fl->file);
					break;
					case 'F':
						sp=F_part(fl->file);
					break;
					case 'G':
						sp=G_part(fl->file);
					break;
					case 'H':
						sp=H_part(fl->file);
					break;
				}
		//		int size=GetParamaterlen(sp);
				double **data;
				data=dmatrix(0,5,0,size-1);
				struct Namelist *name;
				name=(struct Namelist *)malloc(sizeof(struct Namelist));
				Paramater2double(sp,data,name,segment_b,segment_e);

				for(int i=0;i<6;i++)
				{
					for(int j=0;j<size;j++)
					{
						totaldata[i][j][N]=data[i][j];
					}
				}
				free_dmatrix(data,0,5,0,size-1);
				cout<<"Read file "<<fl->file<<" finished!"<<endl;//输出提示
				fl=fl->next;
				N++;
			}

			double **aveg;
			aveg=dmatrix(0,5,0,size-1);
			for(int i=0;i<6;i++)
			{
				for(int j=0;j<size;j++)
				{
					aveg[i][j]=0;
				}
			}

			outfile<<endl;
			outfile<<"******************************************************************"<<endl;
			outfile<<"\t"<<"rise"<<"\t"<<"roll"<<"\t"<<"shift"<<"\t"<<"slide"<<"\t"<<"tilt"<<"\t"<<"twist"<<endl;
			outfile<<endl;

			for(int i=0;i<size;i++)
			{
				outfile<<i+segment_b<<"\t";
				for(int j=0;j<6;j++)
				{
					for(int k=0;k<filesize;k++)
					{
						aveg[j][i]+=totaldata[j][i][k];
					}
					aveg[j][i]=aveg[j][i]/filesize;
					outfile<<fixed<<showpoint;
					
	 				outfile<<setprecision(2)<<aveg[j][i]<<"\t";
				}
				outfile<<endl;
			}
			outfile<<endl;
			outfile<<"******************************************************************"<<endl;
		   cout<<"finished the calculation of average !"<<endl;
		   cout<<"the output write in the file "<<output<<" !"<<endl;
			outfile.close();
			free_f3tensor(totaldata,0,5,0,size-1,0,filesize-1);
		}

		//average for J

		if(choose=='J')
		{
			double ***totaldata;
			struct	Filelist *fl;
			struct Backbone *spt;
			int N=0;
			fl=Readlist(listfile,choose);
			spt=J_part(fl->file);
			int filesize=Getfilelen(fl);	
			int size=GetBackbonelen(spt);
			if(segment!="all")
			{
				size=segment_e - segment_b+1;
			}
			if(segment=="all")
			{
				segment_b=1;
				segment_e=size;
			}
			totaldata=f3tensor(0,13,0,size-1,0,filesize-1);
			ofstream outfile(output.c_str(),ios::app);

			outfile<<"******************************************************************"<<endl;
		//output the input file!
			ifstream infile(inputfile);
			string s;
			getline(infile,s);
			 while(!infile.fail())
			{
				outfile<<"#"<<s<<endl;
				getline(infile,s);
			}
			 outfile<<TIME<<endl; //输出当前时间
			infile.close();
//

			while(fl!=NULL)
			{
				struct Backbone *sp;
				sp=J_part(fl->file);
		//		int size=GetBackbonelen(sp);
				double **data;
				data=dmatrix(0,13,0,size-1);
				struct Namelist *name;
				name=(struct Namelist *)malloc(sizeof(struct Namelist));
				Backbone2double(sp,data,name,segment_b,segment_e);

				for(int i=0;i<14;i++)
				{
					for(int j=0;j<size;j++)
					{
						totaldata[i][j][N]=data[i][j];
					}
				}
				free_dmatrix(data,0,13,0,size-1);
				cout<<"Read file "<<fl->file<<" finished!"<<endl;//输出提示
				fl=fl->next;
				N++;
			}

			double **aveg;
			aveg=dmatrix(0,13,0,size-1);
			for(int i=0;i<14;i++)
			{
				for(int j=0;j<size;j++)
				{
					aveg[i][j]=0;
				}
			}

			outfile<<endl;
			outfile<<"******************************************************************"<<endl;
			outfile<<"\t"<<"alpha"<<"\t"<<"ampli"<<"\t"<<"beta"<<"\t"<<"c1"<<"\t"<<"c1c2"<<"\t"<<"c2"<<"\t"<<"c2c3"<<"\t"<<"c3"<<"\t"<<"chi"<<"\t"<<"delta"<<"\t"<<"epsil"<<"\t"<<"gamma"<<"\t"<<"phase"<<"\t"<<"zeta"<<endl;
			outfile<<endl;

			for(int i=0;i<size;i++)
			{
				outfile<<i+segment_b<<"\t";
				for(int j=0;j<14;j++)
				{
					for(int k=0;k<filesize;k++)
					{
						aveg[j][i]+=totaldata[j][i][k];
					}
					aveg[j][i]=aveg[j][i]/filesize;
					outfile<<fixed<<showpoint;
					outfile<<setprecision(2)<<aveg[j][i]<<"\t";
				}
				outfile<<endl;
			}
			outfile<<endl;
			outfile<<"******************************************************************"<<endl;
		   cout<<"finished the calculation of average !"<<endl;
		   cout<<"the output write in the file "<<output<<" !"<<endl;
			outfile.close();
			free_f3tensor(totaldata,0,13,0,size-1,0,filesize-1);
		}

	}

	
//计算某一数据的分布


	if(operate=="distribution")
	{
		//part 1: get the data
		if(choose=='E'||choose=='F'||choose=='G'||choose=='H')
		{
			double ***totaldata;
			struct	Filelist *fl;
			struct Paramater *spt;
			int N=0;
			ofstream outfile(output.c_str(),ios::app);
			fl=Readlist(listfile,choose);
			switch(choose)
			{
			case 'E':
				spt=E_part(fl->file);
				break;
			case 'F':
				spt=F_part(fl->file);
				break;
			case 'G':
				spt=G_part(fl->file);
				break;
			case 'H':
				spt=H_part(fl->file);
				break;
			}
			int filesize=Getfilelen(fl);	
			int size=GetParamaterlen(spt);
			if(segment!="all")
			{
				size=segment_e - segment_b+1;
			}
			if(segment=="all")
			{
				segment_b=1;
				segment_e=size;
			}
			totaldata=f3tensor(0,5,0,size-1,0,filesize-1);
			outfile<<"******************************************************************"<<endl;

			//output the input file!
			ifstream infile(inputfile);
			string s;
			 getline(infile,s);
			while(!infile.fail())
			{
				outfile<<"#"<<s<<endl;
				getline(infile,s);
			}
		    outfile<<TIME<<endl;  //输出当前时间
			infile.close();

//
			while(fl!=NULL)
			{
				struct Paramater *sp; 
				switch(choose)
				{
					case 'E':
						sp=E_part(fl->file);
					break;
					case 'F':
						sp=F_part(fl->file);
					break;
					case 'G':
						sp=G_part(fl->file);
					break;
					case 'H':
						sp=H_part(fl->file);
					break;
				}
		//		int size=GetParamaterlen(sp);
				double **data;
				data=dmatrix(0,5,0,size-1);
				struct Namelist *name;
				name=(struct Namelist *)malloc(sizeof(struct Namelist));
				Paramater2double(sp,data,name,segment_b,segment_e);

				for(int i=0;i<6;i++)
				{
					for(int j=0;j<size;j++)
					{
						totaldata[i][j][N]=data[i][j];
					}
				}
				free_dmatrix(data,0,5,0,size-1);
				cout<<"Read file "<<fl->file<<" finished!"<<endl;//输出提示
				fl=fl->next;
				N++;
			}
// finished the input data
			//calculate the distribution!
			double *vect;
			vect=dvector(0, size*filesize-1) ;  
			for(int i=0;i<6;i++)
			{
				outfile<<"******************************************************************"<<endl;
				switch(i)
				{
					case 0:
						outfile<<"the distribution of RISE"<<endl;
						break;
					case 1:
						outfile<<"the distribution of ROLL"<<endl;
						break;
					case 2:
						outfile<<"the distribution of SHIFT"<<endl;
						break;
					case 3:
						outfile<<"the distribution of SLIDE"<<endl;
						break;
					case 4:
						outfile<<"the distribution of TILT"<<endl;
						break;
					case 5:
						outfile<<"the distribution of TWIST"<<endl;
						break;
				}
				outfile<<"******************************************************************"<<endl;
				//
				for(int m=0;m<size;m++)
				{
					for(int n=0;n<filesize;n++)
					{
						vect[m*filesize+n]=totaldata[i][m][n];
					}
				}
				//把二维的数据转化为一维的数据！
				
				Distribution(vect,size*filesize,output);
				outfile<<"******************************************************************"<<endl;
			}
		   cout<<"finished the calculation of distribution !"<<endl;
		   cout<<"the output write in the file "<<output<<" !"<<endl;
			outfile.close();
			free_f3tensor(totaldata,0,5,0,size-1,0,filesize-1);
			// finished the calculation !



		}

		if(choose=='J')
		{
			double ***totaldata;
			struct	Filelist *fl;
			struct Backbone *spt;
			int N=0;
			fl=Readlist(listfile,choose);
			spt=J_part(fl->file);
			int filesize=Getfilelen(fl);	
			int size=GetBackbonelen(spt);
			if(segment!="all")
			{
				size=segment_e - segment_b+1;
			}
			if(segment=="all")
			{
				segment_b=1;
				segment_e=size;
			}
			totaldata=f3tensor(0,13,0,size-1,0,filesize-1);
			ofstream outfile(output.c_str(),ios::app);

			outfile<<"******************************************************************"<<endl;
		//output the input file!
			ifstream infile(inputfile);
			string s;
			getline(infile,s);
			 while(!infile.fail())
			{
				outfile<<"#"<<s<<endl;
				getline(infile,s);
			}
			 outfile<<TIME<<endl; //输出当前时间
			infile.close();
//

			while(fl!=NULL)
			{
				struct Backbone *sp;
				sp=J_part(fl->file);
		//		int size=GetBackbonelen(sp);
				double **data;
				data=dmatrix(0,13,0,size-1);
				struct Namelist *name;
				name=(struct Namelist *)malloc(sizeof(struct Namelist));
				Backbone2double(sp,data,name,segment_b,segment_e);

				for(int i=0;i<14;i++)
				{
					for(int j=0;j<size;j++)
					{
						totaldata[i][j][N]=data[i][j];
					}
				}
				free_dmatrix(data,0,13,0,size-1);
				cout<<"Read file "<<fl->file<<" finished!"<<endl;//输出提示
				fl=fl->next;
				N++;
			}

			double *vect;
			vect=dvector(0, size*filesize-1) ;  
			for(int i=0;i<14;i++)
			{
				outfile<<"******************************************************************"<<endl;
				switch(i)
				{
					case 0:
						outfile<<"the distribution of ALPHA"<<endl;
						break;
					case 1:
						outfile<<"the distribution of AMPLI"<<endl;
						break;
					case 2:
						outfile<<"the distribution of BETA"<<endl;
						break;
					case 3:
						outfile<<"the distribution of C1'"<<endl;
						break;
					case 4:
						outfile<<"the distribution of C1'-C2'"<<endl;
						break;
					case 5:
						outfile<<"the distribution of C2'"<<endl;
						break;
					case 6:
						outfile<<"the distribution of C2'-C3'"<<endl;
						break;
				    case 7:
						outfile<<"the distribution of C3'"<<endl;
						break;
					case 8:
						outfile<<"the distribution of CHI"<<endl;
						break;
					case 9:
						outfile<<"the distribution of DELTA"<<endl;
						break;
					case 10:
						outfile<<"the distribution of ESPIL"<<endl;
						break;
					case 11:
						outfile<<"the distribution of GAMMA"<<endl;
						break;
					case 12:
						outfile<<"the distribution of PHASE"<<endl;
						break;
					case 13:
						outfile<<"the distribution of ZETA"<<endl;
						break;
					}
				outfile<<"******************************************************************"<<endl;
				//
				for(int m=0;m<size;m++)
				{
					for(int n=0;n<filesize;n++)
					{
						vect[m*filesize+n]=totaldata[i][m][n];
					}
				}
				//把二维的数据转化为一维的数据！
				
				Distribution(vect,size*filesize,output);
				outfile<<"******************************************************************"<<endl;
			}
		   cout<<"finished the calculation of distribution !"<<endl;
		   cout<<"the output write in the file "<<output<<" !"<<endl;
			outfile.close();
			free_f3tensor(totaldata,0,13,0,size-1,0,filesize-1);
			// finished the calculation !
		}

	}
/*计算刚性*/
	
	if(operate=="stiffness")
	{
		/*get the data*/
		if(choose=='E'||choose=='F'||choose=='G'||choose=='H')
		{
			double ***totaldata;
			struct	Filelist *fl;
			struct Paramater *spt;
			int N=0;
			ofstream outfile(output.c_str(),ios::app);
			fl=Readlist(listfile,choose);
			switch(choose)
			{
			case 'E':
				spt=E_part(fl->file);
				break;
			case 'F':
				spt=F_part(fl->file);
				break;
			case 'G':
				spt=G_part(fl->file);
				break;
			case 'H':
				spt=H_part(fl->file);
				break;
			}
			int filesize=Getfilelen(fl);	
			int size=GetParamaterlen(spt);
			if(segment!="all")
			{
				size=segment_e - segment_b+1;
			}
			if(segment=="all")
			{
				segment_b=1;
				segment_e=size;
			}
			totaldata=f3tensor(0,5,0,size-1,0,filesize-1);
			outfile<<"******************************************************************"<<endl;

			//output the input file!
			ifstream infile(inputfile);
			string s;
			 getline(infile,s);
			while(!infile.fail())
			{
				outfile<<"#"<<s<<endl;
				getline(infile,s);
			}
		    outfile<<TIME<<endl;  //输出当前时间
			infile.close();

//
			while(fl!=NULL)
			{
				struct Paramater *sp; 
				switch(choose)
				{
					case 'E':
						sp=E_part(fl->file);
					break;
					case 'F':
						sp=F_part(fl->file);
					break;
					case 'G':
						sp=G_part(fl->file);
					break;
					case 'H':
						sp=H_part(fl->file);
					break;
				}
		//		int size=GetParamaterlen(sp);
				double **data;
				data=dmatrix(0,5,0,size-1);
				struct Namelist *name;
				name=(struct Namelist *)malloc(sizeof(struct Namelist));
				Paramater2double(sp,data,name,segment_b,segment_e);

				for(int i=0;i<6;i++)
				{
					for(int j=0;j<size;j++)
					{
						totaldata[i][j][N]=data[i][j];
					}
				}
				free_dmatrix(data,0,5,0,size-1);
				cout<<"Read file "<<fl->file<<" finished!"<<endl;//输出提示
				fl=fl->next;
				N++;
			}
// finished the input data
			/*calculate the stiffness! */
			double **stiff;
			double **matrix;
			double **inve_matrix;

			/*output the title */
				outfile<<"******************************************************************"<<endl;
				outfile<<"calculate the stiffness of part "<<choose<<endl;
				outfile<<"******************************************************************"<<endl;
				
		for(int x=segment_b-1;x<segment_e;x++)   /* the loop for segment  */
		{
			stiff=dmatrix(0,5,0, filesize-1) ;  /* hold the space!*/
			matrix=dmatrix(0,5,0,5);
			inve_matrix=dmatrix(0,5,0,5);

			for(int i=0;i<6;i++)
			{
					for(int n=0;n<filesize;n++)
					{
						stiff[i][n]=totaldata[i][x][n];
					}			
			}

			Getmatrix(stiff,matrix,filesize);  /*cteate the helical matrix!*/
			free_dmatrix(stiff,0,5,0,filesize-1);
			inverse_matrix(matrix, inve_matrix,6);
			free_dmatrix(matrix,0,5,0,5);

			outfile<<"the stiffness of segment "<<x+1<<endl;
			outfile<<"******************************************************************"<<endl;
			outfile<<"\t"<<"rise"<<"\t"<<"roll"<<"\t"<<"shift"<<"\t"<<"slide"<<"\t"<<"tilt"<<"\t"<<"twist"<<endl;
			outfile<<fixed<<showpoint;
			for(int i=0;i<6;i++)
			{
				switch(i)
				{
				case 0:
					outfile<<"rise"<<"\t";
					break;
				case 1:
					outfile<<"roll"<<"\t";
					break;
				case 2:
					outfile<<"shift"<<"\t";
					break;
				case 3:
					outfile<<"slide"<<"\t";
					break;
				case 4:
					outfile<<"tilt"<<"\t";
					break;
				case 5:
					outfile<<"twist"<<"\t";
					break;
				}
				for(int j=0;j<6;j++)
				{
					outfile<<setprecision(2)<<R*temperature*inve_matrix[i][j]<<"\t";
				}
				outfile<<endl;
			}
			outfile<<"******************************************************************"<<endl;
		}
		cout<<"finished the calculation of stiffness !"<<endl;
		cout<<"the output write in the file "<<"\""<<output<<"\"  !"<<endl;
		outfile.close();
		free_f3tensor(totaldata,0,5,0,size-1,0,filesize-1);
			// finished the calculation !

		}


		else
		{
			cout<<"wrong input, please check!"<<endl;
			exit(0);
		}

	}


	if(operate!="stiffness"&&operate!="average"&&operate!="distribution")
	{
		cout<<"Input a wrong operate. the correct oprtate is 'average/distribution/stiffness'"<<endl;
		exit(0);
	}
	return 0;
}

void ReadInput(char *inputfile,string &operate,char &choose,string &output,double &temperature,string &segment,int &segment_b,int &segment_e)
{
	ifstream infile(inputfile);
	while(!infile.fail())
	{
		string st;
		getline(infile,st);
		if(Split(st,' ',0)=="begin"||Split(st,' ',0)=="BEGIN")
		{
			operate=Split(st,' ',1);
		}
		if(Split(st,' ',0)=="--choose"||Split(st,' ',0)=="--CHOOSE")
		{
			choose=Split(st,' ',1).c_str()[0];
		}
		if(Split(st,' ',0)=="--output"||Split(st,' ',0)=="--OUTPUT")
		{
			output=Split(st,' ',1);
		}
		if(Split(st,' ',0)=="--temperature"||Split(st,' ',0)=="--TEMPERATURE")
		{
			temperature=atof(Split(st,' ',1).c_str());
		}
		if(Split(st,' ',0)=="--segment"||Split(st,' ',0)=="--SEGMENT")
		{
			segment=Split(st,' ',1);
			if(segment.find("-")<100)
			{
				segment_b=atoi(Split(segment,'-',0).c_str());
				segment_e=atoi(Split(segment,'-',1).c_str());
			}
		}
		if(Split(st,' ',0)=="end"||Split(st,' ',0)=="END")
		{
			break;
		}
	}
	if(output==" ")
	{
		output="output.txt";
	}
	infile.close();
}

void Printversion()
{
		cout<<endl;
		cout<<"--------------------CurvesTest version 1.1.0--------------------"<<endl;
		cout<< "A command-line based program to  analyze Cur52 result."<<endl;
		cout<<"- Authors:   H. Zhu"<<endl;
		cout<<"- Copyright: PCML USTC "<<endl;
		cout<<endl;
}


void Printhelp()
{
	cout<<endl;
	cout<<"----------An Input Example!----------"<<endl;
	cout<<"\t"<<"BEGIN stiffness"<<endl;
	cout<<"\t"<<"--CHOOSE E"<<endl;
	cout<<"\t"<<"--TEMPERATURE 300"<<endl;
	cout<<"\t"<<"--OUTPUT stiffness.txt"<<endl;
	cout<<"\t"<<"--SEGMENT 1-12"<<endl;
	cout<<"\t"<<"END"<<endl;
/**/
	cout<<"-------------------------------------"<<endl;

	cout<<"BEGIN"<<" : \t"<<"now 'average' , 'distribution' , 'stiffness' are available!"<<endl;
	cout<<"choose"<<" : \t"<<"you can input a part to calculate! E,F,G,H,J parts are available!"<<endl;
	cout<<"temperature"<<" : \t"<<"input the temperature of  simulation.the temperature is only"<<endl;
	cout<<"                need in calculating stiffness."<<endl;
	cout<<"output"<<" : \t"<<"the output file name!"<<endl;
	cout<<"segment"<<" : \t"<<"choose the segment to calculate!"<<endl;
	cout<<"-------------------------------------"<<endl;

}