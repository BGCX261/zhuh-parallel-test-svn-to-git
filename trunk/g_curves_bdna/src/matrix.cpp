#include "matrix.h"

double eigenvalue(double ** matrix,int N)
{
	
	double * x;
	double * nx;
	double xmax;
	double oxmax=0;
	double ooxmax=0;
	//≥ı ºªØX°æi°ø
	x=dvector(0,N-1);
	nx=dvector(0,N-1);
	for(int i=0;i<N;i++)
	{
		x[i]=1;
	}
	//
	int h=0;
	while(true)
	{
		for(int j=0;j<N;j++)
		{
			nx[j]=0;
			for(int k=0;k<N;k++)
			{
				nx[j]+=matrix[j][k]*x[k];
			}
		}
		xmax=0.0;
		for(int j=0;j<N;j++)
		{
			if(fabs(nx[j])>xmax)
			{
				xmax=fabs(nx[j]);
			}
		}

		if(fabs(xmax-oxmax)<EPSILON&&fabs(oxmax-ooxmax)<EPSILON)
		{			
			break;
		}
        //
		if(fabs(xmax-oxmax)<EPSILON/10&&fabs(oxmax-ooxmax)>10*EPSILON)
		{
					double x_max,y_max;

					for(int j=0;j<N;j++)
					{
							nx[j]/=xmax;    
							x[j]=nx[j];    //Y(k-1)=X(k-1)/xmax;
					}
					y_max=x[0]; //

					for(int j=0;j<N;j++)
					{
						nx[j]=0;
						for(int k=0;k<N;k++)
						{
							nx[j]+=matrix[j][k]*x[k];   //X(k)=Y(k-1)*Matrix;
						}
					}
					
					//
					for(int j=0;j<N;j++)
					{
						x[j]=nx[j];   //Y(k)=X(k);
					}

					for(int j=0;j<N;j++)
					{
						nx[j]=0;
						for(int k=0;k<N;k++)
						{
							nx[j]+=matrix[j][k]*x[k];   //X(k+1)=X(k)*Matrix;
						}
					}
					x_max=nx[0];
					if(h%2==0)
					{
						xmax=sqrt(x_max/y_max);
					}
		break;
						
		}
		//

		if(h%2==0)
		{
			oxmax=xmax;
		}
		else
		{
			ooxmax=xmax;
		}

		for(int j=0;j<N;j++)
		{
			nx[j]/=xmax;
			x[j]=nx[j];
		}
		h++;
	}
	return xmax;
}


