#include "curves.h"

void A_part(char *file)
{
	ifstream infile;
	string s;
	infile.open(file);
	while(!infile.fail())
	{

	}
}

void B_part(char *file)
{
	ifstream infile;
	string s;
	infile.open(file);
	while(!infile.fail())
	{
	}
}

void C_part(char *file)
{
	ifstream infile;
	string s;
	infile.open(file);
	while(!infile.fail())
	{
	}

}

void D_part(char *file)
{
	ifstream infile;
	string s;
	infile.open(file);
	while(!infile.fail())
	{
	}
}
/*提取文件中的数据到链表*/
struct Paramater *E_part(char *file)
{
	ifstream infile(file);
	string s;
	struct Paramater *head;
	struct Paramater *p1,*p2;
	head=NULL;
	int n=0;
	while(!infile.fail())
	{
		getline(infile,s);
			if(s.find("|E|")<100)
			{
				getline(infile,s);
				getline(infile,s);
				while(s.find("--")>100)
				{
					if(s.find("/")<100)
					{
		
						p1=(struct Paramater *) malloc(sizeof(struct Paramater));
						p1->rise=atof(Split(s,' ',6).data());
						p1->roll=atof(Split(s,' ',8).data());
						p1->shift=atof(Split(s,' ',4).data());
						p1->slide=atof(Split(s,' ',5).data());
						p1->tilt=atof(Split(s,' ',7).data());
						p1->twist=atof(Split(s,' ',9).data());
						string name=Split(s,' ',1)+Split(s,' ',2)+Split(s,' ',3);
						strcpy(p1->name,name.c_str());

						n++;
						if(n==1)
						{head=p1;}
						else
						{p2->next=p1;}
						p2=p1;
					}
					getline(infile,s);
				}
			}
	}
	infile.close();
	p2->next=NULL;
	return head;
}
/*提取文件中的数据到链表*/
struct Paramater *F_part(char *file)
{
	ifstream infile(file);
	string s;
	struct Paramater *head;
	struct Paramater *p1,*p2;

	head=NULL;
	int n=0;
	while(!infile.fail())
	{
		getline(infile,s);
			if(s.find("|F|")<100)
			{
				getline(infile,s);
				getline(infile,s);
				while(s.find("--")>100)
				{
					if(s.find("/")<100)
					{
	
						p1=(struct Paramater *) malloc(sizeof(struct Paramater));
						p1->rise=atof(Split(s,' ',6).data());
						p1->roll=atof(Split(s,' ',8).data());
						p1->shift=atof(Split(s,' ',4).data());
						p1->slide=atof(Split(s,' ',5).data());
						p1->tilt=atof(Split(s,' ',7).data());
						p1->twist=atof(Split(s,' ',9).data());
						string name=Split(s,' ',1)+Split(s,' ',2)+Split(s,' ',3);
						strcpy(p1->name,name.c_str());

						n++;
						if(n==1)
						{head=p1;}
						else
						{p2->next=p1;}
						p2=p1;
					}
					getline(infile,s);
				}
			}
	}
	infile.close();
	p2->next=NULL;
	return head;
}
//提取文件中的数据到链表
struct Paramater *G_part(char *file)
{
	ifstream infile(file);
	string s;
	struct Paramater *head;
	struct Paramater *p1,*p2;

	head=NULL;
	int n=0;
	while(!infile.fail())
	{
		getline(infile,s);
			if(s.find("|G|")<100)
			{
				getline(infile,s);
				getline(infile,s);
				while(s.find("--")>100)
				{
					if(s.find("/")<100)
					{
		
						p1=(struct Paramater *) malloc(sizeof(struct Paramater));
						p1->rise=atof(Split(s,' ',6).data());
						p1->roll=atof(Split(s,' ',8).data());
						p1->shift=atof(Split(s,' ',4).data());
						p1->slide=atof(Split(s,' ',5).data());
						p1->tilt=atof(Split(s,' ',7).data());
						p1->twist=atof(Split(s,' ',9).data());
						string name=Split(s,' ',1)+Split(s,' ',2)+Split(s,' ',3);
						strcpy(p1->name,name.c_str());

						n++;
						if(n==1)
						{head=p1;}
						else
						{p2->next=p1;}
						p2=p1;
					}
					getline(infile,s);
				}
			}
	}
	infile.close();
	p2->next=NULL;
	return head;
}
//提取文件中的数据到链表
struct Paramater *H_part(char *file)
{
	ifstream infile(file);
	string s;
	struct Paramater *head;
	struct Paramater *p1,*p2;

