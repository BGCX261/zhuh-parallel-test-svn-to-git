#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <iomanip>

#include <stdio.h>
#include <stdlib.h>
#include  "m_f.h"

using namespace std;

string Split(string s,char a,int n);
void Distribution(double *sd,int N,char * filename);

int main(int argc,char * argv[])
{
	char * input;
	int num;
	char * output;
	switch(argc)
	{
	case 7:
		for(int i=0;i<7;i++)
		{
			if(string(argv[i])=="-f")
			{
				input=argv[i+1];
			}
			if(string(argv[i])=="-n")
			{
				num=atoi(argv[i+1]);
			}
			if(string(argv[i])=="-o")
			{
				output=argv[i+1];
			}
		}
		break;
	default:
		cout<<"Usage: Distribution -f filename -n num -o output"<<endl;
		exit(0);

	}

	ifstream in(input);
	string ss;
	getline(in,ss);
	vector<double> vd;
	while(!in.fail())
	{
		string temp="";
		if(ss.at(0)!='#')
		{	
			if(ss.find('\t')<100)
			{
				temp=Split(ss,'\t',num-1);
			}
			else
			{	
				temp=Split(ss,' ',num-1);
			}
			vd.push_back(atof(temp.c_str()));
		}	
		getline(in,ss);
	}
	double * sd;
	sd=dvector(0,vd.size()-1);
	for(int i=0;i<vd.size();i++)
	{
		sd[i]=vd.at(i);
	}
	Distribution(sd,vd.size(),output);
}

void Distribution(double *sd,int N,char * output)
{
	ofstream outfile;
	double  *sf;
	double  *ds;
	int LENGTH=20;
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
	outfile.open(output);
	for(int i=0;i<LENGTH;i++)
	{
		total+=ds[i];
	}
	for(int i=0;i<LENGTH;i++)
	{
		outfile<<fixed<<showpoint;
		outfile<<setprecision(3)<<MIN+(i+0.5)*(MAX-MIN)/LENGTH<<"\t\t"<<ds[i]*LENGTH/total/(MAX-MIN)<<endl;
	}

	outfile.close();
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
