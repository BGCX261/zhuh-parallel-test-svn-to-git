#ifndef READ_NDX_H
#define READ_NDX_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<string>  read_2_group(char * index_file);
vector<int>  read_2_group_n(char * index_file);
vector<int>  read_group_2_serial(char * index_file, string group_name);

#endif

