#include "structure.h"

void base_pair_parameters(double **rotation_matrix_1,double **rotation_matrix_2,double * origin_vector_1,double * origin_vector_2,double & shear,double & stretch,double & stagger,double & buckle,double & propeller,double &opening)
{
	double gamma;
	double omega;
	double phi;
	double kappa;
	double sigma;
	double displacement_x=0;
	double displacement_y=0;
	double displacement_z=0;
	double *  b0_vector;
	double *  y1_vector;
	double *  y2_vector;

	b0_vector=dvector(0,2);
	y1_vector=dvector(0,2);
	y2_vector=dvector(0,2);

	double ** rotate_matrix_1;  
	double ** rotate_matrix_2;
	double ** transformed_orientation_matrix_1;
	double ** transformed_orientation_matrix_2;

	rotate_matrix_1=dmatrix(0,2,0,2);
    rotate_matrix_2=dmatrix(0,2,0,2);
	transformed_orientation_matrix_1=dmatrix(0,2,0,2);
	transformed_orientation_matrix_2=dmatrix(0,2,0,2);

	double ** MBT_matirx;

	MBT_matirx=dmatrix(0,2,0,2);

//	double * MBT_origin_vector;
//	MBT_origin_vector=dvector(0,2);

	double * x_vector_temp_1;
	double * x_vector_temp_2;
	double * cross_result_temp;
	double * cross_b0_xmat_temp;
	double * x_vector_MBT;
	double * y_vector_MBT;

	x_vector_temp_1=dvector(0,2);
	x_vector_temp_2=dvector(0,2);
	cross_result_temp=dvector(0,2);
	cross_b0_xmat_temp=dvector(0,2);
	x_vector_MBT=dvector(0,2);
	y_vector_MBT=dvector(0,2);

	double total=0;

	double ** displacement_matrix;
	displacement_matrix=dmatrix(0,2,0,2);


	for(int i=0;i<3;i++)
	{
		y1_vector[i]=rotation_matrix_1[i][1];
		y2_vector[i]=rotation_matrix_2[i][1];
	}
	gamma=acos(dot_product_vector(y1_vector,y2_vector,3));  //calculate buckleopening angle.
	cross_product_vector(y2_vector,y1_vector,b0_vector);//buckle-opening axis
	//
	
	for(int i=0;i<3;i++)
	{
		total+=b0_vector[i]*b0_vector[i];
	}
	for(int i=0;i<3;i++)
	{
		b0_vector[i]=b0_vector[i]/sqrt(total);
	}   //   normalize the b0;

	//
	rotate_matrix_1[0][0]= cos(-gamma/2) + (1-cos(-gamma/2))*b0_vector[0]*b0_vector[0];
	rotate_matrix_1[0][1]= (1-cos(-gamma/2))*b0_vector[0]*b0_vector[1] - b0_vector[2]*sin(-gamma/2);
	rotate_matrix_1[0][2]= (1-cos(-gamma/2))*b0_vector[0]*b0_vector[2] + b0_vector[1]*sin(-gamma/2);
	rotate_matrix_1[1][0]= (1-cos(-gamma/2))*b0_vector[0]*b0_vector[1] + b0_vector[2]*sin(-gamma/2); 
	rotate_matrix_1[1][1]=cos(-gamma/2) + (1-cos(-gamma/2))*b0_vector[1]*b0_vector[1];
	rotate_matrix_1[1][2]=(1-cos(-gamma/2))*b0_vector[1]*b0_vector[2] - b0_vector[0]*sin(-gamma/2);
	rotate_matrix_1[2][0]=(1-cos(-gamma/2))*b0_vector[0]*b0_vector[2] - b0_vector[1]*sin(-gamma/2);
	rotate_matrix_1[2][1]=(1-cos(-gamma/2))*b0_vector[1]*b0_vector[2] + b0_vector[0]*sin(-gamma/2);
	rotate_matrix_1[2][2]=cos(-gamma/2) + (1-cos(-gamma/2))*b0_vector[2]*b0_vector[2];
	//create rotate_matrix_1;
	rotate_matrix_2[0][0]= cos(gamma/2) + (1-cos(gamma/2))*b0_vector[0]*b0_vector[0];
	rotate_matrix_2[0][1]= (1-cos(gamma/2))*b0_vector[0]*b0_vector[1] - b0_vector[2]*sin(gamma/2);
	rotate_matrix_2[0][2]= (1-cos(gamma/2))*b0_vector[0]*b0_vector[2] + b0_vector[1]*sin(gamma/2);
	rotate_matrix_2[1][0]= (1-cos(gamma/2))*b0_vector[0]*b0_vector[1] + b0_vector[2]*sin(gamma/2); 
	rotate_matrix_2[1][1]=cos(gamma/2) + (1-cos(gamma/2))*b0_vector[1]*b0_vector[1];
	rotate_matrix_2[1][2]=(1-cos(gamma/2))*b0_vector[1]*b0_vector[2] - b0_vector[0]*sin(gamma/2);
	rotate_matrix_2[2][0]=(1-cos(gamma/2))*b0_vector[0]*b0_vector[2] - b0_vector[1]*sin(gamma/2);
	rotate_matrix_2[2][1]=(1-cos(gamma/2))*b0_vector[1]*b0_vector[2] + b0_vector[0]*sin(gamma/2);
	rotate_matrix_2[2][2]=cos(gamma/2) + (1-cos(gamma/2))*b0_vector[2]*b0_vector[2];
	//create rotate_matrix_2;

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			transformed_orientation_matrix_1[i][j]=0;
			transformed_orientation_matrix_2[i][j]=0;
			for(int k=0;k<3;k++)
			{
				transformed_orientation_matrix_1[i][j]+=rotate_matrix_1[i][k]*rotation_matrix_1[k][j];
				transformed_orientation_matrix_2[i][j]+=rotate_matrix_2[i][k]*rotation_matrix_2[k][j];
			}	
		}
	}		//get the orientation matirx of transformed bases.

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			MBT_matirx[i][j]=(transformed_orientation_matrix_1[i][j]+transformed_orientation_matrix_2[i][j])/2;
		}
