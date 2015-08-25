#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>

#include "m_f.h"
#include "atomlib.h"

#define EPSILON 0.000001

using namespace std;

double eigenvalue(double ** matrix,int N,double * vector);
void  eigenvector(double ** matrix,int N,double eigencalue);

void  Rotation_matrix(double **experiment_matrix,char base,double ** rotation_matrix);
void Least_square_fit_frame(double ** experiment_matrix,double ** rotation_matrix,char base,double ** fitted_matrix);
void origin_vector(double ** experiment_matrix,double ** rotation_matrix,char base,double * o_vector);

double dot_product_vector(double * vector_1,double * vector_2,int N);
void cross_product_vector(double * vector_1,double * vectoor_2,double * vector_result);

void rotate_2_vector(double * vector_1,double * vector_2,double * vector_result);


#endif
