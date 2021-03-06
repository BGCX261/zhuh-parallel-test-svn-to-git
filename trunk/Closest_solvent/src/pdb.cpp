#include "pdb.h"

struct atom *  read_pdb_to_atom(char * pdb_file_name)
{
	struct atom * head;
	struct atom * p1,*p2;
	int n=0;
	head=NULL;
	string s;
	ifstream infile(pdb_file_name);
	while(!infile.fail())
	{
		getline(infile,s);
		if(s.find("ATOM")<100||s.find("HETATM")<100)
		{
			p1=(struct atom *) malloc(sizeof(struct atom));

			strcpy(p1->character,Split(s.substr(0,6),' ',0).c_str());
			p1->atom_serial_number=atoi(Split(s.substr(6,5),' ',0).c_str());
			strcpy(p1->atom_name,Split(s.substr(12,4),' ',0).c_str());
			p1->alternate_location_indicator=s.at(16);
			strcpy(p1->reside_name,Split(s.substr(17,3),' ',0).c_str());
			p1->chain_identifier=s.at(21);
			p1->reside_sequence_number=atoi(Split(s.substr(22,4),' ',0).c_str());
			p1->code_for_insertions_of_residues=s.at(26);
			p1->x_coordinate=atof(Split(s.substr(30,8),' ',0).c_str());
			p1->y_coordinate=atof(Split(s.substr(38,8),' ',0).c_str());
			p1->z_coordinate=atof(Split(s.substr(46,8),' ',0).c_str());
			if(s.size()>59)
			{
				p1->occupancy=atof(Split(s.substr(54,6),' ',0).c_str());
			}
			else
			{
				p1->occupancy=NULL;
			}
			if(s.size()>65)
			{
				p1->temperature_factor=atof(Split(s.substr(60,6),' ',0).c_str());
			}
			else
			{
				p1->temperature_factor=NULL;
			}
			if(s.size()>75)
			{
				strcpy(p1->segment_identifier,Split(s.substr(72,4),' ',0).c_str());
			}
			else
			{
				p1->segment_identifier[0]=NULL;
			}
			if(s.size()>77)
			{
				strcpy(p1->element_symbol,Split(s.substr(76,2),' ',0).c_str());
			}
			else
			{
				p1->element_symbol[0]=NULL;
			}
			if(s.size()>79)
			{
				strcpy(p1->charge,Split(s.substr(78,2),' ',0).c_str());
			}
			else
			{
				p1->charge[0]=NULL;
			}

		    n++;
			if(n==1)
			{head=p1;}
			else
			{p2->next=p1;}
			p2=p1;
		}

	//	getline(infile,s);
	}
	infile.close();
	p2->next=NULL;
	return head;
}

// struct chain * read_pdb_to_chain(struct atom * ahead)
// {
// 	struct atom * p1;
// 	p1=ahead;
// 	struct chain * head;
// 	struct chain * cp1, * cp2;
// 	int n=0;
// 	while(p1!=NULL)
// 	{
// 		cp1=(struct chain * )malloc(sizeof(struct chain)  );

// 		if(p1->reside_sequence_number>n&&(string(p1->reside_name).find('A')<10||string(p1->reside_name).find('C')<10||string(p1->reside_name).find('T')<10||string(p1->reside_name).find('G')<10||string(p1->reside_name).find('U')<10))
// 		{
// 			if(string(p1->reside_name).find('A')<10)
// 			{
// 				cp1->base_name='A'; //
// 				cp1->chain_indicator=p1->chain_identifier;
// 				cp1->reside_sequence_number=p1->reside_sequence_number;
// 				n++;
// 			}
// 			if(string(p1->reside_name).find('T')<10)
// 			{
// 				cp1->base_name='T'; //
// 				cp1->chain_indicator=p1->chain_identifier;
// 				cp1->reside_sequence_number=p1->reside_sequence_number;
// 				n++;
// 			}
// 			if(string(p1->reside_name).find('C')<10)
// 			{
// 				cp1->base_name='C'; //
// 				cp1->chain_indicator=p1->chain_identifier;
// 				cp1->reside_sequence_number=p1->reside_sequence_number;
// 				n++;
// 			}
// 			if(string(p1->reside_name).find('G')<10)
// 			{
// 				cp1->base_name='G'; //
// 				cp1->chain_indicator=p1->chain_identifier;
// 				cp1->reside_sequence_number=p1->reside_sequence_number;
// 				n++;
// 			}
// 			if(string(p1->reside_name).find('U')<10)
// 			{
// 				cp1->base_name='U'; //
// 				cp1->chain_indicator=p1->chain_identifier;
// 				cp1->reside_sequence_number=p1->reside_sequence_number;
// 				n++;
// 			}

// 			if(n==1)
// 			{head=cp1;}
// 			else
// 			{cp2->next=cp1;}
// 			cp2=cp1;
// 		}
// 		p1=p1->next;
// 	}
// 		cp2->next=NULL;
// 		return head;
// }




	void print_chain(struct chain * chain_head)
	{
		struct chain * temp_chain;
		temp_chain=chain_head;
		while(temp_chain!=NULL)
		{
			cout<<temp_chain->base_name<<"\t";
			cout<<temp_chain->reside_sequence_number<<"\t";
			cout<<temp_chain->chain_indicator<<endl;
			temp_chain=temp_chain->next;
		}
	}

	char get_base(struct chain * chain_head,int serial_number)
	{
		struct chain * temp_chain;
		temp_chain=chain_head;
		char base;
		while(temp_chain!=NULL)
		{
			if(temp_chain->reside_sequence_number==serial_number)
			{
				base=temp_chain->base_name;
				break;
			}
			temp_chain=temp_chain->next;
		}

		return base;
	}

	struct chain *  get_base_chain(struct chain * chain_head,int serial_number)
	{
		struct chain * temp_chain;
		temp_chain=chain_head;
		struct chain * base;
		base=(struct chain *)malloc(sizeof(struct chain));
		while(temp_chain!=NULL)
		{
			if(temp_chain->reside_sequence_number==serial_number)
			{
				base->base_name=temp_chain->base_name;
				base->chain_indicator=temp_chain->chain_indicator;
				base->reside_sequence_number=temp_chain->reside_sequence_number;
				break;
			}
			temp_chain=temp_chain->next;
		}

		return base;
	}

