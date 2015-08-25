#include "read_xtc.h"


void  read_xtc2structure(char * filename,char * out_file,char * choose,int base_1_serial,int base_2_serial,struct atom * atom_head,int step_frame )
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
		if(strcmp(choose,"bs")==0)
		{
			out<<"#Time\t";
			out<<"shift\t";
			out<<"slide\t";
			out<< "rise\t";
			out<<"tilt\t";
			out<<"roll\t";
			out<<"twist"<<endl;
		}
		if(strcmp(choose,"bp")==0)
		{
			out<<"#Time\t";
			out<<"shear\t";
			out<<"stretch\t";
			out<<"stagger\t";
			out<<"buckle\t";
			out<<"propeller\t";
			out<<"opening"<<endl;
		}
	
		struct chain * chain_head;
		chain_head=read_pdb_to_chain(atom_head);
		struct chain * ch_b_1;
		struct chain * ch_b_2;

		ch_b_1=get_base_chain(chain_head,base_1_serial);
		ch_b_2=get_base_chain(chain_head,base_2_serial);


		struct base_purine_serial * bs_1;
		struct base_purine_serial * bs_2;

//得到G碱基的原子的序号。
		bs_1=read_pdb2purine_base(atom_head,*ch_b_1);
		bs_2=read_pdb2purine_base(atom_head,*ch_b_2);


        x=(rvec * )calloc(natoms,sizeof(x[0]));
        while(1)
       {

              read_return=read_xtc(xtc,natoms,&step,&time_temp,box,x,&p);
			  num_step++;

			if(step%1000==0)
			{
				cout<<"Reading frame : "<<step<<"\t time :"<<time_temp<<endl;
			}
             if(read_return!=0)
            {
                 break;
             }
			if(num_step%step_frame==0)
			{
					double ** q_1_matrix;
					double ** q_2_matrix;

					 q_1_matrix=dmatrix(0,8,0,2);
					 q_2_matrix=dmatrix(0,8,0,2);


					for(int i=0;i<natoms;i++)
			     {
       //    cout<<step<<"\t"<<time_temp<<"\t"<<natom<<"\t"<<x[natom][0]<<"\t"<<x[natom][1]<<"\t"<<x[natom][2]<<endl;


					 //q_1_G_1
						 if((i+1)==bs_1->C2_serial)
						{
							q_1_matrix[6][0]=10*x[i][0];
							q_1_matrix[6][1]=10*x[i][1];
							q_1_matrix[6][2]=10*x[i][2];
							
						}
						if((i+1)==bs_1->C4_serial)
						{
							q_1_matrix[8][0]=10*x[i][0];
							q_1_matrix[8][1]=10*x[i][1];
							q_1_matrix[8][2]=10*x[i][2];	

						}
						if((i+1)==bs_1->C5_serial)
						{
							q_1_matrix[3][0]=10*x[i][0];
							q_1_matrix[3][1]=10*x[i][1];
							q_1_matrix[3][2]=10*x[i][2];
						}
						if((i+1)==bs_1->C6_serial)
						{
							q_1_matrix[4][0]=10*x[i][0];
							q_1_matrix[4][1]=10*x[i][1];
							q_1_matrix[4][2]=10*x[i][2];
						}
						if((i+1)==bs_1->C8_serial)
						{
							q_1_matrix[1][0]=10*x[i][0];
							q_1_matrix[1][1]=10*x[i][1];
							q_1_matrix[1][2]=10*x[i][2];
						}
						if((i+1)==bs_1->N1_serial)
						{
							q_1_matrix[5][0]=10*x[i][0];
							q_1_matrix[5][1]=10*x[i][1];
							q_1_matrix[5][2]=10*x[i][2];
						}
						if((i+1)==bs_1->N3_serial)
						{
							q_1_matrix[7][0]=10*x[i][0];
							q_1_matrix[7][1]=10*x[i][1];
							q_1_matrix[7][2]=10*x[i][2];
						}
						if((i+1)==bs_1->N7_serial)
						{
							q_1_matrix[2][0]=10*x[i][0];
							q_1_matrix[2][1]=10*x[i][1];
							q_1_matrix[2][2]=10*x[i][2];	
						}
						if((i+1)==bs_1->N9_serial)
						{
							q_1_matrix[0][0]=10*x[i][0];
							q_1_matrix[0][1]=10*x[i][1];
							q_1_matrix[0][2]=10*x[i][2];
						}
// q_1_G_2
						if((i+1)==bs_2->C2_serial)
						{
							q_2_matrix[6][0]=10*x[i][0];
							q_2_matrix[6][1]=10*x[i][1];
							q_2_matrix[6][2]=10*x[i][2];
						}
						if((i+1)==bs_2->C4_serial)
						{
							q_2_matrix[8][0]=10*x[i][0];
							q_2_matrix[8][1]=10*x[i][1];
							q_2_matrix[8][2]=10*x[i][2];						
						}
						if((i+1)==bs_2->C5_serial)
						{
							q_2_matrix[3][0]=10*x[i][0];
							q_2_matrix[3][1]=10*x[i][1];
							q_2_matrix[3][2]=10*x[i][2];		
						}
						if((i+1)==bs_2->C6_serial)
						{
							q_2_matrix[4][0]=10*x[i][0];
							q_2_matrix[4][1]=10*x[i][1];
							q_2_matrix[4][2]=10*x[i][2];		
						}
						if((i+1)==bs_2->C8_serial)
						{
							q_2_matrix[1][0]=10*x[i][0];
							q_2_matrix[1][1]=10*x[i][1];
							q_2_matrix[1][2]=10*x[i][2];		
						}
						if((i+1)==bs_2->N1_serial)
						{
							q_2_matrix[5][0]=10*x[i][0];
							q_2_matrix[5][1]=10*x[i][1];
							q_2_matrix[5][2]=10*x[i][2];		
						}
						if((i+1)==bs_2->N3_serial)
						{
							q_2_matrix[7][0]=10*x[i][0];
							q_2_matrix[7][1]=10*x[i][1];
							q_2_matrix[7][2]=10*x[i][2];		
						}
						if((i+1)==bs_2->N7_serial)
						{
							q_2_matrix[2][0]=10*x[i][0];
							q_2_matrix[2][1]=10*x[i][1];
							q_2_matrix[2][2]=10*x[i][2];		
						}
						if((i+1)==bs_2->N9_serial)
						{
							q_2_matrix[0][0]=10*x[i][0];
							q_2_matrix[0][1]=10*x[i][1];
							q_2_matrix[0][2]=10*x[i][2];		
						}

					}
					
			double ** rotation_matrix_1;
			double ** rotation_matrix_2;
			double * o_vector_1;
			double * o_vector_2;
			
			rotation_matrix_1=dmatrix(0,2,0,2);
			rotation_matrix_2=dmatrix(0,2,0,2);
			o_vector_1=dvector(0,2);
			o_vector_2=dvector(0,2);

			Rotation_matrix(q_1_matrix,'G',rotation_matrix_1);
			Rotation_matrix(q_2_matrix,'G',rotation_matrix_2);

			origin_vector(q_1_matrix,rotation_matrix_1,'G',o_vector_1);
			origin_vector(q_2_matrix,rotation_matrix_2,'G',o_vector_2);
			
			
			if(strcmp(choose,"bp")==0)
			{
				double shear=0;
				double stretch=0;
				double stagger=0;
				double buckle=0;
				double propeller=0;
				double opening=0;
				base_pair_parameters(rotation_matrix_1,rotation_matrix_2,o_vector_1,o_vector_2,shear,stretch,stagger,buckle, propeller,opening);
				out<<fixed<<showpoint;
				out<<time_temp<<"\t";
				out<<setprecision(2)<<shear<<"\t";
				out<<setprecision(2)<<stretch<<"\t";
				out<<setprecision(2)<<stagger<<"\t";
				out<<setprecision(2)<<buckle<<"\t";
				out<<setprecision(2)<<propeller<<"\t";
				out<<setprecision(2)<<opening<<endl;
			}

			if(strcmp(choose,"bs")==0)
			{
				double   shift=0;
				double   slide=0;
				double   rise=0;
				double   tilt=0;
				double   roll=0;
				double   twist=0;
				base_step_paramaters(rotation_matrix_1,rotation_matrix_2,o_vector_1,o_vector_2,shift,slide, rise,tilt,roll,twist);

				out<<time_temp<<"\t";
				out<<fixed<<showpoint;
				out<<setprecision(2)<< shift<<"\t";
				out<<setprecision(2)<< slide<<"\t";
				out<<setprecision(2)<< rise<<"\t";
				out<<setprecision(2)<< tilt<<"\t";
				out<<setprecision(2)<< roll<<"\t";
				out<<setprecision(2)<< twist<<endl;
			}

			}
        }
        xdrfile_close(xtc);
		out.close();
}


