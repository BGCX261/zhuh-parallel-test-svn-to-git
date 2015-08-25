#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;

class Information
{
public:
	Information(char *file);
	Information(void);
	bool GetA();
	bool GetB();
	bool GetC();
	bool GetD();
	bool GetE();
	bool GetF();
	bool GetG();
	bool GetH();
	bool GetI();
	bool GetJ();
	bool GetK();
	string GetChain();
private:
	bool A_exist;
	bool B_exist;
	bool C_exist;
	bool D_exist;
	bool E_exist;
	bool F_exist;
	bool G_exist;
	bool H_exist;
	bool I_exist;
	bool J_exist;
	bool K_exist;
	string chain;
};
