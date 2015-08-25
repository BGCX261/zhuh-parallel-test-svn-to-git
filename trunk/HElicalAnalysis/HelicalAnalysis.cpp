// HelicalAnalysis.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <vector>

#include "matrix.h"
#include "Paramater.h"
#include "Information.h"

using namespace std;

vector<Paramater> Readfile(string file,string choose);
string Split(string s,char a,int n);
void Getmatrix(vector<Paramater>,double**);
vector<string> Readlist(char *file);

int main(int argc, char* argv[])
{
	double temperature=300;
	char *file;
	string choose="E";
	
	switch(argc)
	{
	case 1:
		cout<<"Usage:HelicalAnalysis -f file -t temperature -c choose(E/F/G)"<<endl;
		exit(0);
	case 3:
		if(string(argv[1])=="-f")
		{
			file=argv[2];
			break;
		}
	case 5:
		if(string(argv[1])=="-f"&&string(argv[3])=="-t")
		{
			file=argv[2];
			temperature=atof(argv[4]);
			break;
		}
		if(string(argv[3])=="-f"&&string(argv[1])=="-t")
		{
			file=argv[4];
			temperature=atof(argv[2]);
			break;
		}
	case 7:
		if(string(argv[1])=="-f"&&string(argv[3])=="-t"&&string(argv[5])=="-c")
		{
			file=argv[2];
			temperature=atof(argv[4]);
			choose=string(argv[6]);
			break;
		}
	default:
		cout<<"Usage:HelicalAnalysis -f file -t temperature -c choose(E/F/G)"<<endl;
		exit(0);
	}
	vector<string> ss=Readlist(file);
	int si=ss.size();
	vector<Paramater> sx=Readfile(ss[0],choose);
	int sl=sx.size();
	double ***pli;
	pli=f3tensor(0,sl-1,0,si-1,0,5);

	for(int i=0;i<si;i++)
	{
		vector<Paramater> sp=Readfile(ss[i],choose);
		for(int j=0;j<sl;j++)
		{
			pli[j][i][0]=sp[j].GetRise();
			pli[j][i][1]=sp[j].GetRoll();
			pli[j][i][2]=sp[j].GetShift();
			pli[j][i][3]=sp[j].GetSlide();
			pli[j][i][4]=sp[j].GetTilt();
			pli[j][i][5]=sp[j].GetTwist();
		}
	}
	cout<<setw(12)<<"Rise"<<"\t\t"<<"Roll"<<setw(16)<<"Shift"<<setw(16)<<"Slide"<<setw(16)<<"Tilt"<<setw(16)<<"Twist"<<endl;
	for(int i=0;i<sl;i++)
	{
		vector<Paramater> sp;
		for(int j=0;j<si;j++)
		{
			Paramater temp(pli[i][j][0],pli[i][j][1],pli[i][j][2],pli[i][j][3],pli[i][j][4],pli[i][j][5],"");
			sp.push_back(temp);
		}
		double **result;
		double **inverse;
		result=dmatrix(0,5,0,5);
		inverse=dmatrix(0,5,0,5);
		Getmatrix(sp,result);
		inverse_matrix(result,inverse,6);
		cout<<sx[i].GetName();
		for(int m=0;m<6;m++)
        {
             for(int n=0;n<6;n++)
             {
                  if(m==n)
                  {
					  cout<<fixed<<showpoint;
					  cout<<"\t"<<setprecision(6)<<inverse[m][n]*8.3145*temperature/1000/4.2;
                  }
				  
             }
			 
        }
		cout<<endl;
		free_dmatrix(result,0,5,0,5);
		free_dmatrix(inverse,0,5,0,5);
	}
	free_f3tensor(pli,0,sl-1,0,si-1,0,5);

	return 0;
}

vector<Paramater> Readfile(string file,string choose)
{
	ifstream infile(file.c_str());
	cout<<"Read File "<<file<<endl;
	string s;
	vector<Paramater> vp;
	getline(infile,s);
	while(!infile.fail())
	{
			if(s.find(choose)<100)
			{
				getline(infile,s);
				getline(infile,s);
				while(s.find("--")>100)
				{
					if(s.find("/")<100)
					{
						Paramater pa(atof(Split(s,' ',6).data()),atof(Split(s,' ',8).data()),atof(Split(s,' ',4).data()),atof(Split(s,' ',5).data()),atof(Split(s,' ',7).data()),atof(Split(s,' ',9).data()),Split(s,' ',1)+Split(s,' ',2)+Split(s,' ',3));
						vp.push_back(pa);
					}
					getline(infile,s);
				}
			}
			getline(infile,s);
	}
	infile.close();
	return vp;

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

void Getmatrix(vector<Paramater> sp,double** ma)
{
	
	double *temp;
	double **para;
	int si=sp.size();
	temp=dvector(0,5);
	para=dmatrix(0,5,0,si-1);
	
	for(int i=0;i<6;i++)
	{
		temp[i]=0;
	}
	for(int i=0;i<si;i++)
	{
		para[0][i]=sp[i].GetRise();
		temp[0]+=para[0][i];
		para[1][i]=sp[i].GetRoll();
		temp[1]+=para[1][i];
		para[2][i]=sp[i].GetShift();
		temp[2]+=para[2][i];
		para[3][i]=sp[i].GetSlide();
		temp[3]+=para[3][i];
		para[4][i]=sp[i].GetTilt();
		temp[4]+=para[4][i];
		para[5][i]=sp[i].GetTwist();
		temp[5]+=para[5][i];
	}
	Paramater ave(temp[0]/si,temp[1]/si,temp[2]/si,temp[3]/si,temp[4]/si,temp[5]/si,"avg");

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
         cov[0]=para[0][i]-ave.GetRise();
         cov[1]=para[1][i]-ave.GetRoll();
         cov[2]=para[2][i]-ave.GetShift();
         cov[3]=para[3][i]-ave.GetSlide();
         cov[4]=para[4][i]-ave.GetTilt();
         cov[5]=para[5][i]-ave.GetTwist();

          for(int m=0;m<6;m++)
          {
              for(int n=0;n<6;n++)
              {
                  ma[m][n]+=cov[m]*cov[n]/si;
              }
          }
     }
	free_dvector(temp,0,5);
	free_dmatrix(para,0,5,0,si-1);
}

vector<string> Readlist(char *file)
{
	vector<string> ss;
	ifstream infile;
	infile.open(file);
	string s;
	infile>>s;
	while(!infile.fail())
	{
		ss.push_back(s);
		infile>>s;
	}
	infile.close();
	return ss;			
}