//		MBT_origin_vector[i]=(origin_vector_1+origin_vector_2)/2;
	}    // create the MBT matrix;



	for(int i=0;i<3;i++)
	{
		x_vector_temp_1[i]=transformed_orientation_matrix_1[i][0];
		x_vector_temp_2[i]=transformed_orientation_matrix_2[i][0];
		y_vector_MBT[i]=MBT_matirx[i][1];
	}
	omega=acos(dot_product_vector(x_vector_temp_1,x_vector_temp_2,3));
	cross_product_vector(x_vector_temp_2,x_vector_temp_1,cross_result_temp);
	if(dot_product_vector(cross_result_temp,y_vector_MBT,3)<0)
	{
		omega=-omega;
	}   // for omega

	total=0;
	for(int i=0;i<3;i++)
	{
		total+=MBT_matirx[i][0]*MBT_matirx[i][0];
	}
	for(int i=0;i<3;i++)
	{
		x_vector_MBT[i]=MBT_matirx[i][0]/sqrt(total);
	}   //  normalize the MBT_matirx of x;

	phi=acos(dot_product_vector(b0_vector,x_vector_MBT,3));

	cross_product_vector(b0_vector,x_vector_MBT,cross_b0_xmat_temp);

	if(dot_product_vector(cross_b0_xmat_temp,y_vector_MBT,3)<0)
	{
		phi= - phi;
	}  //for phi;

	kappa=gamma* cos(phi);
	sigma=gamma * sin(phi);

	//get kappa and sigma;
	

	for(int i=0;i<3;i++)
	{
		displacement_x+=(origin_vector_1[i] - origin_vector_2[i])*MBT_matirx[i][0];
		displacement_y+=(origin_vector_1[i] - origin_vector_2[i])*MBT_matirx[i][1];
		displacement_z+=(origin_vector_1[i] - origin_vector_2[i])*MBT_matirx[i][2];
	}

	shear=displacement_x;
	stretch=displacement_y;
	stagger=displacement_z;
	buckle=kappa/PI * 180; 
	propeller=omega /PI * 180;
	opening=sigma/PI * 180;

}

