#ifndef	MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include "constants.h"
#include "m_f.h"

void ludcmp(double **a, int n, int *indx, double *d);
void lubksb(double **a, int n, int *indx, double b[]);
void inverse_matrix(double **a_origin, double **a_origin_inverse,int N);
void inverse_matrix_NR(double **a_origin, double **a_origin_inverse,int N);
double det_matrix(double **ah,int N);
void multi_matrix1(double **a, double **b,int N);
void multi_matrix2(double **a, double *b,int N);
void multi_matrix1_NR(double **a, double **b,int N);
void multi_matrix2_NR(double **a, double *b,int N);
void tridag(double a[], double b[], double c[], double r[], double u[], unsigned long n);
#endif
