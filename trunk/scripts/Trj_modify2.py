#!/usr/bin/env python
"""
Trj_modify is used to fit the frames in trajectory to the first frame 
by trans and rot.
@change:
    - 2011.12.26.
        - Add those words.
        - Modified it.
"""

from MDAnalysis import Universe, Writer
from MDAnalysis.core.util import greedy_splitext

from MDPackage import Simple_atom
from MDPackage import usage
from MDPackage.mymath import least_squares_fitting
import os.path
import numpy
import sys
import time as Time

#import psyco ; psyco.jit() 
#from psyco.classes import *


def Usage():
    print "Usage: Trj_modify.py topfile trjfile output.xtc"

def Move_2_center(top_file,trj_file,trjout_file):
    u=Universe(top_file,trj_file)
    TRAJ_FRAMES=u.trajectory.numframes
    w = Writer(trjout_file, u.trajectory.numatoms)

    atoms=Simple_atom.Get_atom_list(top_file)
    SOLUTE_COUNT = 0
    for atom_ID in atoms:
        if atoms[atom_ID].residue_name != "SOL" and atoms[atom_ID].residue_name != "WAT":
            SOLUTE_COUNT +=1
        else:
            pass

    print '''Note: this program will read the pbc condition and use the dimensions \
read from trajectory files. You should make sure the dimensions are right or \
it will create a wrong output trajectory file.'''

    START_TIME=Time.time()
    NUM_ATOMS = u.trajectory.numatoms
    # loop through the trajectory and write a frame for every step
    for ts in u.trajectory:

        dimensions=ts.dimensions


        for i in range(SOLUTE_COUNT):
            if ts._x[i] > dimensions[0]:
                ts._x[i]=ts._x[i]-dimensions[0]
            if ts._x[i] <0:
                ts._x[i]=ts._x[i]+dimensions[0]

            if ts._y[i] > dimensions[1]:
                ts._y[i]=ts._y[i]-dimensions[1]
            if ts._y[i] <0:
                ts._y[i]=ts._y[i]+dimensions[1]

            if ts._z[i] > dimensions[2]:
                ts._z[i]=ts._z[i]-dimensions[2]
            if ts._z[i] < 0:
                ts._z[i]=ts._z[i]+dimensions[2]

        NOW_TIME=Time.time()
        BIN_TIME=NOW_TIME-START_TIME
        if ts.frame % 100 == 0:
#            usage.echo("%8.4f   %8.4f   %8.4f\r" %(dimensions[0],dimensions[1],dimensions[2]))
            usage.echo(" "*40+"Converted frame %d, time used: %8.2f s, time left: %8.2f s \r" \
                % (ts.frame,BIN_TIME,BIN_TIME*(float(TRAJ_FRAMES)/ts.frame-1) ))
#    for ts in u.trajectory:
        w.write(ts)
#        usage.echo("Writting frame %d\r"  %ts.frame)
    w.close_trajectory()
    print "Converted %r --> %r" % (intrj, outtrj)



if __name__=="__main__":
    if len(sys.argv)!=4:
        Usage()
        sys.exit()

    topol =sys.argv[1] #PRMpbc
    intrj =sys.argv[2] #TRJpbc_bz2
    outtrj = sys.argv[3]
    Move_2_center(topol,intrj,outtrj)    