void base_step_paramaters(double **rotation_matrix_1,double **rotation_matrix_2,double * origin_vector_1,double * origin_vector_2,double & shift,double & slide,double & rise,double & tilt,double & roll,double & twist)
{
	double gamma;
	double omega;
	double phi;
	double kappa;
	double sigma;
	double displacement_x=0;
	double displacement_y=0;
	double displacement_z=0;
	double *  rt_vector;
	double *  z1_vector;
	double *  z2_vector;

	rt_vector=dvector(0,2);
	z1_vector=dvector(0,2);
	z2_vector=dvector(0,2);

	double ** rotate_matrix_1;  
	double ** rotate_matrix_2;
	double ** transformed_orientation_matrix_1;
	double ** transformed_orientation_matrix_2;

	rotate_matrix_1=dmatrix(0,2,0,2);
    rotate_matrix_2=dmatrix(0,2,0,2);
	transformed_orientation_matrix_1=dmatrix(0,2,0,2);
	transformed_orientation_matrix_2=dmatrix(0,2,0,2);

	double ** MST_matirx;

	MST_matirx=dmatrix(0,2,0,2);

//	double * MST_origin_vector;
//	MST_origin_vector=dvector(0,2);

	double * y_vector_temp_1;
	double * y_vector_temp_2;
	double * cross_result_temp;
	double * cross_rt_ymat_temp;
	double * y_vector_MST;
	double * z_vector_MST;

	y_vector_temp_1=dvector(0,2);
	y_vector_temp_2=dvector(0,2);
	cross_result_temp=dvector(0,2);
	cross_rt_ymat_temp=dvector(0,2);
	y_vector_MST=dvector(0,2);
	z_vector_MST=dvector(0,2);

	double total=0;

//	double ** displacement_matrix;
//	displacement_matrix=dmatrix(0,2,0,2);


	for(int i=0;i<3;i++)
	{
		z1_vector[i]=rotation_matrix_1[i][2];
		z2_vector[i]=rotation_matrix_2[i][2];
	}
	gamma=acos(dot_product_vector(z1_vector,z2_vector,3));  //calculate buckleopening angle.
	cross_product_vector(z1_vector,z2_vector,rt_vector);//buckle-opening axis
	//
	
	for(int i=0;i<3;i++)
	{
		total+=rt_vector[i]*rt_vector[i];
	}
	for(int i=0;i<3;i++)
	{
		rt_vector[i]=rt_vector[i]/sqrt(total);
	}   //   normalize the b0;

	//
	rotate_matrix_2[0][0]= cos(-gamma/2) + (1-cos(-gamma/2))*rt_vector[0]*rt_vector[0];
	rotate_matrix_2[0][1]= (1-cos(-gamma/2))*rt_vector[0]*rt_vector[1] - rt_vector[2]*sin(-gamma/2);
	rotate_matrix_2[0][2]= (1-cos(-gamma/2))*rt_vector[0]*rt_vector[2] + rt_vector[1]*sin(-gamma/2);
	rotate_matrix_2[1][0]= (1-cos(-gamma/2))*rt_vector[0]*rt_vector[1] + rt_vector[2]*sin(-gamma/2); 
	rotate_matrix_2[1][1]=cos(-gamma/2) + (1-cos(-gamma/2))*rt_vector[1]*rt_vector[1];
	rotate_matrix_2[1][2]=(1-cos(-gamma/2))*rt_vector[1]*rt_vector[2] - rt_vector[0]*sin(-gamma/2);
	rotate_matrix_2[2][0]=(1-cos(-gamma/2))*rt_vector[0]*rt_vector[2] - rt_vector[1]*sin(-gamma/2);
	rotate_matrix_2[2][1]=(1-cos(-gamma/2))*rt_vector[1]*rt_vector[2] + rt_vector[0]*sin(-gamma/2);
	rotate_matrix_2[2][2]=cos(-gamma/2) + (1-cos(-gamma/2))*rt_vector[2]*rt_vector[2];
	//create rotate_matrix_1;
	rotate_matrix_1[0][0]= cos(gamma/2) + (1-cos(gamma/2))*rt_vector[0]*rt_vector[0];
	rotate_matrix_1[0][1]= (1-cos(gamma/2))*rt_vector[0]*rt_vector[1] - rt_vector[2]*sin(gamma/2);
	rotate_matrix_1[0][2]= (1-cos(gamma/2))*rt_vector[0]*rt_vector[2] + rt_vector[1]*sin(gamma/2);
	rotate_matrix_1[1][0]= (1-cos(gamma/2))*rt_vector[0]*rt_vector[1] + rt_vector[2]*sin(gamma/2); 
	rotate_matrix_1[1][1]=cos(gamma/2) + (1-cos(gamma/2))*rt_vector[1]*rt_vector[1];
	rotate_matrix_1[1][2]=(1-cos(gamma/2))*rt_vector[1]*rt_vector[2] - rt_vector[0]*sin(gamma/2);
	rotate_matrix_1[2][0]=(1-cos(gamma/2))*rt_vector[0]*rt_vector[2] - rt_vector[1]*sin(gamma/2);
	rotate_matrix_1[2][1]=(1-cos(gamma/2))*rt_vector[1]*rt_vector[2] + rt_vector[0]*sin(gamma/2);
	rotate_matrix_1[2][2]=cos(gamma/2) + (1-cos(gamma/2))*rt_vector[2]*rt_vector[2];
	//create rotate_matrix_2;

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			transformed_orientation_matrix_1[i][j]=0;
			transformed_orientation_matrix_2[i][j]=0;
			for(int k=0;k<3;k++)
			{
				transformed_orientation_matrix_1[i][j]+=rotate_matrix_1[i][k]*rotation_matrix_1[k][j];
				transformed_orientation_matrix_2[i][j]+=rotate_matrix_2[i][k]*rotation_matrix_2[k][j];
			}	
		}
	}		//get the orientation matirx of transformed bases.

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			MST_matirx[i][j]=(transformed_orientation_matrix_1[i][j]+transformed_orientation_matrix_2[i][j])/2;
		}
