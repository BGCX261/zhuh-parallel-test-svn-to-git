#include "Information.h"

Information::Information(void)
{}

Information::Information(char *file)
{
	ifstream infile;
	string s;
	infile.open(file);
	while(!infile.fail())
	{
		getline(infile,s);
		if(s.find("Strand")<100&&s.find("has")<100&&s.find("bases")<100)
		{
			int m=s.find(":");
			string temp=s.substr(m+2);
			chain+=temp+"\n";
		}
		if(s.find("|A|"))
		{
			A_exist=true;
		}
		if(s.find("|B|"))
		{
			B_exist=true;
		}
		if(s.find("|C|"))
		{
			C_exist=true;
		}
		if(s.find("|D|"))
		{
			D_exist=true;
		}
		if(s.find("|E|"))
		{
			E_exist=true;
		}
		if(s.find("|F|"))
		{
			F_exist=true;
		}
		if(s.find("|G|"))
		{
			G_exist=true;
		}
		if(s.find("|H|"))
		{
			H_exist=true;
		}
		if(s.find("|I|"))
		{
			I_exist=true;
		}
		if(s.find("|J|"))
		{
			J_exist=true;
		}
		if(s.find("|K|"))
		{
			K_exist=true;
		}

	}
	infile.close();
}
bool Information::GetA()
{
	return A_exist;
}
bool Information::GetB()
{
	return B_exist;
}
bool Information::GetC()
{
	return C_exist;
}
bool Information::GetD()
{
	return D_exist;
}
bool Information::GetE()
{
	return E_exist;
}
bool Information::GetF()
{
	return F_exist;
}
bool Information::GetG()
{
	return G_exist;
}
bool Information::GetH()
{
	return H_exist;
}
bool Information::GetI()
{
	return I_exist;
}
bool Information::GetJ()
{
	return J_exist;
}
bool Information::GetK()
{
	return K_exist;
}
string Information::GetChain()
{
	return chain;
}

