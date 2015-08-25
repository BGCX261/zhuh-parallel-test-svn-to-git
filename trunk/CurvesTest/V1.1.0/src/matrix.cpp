#include "matrix.h"
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void ludcmp(double **a, int n, int *indx, double *d)
{
	int i,imax,j,k;
	double big,dum,sum,temp;
	double *vv;
	
	vv=dvector_NR(1,n);
	*d=1.0;
	for (i=1;i<=n;i++) {
		big=0.0;
		for (j=1;j<=n;j++)
			if ((temp=fabs(a[i][j])) > big) big=temp;
			if (big == 0.0) nrerror("Singular matrix in routine ludcmp");
			vv[i]=1.0/big;
	}
	
	for (j=1;j<=n;j++) {
		for (i=1;i<j;i++) {
			sum=a[i][j];
			for (k=1;k<i;k++) sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
		}
		big=0.0;
		for (i=j;i<=n;i++) {
			sum=a[i][j];
			for (k=1;k<j;k++)
				sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
			if ( (dum=vv[i]*fabs(sum)) >= big) {
				big=dum;
				imax=i;
			}
		}
		
		if (j != imax) {
			for (k=1;k<=n;k++) {
				dum=a[imax][k];
				a[imax][k]=a[j][k];
				a[j][k]=dum;
			}
			
			*d = -(*d);
			
			vv[imax]=vv[j];
			
		}
		
		indx[j]=imax;
		
		if (a[j][j] == 0.0) a[j][j]=TINY;
		
		if (j != n) {
			
			dum=1.0/(a[j][j]);
			
			for (i=j+1;i<=n;i++) a[i][j] *= dum;
			
		}
		
	}
	
	free_dvector_NR(vv,1,n);
	
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void lubksb(double **a, int n, int *indx, double b[])
{
	
	int i,ii=0,ip,j;
	double sum;
	
	for (i=1;i<=n;i++) {
		
		ip=indx[i];
		
		sum=b[ip];
		
		b[ip]=b[i];
		
		if (ii)
			
			for (j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];
			
		else if (sum) ii=i;
			
		b[i]=sum;
			
	}
	
	for (i=n;i>=1;i--) {
		
		sum=b[i];
		
		for (j=i+1;j<=n;j++) sum -= a[i][j]*b[j];
		
		b[i]=sum/a[i][i];
		
	}
	
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void inverse_matrix(double **a_origin, double **a_origin_inverse,int N) ///求逆矩阵
{
	
	double **a,**y,d,*col;
	int i,j,*indx;
	a=dmatrix_NR(1,N,1,N);
	col=dvector_NR(1,N);
	y=dmatrix_NR(1,N,1,N);
	indx=ivector_NR(1,N);
	
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
		{
			
			a[i][j]=a_origin[i-1][j-1];
			
		}
		
		ludcmp(a,N,indx,&d);
		for(j=1;j<=N;j++)
		{
			
			for(i=1;i<=N;i++) col[i]=0.0;
			col[j]=1.0;
			lubksb(a,N,indx,col);
			for(i=1;i<=N;i++) y[i][j]=col[i];
		}
		
		for(i=1;i<=N;i++)
			for(j=1;j<=N;j++)
			{
				a_origin_inverse[i-1][j-1]=y[i][j];
			}
			
			
			
			free_dmatrix_NR(a,1,N,1,N);
			free_dvector_NR(col,1,N);
			free_dmatrix_NR(y,1,N,1,N);
			free_ivector_NR(indx,1,N);
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void inverse_matrix_NR(double **a_origin, double **a_origin_inverse,int N) ///求逆矩阵
{
	
	double **a,**y,d,*col;
	int i,j,*indx;
	a=dmatrix_NR(1,N,1,N);
	col=dvector_NR(1,N);
	y=dmatrix_NR(1,N,1,N);
	indx=ivector_NR(1,N);
	
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
		{
			
			a[i][j]=a_origin[i][j];
			
		}
		
		ludcmp(a,N,indx,&d);
		for(j=1;j<=N;j++)
		{
			
			for(i=1;i<=N;i++) col[i]=0.0;
			col[j]=1.0;
			lubksb(a,N,indx,col);
			for(i=1;i<=N;i++) y[i][j]=col[i];
		}
		
		for(i=1;i<=N;i++)
			for(j=1;j<=N;j++)
			{
				a_origin_inverse[i][j]=y[i][j];
			}
			
			
			
			free_dmatrix_NR(a,1,N,1,N);
			free_dvector_NR(col,1,N);
			free_dmatrix_NR(y,1,N,1,N);
			free_ivector_NR(indx,1,N);
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
double det_matrix(double **ah,int N) ///求矩阵的行列式
{
	double **a,d;
	int i,j;
	int *indx;
	
	a=dmatrix_NR(1,N,1,N);
	indx=ivector_NR(1,N);
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
		{
			a[i][j]=ah[i-1][j-1];
		}
		
		ludcmp(a,N,indx,&d);
		
		for(j=1;j<=N;j++)
			
			d *=a[j][j];
		
		
		
		free_dmatrix_NR(a,1,N,1,N);
		free_ivector_NR(indx,1,N);
		
		return d;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void multi_matrix1(double **a, double **b,int N) ///求矩阵的乘积
{
	int i,j,k;
	double **c;
	c=dmatrix(0, N, 0, N);
	
	for(i=0;i<=N;i++){
		for(j=0;j<=N;j++)
		{
			c[i][j]=0.0;
		}
	}
	for(i=0;i<=N;i++){
		for(j=0;j<=N;j++){
			for(k=0;k<=N;k++){
				c[i][j]=c[i][j]+a[i][k]*b[k][j];
			}
		}
	}
	
	for(i=0;i<=N;i++){
		for(j=0;j<=N;j++){
			b[i][j]=c[i][j];
		}
	}
	free_dmatrix(c,0,N,0,N);	
}
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void multi_matrix2(double **a, double *b,int N) ///求矩阵的乘积
{
	int i,j;
	double *c;
	c=dvector(0,N);
	
	for(i=0;i<=N;i++)
	{
		c[i]=0.0;
	}
	for(i=0;i<=N;i++){
		for(j=0;j<=N;j++){
			c[i]=c[i]+a[i][j]*b[j];
		}
	}
	for(i=0;i<=N;i++){
		b[i]=c[i];
	}
	free_dvector(c, 0, N);
}
/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
void multi_matrix1_NR(double **a, double **b,int N)
{
	int i,j,k;
	double **c;
	c=dmatrix_NR(1,N,1,N);
	
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++)
		{
			c[i][j]=0.0;
		}
	}
	
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			for(k=1;k<=N;k++){
				c[i][j]=c[i][j]+a[i][k]*b[k][j];
			}
		}
	}
	
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			b[i][j]=c[i][j];
		}
	}
	
	free_dmatrix_NR(c,1,N,1,N);
}
/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
void multi_matrix2_NR(double **a, double *b,int N)
{
	int i,j;
	double *c;
	c=dvector_NR(1,N);
	
	for(i=1;i<=N;i++)
	{
		c[i]=0.0;
	}
	
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			c[i]=c[i]+a[i][j]*b[j];
		}
	}
	
	for(i=1;i<=N;i++){
		b[i]=c[i];
	}
	
	free_dvector_NR(c,1,N);
}
/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
void tridag(double a[], double b[], double c[], double r[], double u[], unsigned long n)
{

	unsigned long j;

	double bet,*gam;

	gam=dvector_NR(1,n);

	if (b[1] == 0.0) nrerror("Error 1 in tridag");

	u[1]=r[1]/(bet=b[1]);

	for (j=1;j<=n;j++) {

		gam[j]=c[j-1]/bet;

		bet=b[j]-a[j]*gam[j];

		if (bet == 0.0)	nrerror("Error 2 in tridag");

		u[j]=(r[j]-a[j]*u[j-1])/bet;

	}

	for (j=(n-1);j>=1;j--){
		
		u[j] -= gam[j+1]*u[j+1];
	}

	free_dvector_NR(gam,1,n);

}
/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


