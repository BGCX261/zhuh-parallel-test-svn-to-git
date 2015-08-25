#include "read_xtc.h"
/*
 * read a base one time.
 */

void  read_xtc2Rotation_matrix(char * filename,const char * out_file,int base_serial,struct atom * atom_head,int step_frame )
{
        int natoms,step;
        float time_temp;
        float p;
        matrix box;
        rvec *x;
        XDRFILE *xtc;
        xtc=xdrfile_open(filename,"r");
        int read_return=read_xtc_natoms(filename,&natoms);
		
		int num_step=0;

		ofstream out(out_file);
		out<<"#calculate the distence of  ion to the center of the two quartets in z-axis/"<<endl;
		out<<"#Time\t"<<"R[0][0]"<<"\t"<<"R[0][1]"<<"\t"<<"R[0][2]"<<"\t";
		out<<"R[1][0]"<<"\t"<<"R[1][1]"<<"\t"<<"R[1][2]"<<"\t";
		out<<"R[2][0]"<<"\t"<<"R[2][1]"<<"\t"<<"R[2][2]"<<"\t";
		out<<"origin[0]"<<"origin[1]"<<"origin[2]"<<endl;

		struct chain * chain_head;
		chain_head=read_pdb_to_chain(atom_head);
		struct chain * group_1;
		group_1=get_base_chain(chain_head,base_serial);

		struct base_purine_serial * bs_purine_group_1;
		struct base_pyrimidine_serial * bs_pyrimidine_group_1;

		if(group_1->base_name=='A' || group_1->base_name=='G' )
		{
			bs_purine_group_1=read_pdb2purine_base(atom_head,*group_1);
		}
		else
		{
			bs_pyrimidine_group_1=read_pdb2pyrimidine_base(atom_head,*group_1);
		}

        x=(rvec * )calloc(natoms,sizeof(x[0]));
        while(1)
       {
              read_return=read_xtc(xtc,natoms,&step,&time_temp,box,x,&p);
			  num_step++;

			if(step%100000==0)
			{
				cout<<"Reading frame : "<<step<<"\t time :"<<time_temp<<" ps"<<endl;
			}
             if(read_return!=0)
            {
                 break;
            }
			if(num_step%step_frame==0)
			{

				double ** base_matrix;
				if(group_1->base_name=='A' || group_1->base_name=='G' )
				{
					base_matrix=dmatrix(0,8,0,2);
					for(int i=0;i<natoms;i++)
					{
						if((i+1)==bs_purine_group_1->C2_serial)
						{
							base_matrix[6][0]=10*x[i][0];
							base_matrix[6][1]=10*x[i][1];
							base_matrix[6][2]=10*x[i][2];
						}
						if((i+1)==bs_purine_group_1->C4_serial)
						{
							base_matrix[8][0]=10*x[i][0];
							base_matrix[8][1]=10*x[i][1];
							base_matrix[8][2]=10*x[i][2];

						}
						if((i+1)==bs_purine_group_1->C5_serial)
						{
							base_matrix[3][0]=10*x[i][0];
							base_matrix[3][1]=10*x[i][1];
							base_matrix[3][2]=10*x[i][2];
						}
						if((i+1)==bs_purine_group_1->C6_serial)
						{
							base_matrix[4][0]=10*x[i][0];
							base_matrix[4][1]=10*x[i][1];
							base_matrix[4][2]=10*x[i][2];
						}
						if((i+1)==bs_purine_group_1->C8_serial)
						{
							base_matrix[1][0]=10*x[i][0];
							base_matrix[1][1]=10*x[i][1];
							base_matrix[1][2]=10*x[i][2];
						}
						if((i+1)==bs_purine_group_1->N1_serial)
						{
							base_matrix[5][0]=10*x[i][0];
							base_matrix[5][1]=10*x[i][1];
							base_matrix[5][2]=10*x[i][2];
						}
						if((i+1)==bs_purine_group_1->N3_serial)
						{
							base_matrix[7][0]=10*x[i][0];
							base_matrix[7][1]=10*x[i][1];
							base_matrix[7][2]=10*x[i][2];
						}
						if((i+1)==bs_purine_group_1->N7_serial)
						{
							base_matrix[2][0]=10*x[i][0];
							base_matrix[2][1]=10*x[i][1];
							base_matrix[2][2]=10*x[i][2];
						}
						if((i+1)==bs_purine_group_1->N9_serial)
						{
							base_matrix[0][0]=10*x[i][0];
							base_matrix[0][1]=10*x[i][1];
							base_matrix[0][2]=10*x[i][2];
						}
					}
				}
				else
				{
					base_matrix=dmatrix(0,5,0,2);
					for(int i=0;i<natoms;i++)
					{
						if((i+1)==bs_pyrimidine_group_1->C2_serial)
						{
							base_matrix[1][0]=10*x[i][0];
							base_matrix[1][1]=10*x[i][1];
							base_matrix[1][2]=10*x[i][2];
						}
						if((i+1)==bs_pyrimidine_group_1->C4_serial)
						{
							base_matrix[3][0]=10*x[i][0];
							base_matrix[3][1]=10*x[i][1];
							base_matrix[3][2]=10*x[i][2];
						}
						if((i+1)==bs_pyrimidine_group_1->C5_serial)
						{
							base_matrix[4][0]=10*x[i][0];
							base_matrix[4][1]=10*x[i][1];
							base_matrix[4][2]=10*x[i][2];
						}
						if((i+1)==bs_pyrimidine_group_1->C6_serial)
						{
							base_matrix[5][0]=10*x[i][0];
							base_matrix[5][1]=10*x[i][1];
							base_matrix[5][2]=10*x[i][2];
						}
						if((i+1)==bs_pyrimidine_group_1->N1_serial)
						{
							base_matrix[0][0]=10*x[i][0];
							base_matrix[0][1]=10*x[i][1];
							base_matrix[0][2]=10*x[i][2];
						}
						if((i+1)==bs_pyrimidine_group_1->N3_serial)
						{
							base_matrix[2][0]=10*x[i][0];
							base_matrix[2][1]=10*x[i][1];
							base_matrix[2][2]=10*x[i][2];
						}
					}
				}
					
				double ** rotation_matrix;
				rotation_matrix=dmatrix(0,2,0,2);
				Rotation_matrix(base_matrix,group_1->base_name,rotation_matrix);

				//it's the origin of this base/
				double * origin_vector;
				origin_vector=dvector(0,2);
				Origin_vector(base_matrix,rotation_matrix,group_1->base_name,origin_vector);

				out<<fixed<<showpoint;
				out<<time_temp<<"\t";
				for(int i=0;i<3;i++)
				{
					for(int j=0;j<3;j++)
					{
						out<<setprecision(4)<<rotation_matrix[i][j]<<"\t";
					}
				}
				for(int i=0;i<3;i++)
				{
					out<<setprecision(4)<<origin_vector[i]<<"\t";
				}
				out<<endl;

				free_dvector(origin_vector,0,2);
				free_dmatrix(rotation_matrix,0,2,0,2);
				if(group_1->base_name=='A' || group_1->base_name=='G' )
				{
					free_dmatrix(base_matrix,0,8,0,2);
				}
				else
				{
					free_dmatrix(base_matrix,0,5,0,2);
				}
			}
        }
        xdrfile_close(xtc);
		out.close();
}