//		MST_origin_vector[i]=(origin_vector_1+origin_vector_2)/2;
	}    // create the MST matrix;



	for(int i=0;i<3;i++)
	{
		y_vector_temp_1[i]=transformed_orientation_matrix_1[i][1];
		y_vector_temp_2[i]=transformed_orientation_matrix_2[i][1];
		z_vector_MST[i]=MST_matirx[i][2];
	}
	omega=acos(dot_product_vector(y_vector_temp_1,y_vector_temp_2,3));
	cross_product_vector(y_vector_temp_1,y_vector_temp_2,cross_result_temp);
	if(dot_product_vector(cross_result_temp,z_vector_MST,3)<0)
	{
		omega=-omega;
	}   // for omega

	total=0;
	for(int i=0;i<3;i++)
	{
		total+=MST_matirx[i][1]*MST_matirx[i][1];
	}
	for(int i=0;i<3;i++)
	{
		y_vector_MST[i]=MST_matirx[i][1]/sqrt(total);
	}   //  normalize the MST_matirx of x;

	phi=acos(dot_product_vector(rt_vector,y_vector_MST,3));

	cross_product_vector(rt_vector,y_vector_MST,cross_rt_ymat_temp);

	if(dot_product_vector(cross_rt_ymat_temp,z_vector_MST,3)<0)
	{
		phi= - phi;
	}  //for phi;

	kappa=gamma* cos(phi);
	sigma=gamma * sin(phi);

	//get kappa and sigma;
	

	for(int i=0;i<3;i++)
	{
		displacement_x+=(origin_vector_2[i] - origin_vector_1[i])*MST_matirx[i][0];
		displacement_y+=(origin_vector_2[i] - origin_vector_1[i])*MST_matirx[i][1];
		displacement_z+=(origin_vector_2[i] - origin_vector_1[i])*MST_matirx[i][2];
	}


	shift=displacement_x;
	slide=displacement_y;
	rise=displacement_z;
	roll=kappa/PI * 180; 
	twist=omega /PI * 180;
	tilt=sigma/PI * 180;

}