	head=NULL;
	int n=0;
	while(!infile.fail())
	{
		getline(infile,s);
			if(s.find("|H|")<100)
			{
				getline(infile,s);
				getline(infile,s);
				while(s.find("--")>100)
				{
					if(s.find("/")<100)
					{
		
						p1=(struct Paramater *) malloc(sizeof(struct Paramater));
						p1->rise=atof(Split(s,' ',6).data());
						p1->roll=atof(Split(s,' ',8).data());
						p1->shift=atof(Split(s,' ',4).data());
						p1->slide=atof(Split(s,' ',5).data());
						p1->tilt=atof(Split(s,' ',7).data());
						p1->twist=atof(Split(s,' ',9).data());
						string name=Split(s,' ',1)+Split(s,' ',2)+Split(s,' ',3);
						strcpy(p1->name,name.c_str());

						n++;
						if(n==1)
						{head=p1;}
						else
						{p2->next=p1;}
						p2=p1;
					}
					getline(infile,s);
				}
			}
	}
	infile.close();
	p2->next=NULL;
	return head;
}

void I_part(char *file)
{
	ifstream infile;
	string s;
	infile.open(file);
	while(!infile.fail())
	{
	}
}
//提取文件中的数据到链表
struct Backbone *J_part(char * file)   //文件残缺造成的读取异常未解决！
{
	ifstream infile(file);
	string s;

	struct Backbone *head;
	struct Backbone *p1,*p2;
	
	head=NULL;
	int n=0;

