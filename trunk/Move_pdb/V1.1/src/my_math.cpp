#include "my_math.h"

void rotate(double x,double y,double z,double ro_x,double ro_y,double ro_z, double & res_x,double & res_y,double & res_z)
{
	double temp_x;
	double temp_y;
	double temp_z;

	double setta_x=asin(z/sqrt(y*y+z*z));
	if(y<0)
	{
		setta_x=PI-setta_x;
	}
	temp_x=x;
	temp_z=sqrt(y*y+z*z)*sin(setta_x+ro_x);
	temp_y=sqrt(y*y+z*z)*cos(setta_x+ro_x);

	double temp_x_2;
	double temp_y_2;
	double temp_z_2;
	
	double setta_y=asin(temp_x/sqrt(temp_x*temp_x+temp_z*temp_z));
	if(temp_z<0)
	{
		setta_y=PI-setta_y;
	}
	temp_x_2=sqrt(temp_x*temp_x+temp_z*temp_z)*sin(setta_y+ro_y);
	temp_y_2=temp_y;
	temp_z_2=sqrt(temp_x*temp_x+temp_z*temp_z)*cos(setta_y+ro_y);

	double temp_x_3;
	double temp_y_3;
	double temp_z_3;
	
	double setta_z=asin(temp_y_2/sqrt(temp_x_2*temp_x_2+temp_y_2*temp_y_2));
	if(temp_x_2<0)
	{
		setta_z=PI-setta_z;
	}
	temp_y_3=sqrt(temp_x_2*temp_x_2+temp_y_2*temp_y_2)*sin(setta_z+ro_z);
	temp_z_3=temp_z_2;
	temp_x_3=sqrt(temp_x_2*temp_x_2+temp_y_2*temp_y_2)*cos(setta_z+ro_z);

	res_x=temp_x_3;
	res_y=temp_y_3;
	res_z=temp_z_3;
}
