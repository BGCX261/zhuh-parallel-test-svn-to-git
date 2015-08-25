#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

struct Atom
{
	char chain[5];
		int  reside;
		char atom[20] ;	
		struct Atom *next; 
};

struct Filelist
{
	char file[20];
	struct Filelist *next;
};


struct Filelist *Readlist(char *file);
int Getfilelen(struct Filelist *head);
int Getatomlen(struct Atom *head);
string Split(string s,char a,int n);
vector<string> Split_v(string s,char a);
void ReadInput(char *inputfile,string &operate,string &output,struct Atom *& atom_A,struct Atom *& atom_B,struct Atom * &atom_C);
void GetXYZ(char * file, struct Atom * atom_A,struct Atom *atom_B,struct Atom * atom_C,double * vect);
void GetNum(string in,struct Atom * atom_T, double &x,double &y,double &z,int Len);
double angle(double * vect,double &L,double &H,double &aa,double &bb,double &cc);
#endif