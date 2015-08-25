#include "read_pdb.h"



vector<double>  read_pdb_2_atom(char * pdb_file,vector<int > vi)
{
	vector<double> vd;
	string s;
	int num=0;
	ifstream in(pdb_file);
	getline(in,s);
	while(!in.fail())
	{
		while(s.find("ATOM")<20&&!in.fail())
			 {			  
				 if(num<vi.size()&&atoi(Split(s.substr(6,5),' ',0).c_str())==vi.at(num))
						{
							vd.push_back(atof(Split(s.substr(60,6),' ',0).c_str()));
							num++;
						}
						getline(in,s);
			}
			getline(in,s);
	}
	in.close();
	return vd;
}	

struct atom *  whirl_atom(struct atom * atom_shift, double oren_x, double oren_y, double oren_z)
 {
	 struct atom * atom_whirl;
	 struct atom * atom_temp;
	 atom_temp=atom_shift;
	 struct atom * atom_p1;
	 struct atom * atom_p2;
	 int n=0;
	 int s=0;
	atom_whirl=NULL;

	double cent_x=0;
	double cent_y=0;
	double cent_z=0;

	 while(atom_temp!=NULL)
	 {
		 cent_x+=atom_temp->x_coordinate;
		 cent_y+=atom_temp->y_coordinate;
		 cent_z+=atom_temp->z_coordinate;
		 atom_temp=atom_temp->next;
		 n++;
	}
	 cent_x=cent_x/n;
	 cent_y=cent_y/n;
	 cent_z=cent_z/n;

	 while(atom_shift!=NULL)
	 {
		atom_p1=(struct atom *)malloc(sizeof(struct atom));

		double res_x=0;
		double res_y=0;
		double res_z=0;


		atom_p1->alternate_location_indicator=atom_shift->alternate_location_indicator;
		strcpy(atom_p1->atom_name,atom_shift->atom_name);
		atom_p1->atom_serial_number=atom_shift->atom_serial_number;
		atom_p1->chain_identifier=atom_shift->chain_identifier;
		strcpy(atom_p1->character,atom_shift->character);
		strcpy(atom_p1->charge,atom_shift->charge);
		atom_p1->code_for_insertions_of_residues=atom_shift->code_for_insertions_of_residues;
		strcpy(atom_p1->element_symbol,atom_shift->element_symbol);
		atom_p1->occupancy=atom_shift->occupancy;
		strcpy(atom_p1->reside_name,atom_shift->reside_name);
		atom_p1->reside_sequence_number=atom_shift->reside_sequence_number;
		strcpy(atom_p1->segment_identifier,atom_shift->segment_identifier);
		atom_p1->temperature_factor=atom_shift->temperature_factor;

		rotate(atom_shift->x_coordinate-cent_x,atom_shift->y_coordinate-cent_y,atom_shift->z_coordinate-cent_z,oren_x,oren_y,oren_z,res_x,  res_y,  res_z);

		atom_p1->x_coordinate=res_x+cent_x;
		atom_p1->y_coordinate=res_y+cent_y;
		atom_p1->z_coordinate=res_z+cent_z;

		atom_shift=atom_shift->next;

			s++;
			if(s==1)
			{
				atom_whirl=atom_p1;
			}
			else
			{
				atom_p2->next=atom_p1;
			}
			atom_p2=atom_p1;
	}
	 atom_p2->next=NULL;
	 return atom_whirl;
 }

struct atom *  shift_atom(struct atom * atom_st, double shift_x, double shift_y, double shift_z)
 {
	 struct atom * atom_struct;
	 atom_struct=atom_st;
	 struct atom * atom_shift;
	 struct atom * atom_p1;
	 struct atom * atom_p2;
	 int n=0;
	atom_shift=NULL;
	 while(atom_struct!=NULL)
	 {
		atom_p1=(struct atom *)malloc(sizeof(struct atom));
		atom_p1->alternate_location_indicator=atom_struct->alternate_location_indicator;
		strcpy(atom_p1->atom_name,atom_struct->atom_name);
		atom_p1->atom_serial_number=atom_struct->atom_serial_number;
		atom_p1->chain_identifier=atom_struct->chain_identifier;
		strcpy(atom_p1->character,atom_struct->character);
		strcpy(atom_p1->charge,atom_struct->charge);
		atom_p1->code_for_insertions_of_residues=atom_struct->code_for_insertions_of_residues;
		strcpy(atom_p1->element_symbol,atom_struct->element_symbol);
		atom_p1->occupancy=atom_struct->occupancy;
		strcpy(atom_p1->reside_name,atom_struct->reside_name);
		atom_p1->reside_sequence_number=atom_struct->reside_sequence_number;
		strcpy(atom_p1->segment_identifier,atom_struct->segment_identifier);
		atom_p1->temperature_factor=atom_struct->temperature_factor;
			
		atom_p1->x_coordinate=atom_struct->x_coordinate+shift_x;
		atom_p1->y_coordinate=atom_struct->y_coordinate+shift_y;
		atom_p1->z_coordinate=atom_struct->z_coordinate+shift_z;

		atom_struct=atom_struct->next;

			n++;
			if(n==1)
			{
				atom_shift=atom_p1;
			}
			else
			{
				atom_p2->next=atom_p1;
			}
			atom_p2=atom_p1;
	}
	 atom_p2->next=NULL;
	 return atom_shift;

 }

