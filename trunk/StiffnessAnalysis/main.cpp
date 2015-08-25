#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>

#define R 8.3145

using namespace std;

void StiffnessAnalysis(char *infile,string outfile,float temperature);
stack<string> Split(string s,char a);

int main(int argc,char *argv[])
{	
	char* infile;
	string outfile;
	float temperature=300;
	switch(argc)
	{
		case 1:
			cout<<"Using:StiffnessAnalysis -f eigenvaluefile.txt -t temperature -o outfile.txt"<<endl;
			exit(0);
		case 3:
			if(string(argv[1])=="-f")
			{
				infile=argv[2];
			}
			else
			{
				cout<<"Using:StiffnessAnalysis -f eigenvaluefile.txt -t temperature -o outfile.txt"<<endl;
				exit(0);
			}
			break;
		case 5:
			if(string(argv[1])=="-f"&&string(argv[3])=="-t")
			{
				infile=argv[2];
				temperature=atof(argv[4]);
			}

			else if(string(argv[1])=="-f"&&string(argv[3])=="-o")
			{
				infile=argv[2];
				outfile=string(argv[4]);
			}

			else
			{
				cout<<"Using:StiffnessAnalysis -f eigenvaluefile.txt -t temperature -o outfile.txt"<<endl;
				exit(0);
			}
			break;
		case 7:
			if(string(argv[1])=="-f"&&string(argv[3])=="-t"&&string(argv[5])=="-o")
			{
				infile=argv[2];
				temperature=atof(argv[4]);
				outfile=string(argv[6]);
			}
			else
			{
				cout<<"Using:StiffnessAnalysis -f eigenvaluefile.txt -t temperature -o outfile.txt"<<endl;
				exit(0);
			}
			break;
		default:
			cout<<"Using:StiffnessAnalysis -f eigenvaluefile.txt -t temperature -o outfile.txt"<<endl;
			exit(0);
	}
	if(outfile.empty())
	{
		int point=string(infile).find('.');
		outfile=string(infile).substr(0,point)+"_new.txt";
	}
	StiffnessAnalysis(infile,outfile,temperature);
	cout<<"Creat stiffness file "<<outfile<<"!"<<endl;
	return 0;
}

void StiffnessAnalysis(char *infile,string outfile,float temperature)
{
	ifstream in;
	ofstream out;
	string s;
	in.open(infile);
	out.open("temp");
	getline(in,s);
	while(!in.fail())
	{
		if((int)s[0]>47&&(int)s[0]<58)
		{
			stack<string> vs=Split(s,'\t');
			double te=atof(vs.top().data());
			vs.pop();
			out<<vs.top()<<setw(20)<<R*temperature/te<<endl;
			getline(in,s);
			continue;
		}
		out<<s<<endl;
		getline(in,s);
	}
	in.close();
	out.close();
	rename("temp",outfile.data());
}

stack<string> Split(string s,char a)
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
	return sm;
}