	while(!infile.fail())
	{
		getline(infile,s);
			if(s.find("|J|")<100)
			{
				getline(infile,s);
				getline(infile,s);
				
				while(s.find("Torsions")>100)
				{
					if(s.find(")")<100)
					{
						
						p1=(struct Backbone *) malloc(sizeof(struct Backbone));
						strcpy(p1->name,(Split(s,' ',0)).c_str());
						p1->c1c2=(atof(Split(s,' ',2).data()));
						p1->c2c3=(atof(Split(s,' ',3).data()));
						p1->phase=(atof(Split(s,' ',4).data()));
						p1->ampli=(atof(Split(s,' ',5).data()));
						strcpy(p1->pucker,(Split(s,' ',6)).c_str());
						p1->c1=(atof(Split(s,' ',7).data()));
						p1->c2=(atof(Split(s,' ',8).data()));
						p1->c3=(atof(Split(s,' ',9).data()));

						n++;
						if(n==1)
						{head=p1;}
						else
						{p2->next=p1;}
						p2=p1;
						
					}
					getline(infile,s);
				}
				while(s.find("--")>100)
				{
					if(s.find(")")<100)
					{
						struct Backbone *temp1,*temp2;
						temp1=head;

						while(strcmp(temp1->name,(Split(s,' ',0)).c_str())!=0&&temp1->next!=NULL)
						{
							temp2=temp1;
							temp1=temp1->next;
						}
						if(strcmp(temp1->name,(Split(s,' ',0)).c_str())==0)
						{
							temp1->chi=(atof(Split(s,' ',2).data()));
							if(Split(s,' ',3).find("..")>100)
							{
								temp1->gamma=(atof(Split(s,' ',3).data()));
							}
							else
							{
								temp1->gamma=0;
							}
							temp1->delta=(atof(Split(s,' ',4).data()));
							if(Split(s,' ',5).find("..")>100)
							{
								temp1->epsil=(atof(Split(s,' ',5).data()));
							}
							else
							{
								temp1->epsil=0;
							}
							if(Split(s,' ',6).find("..")>100)
							{
								temp1->zeta=(atof(Split(s,' ',6).data()));
							}
							else
							{
								temp1->zeta=0;
							}
							if(Split(s,' ',7).find("..")>100)
							{
								temp1->alpha=(atof(Split(s,' ',7).data()));
							}
							else
							{
								temp1->alpha=0;
							}
							if(Split(s,' ',8).find("..")>100)
							{
								temp1->beta=(atof(Split(s,' ',8).data()));
							}
							else
							{
								temp1->beta=0;
							}
					//		break;
						}
					}
					getline(infile,s);

					if(s.find("2nd")<100)
					{
						while(s.find("Torsions")>100)
						{
							if(s.find(")")<100)
							{
								p1=(struct Backbone *) malloc(sizeof(struct Backbone));
								strcpy(p1->name,(Split(s,' ',0)).c_str());
								p1->c1c2=(atof(Split(s,' ',2).data()));
								p1->c2c3=(atof(Split(s,' ',3).data()));
								p1->phase=(atof(Split(s,' ',4).data()));
								p1->ampli=(atof(Split(s,' ',5).data()));
								strcpy(p1->pucker,(Split(s,' ',6)).c_str());
								p1->c1=(atof(Split(s,' ',7).data()));
								p1->c2=(atof(Split(s,' ',8).data()));
								p1->c3=(atof(Split(s,' ',9).data()));

								n++;
								if(n==1)
								{head=p1;}
								else
								{p2->next=p1;}
								p2=p1;
							}
							getline(infile,s);
						}

						while(s.find("--")>100)
						{
							if(s.find(")")<100)
							{
								struct Backbone *temp1,*temp2;
								temp1=head;

								while(strcmp(temp1->name,(Split(s,' ',0)).c_str())!=0&&temp1->next!=NULL)
								{
									temp2=temp1;
									temp1=temp1->next;
								}
								if(strcmp(temp1->name,(Split(s,' ',0)).c_str())==0)
								{
									temp1->chi=(atof(Split(s,' ',2).data()));
									if(Split(s,' ',3).find("..")>100)
									{
										temp1->gamma=(atof(Split(s,' ',3).data()));
									}
									temp1->delta=(atof(Split(s,' ',4).data()));
									if(Split(s,' ',5).find("..")>100)
									{
										temp1->epsil=(atof(Split(s,' ',5).data()));
									}
									if(Split(s,' ',6).find("..")>100)
									{
										temp1->zeta=(atof(Split(s,' ',6).data()));
									}
									if(Split(s,' ',7).find("..")>100)
									{
										temp1->alpha=(atof(Split(s,' ',7).data()));
									}
									if(Split(s,' ',8).find("..")>100)
									{
										temp1->beta=(atof(Split(s,' ',8).data()));
									}
									break;
								}
							}
							getline(infile,s);
						}
					}
				}
			}
		}
	infile.close();
	p2->next=NULL;
	return head;
}

void K_part(char *file)
{
	ifstream infile;
	string s;
	infile.open(file);
	while(!infile.fail())
	{
	}
}

//求取一维数据平均值
double average(double *vd,int N)
{
	double total=0;
	int size=0;
	for(int i=0;i<N;i++)
	{
		if(vd[i]!=0)
		{
			total+=vd[i];
			size++;
		}
	}
	return (double)total/size;
}

