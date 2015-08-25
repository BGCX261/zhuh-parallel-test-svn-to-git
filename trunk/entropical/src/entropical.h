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


//Change from entropical 1.00 to entropical 1.01: M.I. for modes with low anharmonicity 
// (0.007 > s_anharmonic[j]/s_quantum[j] > 0.000) is included.
//Changes in entropical 1.02: Also negative M.I.'s are included (and don't cause mode
// to get s_anharmonic=0).
//Changes in entropical 1.03: The covariance matrix is now calculated with the unbiased 
// formula with denominator (N-1) and not (N).
//Changes in entropical 1.03d: Aesthetic changes in the output for distribution version
//

#include <iostream>
// #include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
//#include "tnt_array1d.h"
//#include "tnt_array1d_utils.h"
//#include "tnt_array2d.h"
//#include "tnt_array2d_utils.h"
//#include "tnt_math_utils.h"
//#include "jama_eig.h"
#include "ANN.h"
#include "functions.h"

#define GAMMA_CONSTANT 0.577215664901532861
#define MATH_PI  3.1415926535897932


/* What this function do? */
//double kann(const char *zt_temp_file, int trun_size, int maxPts, int dim, int row1, int row2)
double kann(const char *zt_temp_file, int trun_size, int maxPts, int dim, int row1, int row2);
