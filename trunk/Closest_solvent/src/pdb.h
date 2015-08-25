#ifndef PDB_H
#define PDB_H

#include <fstream>
#include <stdlib.h>
#include <string.h>

#include "string_operate.h"

#include "atom.h"

// struct chain
// {
// 	char  base_name;
// 	char chain_indicator;
// 	int reside_sequence_number;
// 	struct chain * next;
// };

class PDB : public Atom
{
public:
	std::string character;
	char alternate_location_indicator;
	char chain_identifier;
	char code_for_insertions_of_residues;
	double occupancy;
	double temperature_factor;
	std::string segment_identifier;
	std::string element_symbol;
	std::string charge;
};


struct chain * read_pdb_to_chain(struct atom * head);
struct atom *  read_pdb_to_atom(char * pdb_file_name);

void print_chain(struct chain * temp_chain);
char get_base(struct chain * chain_head,int serial_number);

struct chain *  get_base_chain(struct chain * chain_head,int serial_number);
#endif


