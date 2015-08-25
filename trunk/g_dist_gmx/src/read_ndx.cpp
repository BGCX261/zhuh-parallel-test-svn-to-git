#include "read_ndx.h"
#include "string_operate.h"

vector<string>  read_2_group(char * index_file)
{
	vector<string> vs;
	string s;
	ifstream in(index_file);
	while(!in.fail())
	{
		getline(in,s);
		if(s.find("[")<10)
		{
			vs.push_back(Split(Split(Split(s,'[',0),']',0),' ',0));
		}
	}
	in.close();
	return vs;
}

vector<int>  read_2_group_n(char * index_file)
{
	vector<int> vs;
	string s;
	int num=0;
	ifstream in(index_file);
	getline(in,s);
	while(!in.fail())
	{	
		while(s.find("[")<10)
		{
			getline(in,s);
			while(s.find("[")>100&&s.size()>0)
			{
				num+=Split_v(s,' ').size();
				getline(in,s);
			}
			vs.push_back(num);
			num=0;
		}
		getline(in,s);
	}
	in.close();
	return vs;
}


vector<int>  read_group_2_serial(char * index_file, string group_name)
{
	vector<int> vi;
	string s;
	ifstream in(index_file);
	while(!in.fail())
	{
		getline(in,s);
		if((s.find("[")<10)&(Split(Split(Split(s,'[',0),']',0),' ',0)==group_name))
		{
			getline(in,s);
			vector<string> temp;
			while(s.find("[")>10&&!in.fail())
			{
				temp.clear();
				temp=Split_v(s,' ');
				for(int i=0;i<temp.size();i++)
				{
					vi.push_back(atoi(temp.at(i).c_str()));
				}
				getline(in,s);
			}
			
		}
	}
	in.close();
	return vi;
}