#include <iostream>

using namespace std;

class Atom 
{
public:
 	std::string atom_name;
	int atom_serial;
	std::string reside_name;
	int reside_serial;
	double coor_x;
	double coor_y;
	double coor_z;
	std::string atom_2_gro();
	std::string atom_2_pdb();
};