void  read_trr2Rotation_matrix(char * filename,const char * out_file,int base_serial,struct atom * atom_head,int step_frame )
{
    int natoms,step;
    float time_temp;
    float lambda;
    matrix box;
    rvec *x,*v,*f;
    XDRFILE *xtc;
    xtc=xdrfile_open(filename,"r");
    int read_return=read_xtc_natoms(filename,&natoms);

	int num_step=0;

	ofstream out(out_file);
	out<<"#calculate the distence of  ion to the center of the two quartets in z-axis/"<<endl;
	out<<"#Time\t"<<"R[0][0]"<<"\t"<<"R[0][1]"<<"\t"<<"R[0][2]"<<"\t";
	out<<"R[1][0]"<<"\t"<<"R[1][1]"<<"\t"<<"R[1][2]"<<"\t";
	out<<"R[2][0]"<<"\t"<<"R[2][1]"<<"\t"<<"R[2][2]"<<"\t";
	out<<"origin[0]"<<"origin[1]"<<"origin[2]"<<endl;

	struct chain * chain_head;
	chain_head=read_pdb_to_chain(atom_head);
	struct chain * group_1;
	group_1=get_base_chain(chain_head,base_serial);

	struct base_purine_serial * bs_purine_group_1;
	struct base_pyrimidine_serial * bs_pyrimidine_group_1;

	if(group_1->base_name=='A' || group_1->base_name=='G' )
	{
		bs_purine_group_1=read_pdb2purine_base(atom_head,*group_1);
	}
	else
	{
		bs_pyrimidine_group_1=read_pdb2pyrimidine_base(atom_head,*group_1);
	}

    x=(rvec * )calloc(natoms,sizeof(x[0]));
    while(1)
   {
    	read_return=read_trr(xtc,natoms,&step,&time_temp,&lambda,box,x,v,f);
		  num_step++;

		if(step%100000==0)
		{
			cout<<"Reading frame : "<<step<<"\t time :"<<time_temp<<" ps"<<endl;
		}
         if(read_return!=0)
        {
             break;
        }
		if(num_step%step_frame==0)
		{

			double ** base_matrix;
			if(group_1->base_name=='A' || group_1->base_name=='G' )
			{
				base_matrix=dmatrix(0,8,0,2);
				for(int i=0;i<natoms;i++)
				{
					if((i+1)==bs_purine_group_1->C2_serial)
					{
						base_matrix[6][0]=10*x[i][0];
						base_matrix[6][1]=10*x[i][1];
						base_matrix[6][2]=10*x[i][2];
					}
					if((i+1)==bs_purine_group_1->C4_serial)
					{
						base_matrix[8][0]=10*x[i][0];
						base_matrix[8][1]=10*x[i][1];
						base_matrix[8][2]=10*x[i][2];

					}
					if((i+1)==bs_purine_group_1->C5_serial)
					{
						base_matrix[3][0]=10*x[i][0];
						base_matrix[3][1]=10*x[i][1];
						base_matrix[3][2]=10*x[i][2];
					}
					if((i+1)==bs_purine_group_1->C6_serial)
					{
						base_matrix[4][0]=10*x[i][0];
						base_matrix[4][1]=10*x[i][1];
						base_matrix[4][2]=10*x[i][2];
					}
					if((i+1)==bs_purine_group_1->C8_serial)
					{
						base_matrix[1][0]=10*x[i][0];
						base_matrix[1][1]=10*x[i][1];
						base_matrix[1][2]=10*x[i][2];
					}
					if((i+1)==bs_purine_group_1->N1_serial)
					{
						base_matrix[5][0]=10*x[i][0];
						base_matrix[5][1]=10*x[i][1];
						base_matrix[5][2]=10*x[i][2];
					}
					if((i+1)==bs_purine_group_1->N3_serial)
					{
						base_matrix[7][0]=10*x[i][0];
						base_matrix[7][1]=10*x[i][1];
						base_matrix[7][2]=10*x[i][2];
					}
					if((i+1)==bs_purine_group_1->N7_serial)
					{
						base_matrix[2][0]=10*x[i][0];
						base_matrix[2][1]=10*x[i][1];
						base_matrix[2][2]=10*x[i][2];
					}
					if((i+1)==bs_purine_group_1->N9_serial)
					{
						base_matrix[0][0]=10*x[i][0];
						base_matrix[0][1]=10*x[i][1];
						base_matrix[0][2]=10*x[i][2];
					}
				}
			}
			else
			{
				base_matrix=dmatrix(0,5,0,2);
				for(int i=0;i<natoms;i++)
				{
					if((i+1)==bs_pyrimidine_group_1->C2_serial)
					{
						base_matrix[1][0]=10*x[i][0];
						base_matrix[1][1]=10*x[i][1];
						base_matrix[1][2]=10*x[i][2];
					}
					if((i+1)==bs_pyrimidine_group_1->C4_serial)
					{
						base_matrix[3][0]=10*x[i][0];
						base_matrix[3][1]=10*x[i][1];
						base_matrix[3][2]=10*x[i][2];
					}
					if((i+1)==bs_pyrimidine_group_1->C5_serial)
					{
						base_matrix[4][0]=10*x[i][0];
						base_matrix[4][1]=10*x[i][1];
						base_matrix[4][2]=10*x[i][2];
					}
					if((i+1)==bs_pyrimidine_group_1->C6_serial)
					{
						base_matrix[5][0]=10*x[i][0];
						base_matrix[5][1]=10*x[i][1];
						base_matrix[5][2]=10*x[i][2];
					}
					if((i+1)==bs_pyrimidine_group_1->N1_serial)
					{
						base_matrix[0][0]=10*x[i][0];
						base_matrix[0][1]=10*x[i][1];
						base_matrix[0][2]=10*x[i][2];
					}
					if((i+1)==bs_pyrimidine_group_1->N3_serial)
					{
						base_matrix[2][0]=10*x[i][0];
						base_matrix[2][1]=10*x[i][1];
						base_matrix[2][2]=10*x[i][2];
					}
				}
			}

			double ** rotation_matrix;
			rotation_matrix=dmatrix(0,2,0,2);
			Rotation_matrix(base_matrix,group_1->base_name,rotation_matrix);

			//it's the origin of this base/
			double * origin_vector;
			origin_vector=dvector(0,2);
			Origin_vector(base_matrix,rotation_matrix,group_1->base_name,origin_vector);

			out<<fixed<<showpoint;
			out<<time_temp<<"\t";
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					out<<setprecision(4)<<rotation_matrix[i][j]<<"\t";
				}
			}
			for(int i=0;i<3;i++)
			{
				out<<setprecision(4)<<origin_vector[i]<<"\t";
			}
			out<<endl;

			free_dvector(origin_vector,0,2);
			free_dmatrix(rotation_matrix,0,2,0,2);
			if(group_1->base_name=='A' || group_1->base_name=='G' )
			{
				free_dmatrix(base_matrix,0,8,0,2);
			}
			else
			{
				free_dmatrix(base_matrix,0,5,0,2);
			}
		}
    }
    xdrfile_close(xtc);
	out.close();
}


