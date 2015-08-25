#include "atom.h"

std::string Atom::atom_2_gro()
{
	std::string line;
	line="%5d%5s%5s%5d%8.3f%8.3f%8.3f%8.4f%8.4f%8.4f", %this.residue_serial, %this.resdidue_name,\
	%this.atom_name,%this.atom_number,%this.coor_x,%this.coor_y,%this.coor_z ;
}