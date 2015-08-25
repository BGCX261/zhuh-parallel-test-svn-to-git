/*
 modified by zhuh at 2010.10.15
 1.It's write for gmx. so notice that the unit of eigenvalue is nm2.
 2.another program is for wordom which unit is A2.
 3.
*/
#pragma once
#include <math.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include "m_f.h"

#define K 1.3806504e-23
#define hba 1.05457148e-34
#define R 8.3145
#define E 2.71828183

using namespace std;

double Andricioaei(double *eigval ,int number ,int temperature);
double Schlitter(double *eigval,int number,int temperature);
double ReadEigvalFile(char *filename,int number,int temperature,string choose);
 string Split(string s,char a,int n);

int main(int argc, char* argv[])
{
	char *file;
	double entropy;
	double temperature;
	string choose;
	int number;
	switch(argc)
	{
		case 1:
			cout<<"USage: Qhentropy -f eigvalfile -n number -t temperature -c A<Andricioaei>/S<Schlitter>"<<endl;
			cout<<"Note:"<<endl;
			cout<<"1.It's write for gmx eigenvalue result,which unit is nm2."<<endl;
			cout<<"2.if you forget choose Andricicaei or Schlitter to claculate,the default is Andricioaei."<<endl;
			exit(0);
		case 7:
			if(string(argv[1])=="-f"&&string(argv[3])=="-n"&&string(argv[5])=="-t")
			{
				file=argv[2];
				number=atoi(argv[4]);
				temperature=atof(argv[6]);
				choose="Andricioaei";
					
			}
			if(string(argv[1])=="-n"&&string(argv[3])=="-f"&&string(argv[5])=="-t")
			{
				choose="Andricioaei";
				file=argv[4];
				number=atoi(argv[2]);
				temperature=atof(argv[6]);
			}
			if(string(argv[1])=="-t"&&string(argv[3])=="-n"&&string(argv[5])=="-f")
			{
				choose="Andricioaei";
				file=argv[6];
				number=atoi(argv[2]);
				temperature=atof(argv[4]);
			}
			break;
		case 9:
			if(string(argv[1])=="-f"&&string(argv[3])=="-n"&&string(argv[5])=="-t"&&string(argv[7])=="-c")
			{
				file=argv[2];
				number=atoi(argv[4]);
				temperature=atof(argv[6]);
				choose=argv[8];
			}
			break;
		default:
			cout<<"USage: QHEntropy -f eigvalfile -n number -t temperature -c Andricioaei/Schlitter"<<endl;
			exit(0);
	}
	entropy=ReadEigvalFile(file,number,temperature,choose);
	cout<<setw(10)<<entropy<<endl;
	return 0;
}


double Andricioaei(double *eigval ,int number ,int temperature)
 {
	   double entropy=0.0;
	   for(int i=0;i<number;i++)
       {	
		   double temp=eigval[i];
           double omiga=sqrt(R*temperature*1e21/temp);
           double apart=hba*omiga/K/temperature;
           double tempQ=apart/(exp(apart)-1)-log(1-exp(-apart)) ;
		   
           entropy+=tempQ*R;   
       }
       return entropy;
 }
 double Schlitter(double *eigval,int number,int temperature)
 {	
	    double entropy=0.0;
        for(int i=0;i<number;i++)
        {
			 double temp=eigval[i];
             double omiga=sqrt(R*temperature*1e21/temp);
             double apart=hba*omiga/K/temperature;
             double tempQ=log(1+pow(E/apart, 2));
             entropy+=0.5*tempQ*R;
        }
        return entropy;
 }

 double ReadEigvalFile(char *filename,int number,int temperature,string choose)
 {
	 ifstream infile;
	 infile.open(filename);
	 vector<double> eig;
	 double entropy=0;
	 double *eigval;
	 double ei;
	 if(!infile)
	 {  
		 entropy=-1;
	 }
	 else
	 {
		string s;
		getline(infile,s);
		while(!infile.fail())
		{
			if(s.at(0)!='#'&&s.at(0)!='@')
			{
				ei=atof(Split(s,' ',1).c_str());
				eig.push_back(ei);
			}
			getline(infile,s);
		}
		eigval=dvector(0,eig.size()-1);
		int size=eig.size();
	//	cout<<eig.size()<<endl;
		for(int i=0;i<size-1;i++)
		{
			eigval[i]=eig.at(i);
			if(i==0)
			{
		//		cout<<eigval[i]<<endl;
			}
		//	cout<<i<<setw(10)<<eigval[i]<<" hello world!"<<endl;
		}
		if(choose=="Andricioaei")
		{
			entropy=Andricioaei(eigval,number,temperature);
		}
		else if(choose=="Schlitter")
		{
			entropy=Schlitter(eigval,number,temperature);
		}		
	 }
	 infile.close();
	 return entropy;
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

