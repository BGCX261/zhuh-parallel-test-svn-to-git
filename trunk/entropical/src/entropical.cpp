/***************************************************************************
 *   Copyright (C) 2008 by Jorge Numata, Michael Wan & Ernst-Walter Knapp  *
 *   numata@chemie.fu-berlin.de  mwan@fas.harvard.edu                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/********************************************************************************
Citation:                                                                       *
Jorge Numata, Michael Wan, Ernst-Walter Knapp                                   *
Conformational entropy of biomolecules: beyond the quasi-harmonic approximation *
Genome Informatics vol. 18 p. 192-205                                           *
http://www.jsbi.org/modules/journal1/index.php/IBSB07/IBSB07019.pdf             *
 ********************************************************************************/

#include "entropical.h"

using namespace std;
void printPt(ostream &out, ANNpoint p)	;

bool readPt(int trun_size,ifstream &in, ANNpoint p, int dim, int row1, int row2);

bool readPt(int trun_size,ifstream &in, ANNpoint p, int dim, int row1, int row2)            // read point (false on EOF)
{
    switch (dim)
    {   
        case 1:
            for (int i=0; i<dim; i++)
            {   
                in.read((char *) &p[i], sizeof (double));

            }   
            if (!in.eof())
            {
                in.seekg((trun_size-dim)*sizeof(double),ios::cur);
            }
          	// cout<<p[0]<<endl;
            break;

        case 2:
            for (int i=0; i<dim; i++){
                in.read((char *) &p[i], sizeof (double));
                if (i<1) in.seekg((row2-row1-1)*8,ios::cur);

            }   
            if (!in.eof()) in.seekg((trun_size-1-row2+row1)*8,ios::cur);
            break;
    }   

    return true;
}

/* What this function do? */
//double kann(const char *zt_temp_file, int trun_size, int maxPts, int dim, int row1, int row2)
double kann(const char *zt_temp_file, int trun_size, int maxPts, int dim, int row1, int row2)
{
	double 			eps	=0;
	int				k	= 6;				// number of nearest neighbors(plus one)
	ANNpointArray	dataPts;				// data points
	ANNpoint		queryPt;				// query point
	ANNidxArray		nnIdx;					// near neighbor indices
	ANNdistArray	dists;					// near neighbor distances
	ANNkd_tree*		kdTree;
    ifstream*   dataIn          = NULL;     

	queryPt = annAllocPt(dim);					// allocate query point
	dataPts = annAllocPts(maxPts, dim);			// allocate data points
	nnIdx = new ANNidx[k];						// allocate near neigh indices
	dists = new ANNdist[k];						// allocate near neighbor dists
	double sumR[k];

	ifstream dataStream;
    dataStream.open( zt_temp_file);// open data file

    dataIn = &dataStream;               // make this the data stream

    dataIn->seekg(row1*8,ios::beg);

//	cout<<"row1, row2: "<<row1<<","<<row2<<endl;        
    for (int i=0;i<maxPts;i++)
    {
        readPt(trun_size,*dataIn,dataPts[i],dim,row1,row2);
   //     printPt(cout,dataPts[i]);
    }
  //  cout<<endl;

	kdTree = new ANNkd_tree(dataPts, maxPts,dim);

	for (int i = 0;i < k; i++) 
	{		
		sumR[i] = 0.0;				
	}

	for (int i=0;i<maxPts;i++) 
	{

		queryPt=dataPts[i];

		kdTree->annkSearch(queryPt,k,nnIdx,	dists,eps);		
		// cout<< i <<"\t";

//		cout<<i<<"\t";
		for (int j = 1;j < k; j++) 
		{		
			if (dists[j] > 0.0)
			{
//				cout<<nnIdx[j]<<"\t"<<dists[j]<<"\t";
				sumR[j] += log (dists[j]);		
			}		
		}
	//		cout<<endl;
	}

//	cout <<row1<<"\t"<<sumR[k-1]<<endl;

	double Lj = 0.0;
	for (int i = 1;i < k; i++)
	{
		Lj += 1.0/((double) i);
	}
	double resu;
	double consts;
	consts=GAMMA_CONSTANT + (double)dim/2.0 * log ( MATH_PI ) -lngamma ( ( (double)dim)/2.0+1.0 );
//	cout<<sumR[k-1]<<"\t"<<consts - Lj<<endl;

	resu= 0.5 * ((double)dim) / ((double)maxPts) * sumR[k-1] + log ((double)maxPts) + consts  -Lj;

///********************************/
	// double Lj = 0.0;
 //    for (int i = 1;i < k; i++) {

 //        sumR[i] *= 0.5 * ((double)dim) / ((double)maxPts);
 //        sumR[i] += 0.577215664901532861;
 //        sumR[i] += -Lj;
 //        sumR[i] += log ((double)maxPts);
 //        sumR[i] += (double)dim/2.0 * log (  3.1415926535897932 );
 //        //  sumR[i] += -log ( gamma(((double)dim)/2.0+1.0) );
 //        sumR[i] += -lngamma ( ( (double)dim)/2.0+1.0);
 //        Lj += 1.0/((double) i); // Lj for the next neighbor-entropy
 //    } 
///********************************/
//	cout<<sumR[k-1]<<"\t"<<resu<<endl;

//	cout<<resu<<endl;

	delete [] nnIdx;							// clean things up
	delete [] dists;
	delete kdTree;
	annClose();									// done with ANN
	annDeallocPts(dataPts);

	// ADDED mwan 14.08.2007 deallocate dataPts
	//return sumR[k-1];
	 return resu;
}


void printPt(ostream &out, ANNpoint p)			// print point
{
	int dim =1;
	out << "(" << p[0];
	for (int i = 1; i < dim; i++) {
		out << ", " << p[i];
	}
	out << ")\n";
}