void eigenvector(double ** matrix,int N,double eigenvalue,double * vector)
{
	double ** B_matrix;
	double * X1_vector;
	double * X2_vector;

	B_matrix=dmatrix(0,N-1,0,N-1);
	X1_vector=dvector(0,N-1);
	X2_vector=dvector(0,N-1);

	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(i==j)
			{
				B_matrix[i][j]=0;
			}
			else
			{
				B_matrix[i][j]=-matrix[i][j]/(matrix[i][i]-eigenvalue);
			}
		}
		X1_vector[i]=0;
		X2_vector[i]=1;
	}
	//
	for(int x=0;x<20;x++)
	{
		for(int i=0;i<N;i++)
		{
			X1_vector[i]=X2_vector[i];
		}

		for(int i=0;i<N;i++)
		{
			double temp=0;
			for(int j=0;j<i;j++)
			{
				temp+=B_matrix[i][j]*X2_vector[j];
			}
			for(int j=i;j<N;j++)
			{
				temp+=B_matrix[i][j]*X1_vector[j];
			}
			X2_vector[i]=temp;
		}

		double diff=0;
		 for(int i=0;i<N;i++)
		 {
			 if(fabs(X2_vector[i]-X1_vector[i])>diff)
			 {
				 diff=fabs(X2_vector[i]-X1_vector[i]);
			 }
		 }
		 if(diff<EPSILON&&diff>0)
		 {
			 break;
		 }
//
		 double total=0;
		for(int i=0;i<N;i++)
		{
				total+=X2_vector[i]*X2_vector[i];
		}
		for(int i=0;i<N;i++)
		{
				vector[i]=X2_vector[i]/sqrt(total);
//				cout<<vector[i]<<"\t";
		}
	//			cout<<endl;
		 //
	}

}
void  Rotation_matrix(double **experiment_matrix,char base,double ** rotation_matrix)
{
	int N;
	double ** strandard_matrix;
	double ** covariance_matrix;
	double ** symmetric_matrix;
	double * eigenvector_matrix;
	
	eigenvector_matrix=dvector(0,3);
	covariance_matrix=dmatrix(0,2,0,2);
	symmetric_matrix=dmatrix(0,3,0,3);

//
	switch(base)
	{
	case 'A':
			N=9;
			strandard_matrix=dmatrix(0,N-1,0,3);
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<3;j++)
				{
					strandard_matrix[i][j]=A_origin[i][j];
				}
			}
			break;
	case 'C':
			N=6;
			strandard_matrix=dmatrix(0,N-1,0,3);
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<3;j++)
				{
					strandard_matrix[i][j]=C_origin[i][j];
				}
			}
			break;
	case 'G':
			N=9;
			strandard_matrix=dmatrix(0,N-1,0,3);
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<3;j++)
				{
					strandard_matrix[i][j]=G_origin[i][j];				
				}
			}
			break;
	case 'T':
		N=6;
			strandard_matrix=dmatrix(0,N-1,0,3);
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<3;j++)
				{
					strandard_matrix[i][j]=T_origin[i][j];
				}
			}
		break;
	case 'U':
		N=6;
			strandard_matrix=dmatrix(0,N-1,0,3);
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<3;j++)
				{
					strandard_matrix[i][j]=U_origin[i][j];
				}
			}
		break;
	default:
		break;
	}
	//create the covariance matrix
	double s_sum_x=0,s_sum_y=0,s_sum_z=0;
	double e_sum_x=0,e_sum_y=0,e_sum_z=0;
	double ** se;
	double **siie;
	se=dmatrix(0,2,0,2);
	siie=dmatrix(0,2,0,2);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			se[i][j]=0;
		}
	}
	for(int m=0;m<3;m++)
	{
		for(int n=0;n<3;n++)
		{
			for(int t=0;t<N;t++)
			{
				se[m][n]+=(strandard_matrix[t][m]*experiment_matrix[t][n]);
			}
		//	cout<<se[m][n]<<endl;
		}
	}
	for(int i=0;i<N;i++)
	{
		s_sum_x+=strandard_matrix[i][0];
		//cout<<s_sum_x<<endl;
		s_sum_y+=strandard_matrix[i][1];
		s_sum_z+=strandard_matrix[i][2];
		e_sum_x+=experiment_matrix[i][0];
	//	cout<<e_sum_x<<endl;
		e_sum_y+=experiment_matrix[i][1];
		e_sum_z+=experiment_matrix[i][2];
	}
	siie[0][0]=s_sum_x*e_sum_x/N;
	//cout<<siie[0][0]<<endl;
	siie[0][1]=s_sum_x*e_sum_y/N;
	siie[0][2]=s_sum_x*e_sum_z/N;
	siie[1][0]=s_sum_y*e_sum_x/N;
	siie[1][1]=s_sum_y*e_sum_y/N;
	siie[1][2]=s_sum_y*e_sum_z/N;
	siie[2][0]=s_sum_z*e_sum_x/N;
	siie[2][1]=s_sum_z*e_sum_y/N;
	siie[2][2]=s_sum_z*e_sum_z/N;

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			covariance_matrix[i][j]=(se[i][j]-siie[i][j])/(N-1);
		//	cout<<covariance_matrix[i][j]<<endl;
		}
	}

	symmetric_matrix[0][0]=covariance_matrix[0][0]+covariance_matrix[1][1]+covariance_matrix[2][2];
	symmetric_matrix[0][1]=covariance_matrix[1][2]-covariance_matrix[2][1];
	symmetric_matrix[0][2]=covariance_matrix[2][0]-covariance_matrix[0][2];
	symmetric_matrix[0][3]=covariance_matrix[0][1]-covariance_matrix[1][0];
	symmetric_matrix[1][0]=covariance_matrix[1][2]-covariance_matrix[2][1];
	symmetric_matrix[1][1]=covariance_matrix[0][0]-covariance_matrix[1][1]-covariance_matrix[2][2];
	symmetric_matrix[1][2]=covariance_matrix[0][1]+covariance_matrix[1][0];
	symmetric_matrix[1][3]=covariance_matrix[2][0]+covariance_matrix[0][2];
	symmetric_matrix[2][0]=covariance_matrix[2][0]-covariance_matrix[0][2];
	symmetric_matrix[2][1]=covariance_matrix[0][1]+covariance_matrix[1][0];
	symmetric_matrix[2][2]=-covariance_matrix[0][0]+covariance_matrix[1][1]-covariance_matrix[2][2];
	symmetric_matrix[2][3]=covariance_matrix[1][2]+covariance_matrix[2][1];
	symmetric_matrix[3][0]=covariance_matrix[0][1]-covariance_matrix[1][0];
	symmetric_matrix[3][1]=covariance_matrix[2][0]+covariance_matrix[0][2];
	symmetric_matrix[3][2]=covariance_matrix[1][2]+covariance_matrix[2][1];
	symmetric_matrix[3][3]=-covariance_matrix[0][0]-covariance_matrix[1][1]+covariance_matrix[2][2];


	double eigenva=eigenvalue(symmetric_matrix,4);

	eigenvector(symmetric_matrix,4,eigenva,eigenvector_matrix);

	rotation_matrix[0][0]=eigenvector_matrix[0]*eigenvector_matrix[0]+eigenvector_matrix[1]*eigenvector_matrix[1]-eigenvector_matrix[2]*eigenvector_matrix[2]-eigenvector_matrix[3]*eigenvector_matrix[3];
	rotation_matrix[0][1]=2*(eigenvector_matrix[1]*eigenvector_matrix[2]-eigenvector_matrix[0]*eigenvector_matrix[3]);
	rotation_matrix[0][2]=2*(eigenvector_matrix[1]*eigenvector_matrix[3]+eigenvector_matrix[0]*eigenvector_matrix[2]);
	rotation_matrix[1][0]=2*(eigenvector_matrix[2]*eigenvector_matrix[1]+eigenvector_matrix[0]*eigenvector_matrix[3]);
	rotation_matrix[1][1]=eigenvector_matrix[0]*eigenvector_matrix[0]-eigenvector_matrix[1]*eigenvector_matrix[1]+eigenvector_matrix[2]*eigenvector_matrix[2]-eigenvector_matrix[3]*eigenvector_matrix[3];
	rotation_matrix[1][2]=2*(eigenvector_matrix[2]*eigenvector_matrix[3]-eigenvector_matrix[0]*eigenvector_matrix[1]);
	rotation_matrix[2][0]=2*(eigenvector_matrix[3]*eigenvector_matrix[1]-eigenvector_matrix[0]*eigenvector_matrix[2]);
	rotation_matrix[2][1]=2*(eigenvector_matrix[3]*eigenvector_matrix[2]+eigenvector_matrix[0]*eigenvector_matrix[1]);
	rotation_matrix[2][2]=eigenvector_matrix[0]*eigenvector_matrix[0]-eigenvector_matrix[1]*eigenvector_matrix[1]-eigenvector_matrix[2]*eigenvector_matrix[2]+eigenvector_matrix[3]*eigenvector_matrix[3];

}	