//生成螺旋参数矩阵
void Getmatrix(double **para,double** ma,int si)
/*for example Getmatirx(para[6][10],ma[6][6],10)*/
{	
	double *temp;
	temp=dvector(0,5);
	
	for(int i=0;i<6;i++)
	{
		temp[i]=0;
	}
	for(int i=0;i<si;i++)
	{
		temp[0]+=para[0][i];
		temp[1]+=para[1][i];
		temp[2]+=para[2][i];
		temp[3]+=para[3][i];
		temp[4]+=para[4][i];
		temp[5]+=para[5][i];
	}
	struct Paramater  *ave;
	ave=(struct Paramater *)malloc(sizeof(struct Paramater));
	ave->rise=temp[0]/si;
	ave->roll=temp[1]/si;
	ave->shift=temp[2]/si;
	ave->slide=temp[3]/si;
	ave->tilt=temp[4]/si;
	ave->twist=temp[5]/si;
	strcpy(ave->name,"ave");

	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			ma[i][j]=0;
		}
	}
	for(int i=0;i<si;i++)
    {
         double cov[6];
		 cov[0]=para[0][i]-ave->rise;
		 cov[1]=para[1][i]-ave->roll;
		 cov[2]=para[2][i]-ave->shift;
		 cov[3]=para[3][i]-ave->slide;
		 cov[4]=para[4][i]-ave->tilt;
		 cov[5]=para[5][i]-ave->twist;

          for(int m=0;m<6;m++)
          {
              for(int n=0;n<6;n++)
              {
                  ma[m][n]+=cov[m]*cov[n]/si;
              }
          }
     }
	free_dvector(temp,0,5);
}
//把文件变成一个链表
struct Filelist *Readlist(char *file,char choose)
{
	struct Filelist *head;
	struct Filelist *p1,*p2;
	struct Information *inf;
	ifstream infile;
	infile.open(file);
	string s;
	infile>>s;
	int n=0;
	while(!infile.fail())
	{
		
		inf=(struct Information *)malloc(sizeof(struct Information));
		Fileanalysis(s,inf);
		switch(choose)
		{
		case 'A':
			if(inf->A_exist)
			{
				p1=(struct Filelist *) malloc(sizeof(struct Filelist));
				strcpy(p1->file,s.c_str());
				n++;
				if(n==1)
				{
						head=p1;
				}
				else 
				{
					p2->next=p1;
				}
				p2=p1;
			}
			break;
		case 'B':
			if(inf->B_exist)
			{
				p1=(struct Filelist *) malloc(sizeof(struct Filelist));
				strcpy(p1->file,s.c_str());
				n++;
				if(n==1)
				{
						head=p1;
				}
				else 
				{
					p2->next=p1;
				}
				p2=p1;
			}
			break;
		case 'C':
			if(inf->C_exist)
			{
				p1=(struct Filelist *) malloc(sizeof(struct Filelist));
				strcpy(p1->file,s.c_str());
				n++;
				if(n==1)
				{
						head=p1;
				}
				else 
				{
					p2->next=p1;
				}
				p2=p1;
			}
			break;
		case 'D':
			if(inf->D_exist)
			{
				p1=(struct Filelist *) malloc(sizeof(struct Filelist));
				strcpy(p1->file,s.c_str());
				n++;
				if(n==1)
				{
						head=p1;
				}
				else 
				{
					p2->next=p1;
				}
				p2=p1;
			}
			break;
		case 'E':
			if(inf->E_exist)
			{
				p1=(struct Filelist *) malloc(sizeof(struct Filelist));
				strcpy(p1->file,s.c_str());
				n++;
				if(n==1)
				{
						head=p1;
				}
				else 
				{
					p2->next=p1;
				}
				p2=p1;
			}
			break;
		case 'F':
			if(inf->F_exist)
			{
				p1=(struct Filelist *) malloc(sizeof(struct Filelist));
				strcpy(p1->file,s.c_str());
				n++;
				if(n==1)
				{
						head=p1;
				}
				else 
				{
					p2->next=p1;
				}
				p2=p1;
			}
			break;
		case 'G':
			if(inf->G_exist)
			{
				p1=(struct Filelist *) malloc(sizeof(struct Filelist));
				strcpy(p1->file,s.c_str());
				n++;
				if(n==1)
				{
						head=p1;
				}
				else 
				{
					p2->next=p1;
				}
				p2=p1;
			}
			break;
		case 'H':
			if(inf->H_exist)
			{
				p1=(struct Filelist *) malloc(sizeof(struct Filelist));
				strcpy(p1->file,s.c_str());
				n++;
				if(n==1)
				{
						head=p1;
				}
				else 
				{
					p2->next=p1;
				}
				p2=p1;
			}
			break;
		case 'I':
			if(inf->I_exist)
			{
				p1=(struct Filelist *) malloc(sizeof(struct Filelist));
				strcpy(p1->file,s.c_str());
				n++;
				if(n==1)
				{
						head=p1;
				}
				else 
				{
					p2->next=p1;
				}
				p2=p1;
			}
			break;
		case 'J':
			if(inf->J_exist)
			{
				p1=(struct Filelist *) malloc(sizeof(struct Filelist));
				strcpy(p1->file,s.c_str());
				n++;
				if(n==1)
				{
						head=p1;
				}
				else 
				{
					p2->next=p1;
				}
				p2=p1;
			}
			break;
		case 'K':
			if(inf->K_exist)
			{
				p1=(struct Filelist *) malloc(sizeof(struct Filelist));
				strcpy(p1->file,s.c_str());
				n++;
				if(n==1)
				{
						head=p1;
				}
				else 
				{
					p2->next=p1;
				}
				p2=p1;
			}
			break;
		default:
			cout<<"A wrong chooose paramater is exist! "<<endl;
			exit(0);
		}
		infile>>s;
	}
	p2->next=NULL;
	infile.close();
	return head;			
}