void write_pdb(struct atom * atom_write, char * file_name)
{
	ofstream out(file_name);
	while(atom_write!=NULL)
	{
		if(atom_write->character!=NULL)
		{
			if(string(atom_write->character).size()==4)
			{
				out<<setiosflags(ios::left)<<string(atom_write->character)<<"  ";
			}
			else
			{
				out<<setiosflags(ios::left)<<string(atom_write->character);
			}
		}
		else
		{
			out<<"      ";
		}
		if(atom_write->atom_serial_number!=NULL)
		{
			out<<setiosflags(ios::right)<<setw(5)<<atom_write->atom_serial_number;
		//	cout<<setiosflags(ios::right)<<setw(5)<<atom_write->atom_serial_number;
		}
		else
		{
			out<<"     ";
		}
		if(atom_write->atom_name!=NULL)
		{
			if(string(atom_write->atom_name).size()>2)
			{
				out<<setiosflags(ios::left)<<setw(5)<<string(atom_write->atom_name);
			}
			if(string(atom_write->atom_name).size()==2)
			{
				out<<setiosflags(ios::left)<<setw(4)<<string(atom_write->atom_name)<<" ";
			}
			if(string(atom_write->atom_name).size()==1)
			{
				out<<setiosflags(ios::left)<<setw(3)<<string(atom_write->atom_name)<<"  ";
			}
		//	cout<<setiosflags(ios::left)<<setw(4)<<string(atom_write->atom_name);
		}
		else
		{
			out<<"    ";
		}
		if(atom_write->chain_identifier!=NULL)
		{
			out<<setw(1)<<atom_write->alternate_location_indicator;
		//	cout<<setw(1)<<atom_write->alternate_location_indicator;
		}
		else
		{
			out<<" ";
		}
		if(atom_write->reside_name!=NULL)
		{
			out<<setiosflags(ios::right)<<setw(3)<<string(atom_write->reside_name);
		//	cout<<setiosflags(ios::right)<<setw(3)<<string(atom_write->reside_name);
		}
		else
		{
			out<<"   ";
		}
		if(atom_write->chain_identifier!=NULL)
		{
			out<<setw(2)<<atom_write->chain_identifier;
	//		cout<<setw(2)<<atom_write->chain_identifier;
		}
		else
		{
			out<<" ";
		}
		if(atom_write->reside_sequence_number!=NULL)
		{
			out<<setiosflags(ios::right)<<setw(4)<<atom_write->reside_sequence_number;
		}
		else
		{
			out<<"    ";
		}
		if(atom_write->code_for_insertions_of_residues!=NULL)
		{
			out<<setw(1)<<atom_write->code_for_insertions_of_residues;
		}
		else
		{
			out<<" ";
		}
		if(atom_write->x_coordinate!=NULL)
		{
			out<<fixed<<showpoint;
			out<<setiosflags(ios::right)<<setw(11)<<setprecision(3)<<atom_write->x_coordinate;
		}
		else
		{
			out<<"        ";
		}
		if(atom_write->y_coordinate!=NULL)
		{
			out<<setiosflags(ios::right)<<setw(8)<<setprecision(3)<<atom_write->y_coordinate;
		}
		else
		{
			out<<"        ";
		}
		if(atom_write->z_coordinate!=NULL)
		{
			out<<setiosflags(ios::right)<<setw(8)<<setprecision(3)<<atom_write->z_coordinate;
		}
		else
		{
			out<<"        ";
		}
		if(atom_write->occupancy!=NULL)
		{
			out<<setiosflags(ios::right)<<setw(6)<<setprecision(2)<<atom_write->occupancy;
		}
		else
		{
			out<<"      ";
		}
		if(atom_write->temperature_factor!=NULL)
		{
			out<<setiosflags(ios::right)<<setw(6)<<setprecision(2)<<atom_write->temperature_factor;
		}
		else
		{
			out<<"      ";
		}
		if(atom_write->segment_identifier!=NULL)
		{
			out<<setiosflags(ios::left)<<setw(11)<<string(atom_write->segment_identifier);
		}
		else
		{
			out<<"    ";
		}
		if(atom_write->element_symbol!=NULL)
		{
			out<<setiosflags(ios::right)<<setw(2)<<string(atom_write->element_symbol);
		}
		else
		{
			out<<"  ";
		}
		if(atom_write->charge!=NULL)
		{
			out<<setiosflags(ios::right)<<setw(2)<<string(atom_write->charge)<<endl;
		}
		else
		{
			out<<"  "<<endl;;
		}
		atom_write=atom_write->next;
	}
	out.close();
	cout<<"finish write pdb file "<<file_name<<endl;

	
}