void  Parallel_analysis(char * filename,char * out_file,vector<int> group_1_serial,vector<int> group_2_serial,struct atom * atom_head ,int step_frame)
{
	int length_1=group_1_serial.size();
	int length_2=group_2_serial.size();
	string outname;
	ofstream out(out_file);
	out<<"#calculate the angle and distance between two groups"<<endl;
	out<<"#Time\t dist \t angle"<<endl;
	char  i_s[20];
	for(int i=0;i<length_1;i++)
	{
		sprintf(i_s, "%d", i);
		string st(i_s);
		outname="group_1_";
		outname.append(st);
		const char * temp=outname.c_str();
		cout<<"Reading the base "<<i+1<<" in group 1."<<endl;
		cout<<"The result write in "<<outname<<endl;
		read_xtc2Rotation_matrix(filename,temp,group_1_serial.at(i),atom_head,step_frame);
	}
	for(int i=0;i<length_2;i++)
	{
		sprintf(i_s, "%d", i);
		string st(i_s);
		outname="group_2_";
		outname.append(st);
		const char * temp=outname.c_str();
		cout<<"Reading the base "<<i+1<<" in group 2."<<endl;
		cout<<"The result write in "<<outname<<endl;
		read_xtc2Rotation_matrix(filename,temp,group_2_serial.at(i),atom_head,step_frame);
	}
	double ** vector_group_1;
	double ** vector_group_2;
	vector_group_1=dmatrix(0,length_1-1,0,2);
	vector_group_2=dmatrix(0,length_2-1,0,2);


	vector<ifstream *> in_group_1;
	vector<ifstream *> in_group_2;


	for(int i=0;i<length_1;i++)
	{
		outname="group_1_";
		sprintf(i_s, "%d", i);
		string st(i_s);
		outname.append(st);
		const char * temp=outname.c_str();
		ifstream *ifp= new ifstream(temp);
		in_group_1.push_back(ifp);
	}
	for(int i=0;i<length_2;i++)
	{
		sprintf(i_s, "%d", i);
		outname="group_2_";
		string st(i_s);
		outname.append(st);
		const char * temp=outname.c_str();
		ifstream *ifp=new ifstream(temp);
		in_group_2.push_back(ifp);
	}

	vector<string> s_temp_1;
	vector<string> s_temp_2;
	for(int i=0;i<length_1;i++)
	{
		string st;
		getline(*in_group_1.at(i),st);
		s_temp_1.push_back(st);
	}

	for(int i=0;i<length_2;i++)
	{
		string st;
		getline(*in_group_2.at(i),st);
		s_temp_2.push_back(st);
	}


	while(!(*in_group_1.at(0)).fail())
	{
		float time_temp;
		double ** rotation_matrix_group_1;
		double ** rotation_matrix_group_2;

		double * orient_group_1;
		double * center_group_1;
		double * orient_group_2;
		double * center_group_2;

		double * orient_total;
		double * dist_vector;

		if(s_temp_1.at(0).find('#')>10)
		{
			orient_group_1=dvector(0,2);
			orient_group_2=dvector(0,2);
			center_group_1=dvector(0,2);
			center_group_2=dvector(0,2);

			orient_total=dvector(0,2);
			dist_vector=dvector(0,2);

			vector<string> temp_v;

			switch(length_1)
			{
			case 1:
				temp_v=Split_v(s_temp_1.at(0),'\t');
				time_temp=atof(temp_v.at(0).c_str());
				orient_group_1[0]=atof(temp_v.at(3).c_str());
				orient_group_1[1]=atof(temp_v.at(6).c_str());
				orient_group_1[2]=atof(temp_v.at(9).c_str());
				center_group_1[0]=atof(temp_v.at(10).c_str());
				center_group_1[1]=atof(temp_v.at(11).c_str());
				center_group_1[2]=atof(temp_v.at(12).c_str());
			break;
			case 2:
			case 4:
				rotation_matrix_group_1=dmatrix(0,length_1-1,0,2);
				for(int i=0;i<3;i++)
				{
					center_group_1[i]=0;
				}
				for(int i=0;i<length_1;i++)
				{
					temp_v.clear();
					temp_v=Split_v(s_temp_1.at(i),'\t');
					time_temp=atof(temp_v.at(0).c_str());
					rotation_matrix_group_1[i][0]=atof(temp_v.at(3).c_str());
					rotation_matrix_group_1[i][1]=atof(temp_v.at(6).c_str());
					rotation_matrix_group_1[i][2]=atof(temp_v.at(9).c_str());
					center_group_1[0]+=(atof(temp_v.at(10).c_str())/length_1);
					center_group_1[1]+=(atof(temp_v.at(11).c_str())/length_1);
					center_group_1[2]+=(atof(temp_v.at(12).c_str())/length_1);
				}
				rotate_n_vector(rotation_matrix_group_1,length_1,orient_group_1);
				free_dmatrix(rotation_matrix_group_1,0,length_1-1,0,2);
			break;
			default:
				cout<<""<<endl;
				exit(0);
			}

			switch(length_2)
			{
			case 1:
				temp_v.clear();
				temp_v=Split_v(s_temp_2.at(0),'\t');
				orient_group_2[0]=atof(temp_v.at(3).c_str());
				orient_group_2[1]=atof(temp_v.at(6).c_str());
				orient_group_2[2]=atof(temp_v.at(9).c_str());
				center_group_2[0]=atof(temp_v.at(10).c_str());
				center_group_2[1]=atof(temp_v.at(11).c_str());
				center_group_2[2]=atof(temp_v.at(12).c_str());
			break;
			case 2:
			case 4:

				rotation_matrix_group_2=dmatrix(0,length_2-1,0,2);
				for(int i=0;i<3;i++)
				{
					center_group_2[i]=0;
				}
				for(int i=0;i<length_2;i++)
				{
					temp_v.clear();
					temp_v=Split_v(s_temp_2.at(i),'\t');
					rotation_matrix_group_2[i][0]=atof(temp_v.at(3).c_str());
					rotation_matrix_group_2[i][1]=atof(temp_v.at(6).c_str());
					rotation_matrix_group_2[i][2]=atof(temp_v.at(9).c_str());
					center_group_2[0]+=(atof(temp_v.at(10).c_str())/length_2);
					center_group_2[1]+=(atof(temp_v.at(11).c_str())/length_2);
					center_group_2[2]+=(atof(temp_v.at(12).c_str())/length_2);
				}
				rotate_n_vector(rotation_matrix_group_2,length_2,orient_group_2);
				free_dmatrix(rotation_matrix_group_2,0,length_2-1,0,2);

			break;
			default:
				cout<<""<<endl;
				exit(0);
			}

			if(dot_product_vector(orient_group_1,orient_group_2,3)<0)
			{
				for(int i=0;i<3;i++)
				{
					orient_group_2[i]=-orient_group_2[i];
				}
			}

			rotate_2_vector(orient_group_1,orient_group_2,orient_total);

			for(int i=0;i<3;i++)
			{
				dist_vector[i]=center_group_2[i]-center_group_1[i];
			}

			double dist;  //the dist of two groups in the z-axis.
			double gamma; //the angle between the planes of two groups.
			dist=dot_product_vector(dist_vector,orient_total,3);
			dist=sqrt(dist*dist);
			gamma=dot_product_vector(orient_group_1,orient_group_2,3);  
			// the orient_group_1 and orient_group_2 are unit vectors 
			gamma=acos(gamma)/3.1416*180;

			out<<setprecision(5)<<time_temp<<setw(10)<<dist<<setw(10)<<gamma<<endl;
	//left for output
			free_dvector(orient_group_1,0,2);
			free_dvector(orient_group_2,0,2);
			free_dvector(center_group_1,0,2);
			free_dvector(center_group_2,0,2);
			free_dvector(orient_total,0,2);
			free_dvector(dist_vector,0,2);
		}

		s_temp_1.clear();
		s_temp_2.clear();

		for(int i=0;i<length_1;i++)
		{
			string st;
			getline(*in_group_1.at(i),st);
			s_temp_1.push_back(st);
		}
		for(int i=0;i<length_2;i++)
		{
			string st;
			getline(*in_group_2.at(i),st);
			s_temp_2.push_back(st);
		}
	}

	for(int i=0;i<length_1;i++)
	{
		(*in_group_1.at(i)).close();
		delete in_group_1.at(i);
	}
	for(int i=0;i<length_2;i++)
	{
		(*in_group_2.at(i)).close();
		delete in_group_2.at(i);
	}
	out.close();
	cout<<"Finished writting the result to "<<out_file<<endl;

}
