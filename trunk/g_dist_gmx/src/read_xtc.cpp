#include "read_xtc.h"


vector<double>  read_xtc2dist(char * filename,vector<int> serial_1,vector<int> serial_2,vector<double> mass_1,vector<double> mass_2)

{
        int natoms,step;
        float time_temp;
        float p;
		vector<double> coor_x;
		vector<double> coor_y;
		vector<double> coor_z;
		vector<double> result;
        matrix box;
        rvec *x;
        XDRFILE *xtc;
        xtc=xdrfile_open(filename,"r");
        int read_return=read_xtc_natoms(filename,&natoms);


        x=(rvec * )calloc(natoms,sizeof(x[0]));
        while(1)
        {
                read_return=read_xtc(xtc,natoms,&step,&time_temp,box,x,&p);
		if(step%100000==0)
		{
			
			cout<<"Reading frame"<<"\t"<<step<<" time "<<time_temp<<endl;
		}
                if(read_return!=0)
                {
                        break;
                }

				coor_x.clear();
				coor_y.clear();
				coor_z.clear();

				for(int i=0;i<serial_1.size();i++)
                {
       //                 cout<<step<<"\t"<<time_temp<<"\t"<<natom<<"\t"<<x[natom][0]<<"\t"<<x[natom][1]<<"\t"<<x[natom][2]<<endl;
					
					int natom=serial_1.at(i);
					coor_x.push_back(x[natom][0]);
					coor_y.push_back(x[natom][1]);
					coor_z.push_back(x[natom][2]);
				}
				vector<double> cent_1 =get_center(coor_x,coor_y,coor_z,mass_1);

				coor_x.clear();
				coor_y.clear();
				coor_z.clear();
				for(int i=0;i<serial_2.size();i++)
				{
					int natom=serial_2.at(i);
					coor_x.push_back(x[natom][0]);
					coor_y.push_back(x[natom][1]);
					coor_z.push_back(x[natom][2]);
				}
				vector<double> cent_2 =get_center(coor_x,coor_y,coor_z,mass_2);

				double dist_temp=get_dist(cent_1,cent_2);

				result.push_back(time_temp);
				result.push_back(dist_temp);

        }
        xdrfile_close(xtc);
		return result;

}