//字符串拆分函数
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

//求取数据分布的函数
void Distribution(double *sd,int N,string filename)
{
	ofstream outfile;
	double  *sf;
	double  *ds;
	int LENGTH=100;
	sf=dvector(0,N-1) ;
	ds=dvector(0,LENGTH-1);

	double MAX=sd[0],MIN=sd[0];
	double total=0;
	
	for(int i=0;i<N;i++)
	{
		if(MAX<sd[i])
		{
			MAX=sd[i];
		}
		if(MIN>sd[i])
		{
			MIN=sd[i];
		}
		sf[i]=sd[i];
	}
//	cout<<MAX<<"\t"<<MIN<<endl;   /* just for debug!*/
	
	for(int i=0;i<LENGTH;i++)
	{
		ds[i]=0;
		for(int j=0;j<N;j++)
		{
			if(sf[j]>MIN+i*(MAX-MIN)/LENGTH&&sf[j]<MIN+(i+1)*(MAX-MIN)/LENGTH)
			{
				ds[i]++;
			}
		}
	}
	outfile.open(filename.c_str(),ios::app);
	for(int i=0;i<LENGTH;i++)
	{
		total+=ds[i];
	}
	for(int i=0;i<LENGTH;i++)
	{
		outfile<<fixed<<showpoint;
		outfile<<setprecision(2)<<MIN+(i+0.5)*(MAX-MIN)/LENGTH<<"\t\t"<<ds[i]*LENGTH/total/(MAX-MIN)<<endl;
	}

	outfile.close();
}

//把parameter的链表文件转化为二维的数组。
void Paramater2double(struct Paramater *head,double **data,struct Namelist *name,int begin, int end)
{
	struct Paramater *p1;
	struct Namelist *nhead,*np1,*np2;
	p1=head;
	int n=0;
	while(p1!=NULL )
	{
		np1=(struct Namelist *) malloc(sizeof(struct Namelist));
		strcpy(np1->name,p1->name);
		if(n>=(begin-1)&&n<=(end-1))
		{
			data[0][n+1-begin]=p1->rise;
			data[1][n+1-begin]=p1->roll;
			data[2][n+1-begin]=p1->shift;
			data[3][n+1-begin]=p1->slide;
			data[4][n+1-begin]=p1->tilt;
			data[5][n+1-begin]=p1->twist;
		}
		n++;
		p1=p1->next;
		if(n==1)
		{nhead=np1;}
		else
		{np2->next=np1;}
		np2=np1;
	}
}
//把backbone的链表转化为二维的数组
void Backbone2double(struct Backbone *head,double **data,struct Namelist *name,int begin,int end)
{
	struct Backbone *p1;
	struct Namelist *nhead,*np1,*np2;
	p1=head;
	int n=0;
	while(p1!=NULL)
	{
		np1=(struct Namelist *) malloc(sizeof(struct Namelist));
		strcpy(np1->name,p1->name);
		if(n>=(begin-1)&&n<=(end-1))
		{
			data[0][n+1-begin]=p1->alpha;
			data[1][n+1-begin]=p1->ampli;
			data[2][n+1-begin]=p1->beta;
			data[3][n+1-begin]=p1->c1;
			data[4][n+1-begin]=p1->c1c2;
			data[5][n+1-begin]=p1->c2;
			data[6][n+1-begin]=p1->c2c3;
			data[7][n+1-begin]=p1->c3;
			data[8][n+1-begin]=p1->chi;
			data[9][n+1-begin]=p1->delta;
			data[10][n+1-begin]=p1->epsil;
			data[11][n+1-begin]=p1->gamma;
			data[12][n+1-begin]=p1->phase;
			data[13][n+1-begin]=p1->zeta;
		}
		n++;
		p1=p1->next;
		if(n==1)
		{nhead=np1;}
		else
		{np2->next=np1;}
		np2=np1;
	}
}
//得到parameters的长度
int GetParamaterlen(struct Paramater *head)
{
	int n=1;
	while(head->next!=NULL)
	{
		n++;
		head=head->next;
	}
	return n;
}
//得到backbone的长度
int GetBackbonelen(struct Backbone *head)
{
	int n=1;
	while(head->next!=NULL)
	{
		n++;
		head=head->next;
	}
	return n;
}
//得到filelist中的文件的数目。
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


