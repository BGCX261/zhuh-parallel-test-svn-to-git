#include "read_trr.h"


void  read_trr2structure(char * filename,char * out_file, int ion_position,vector<int> quartet_1_serial,vector<int> quartet_2_serial,struct atom * atom_head,int step_frame )
{
        int natoms,step;
        float time_temp;
        float lambda;
        matrix box;
        rvec *x,*v,*f;
        XDRFILE *xtc;
        xtc=xdrfile_open(filename,"r");
        int read_return=read_trr_natoms(filename,&natoms);
		
		int num_step=0;

		ofstream out(out_file);
		out<<"#calculate the distence of  ion to the center of the two quartets in z-axis/"<<endl;
		out<<"#Time\t"<<"dist2ions"<<"\t"<<"dist2quartets"<<endl;

		double * ion_coor;
		ion_coor=dvector(0,2);


		struct chain * chain_head;
		chain_head=read_pdb_to_chain(atom_head);
		struct chain * ch_q_1_G_1;
		struct chain * ch_q_1_G_2;
		struct chain * ch_q_1_G_3;
		struct chain * ch_q_1_G_4;
		struct chain * ch_q_2_G_1;
		struct chain * ch_q_2_G_2;
		struct chain * ch_q_2_G_3;
		struct chain * ch_q_2_G_4;
		ch_q_1_G_1=get_base_chain(chain_head,quartet_1_serial.at(0));
		ch_q_1_G_2=get_base_chain(chain_head,quartet_1_serial.at(1));
		ch_q_1_G_3=get_base_chain(chain_head,quartet_1_serial.at(2));
		ch_q_1_G_4=get_base_chain(chain_head,quartet_1_serial.at(3));
		ch_q_2_G_1=get_base_chain(chain_head,quartet_2_serial.at(0));
		ch_q_2_G_2=get_base_chain(chain_head,quartet_2_serial.at(1));
		ch_q_2_G_3=get_base_chain(chain_head,quartet_2_serial.at(2));
		ch_q_2_G_4=get_base_chain(chain_head,quartet_2_serial.at(3));

		struct base_purine_serial * bs_q_1_G_1;
		struct base_purine_serial * bs_q_1_G_2;
		struct base_purine_serial * bs_q_1_G_3;
		struct base_purine_serial * bs_q_1_G_4;
		struct base_purine_serial * bs_q_2_G_1;
		struct base_purine_serial * bs_q_2_G_2;
		struct base_purine_serial * bs_q_2_G_3;
		struct base_purine_serial * bs_q_2_G_4;
//得到G碱基的原子的序号。
		bs_q_1_G_1=read_pdb2purine_base(atom_head,*ch_q_1_G_1);
		bs_q_1_G_2=read_pdb2purine_base(atom_head,*ch_q_1_G_2);
		bs_q_1_G_3=read_pdb2purine_base(atom_head,*ch_q_1_G_3);
		bs_q_1_G_4=read_pdb2purine_base(atom_head,*ch_q_1_G_4);
		bs_q_2_G_1=read_pdb2purine_base(atom_head,*ch_q_2_G_1);
		bs_q_2_G_2=read_pdb2purine_base(atom_head,*ch_q_2_G_2);
		bs_q_2_G_3=read_pdb2purine_base(atom_head,*ch_q_2_G_3);
		bs_q_2_G_4=read_pdb2purine_base(atom_head,*ch_q_2_G_4);



        x=( rvec * )calloc(natoms,sizeof(x[0]));
        while(1)
       {

              read_return=read_trr(xtc,natoms,&step,&time_temp,&lambda,box,x,v,f);
			  num_step++;

			if(step%10000==0)
			{
				cout<<"Reading frame : "<<step<<"\t time :"<<time_temp<<endl;
			}
             if(read_return!=0)
            {
                 break;
             }
			if(num_step%step_frame==0)
			{
					double ** q_1_G_1_matrix;
					double ** q_1_G_2_matrix;
					double ** q_1_G_3_matrix;
					double ** q_1_G_4_matrix;
					double ** q_2_G_1_matrix;
					double ** q_2_G_2_matrix;
					double ** q_2_G_3_matrix;
					double ** q_2_G_4_matrix;

					 q_1_G_1_matrix=dmatrix(0,8,0,2);
					 q_1_G_2_matrix=dmatrix(0,8,0,2);
					 q_1_G_3_matrix=dmatrix(0,8,0,2);
					 q_1_G_4_matrix=dmatrix(0,8,0,2);
					 q_2_G_1_matrix=dmatrix(0,8,0,2);
					 q_2_G_2_matrix=dmatrix(0,8,0,2);
					 q_2_G_3_matrix=dmatrix(0,8,0,2);
					 q_2_G_4_matrix=dmatrix(0,8,0,2);

					for(int i=0;i<natoms;i++)
			     {
       //    cout<<step<<"\t"<<time_temp<<"\t"<<natom<<"\t"<<x[natom][0]<<"\t"<<x[natom][1]<<"\t"<<x[natom][2]<<endl;
						if((i+1)==ion_position)
						{
							ion_coor[0]=10*x[i][0];
							ion_coor[1]=10*x[i][1];
							ion_coor[2]=10*x[i][2];
	//						cout<<"get ions coordination"<<endl;
						}

					 //q_1_G_1
						 if((i+1)==bs_q_1_G_1->C2_serial)
						{
							q_1_G_1_matrix[6][0]=10*x[i][0];
							q_1_G_1_matrix[6][1]=10*x[i][1];
							q_1_G_1_matrix[6][2]=10*x[i][2];
							
						}
						if((i+1)==bs_q_1_G_1->C4_serial)
						{
							q_1_G_1_matrix[8][0]=10*x[i][0];
							q_1_G_1_matrix[8][1]=10*x[i][1];
							q_1_G_1_matrix[8][2]=10*x[i][2];	

						}
						if((i+1)==bs_q_1_G_1->C5_serial)
						{
							q_1_G_1_matrix[3][0]=10*x[i][0];
							q_1_G_1_matrix[3][1]=10*x[i][1];
							q_1_G_1_matrix[3][2]=10*x[i][2];
						}
						if((i+1)==bs_q_1_G_1->C6_serial)
						{
							q_1_G_1_matrix[4][0]=10*x[i][0];
							q_1_G_1_matrix[4][1]=10*x[i][1];
							q_1_G_1_matrix[4][2]=10*x[i][2];
						}
						if((i+1)==bs_q_1_G_1->C8_serial)
						{
							q_1_G_1_matrix[1][0]=10*x[i][0];
							q_1_G_1_matrix[1][1]=10*x[i][1];
							q_1_G_1_matrix[1][2]=10*x[i][2];
						}
						if((i+1)==bs_q_1_G_1->N1_serial)
						{
							q_1_G_1_matrix[5][0]=10*x[i][0];
							q_1_G_1_matrix[5][1]=10*x[i][1];
							q_1_G_1_matrix[5][2]=10*x[i][2];
						}
						if((i+1)==bs_q_1_G_1->N3_serial)
						{
							q_1_G_1_matrix[7][0]=10*x[i][0];
							q_1_G_1_matrix[7][1]=10*x[i][1];
							q_1_G_1_matrix[7][2]=10*x[i][2];
						}
						if((i+1)==bs_q_1_G_1->N7_serial)
						{
							q_1_G_1_matrix[2][0]=10*x[i][0];
							q_1_G_1_matrix[2][1]=10*x[i][1];
							q_1_G_1_matrix[2][2]=10*x[i][2];	
						}
						if((i+1)==bs_q_1_G_1->N9_serial)
						{
							q_1_G_1_matrix[0][0]=10*x[i][0];
							q_1_G_1_matrix[0][1]=10*x[i][1];
							q_1_G_1_matrix[0][2]=10*x[i][2];
						}
// q_1_G_2
						if((i+1)==bs_q_1_G_2->C2_serial)
						{
							q_1_G_2_matrix[6][0]=10*x[i][0];
							q_1_G_2_matrix[6][1]=10*x[i][1];
							q_1_G_2_matrix[6][2]=10*x[i][2];
						}
						if((i+1)==bs_q_1_G_2->C4_serial)
						{
							q_1_G_2_matrix[8][0]=10*x[i][0];
							q_1_G_2_matrix[8][1]=10*x[i][1];
							q_1_G_2_matrix[8][2]=10*x[i][2];						
						}
						if((i+1)==bs_q_1_G_2->C5_serial)
						{
							q_1_G_2_matrix[3][0]=10*x[i][0];
							q_1_G_2_matrix[3][1]=10*x[i][1];
							q_1_G_2_matrix[3][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_2->C6_serial)
						{
							q_1_G_2_matrix[4][0]=10*x[i][0];
							q_1_G_2_matrix[4][1]=10*x[i][1];
							q_1_G_2_matrix[4][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_2->C8_serial)
						{
							q_1_G_2_matrix[1][0]=10*x[i][0];
							q_1_G_2_matrix[1][1]=10*x[i][1];
							q_1_G_2_matrix[1][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_2->N1_serial)
						{
							q_1_G_2_matrix[5][0]=10*x[i][0];
							q_1_G_2_matrix[5][1]=10*x[i][1];
							q_1_G_2_matrix[5][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_2->N3_serial)
						{
							q_1_G_2_matrix[7][0]=10*x[i][0];
							q_1_G_2_matrix[7][1]=10*x[i][1];
							q_1_G_2_matrix[7][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_2->N7_serial)
						{
							q_1_G_2_matrix[2][0]=10*x[i][0];
							q_1_G_2_matrix[2][1]=10*x[i][1];
							q_1_G_2_matrix[2][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_2->N9_serial)
						{
							q_1_G_2_matrix[0][0]=10*x[i][0];
							q_1_G_2_matrix[0][1]=10*x[i][1];
							q_1_G_2_matrix[0][2]=10*x[i][2];		
						}
//q_1_G_3
						if((i+1)==bs_q_1_G_3->C2_serial)
						{
							q_1_G_3_matrix[6][0]=10*x[i][0];
							q_1_G_3_matrix[6][1]=10*x[i][1];
							q_1_G_3_matrix[6][2]=10*x[i][2];
						}
						if((i+1)==bs_q_1_G_3->C4_serial)
						{
							q_1_G_3_matrix[8][0]=10*x[i][0];
							q_1_G_3_matrix[8][1]=10*x[i][1];
							q_1_G_3_matrix[8][2]=10*x[i][2];						
						}
						if((i+1)==bs_q_1_G_3->C5_serial)
						{
							q_1_G_3_matrix[3][0]=10*x[i][0];
							q_1_G_3_matrix[3][1]=10*x[i][1];
							q_1_G_3_matrix[3][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_3->C6_serial)
						{
							q_1_G_3_matrix[4][0]=10*x[i][0];
							q_1_G_3_matrix[4][1]=10*x[i][1];
							q_1_G_3_matrix[4][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_3->C8_serial)
						{
							q_1_G_3_matrix[1][0]=10*x[i][0];
							q_1_G_3_matrix[1][1]=10*x[i][1];
							q_1_G_3_matrix[1][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_3->N1_serial)
						{
							q_1_G_3_matrix[5][0]=10*x[i][0];
							q_1_G_3_matrix[5][1]=10*x[i][1];
							q_1_G_3_matrix[5][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_3->N3_serial)
						{
							q_1_G_3_matrix[7][0]=10*x[i][0];
							q_1_G_3_matrix[7][1]=10*x[i][1];
							q_1_G_3_matrix[7][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_3->N7_serial)
						{
							q_1_G_3_matrix[2][0]=10*x[i][0];
							q_1_G_3_matrix[2][1]=10*x[i][1];
							q_1_G_3_matrix[2][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_3->N9_serial)
						{
							q_1_G_3_matrix[0][0]=10*x[i][0];
							q_1_G_3_matrix[0][1]=10*x[i][1];
							q_1_G_3_matrix[0][2]=10*x[i][2];		
						}
//q_1_G_4
						if((i+1)==bs_q_1_G_4->C2_serial)
						{
							q_1_G_4_matrix[6][0]=10*x[i][0];
							q_1_G_4_matrix[6][1]=10*x[i][1];
							q_1_G_4_matrix[6][2]=10*x[i][2];
						}
						if((i+1)==bs_q_1_G_4->C4_serial)
						{
							q_1_G_4_matrix[8][0]=10*x[i][0];
							q_1_G_4_matrix[8][1]=10*x[i][1];
							q_1_G_4_matrix[8][2]=10*x[i][2];						
						}
						if((i+1)==bs_q_1_G_4->C5_serial)
						{
							q_1_G_4_matrix[3][0]=10*x[i][0];
							q_1_G_4_matrix[3][1]=10*x[i][1];
							q_1_G_4_matrix[3][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_4->C6_serial)
						{
							q_1_G_4_matrix[4][0]=10*x[i][0];
							q_1_G_4_matrix[4][1]=10*x[i][1];
							q_1_G_4_matrix[4][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_4->C8_serial)
						{
							q_1_G_4_matrix[1][0]=10*x[i][0];
							q_1_G_4_matrix[1][1]=10*x[i][1];
							q_1_G_4_matrix[1][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_4->N1_serial)
						{
							q_1_G_4_matrix[5][0]=10*x[i][0];
							q_1_G_4_matrix[5][1]=10*x[i][1];
							q_1_G_4_matrix[5][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_4->N3_serial)
						{
							q_1_G_4_matrix[7][0]=10*x[i][0];
							q_1_G_4_matrix[7][1]=10*x[i][1];
							q_1_G_4_matrix[7][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_4->N7_serial)
						{
							q_1_G_4_matrix[2][0]=10*x[i][0];
							q_1_G_4_matrix[2][1]=10*x[i][1];
							q_1_G_4_matrix[2][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_1_G_4->N9_serial)
						{
							q_1_G_4_matrix[0][0]=10*x[i][0];
							q_1_G_4_matrix[0][1]=10*x[i][1];
							q_1_G_4_matrix[0][2]=10*x[i][2];		
						}
//q_2_G_1
						if((i+1)==bs_q_2_G_1->C2_serial)
						{
							q_2_G_1_matrix[6][0]=10*x[i][0];
							q_2_G_1_matrix[6][1]=10*x[i][1];
							q_2_G_1_matrix[6][2]=10*x[i][2];
						}
						if((i+1)==bs_q_2_G_1->C4_serial)
						{
							q_2_G_1_matrix[8][0]=10*x[i][0];
							q_2_G_1_matrix[8][1]=10*x[i][1];
							q_2_G_1_matrix[8][2]=10*x[i][2];						
						}
						if((i+1)==bs_q_2_G_1->C5_serial)
						{
							q_2_G_1_matrix[3][0]=10*x[i][0];
							q_2_G_1_matrix[3][1]=10*x[i][1];
							q_2_G_1_matrix[3][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_1->C6_serial)
						{
							q_2_G_1_matrix[4][0]=10*x[i][0];
							q_2_G_1_matrix[4][1]=10*x[i][1];
							q_2_G_1_matrix[4][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_1->C8_serial)
						{
							q_2_G_1_matrix[1][0]=10*x[i][0];
							q_2_G_1_matrix[1][1]=10*x[i][1];
							q_2_G_1_matrix[1][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_1->N1_serial)
						{
							q_2_G_1_matrix[5][0]=10*x[i][0];
							q_2_G_1_matrix[5][1]=10*x[i][1];
							q_2_G_1_matrix[5][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_1->N3_serial)
						{
							q_2_G_1_matrix[7][0]=10*x[i][0];
							q_2_G_1_matrix[7][1]=10*x[i][1];
							q_2_G_1_matrix[7][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_1->N7_serial)
						{
							q_2_G_1_matrix[2][0]=10*x[i][0];
							q_2_G_1_matrix[2][1]=10*x[i][1];
							q_2_G_1_matrix[2][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_1->N9_serial)
						{
							q_2_G_1_matrix[0][0]=10*x[i][0];
							q_2_G_1_matrix[0][1]=10*x[i][1];
							q_2_G_1_matrix[0][2]=10*x[i][2];		
						}
//q_2_G_2
						if((i+1)==bs_q_2_G_2->C2_serial)
						{
							q_2_G_2_matrix[6][0]=10*x[i][0];
							q_2_G_2_matrix[6][1]=10*x[i][1];
							q_2_G_2_matrix[6][2]=10*x[i][2];
						}
						if((i+1)==bs_q_2_G_2->C4_serial)
						{
							q_2_G_2_matrix[8][0]=10*x[i][0];
							q_2_G_2_matrix[8][1]=10*x[i][1];
							q_2_G_2_matrix[8][2]=10*x[i][2];						
						}
						if((i+1)==bs_q_2_G_2->C5_serial)
						{
							q_2_G_2_matrix[3][0]=10*x[i][0];
							q_2_G_2_matrix[3][1]=10*x[i][1];
							q_2_G_2_matrix[3][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_2->C6_serial)
						{
							q_2_G_2_matrix[4][0]=10*x[i][0];
							q_2_G_2_matrix[4][1]=10*x[i][1];
							q_2_G_2_matrix[4][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_2->C8_serial)
						{
							q_2_G_2_matrix[1][0]=10*x[i][0];
							q_2_G_2_matrix[1][1]=10*x[i][1];
							q_2_G_2_matrix[1][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_2->N1_serial)
						{
							q_2_G_2_matrix[5][0]=10*x[i][0];
							q_2_G_2_matrix[5][1]=10*x[i][1];
							q_2_G_2_matrix[5][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_2->N3_serial)
						{
							q_2_G_2_matrix[7][0]=10*x[i][0];
							q_2_G_2_matrix[7][1]=10*x[i][1];
							q_2_G_2_matrix[7][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_2->N7_serial)
						{
							q_2_G_2_matrix[2][0]=10*x[i][0];
							q_2_G_2_matrix[2][1]=10*x[i][1];
							q_2_G_2_matrix[2][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_2->N9_serial)
						{
							q_2_G_2_matrix[0][0]=10*x[i][0];
							q_2_G_2_matrix[0][1]=10*x[i][1];
							q_2_G_2_matrix[0][2]=10*x[i][2];		
						}
//q_2_G_3
						if((i+1)==bs_q_2_G_3->C2_serial)
						{
							q_2_G_3_matrix[6][0]=10*x[i][0];
							q_2_G_3_matrix[6][1]=10*x[i][1];
							q_2_G_3_matrix[6][2]=10*x[i][2];
						}
						if((i+1)==bs_q_2_G_3->C4_serial)
						{
							q_2_G_3_matrix[8][0]=10*x[i][0];
							q_2_G_3_matrix[8][1]=10*x[i][1];
							q_2_G_3_matrix[8][2]=10*x[i][2];						
						}
						if((i+1)==bs_q_2_G_3->C5_serial)
						{
							q_2_G_3_matrix[3][0]=10*x[i][0];
							q_2_G_3_matrix[3][1]=10*x[i][1];
							q_2_G_3_matrix[3][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_3->C6_serial)
						{
							q_2_G_3_matrix[4][0]=10*x[i][0];
							q_2_G_3_matrix[4][1]=10*x[i][1];
							q_2_G_3_matrix[4][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_3->C8_serial)
						{
							q_2_G_3_matrix[1][0]=10*x[i][0];
							q_2_G_3_matrix[1][1]=10*x[i][1];
							q_2_G_3_matrix[1][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_3->N1_serial)
						{
							q_2_G_3_matrix[5][0]=10*x[i][0];
							q_2_G_3_matrix[5][1]=10*x[i][1];
							q_2_G_3_matrix[5][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_3->N3_serial)
						{
							q_2_G_3_matrix[7][0]=10*x[i][0];
							q_2_G_3_matrix[7][1]=10*x[i][1];
							q_2_G_3_matrix[7][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_3->N7_serial)
						{
							q_2_G_3_matrix[2][0]=10*x[i][0];
							q_2_G_3_matrix[2][1]=10*x[i][1];
							q_2_G_3_matrix[2][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_3->N9_serial)
						{
							q_2_G_3_matrix[0][0]=10*x[i][0];
							q_2_G_3_matrix[0][1]=10*x[i][1];
							q_2_G_3_matrix[0][2]=10*x[i][2];		
						}
//q_2_G_4
						if((i+1)==bs_q_2_G_4->C2_serial)
						{
							q_2_G_4_matrix[6][0]=10*x[i][0];
							q_2_G_4_matrix[6][1]=10*x[i][1];
							q_2_G_4_matrix[6][2]=10*x[i][2];
						}
						if((i+1)==bs_q_2_G_4->C4_serial)
						{
							q_2_G_4_matrix[8][0]=10*x[i][0];
							q_2_G_4_matrix[8][1]=10*x[i][1];
							q_2_G_4_matrix[8][2]=10*x[i][2];						
						}
						if((i+1)==bs_q_2_G_4->C5_serial)
						{
							q_2_G_4_matrix[3][0]=10*x[i][0];
							q_2_G_4_matrix[3][1]=10*x[i][1];
							q_2_G_4_matrix[3][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_4->C6_serial)
						{
							q_2_G_4_matrix[4][0]=10*x[i][0];
							q_2_G_4_matrix[4][1]=10*x[i][1];
							q_2_G_4_matrix[4][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_4->C8_serial)
						{
							q_2_G_4_matrix[1][0]=10*x[i][0];
							q_2_G_4_matrix[1][1]=10*x[i][1];
							q_2_G_4_matrix[1][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_4->N1_serial)
						{
							q_2_G_4_matrix[5][0]=10*x[i][0];
							q_2_G_4_matrix[5][1]=10*x[i][1];
							q_2_G_4_matrix[5][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_4->N3_serial)
						{
							q_2_G_4_matrix[7][0]=10*x[i][0];
							q_2_G_4_matrix[7][1]=10*x[i][1];
							q_2_G_4_matrix[7][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_4->N7_serial)
						{
							q_2_G_4_matrix[2][0]=10*x[i][0];
							q_2_G_4_matrix[2][1]=10*x[i][1];
							q_2_G_4_matrix[2][2]=10*x[i][2];		
						}
						if((i+1)==bs_q_2_G_4->N9_serial)
						{
							q_2_G_4_matrix[0][0]=10*x[i][0];
							q_2_G_4_matrix[0][1]=10*x[i][1];
							q_2_G_4_matrix[0][2]=10*x[i][2];		
						}
					}
					
					double ** q_1_G_1_rotation_matrix;
					double ** q_1_G_2_rotation_matrix;
					double ** q_1_G_3_rotation_matrix;
					double ** q_1_G_4_rotation_matrix;
					double ** q_2_G_1_rotation_matrix;
					double ** q_2_G_2_rotation_matrix;
					double ** q_2_G_3_rotation_matrix;
					double ** q_2_G_4_rotation_matrix;

					q_1_G_1_rotation_matrix=dmatrix(0,2,0,2);
					q_1_G_2_rotation_matrix=dmatrix(0,2,0,2);
					q_1_G_3_rotation_matrix=dmatrix(0,2,0,2);
					q_1_G_4_rotation_matrix=dmatrix(0,2,0,2);
					q_2_G_1_rotation_matrix=dmatrix(0,2,0,2);
					q_2_G_2_rotation_matrix=dmatrix(0,2,0,2);
					q_2_G_3_rotation_matrix=dmatrix(0,2,0,2);
					q_2_G_4_rotation_matrix=dmatrix(0,2,0,2);

					Rotation_matrix(q_1_G_1_matrix,'G',q_1_G_1_rotation_matrix);
					Rotation_matrix(q_1_G_2_matrix,'G',q_1_G_2_rotation_matrix);
					Rotation_matrix(q_1_G_3_matrix,'G',q_1_G_3_rotation_matrix);
					Rotation_matrix(q_1_G_4_matrix,'G',q_1_G_4_rotation_matrix);
					Rotation_matrix(q_2_G_1_matrix,'G',q_2_G_1_rotation_matrix);
					Rotation_matrix(q_2_G_2_matrix,'G',q_2_G_2_rotation_matrix);
					Rotation_matrix(q_2_G_3_matrix,'G',q_2_G_3_rotation_matrix);
					Rotation_matrix(q_2_G_4_matrix,'G',q_2_G_4_rotation_matrix);

					//以q_1_G_1为基准，校正z-axis的方向。
					double * vector_q_1_G_1;
					double * vector_q_1_G_2;
					double * vector_q_1_G_3;
					double * vector_q_1_G_4;
					double * vector_q_2_G_1;
					double * vector_q_2_G_2;
					double * vector_q_2_G_3;
					double * vector_q_2_G_4;

					vector_q_1_G_1=dvector(0,2);
					vector_q_1_G_2=dvector(0,2);
					vector_q_1_G_3=dvector(0,2);
					vector_q_1_G_4=dvector(0,2);
					vector_q_2_G_1=dvector(0,2);
					vector_q_2_G_2=dvector(0,2);
					vector_q_2_G_3=dvector(0,2);
					vector_q_2_G_4=dvector(0,2);

					for(int i=0;i<3;i++)
					{
						vector_q_1_G_1[i]=q_1_G_1_rotation_matrix[i][2];
						vector_q_1_G_2[i]=q_1_G_2_rotation_matrix[i][2];
						vector_q_1_G_3[i]=q_1_G_3_rotation_matrix[i][2];
						vector_q_1_G_4[i]=q_1_G_4_rotation_matrix[i][2];
						vector_q_2_G_1[i]=q_2_G_1_rotation_matrix[i][2];
						vector_q_2_G_2[i]=q_2_G_2_rotation_matrix[i][2];
						vector_q_2_G_3[i]=q_2_G_3_rotation_matrix[i][2];
						vector_q_2_G_4[i]=q_2_G_4_rotation_matrix[i][2];
					}

					if(dot_product_vector(vector_q_1_G_1,vector_q_1_G_2,3)<0)
					{
						for(int i=1;i<3;i++)
						{
							for(int j=0;j<3;j++)
							{
								q_1_G_2_rotation_matrix[j][i]= - q_1_G_2_rotation_matrix[j][i];
							}
						}
					}
					if(dot_product_vector(vector_q_1_G_1,vector_q_1_G_3,3)<0)
					{
						for(int i=1;i<3;i++)
						{
							for(int j=0;j<3;j++)
							{
								q_1_G_3_rotation_matrix[j][i]= - q_1_G_3_rotation_matrix[j][i];
							}
						}
					}
					if(dot_product_vector(vector_q_1_G_1,vector_q_1_G_4,3)<0)
					{
						for(int i=1;i<3;i++)
						{
							for(int j=0;j<3;j++)
							{
								q_1_G_4_rotation_matrix[j][i]= - q_1_G_4_rotation_matrix[j][i];
							}
						}
					}
					if(dot_product_vector(vector_q_1_G_1,vector_q_2_G_1,3)<0)
					{
						for(int i=1;i<3;i++)
						{
							for(int j=0;j<3;j++)
							{
								q_2_G_1_rotation_matrix[j][i]= - q_2_G_1_rotation_matrix[j][i];
							}
						}
					}
					if(dot_product_vector(vector_q_1_G_1,vector_q_2_G_2,3)<0)
					{
						for(int i=1;i<3;i++)
						{
							for(int j=0;j<3;j++)
							{
								q_2_G_2_rotation_matrix[j][i]= - q_2_G_2_rotation_matrix[j][i];
							}
						}
					}
					if(dot_product_vector(vector_q_1_G_1,vector_q_2_G_3,3)<0)
					{
						for(int i=1;i<3;i++)
						{
							for(int j=0;j<3;j++)
							{
								q_2_G_3_rotation_matrix[j][i]= - q_2_G_3_rotation_matrix[j][i];
							}
						}
					}
					if(dot_product_vector(vector_q_1_G_1,vector_q_2_G_4,3)<0)
					{
						for(int i=1;i<3;i++)
						{
							for(int j=0;j<3;j++)
							{
								q_2_G_4_rotation_matrix[j][i]= - q_2_G_4_rotation_matrix[j][i];
							}
						}
					}


					free_dvector(vector_q_1_G_1,0,2);
					free_dvector(vector_q_1_G_2,0,2);
					free_dvector(vector_q_1_G_3,0,2);
					free_dvector(vector_q_1_G_4,0,2);
					free_dvector(vector_q_2_G_1,0,2);
					free_dvector(vector_q_2_G_2,0,2);
					free_dvector(vector_q_2_G_3,0,2);
					free_dvector(vector_q_2_G_4,0,2);


					//get the origin position of 8 guanine.
					double * origin_vector_q_1_G_1;
					double * origin_vector_q_1_G_2;
					double * origin_vector_q_1_G_3;
					double * origin_vector_q_1_G_4;
					double * origin_vector_q_2_G_1;
					double * origin_vector_q_2_G_2;
					double * origin_vector_q_2_G_3;
					double * origin_vector_q_2_G_4;

					origin_vector_q_1_G_1=dvector(0,2);
					origin_vector_q_1_G_2=dvector(0,2);
					origin_vector_q_1_G_3=dvector(0,2);
					origin_vector_q_1_G_4=dvector(0,2);
					origin_vector_q_2_G_1=dvector(0,2);
					origin_vector_q_2_G_2=dvector(0,2);
					origin_vector_q_2_G_3=dvector(0,2);
					origin_vector_q_2_G_4=dvector(0,2);


					origin_vector(q_1_G_1_matrix,q_1_G_1_rotation_matrix,'G',origin_vector_q_1_G_1);
					origin_vector(q_1_G_2_matrix,q_1_G_2_rotation_matrix,'G',origin_vector_q_1_G_2);
					origin_vector(q_1_G_3_matrix,q_1_G_3_rotation_matrix,'G',origin_vector_q_1_G_3);
					origin_vector(q_1_G_4_matrix,q_1_G_4_rotation_matrix,'G',origin_vector_q_1_G_4);
					origin_vector(q_2_G_1_matrix,q_2_G_1_rotation_matrix,'G',origin_vector_q_2_G_1);
					origin_vector(q_2_G_2_matrix,q_2_G_2_rotation_matrix,'G',origin_vector_q_2_G_2);
					origin_vector(q_2_G_3_matrix,q_2_G_3_rotation_matrix,'G',origin_vector_q_2_G_3);
					origin_vector(q_2_G_4_matrix,q_2_G_4_rotation_matrix,'G',origin_vector_q_2_G_4);
				
					//get the z-axis
					vector_q_1_G_1=dvector(0,2);
					vector_q_1_G_2=dvector(0,2);
					vector_q_1_G_3=dvector(0,2);
					vector_q_1_G_4=dvector(0,2);
					vector_q_2_G_1=dvector(0,2);
					vector_q_2_G_2=dvector(0,2);
					vector_q_2_G_3=dvector(0,2);
					vector_q_2_G_4=dvector(0,2);

					for(int i=0;i<3;i++)
					{
						vector_q_1_G_1[i]=q_1_G_1_rotation_matrix[i][2];
						vector_q_1_G_2[i]=q_1_G_2_rotation_matrix[i][2];
						vector_q_1_G_3[i]=q_1_G_3_rotation_matrix[i][2];
						vector_q_1_G_4[i]=q_1_G_4_rotation_matrix[i][2];
						vector_q_2_G_1[i]=q_2_G_1_rotation_matrix[i][2];
						vector_q_2_G_2[i]=q_2_G_2_rotation_matrix[i][2];
						vector_q_2_G_3[i]=q_2_G_3_rotation_matrix[i][2];
						vector_q_2_G_4[i]=q_2_G_4_rotation_matrix[i][2];

		//				cout<<vector_q_1_G_1[i]<<endl;  //for test 
		//				cout<<vector_q_1_G_2[i]<<endl;  //for test 
		//				cout<<vector_q_1_G_3[i]<<endl;  //for test 
		//				cout<<vector_q_1_G_4[i]<<endl;  //for test 
		//				cout<<vector_q_2_G_1[i]<<endl;  //for test 
		//				cout<<vector_q_2_G_2[i]<<endl;  //for test 
			//			cout<<vector_q_2_G_3[i]<<endl;  //for test 
		//				cout<<vector_q_2_G_4[i]<<endl;  //for test 
					}

					double * vector_q_1_G_1_2;
					double * vector_q_1_G_3_4;
					double * vector_q_1_G_1_2_3_4;
					double * vector_q_2_G_1_2;
					double * vector_q_2_G_3_4;
					double * vector_q_2_G_1_2_3_4;
					double * vector_orientation;

					 vector_q_1_G_1_2=dvector(0,2);
					 vector_q_1_G_3_4=dvector(0,2);
					 vector_q_1_G_1_2_3_4=dvector(0,2);
					 vector_q_2_G_1_2=dvector(0,2);
					 vector_q_2_G_3_4=dvector(0,2);
					 vector_q_2_G_1_2_3_4=dvector(0,2);
					 vector_orientation=dvector(0,2);

					rotate_2_vector(vector_q_1_G_1,vector_q_1_G_2, vector_q_1_G_1_2);
					// for test
			//		for(int i=0;i<3;i++)
		//			{
		//				cout<<vector_q_1_G_1_2[i]<<endl;
		//			}
					//
					rotate_2_vector(vector_q_1_G_3,vector_q_1_G_4,vector_q_1_G_3_4);

					rotate_2_vector(vector_q_2_G_1,vector_q_2_G_2,vector_q_2_G_1_2);
					rotate_2_vector(vector_q_2_G_3,vector_q_2_G_4,vector_q_2_G_3_4);

					rotate_2_vector(vector_q_1_G_1_2,vector_q_1_G_3_4,vector_q_1_G_1_2_3_4);
					rotate_2_vector(vector_q_2_G_1_2,vector_q_2_G_3_4,vector_q_2_G_1_2_3_4);

					rotate_2_vector(vector_q_1_G_1_2_3_4,vector_q_2_G_1_2_3_4,vector_orientation);
					//for test
					/*
					for(int i=0;i<3;i++)
					{
						cout<<vector_orientation[i]<<endl;
					}
					*/
					//

					//get the center position.
					double * center_position_vector;
					double * center_1;
					double * center_2;
					double * vector_2_ion;
					double * vector_1_2;
					center_position_vector=dvector(0,2);
					vector_2_ion=dvector(0,2);
					center_1=dvector(0,2);
					center_2=dvector(0,2);
					vector_1_2=dvector(0,2);

					for(int i=0;i<3;i++)
					{
						center_position_vector[i]=(origin_vector_q_1_G_1[i]+origin_vector_q_1_G_2[i]+origin_vector_q_1_G_3[i]+origin_vector_q_1_G_4[i]+origin_vector_q_2_G_1[i]+origin_vector_q_2_G_2[i]+origin_vector_q_2_G_3[i]+origin_vector_q_2_G_4[i])/8;
						center_1[i]=(origin_vector_q_1_G_1[i]+origin_vector_q_1_G_2[i]+origin_vector_q_1_G_3[i]+origin_vector_q_1_G_4[i])/4;
						center_2[i]=(origin_vector_q_2_G_1[i]+origin_vector_q_2_G_2[i]+origin_vector_q_2_G_3[i]+origin_vector_q_2_G_4[i])/4;
						vector_2_ion[i]=ion_coor[i]-center_position_vector[i];

						vector_1_2[i]=center_1[i]-center_2[i];
					}
					
					double length=0;
					double dist_z=0;
					double dist=0;
	
					length=dot_product_vector(vector_orientation,vector_2_ion,3); 
					dist_z=dot_product_vector(vector_orientation,vector_1_2,3);
					dist=sqrt(dot_product_vector(vector_1_2,vector_1_2,3));								
					 
					//
					out<<fixed<<showpoint;
					out<<time_temp<<"\t"<<setprecision(4)<<fabs(length)<<"\t"<<setprecision(4)<<dist<<"\t"<<setprecision(4)<<fabs(dist_z)<<endl;		


					free_dmatrix(q_1_G_1_matrix,0,2,0,8);
					free_dmatrix(q_1_G_2_matrix,0,2,0,8);
					free_dmatrix(q_1_G_3_matrix,0,2,0,8);
					free_dmatrix(q_1_G_4_matrix,0,2,0,8);
					free_dmatrix(q_2_G_1_matrix,0,2,0,8);
					free_dmatrix(q_2_G_2_matrix,0,2,0,8);
					free_dmatrix(q_2_G_3_matrix,0,2,0,8);
					free_dmatrix(q_2_G_4_matrix,0,2,0,8);

					free_dmatrix(q_1_G_1_rotation_matrix,0,2,0,2);
					free_dmatrix(q_1_G_2_rotation_matrix,0,2,0,2);
					free_dmatrix(q_1_G_3_rotation_matrix,0,2,0,2);
					free_dmatrix(q_1_G_4_rotation_matrix,0,2,0,2);
					free_dmatrix(q_2_G_1_rotation_matrix,0,2,0,2);
					free_dmatrix(q_2_G_2_rotation_matrix,0,2,0,2);
					free_dmatrix(q_2_G_3_rotation_matrix,0,2,0,2);
					free_dmatrix(q_2_G_4_rotation_matrix,0,2,0,2);

					free_dvector(vector_q_1_G_1,0,2);
					free_dvector(vector_q_1_G_2,0,2);
					free_dvector(vector_q_1_G_3,0,2);
					free_dvector(vector_q_1_G_4,0,2);
					free_dvector(vector_q_2_G_1,0,2);
					free_dvector(vector_q_2_G_2,0,2);
					free_dvector(vector_q_2_G_3,0,2);
					free_dvector(vector_q_2_G_4,0,2);

					free_dvector(origin_vector_q_1_G_1,0,2);
					free_dvector(origin_vector_q_1_G_2,0,2);
					free_dvector(origin_vector_q_1_G_3,0,2);
					free_dvector(origin_vector_q_1_G_4,0,2);
					free_dvector(origin_vector_q_2_G_1,0,2);
					free_dvector(origin_vector_q_2_G_2,0,2);
					free_dvector(origin_vector_q_2_G_3,0,2);
					free_dvector(origin_vector_q_2_G_4,0,2);

					 free_dvector(vector_q_1_G_1_2,0,2);
					 free_dvector(vector_q_1_G_3_4,0,2);
					 free_dvector(vector_q_1_G_1_2_3_4,0,2);
					 free_dvector(vector_q_2_G_1_2,0,2);
					 free_dvector(vector_q_2_G_3_4,0,2);
					 free_dvector( vector_q_2_G_1_2_3_4,0,2);
				     free_dvector( vector_orientation,0,2);
			}
        }
        xdrfile_close(xtc);
		out.close();
}

