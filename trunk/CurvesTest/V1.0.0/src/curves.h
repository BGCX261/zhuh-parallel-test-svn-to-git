#ifndef CURVES_H
#define CURVES_H

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <iomanip>

#include "m_f.h"
#include "matrix.h"
// #define DEBUG
#define NULL 0

using namespace std;
struct Filelist
{
	char file[20];
	struct Filelist *next;
};
struct Namelist
{
	char name[20];
	struct Namelist *next;
};
struct Information
{	
	bool A_exist;
	bool B_exist;
	bool C_exist;
	bool D_exist;
	bool E_exist;
	bool F_exist;
	bool G_exist;
	bool H_exist;
	bool I_exist;
	bool J_exist;
	bool K_exist;
	char chain[100];
	struct Information * next;
};

struct Paramater
{
	double twist;
    double tilt;
    double roll;
    double shift;
    double rise;
    double slide;
    char name[20];
	struct Paramater * next;
};

struct Backbone
{
	double c1c2;
	double c2c3;
	double phase;
	double ampli;
	char pucker[10];
	double c1;
	double c2;
	double c3;
	double chi;
	double gamma;
	double delta;
	double epsil;
	double zeta;
	double alpha;
	double beta;
	char name[20];
	struct Backbone * next;
};

void A_part(char *file);
void B_part(char *file);
void C_part(char *file);
void D_part(char *file);
struct Paramater *E_part(char *file);
struct Paramater *F_part(char *file);
struct Paramater *G_part(char *file);
struct Paramater *H_part(char *file);
void I_part(char *file);
struct Backbone *J_part(char * file);
void K_part(char *file);

void Getmatrix(double **pama,double** ma,int si);
void Distribution(double *sd,int N,string filename);
struct Filelist *Readlist(char *file);
double average(double *vd,int N);
void Paramater2double(struct Paramater *head,double **data,struct Namelist *name,int begin, int end);
void Backbone2double(struct Backbone *head,double **data,struct Namelist *name,int begin,int end);
string Split(string s,char a,int n);
int GetParamaterlen(struct Paramater *head);
int GetBackbonelen(struct Backbone *head);
int Getfilelen(struct Filelist *head);
#endif