void Fileanalysis(string file, struct Information  *inf)
{
		inf->A_exist=false;
		inf->B_exist=false;
		inf->C_exist=false;
		inf->D_exist=false;
		inf->E_exist=false;
		inf->H_exist=false;
		inf->I_exist=false;
		inf->J_exist=false;
		inf->K_exist=false;

		ifstream infile(file.c_str());
		string s;
	//	string chaintemp=" ";
		getline(infile,s);
		while(!infile.fail())
		{
			/*
				if(s.find("Strand")<100&&s.find("has")<100&&s.find("bases")<100)
				{
					int m=s.find(":");
					string temp=s.substr(m+2);
					chaintemp+=temp.c_str()+"\n";
				}			*/					/*得到链的序列！*/
		
				if(s.find("|A|")<100)   /*判断文件是否完整！*/
				{
					inf->A_exist=true;
				}
				if(s.find("|B|")<100)
				{
					inf->B_exist=true;
				}
				if(s.find("|C|")<10)
				{
					inf->C_exist=true;
				}
				if(s.find("|D|")<100)
				{
					inf->D_exist=true;
				}
				if(s.find("|E|")<100)
				{
					inf->E_exist=true;
				}
				if(s.find("|F|")<100)
				{
					inf->F_exist=true;
				}
				if(s.find("|G|")<100)
				{
					inf->G_exist=true;
				}
				if(s.find("|H|")<100)
				{
					inf->H_exist=true;
				}
				if(s.find("|I|")<100)
				{
					inf->I_exist=true;
				}
				if(s.find("|J|")<100)
				{
					inf->J_exist=true;
				}
				if(s.find("|K|")<100)
				{
					inf->K_exist=true;
				}
								
			getline(infile,s);
		}

		if(inf->B_exist==false)
		{
			inf->A_exist=false;
		}
		if(inf->C_exist==false&&inf->E_exist==false)
		{
			inf->B_exist=false;
		}
		if(inf->D_exist==false)
		{
			inf->C_exist=false;
		}
		if(inf->E_exist==false)
		{
			inf->D_exist=false;
		}
		if(inf->F_exist==false&&inf->G_exist==false)
		{
			inf->E_exist=false;
		}
		if(inf->G_exist==false)
		{
			inf->F_exist=false;
		}
		if(inf->H_exist==false&&inf->I_exist==false)
		{
			inf->G_exist=false;
		}
		if(inf->I_exist==false)
		{
			inf->H_exist=false;
		}
		if(inf->J_exist==false)
		{
			inf->I_exist=false;
		}
		if(inf->K_exist==false)
		{
			inf->J_exist=false;
		}
//		inf->chain=chaintemp.c_str();
}
