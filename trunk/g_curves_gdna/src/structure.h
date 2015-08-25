#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "matrix.h"

void base_pair_parameters(double **rotation_matrix_1,double **rotation_matrix_2,double * origin_vector_1,double * origin_vector_2,double & shear,double & stretch,double & stagger,double & buckle,double & propeller,double &opening);
void base_step_paramaters(double **ratation_matrix_1,double **rotation_matrix_2,double * origin_vector_1,double * origin_vector_2,double & shift,double & slide,double & rise,double & tilt,double & roll,double & twist);

void middle_frame(double **rotation_matrix_1,double **rotation_matrix_2,double * origin_vector_1,double * origin_vector_2,double ** middle_matirx,double * middle_origin_vector);
//calculate the middle frame of basepair;

#endif

 