void Least_square_fit_frame(double ** experiment_matrix,double ** rotation_matrix,char base,double ** fitted_matrix)
{
	int N=0;
	double e_ave_x=0 , e_ave_y=0 , e_ave_z=0;
	double s_ave_x=0 , s_ave_y=0 , s_ave_z=0;
	double * o_vector;
	o_vector=dvector(0,2);

	switch (base)
	{
	case 'A':
		N=9;
		for(int i=0;i<N;i++)
		{
			e_ave_x+=experiment_matrix[i][0] ;
			e_ave_y+=experiment_matrix[i][1] ; 
			e_ave_z+=experiment_matrix[i][2];
			s_ave_x+=A_origin[i][0] ; 
			s_ave_y+=A_origin[i][1] ; 
			s_ave_z+=A_origin[i][2];
		}
		break;
	case 'C':
		N=6;
		for(int i=0;i<N;i++)
		{
			e_ave_x+=experiment_matrix[i][0] ;
			e_ave_y+=experiment_matrix[i][1] ; 
			e_ave_z+=experiment_matrix[i][2];
			s_ave_x+=C_origin[i][0] ; 
			s_ave_y+=C_origin[i][1] ; 
			s_ave_z+=C_origin[i][2];
		}
		break;
	case 'G':
		N=9;
		for(int i=0;i<N;i++)
		{
			e_ave_x+=experiment_matrix[i][0] ;
			e_ave_y+=experiment_matrix[i][1] ; 
			e_ave_z+=experiment_matrix[i][2];
			s_ave_x+=G_origin[i][0] ; 
			s_ave_y+=G_origin[i][1] ; 
			s_ave_z+=G_origin[i][2];
		}
		break;
	case 'T':
		N=6;
		for(int i=0;i<N;i++)
		{
			e_ave_x+=experiment_matrix[i][0] ;
			e_ave_y+=experiment_matrix[i][1] ; 
			e_ave_z+=experiment_matrix[i][2];
			s_ave_x+=T_origin[i][0] ; 
			s_ave_y+=T_origin[i][1] ; 
			s_ave_z+=T_origin[i][2];
		}
		break;
	case 'U':
		N=6;
		for(int i=0;i<N;i++)
		{
			e_ave_x+=experiment_matrix[i][0] ;
			e_ave_y+=experiment_matrix[i][1] ; 
			e_ave_z+=experiment_matrix[i][2];
			s_ave_x+=T_origin[i][0] ; 
			s_ave_y+=T_origin[i][1] ; 
			s_ave_z+=T_origin[i][2];
		}
		break;
	}
		e_ave_x=e_ave_x/N ;
		e_ave_y=e_ave_y/N ; 
		e_ave_z=e_ave_z/N;
		s_ave_x=s_ave_x/N ;
		s_ave_y=s_ave_y/N ; 
		s_ave_z=s_ave_z/N;


			o_vector[0]=e_ave_x - s_ave_x*rotation_matrix[0][0] - s_ave_y*rotation_matrix[0][1] - s_ave_z*rotation_matrix[0][2];
			o_vector[1]=e_ave_y - s_ave_x*rotation_matrix[1][0] - s_ave_y*rotation_matrix[1][1] - s_ave_z*rotation_matrix[1][2];
			o_vector[2]=e_ave_z - s_ave_x*rotation_matrix[2][0] - s_ave_y*rotation_matrix[2][1] - s_ave_z*rotation_matrix[2][2];
	//		cout<<o_vector[0]<<endl;
//			cout<<o_vector[1]<<endl;
//			cout<<o_vector[2]<<endl;


		for(int i=0;i<N;i++)
		{
			for(int j=0;j<3;j++)
			{
				fitted_matrix[i][j]=o_vector[j];
				for(int k=0;k<3;k++)
				{
					switch(base)
					{
					case 'A':
						fitted_matrix[i][j]+=A_origin[i][k]*rotation_matrix[j][k];
						break;
					case 'C':
						fitted_matrix[i][j]+=C_origin[i][k]*rotation_matrix[j][k];
						break;
					case 'G':
						fitted_matrix[i][j]+=G_origin[i][k]*rotation_matrix[j][k];
						break;
					case 'T':
						fitted_matrix[i][j]+=T_origin[i][k]*rotation_matrix[j][k];
						break;
					case 'U':
						fitted_matrix[i][j]+=U_origin[i][k]*rotation_matrix[j][k];
						break;
					}
				}
			}
		}
}