void middle_frame(double **rotation_matrix_1,double **rotation_matrix_2,double * origin_vector_1,double * origin_vector_2,double ** middle_matirx,double * middle_origin_vector)
{
	double gamma;
	double *  b0_vector;
	double *  y1_vector;
	double *  y2_vector;

	b0_vector=dvector(0,2);
	y1_vector=dvector(0,2);
	y2_vector=dvector(0,2);

	double ** rotate_matrix_1;  
	double ** rotate_matrix_2;
	double ** transformed_orientation_matrix_1;
	double ** transformed_orientation_matrix_2;

	rotate_matrix_1=dmatrix(0,2,0,2);
    rotate_matrix_2=dmatrix(0,2,0,2);
	transformed_orientation_matrix_1=dmatrix(0,2,0,2);
	transformed_orientation_matrix_2=dmatrix(0,2,0,2);


	double total=0;


	for(int i=0;i<3;i++)
	{
		y1_vector[i]=rotation_matrix_1[i][1];
		y2_vector[i]=rotation_matrix_2[i][1];
	}
	gamma=acos(dot_product_vector(y1_vector,y2_vector,3));  //calculate buckleopening angle.
	cross_product_vector(y2_vector,y1_vector,b0_vector);//buckle-opening axis
	//
	
	for(int i=0;i<3;i++)
	{
		total+=b0_vector[i]*b0_vector[i];
	}
	for(int i=0;i<3;i++)
	{
		b0_vector[i]=b0_vector[i]/sqrt(total);
	}   //   normalize the b0;

	//
	rotate_matrix_1[0][0]= cos(-gamma/2) + (1-cos(-gamma/2))*b0_vector[0]*b0_vector[0];
	rotate_matrix_1[0][1]= (1-cos(-gamma/2))*b0_vector[0]*b0_vector[1] - b0_vector[2]*sin(-gamma/2);
	rotate_matrix_1[0][2]= (1-cos(-gamma/2))*b0_vector[0]*b0_vector[2] + b0_vector[1]*sin(-gamma/2);
	rotate_matrix_1[1][0]= (1-cos(-gamma/2))*b0_vector[0]*b0_vector[1] + b0_vector[2]*sin(-gamma/2); 
	rotate_matrix_1[1][1]=cos(-gamma/2) + (1-cos(-gamma/2))*b0_vector[1]*b0_vector[1];
	rotate_matrix_1[1][2]=(1-cos(-gamma/2))*b0_vector[1]*b0_vector[2] - b0_vector[0]*sin(-gamma/2);
	rotate_matrix_1[2][0]=(1-cos(-gamma/2))*b0_vector[0]*b0_vector[2] - b0_vector[1]*sin(-gamma/2);
	rotate_matrix_1[2][1]=(1-cos(-gamma/2))*b0_vector[1]*b0_vector[2] + b0_vector[0]*sin(-gamma/2);
	rotate_matrix_1[2][2]=cos(-gamma/2) + (1-cos(-gamma/2))*b0_vector[2]*b0_vector[2];
	//create rotate_matrix_1;
	rotate_matrix_2[0][0]= cos(gamma/2) + (1-cos(gamma/2))*b0_vector[0]*b0_vector[0];
	rotate_matrix_2[0][1]= (1-cos(gamma/2))*b0_vector[0]*b0_vector[1] - b0_vector[2]*sin(gamma/2);
	rotate_matrix_2[0][2]= (1-cos(gamma/2))*b0_vector[0]*b0_vector[2] + b0_vector[1]*sin(gamma/2);
	rotate_matrix_2[1][0]= (1-cos(gamma/2))*b0_vector[0]*b0_vector[1] + b0_vector[2]*sin(gamma/2); 
	rotate_matrix_2[1][1]=cos(gamma/2) + (1-cos(gamma/2))*b0_vector[1]*b0_vector[1];
	rotate_matrix_2[1][2]=(1-cos(gamma/2))*b0_vector[1]*b0_vector[2] - b0_vector[0]*sin(gamma/2);
	rotate_matrix_2[2][0]=(1-cos(gamma/2))*b0_vector[0]*b0_vector[2] - b0_vector[1]*sin(gamma/2);
	rotate_matrix_2[2][1]=(1-cos(gamma/2))*b0_vector[1]*b0_vector[2] + b0_vector[0]*sin(gamma/2);
	rotate_matrix_2[2][2]=cos(gamma/2) + (1-cos(gamma/2))*b0_vector[2]*b0_vector[2];
	//create rotate_matrix_2;

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			transformed_orientation_matrix_1[i][j]=0;
			transformed_orientation_matrix_2[i][j]=0;
			for(int k=0;k<3;k++)
			{
				transformed_orientation_matrix_1[i][j]+=rotate_matrix_1[i][k]*rotation_matrix_1[k][j];
				transformed_orientation_matrix_2[i][j]+=rotate_matrix_2[i][k]*rotation_matrix_2[k][j];
			}	
		}
	}		//get the orientation matirx of transformed bases.

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			middle_matirx[i][j]=(transformed_orientation_matrix_1[i][j]+transformed_orientation_matrix_2[i][j])/2;
		}
		middle_origin_vector[i]=(origin_vector_1[i]+origin_vector_2[i])/2;
	}   

}

