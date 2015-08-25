#ifndef PDB_H
#define PDB_H

#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string_operate.h"

struct chain
{
	char  base_name;
	char chain_indicator;
	int reside_sequence_number;
	struct chain * next;
};

struct  atom
{
	char character[10];
	int atom_serial_number;
	char atom_name[20];
	char alternate_location_indicator;
	char reside_name[10];
	char chain_identifier;
	int reside_sequence_number;
	char code_for_insertions_of_residues;
	double x_coordinate;
	double y_coordinate;
	double z_coordinate;
	double occupancy;
	double temperature_factor;
	char segment_identifier[10];
	char element_symbol[10];
	char charge[10];
	struct atom * next;
};
struct base_purine_coordinate
{
	char base_name;
	double N9_x_coordinate;
	double N9_y_coordinate;
	double N9_z_coordinate;
	double C8_x_coordinate;
	double C8_y_coordinate;
	double C8_z_coordinate;
	double N7_x_coordinate;
	double N7_y_coordinate;
	double N7_z_coordinate;
	double C5_x_coordinate;
	double C5_y_coordinate;
	double C5_z_coordinate;
	double C6_x_coordinate;
	double C6_y_coordinate;
	double C6_z_coordinate;
	double N1_x_coordinate;
	double N1_y_coordinate;
	double N1_z_coordinate;
	double C2_x_coordinate;
	double C2_y_coordinate;
	double C2_z_coordinate;
	double N3_x_coordinate;
	double N3_y_coordinate;
	double N3_z_coordinate;
	double C4_x_coordinate;
	double C4_y_coordinate;
	double C4_z_coordinate;
	struct base_purine_coordinate * next;
};    //��¼���ʼ��������Ϣ

struct base_pyrimidine_coordinate
{
	char base_name;
	double C5_x_coordinate;
	double C5_y_coordinate;
	double C5_z_coordinate;
	double C6_x_coordinate;
	double C6_y_coordinate;
	double C6_z_coordinate;
	double N1_x_coordinate;
	double N1_y_coordinate;
	double N1_z_coordinate;
	double C2_x_coordinate;
	double C2_y_coordinate;
	double C2_z_coordinate;
	double N3_x_coordinate;
	double N3_y_coordinate;
	double N3_z_coordinate;
	double C4_x_coordinate;
	double C4_y_coordinate;
	double C4_z_coordinate;
	struct base_pyrimidine_coordinate * next;
};   //��¼��़��������Ϣ


struct base_purine_serial
{
	char base_name;
	char chain_identifier;
	int segment_sequence;
	int N9_serial;
	int C8_serial;
	int N7_serial;
	int C5_serial;
	int C6_serial;
	int N1_serial;
	int C2_serial;
	int N3_serial;
	int C4_serial;
	struct base_purine_serial * next;
};

struct base_pyrimidine_serial
{
	char base_name;
	char chain_identifier;
	int segment_sequence;
	int C5_serial;
	int C6_serial;
	int N1_serial;
	int C2_serial;
	int N3_serial;
	int C4_serial;
	struct base_pyrimidine_serial * next;
};

struct chain * read_pdb_to_chain(struct atom * head);
struct atom *  read_pdb_to_atom(char * pdb_file_name);
struct base_purine_serial  * read_pdb2purine_base(struct atom * head,struct chain a_chain);
struct base_pyrimidine_serial * read_pdb2pyrimidine_base(struct atom * head,struct chain a_chain);
void print_chain(struct chain * temp_chain);
char get_base(struct chain * chain_head,int serial_number);

struct chain *  get_base_chain(struct chain * chain_head,int serial_number);
#endif