double dot_product_vector(double * vector_1,double * vector_2,int N)
{
	double result=0;
	for(int i=0;i<N;i++)
	{
		result+=vector_1[i]*vector_2[i];
	}
	return result;
}
void cross_product_vector(double * vector_1,double * vector_2,double * vector_result)  //for N =3
{
	vector_result[0]=vector_1[1]*vector_2[2]-vector_1[2]*vector_2[1];
	vector_result[1]=vector_1[2]*vector_2[0]-vector_1[0]*vector_2[2];
	vector_result[2]=vector_1[0]*vector_2[1]-vector_1[1]*vector_2[0];
}


void origin_vector(double ** experiment_matrix,double ** rotation_matrix,char base,double * o_vector)
{
	int N=0;
	double e_ave_x=0 , e_ave_y=0 , e_ave_z=0;
	double s_ave_x=0 , s_ave_y=0 , s_ave_z=0;


	switch (base)
	{
	case 'A':
		N=9;
		for(int i=0;i<N;i++)
		{
			e_ave_x+=experiment_matrix[i][0] ;
			e_ave_y+=experiment_matrix[i][1] ; 
			e_ave_z+=experiment_matrix[i][2];
			s_ave_x+=A_origin[i][0] ; 
			s_ave_y+=A_origin[i][1] ; 
			s_ave_z+=A_origin[i][2];
		}
		break;
	case 'C':
		N=6;
		for(int i=0;i<N;i++)
		{
			e_ave_x+=experiment_matrix[i][0] ;
			e_ave_y+=experiment_matrix[i][1] ; 
			e_ave_z+=experiment_matrix[i][2];
			s_ave_x+=C_origin[i][0] ; 
			s_ave_y+=C_origin[i][1] ; 
			s_ave_z+=C_origin[i][2];
		}
		break;
	case 'G':
		N=9;
		for(int i=0;i<N;i++)
		{
			e_ave_x+=experiment_matrix[i][0] ;
			e_ave_y+=experiment_matrix[i][1] ; 
			e_ave_z+=experiment_matrix[i][2];
			s_ave_x+=G_origin[i][0] ; 
			s_ave_y+=G_origin[i][1] ; 
			s_ave_z+=G_origin[i][2];
		}
		break;
	case 'T':
		N=6;
		for(int i=0;i<N;i++)
		{
			e_ave_x+=experiment_matrix[i][0] ;
			e_ave_y+=experiment_matrix[i][1] ; 
			e_ave_z+=experiment_matrix[i][2];
			s_ave_x+=T_origin[i][0] ; 
			s_ave_y+=T_origin[i][1] ; 
			s_ave_z+=T_origin[i][2];
		}
		break;
	case 'U':
		N=6;
		for(int i=0;i<N;i++)
		{
			e_ave_x+=experiment_matrix[i][0] ;
			e_ave_y+=experiment_matrix[i][1] ; 
			e_ave_z+=experiment_matrix[i][2];
			s_ave_x+=T_origin[i][0] ; 
			s_ave_y+=T_origin[i][1] ; 
			s_ave_z+=T_origin[i][2];
		}
		break;
	}
		e_ave_x=e_ave_x/N ;
		e_ave_y=e_ave_y/N ; 
		e_ave_z=e_ave_z/N;
		s_ave_x=s_ave_x/N ;
		s_ave_y=s_ave_y/N ; 
		s_ave_z=s_ave_z/N;

			o_vector[0]=e_ave_x - s_ave_x*rotation_matrix[0][0] - s_ave_y*rotation_matrix[0][1] - s_ave_z*rotation_matrix[0][2];
			o_vector[1]=e_ave_y - s_ave_x*rotation_matrix[1][0] - s_ave_y*rotation_matrix[1][1] - s_ave_z*rotation_matrix[1][2];
			o_vector[2]=e_ave_z - s_ave_x*rotation_matrix[2][0] - s_ave_y*rotation_matrix[2][1] - s_ave_z*rotation_matrix[2][2];


}

void rotate_2_vector(double * vector_1,double * vector_2,double * vector_result)
{
	double gamma;
	double total=0;
	double * b0_vector;
	double ** rotate_matrix_1;

	b0_vector=dvector(0,2);
	 rotate_matrix_1=dmatrix(0,2,0,2);

	gamma=acos(dot_product_vector(vector_1,vector_2,3));  //calculate buckleopening angle.
	cross_product_vector(vector_1,vector_2,b0_vector);//buckle-opening axis
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

	for(int i=0;i<3;i++)
	{
		vector_result[i]=0;
		for(int j=0;j<3;j++)
		{
			vector_result[i]+=rotate_matrix_1[i][j]*vector_2[j];
		}
	}

	double total_2=0;
	for(int i=0;i<3;i++)
	{
		total_2+=vector_result[i]*vector_result[i];
	}
	for(int i=0;i<3;i++)
	{
		vector_result[i]=vector_result[i]/sqrt(total_2);
	}


}

