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


#include "functions.h"

double lngamma (double x)
{
	double tmp,ser;

	if (x<=50) 
	{ 
		return log(GAMMA(x)); 
	}
	tmp= x+4.5;
	tmp-= (x-0.5)*log(tmp);
	ser= 1.0 + 76.18009173/x - 86.50532033/(x+1.) + 24.01409822/(x+2.) -
		1.231739516/(x+3.) + 0.120858003e-2/(x+4.) - 0.536382e-5/(x+5.);

	return -tmp+log(2.50662827465*ser);
}


// Gamma function for argument x.
// Returns 1e308 if argument is a negative integer or 0 or if argument exceeds 171.

double GAMMA(double x)
{
	int i,k,m;
	double ga,gr,r,z;

	static double g[] = {
		1.0,
		0.5772156649015329,
		-0.6558780715202538,
		-0.420026350340952e-1,
		0.1665386113822915,
		-0.421977345555443e-1,
		-0.9621971527877e-2,
		0.7218943246663e-2,
		-0.11651675918591e-2,
		-0.2152416741149e-3,
		0.1280502823882e-3,
		-0.201348547807e-4,
		-0.12504934821e-5,
		0.1133027232e-5,
		-0.2056338417e-6,
		0.6116095e-8,
		0.50020075e-8,
		-0.11812746e-8,
		0.1043427e-9,
		0.77823e-11,
		-0.36968e-11,
		0.51e-12,
		-0.206e-13,
		-0.54e-14,
		0.14e-14};


	if (x > 171.0) return 1e308;    // This value is an overflow flag.
	if (x == (int)x) {
		if (x > 0.0) {
			ga = 1.0;               // use factorial
			for (i=2;i<x;i++) {
				ga *= i;
			}
		}
		else
			ga = 1e308;
	}
	else {
		if (fabs(x) > 1.0) {
			z = fabs(x);
			m = (int)z;
			r = 1.0;
			for (k=1;k<=m;k++) {
				r *= (z-k);
			}
			z -= m;
		}
		else
			z = x;
		gr = g[24];
		for (k=23;k>=0;k--) {
			gr = gr*z+g[k];
		}
		ga = 1.0/(gr*z);
		if (fabs(x) > 1.0) {
			ga *= r;
			if (x < 0.0) {
				ga = -M_PI/(x*ga*sin(M_PI*x));
			}
		}
	}
	return ga;
}


