#!/usr/bin/env python
'''
TODO:
    write all the atoms of the solvent molecule to the index file.
'''
import math
import sys
import numpy
import copy
import string
import MDAnalysis
import MDPackage
from MDPackage import Index
from MDPackage import Simple_atom
from MDPackage import usage
import time as Time

from MDAnalysis.coordinates.xdrfile import libxdrfile 
#import xdrfile_open, xdrfile_close, read_xtc_natoms, read_xtc, DIM, exdrOK


def Min_dist(atom_l,solu_l,solv_coor):
    '''
    atom_l: A full atom list.
    solu_l: A solute atom index list.
    solv_i: Index for one solvent molecule.
    '''

    dist_list =[(atom_l[i].atom_coor_x - atom_l[solv_coor].atom_coor_x)**2 \
    + (atom_l[i].atom_coor_y - atom_l[solv_coor].atom_coor_y)**2 \
    + (atom_l[i].atom_coor_z - atom_l[solv_coor].atom_coor_z)**2 for i in solu_l]
    
    min_dist  =min(dist_list)
    min_index =solu_l[dist_list.index(min_dist)]
#    print min_dist,min_index
    return math.sqrt(min_dist),min_index

def Dist(atom_l,origin,solv_i):
    dist=(atom_l[solv_i].atom_coor_x-origin[0])**2 \
    + (atom_l[solv_i].atom_coor_y-origin[1])**2 \
    + (atom_l[solv_i].atom_coor_z-origin[2])**2

    return math.sqrt(dist)

def Get_solvent_list(atom_list):
    solvent_list = list()
    for atom in atom_list:
        if atom_list[atom].residue_name == "WAT" and atom_list[atom].atom_name == "O":
            solvent_list.append(atom)
        elif atom_list[atom].residue_name == "SOL" and atom_list[atom].atom_name == "OW":
            solvent_list.append(atom)

    return solvent_list

def pRDF(top_file,trj_file,index_file,trjout_file,solute_index,WAT_NUMBER=500):
    '''
    Save the WAT_NUMBER closest water molecules to a new trajectory file.
    '''
    START_TIME       =Time.time()
    
    Atoms            =Simple_atom.Get_atom_list(top_file)
    atom_list        =copy.deepcopy(Atoms)
    index_list       =Index.Read_index_to_Inclass(index_file)
    solute_atom_list =index_list[solute_index].group_list
    solvent_list     =Get_solvent_list(atom_list)

    if len(solvent_list) < WAT_NUMBER:
        print "Error: The number of water molecules (%d) is less than the critical number (%d)." %(len(solvent_list),WAT_NUMBER)

    natoms       = libxdrfile.read_xtc_natoms(trj_file)
    x            = numpy.zeros((natoms, libxdrfile.DIM), dtype=numpy.float32)
    box          = numpy.zeros((libxdrfile.DIM,libxdrfile.DIM), dtype=numpy.float32)
    XTC          = libxdrfile.xdrfile_open(trj_file, 'r')
    
    OUTPUT_ATOMS =len(solute_atom_list)+3*WAT_NUMBER
    XTC_write    =libxdrfile.xdrfile_open(trjout_file,'w')
    x_out        =numpy.zeros((OUTPUT_ATOMS,libxdrfile.DIM),dtype=numpy.float32)

# loop through file until return status signifies end or a problem
# (it should become exdrENDOFFILE on the last iteration)
    status      = libxdrfile.exdrOK
    FIRST_FRAME =True
    solu_list   =list()
    while status == libxdrfile.exdrOK:
        status,step,time,prec = libxdrfile.read_xtc(XTC, box, x)
        # do something with x
        sol_dict=dict()
        sol_dist=list()

###############
        for i in atom_list:
            u_atom = MDPackage.Coor.unit_atom.unit_atom(atom_coor_x=x[i-1,0],atom_coor_y=x[i-1,1],atom_coor_z=x[i-1,2])
            atom_list[i]=u_atom

###############
        
        if FIRST_FRAME == True:
#            FIRST_FRAME = False
            for solvent in solvent_list:
#            usage.echo("Checking solvent atom: %d\r" %(solvent))
                min_dist,solu_temp=Min_dist(atom_list,solute_atom_list,solvent)
                sol_dist.append(min_dist)
                sol_dict[min_dist]=solvent
                solu_list.append(solu_temp)
            solu_list=list(set(solu_list))
        else:
            for solvent in solvent_list:
                min_dist,solu_temp=Min_dist(atom_list,solu_list,solvent)
                sol_dist.append(min_dist)
                sol_dict[min_dist]=solvent

        sorted_sol_dist=sorted(sol_dist)
        STANDARD=sorted_sol_dist[WAT_NUMBER+1]

        for i in range(len(solute_atom_list)):
            x_out[i,0] =x[solute_atom_list[i]-1,0]
            x_out[i,1] =x[solute_atom_list[i]-1,1]
            x_out[i,2] =x[solute_atom_list[i]-1,2]    
        for i in range(WAT_NUMBER):
            for j in range(3):
                x_out[len(solute_atom_list)+3*i+j,0] =x[sol_dict[sorted_sol_dist[i]]-1+j,0]
                x_out[len(solute_atom_list)+3*i+j,1] =x[sol_dict[sorted_sol_dist[i]]-1+j,1]
                x_out[len(solute_atom_list)+3*i+j,2] =x[sol_dict[sorted_sol_dist[i]]-1+j,2]

        status2=libxdrfile.write_xtc(XTC_write,step,time,box,x_out,prec)

        if FIRST_FRAME == True:
            new_list=[Atoms[i] for i in solute_atom_list]
            for i in range(WAT_NUMBER):
                new_list.append(Atoms[sol_dict[sorted_sol_dist[i]]])
                new_list.append(Atoms[sol_dict[sorted_sol_dist[i]]+1])
                new_list.append(Atoms[sol_dict[sorted_sol_dist[i]]+2])

            out_file=string.split(trjout_file,'.')[0]+".pdb"
            Simple_atom.Save_file(out_file,new_list)

            FIRST_FRAME = False

        NOW_TIME=Time.time()
        BIN_TIME=NOW_TIME-START_TIME
        if step % 1000 == 0:
            sys.stderr.write("step %10d, time %10.2f ps, time used: %6.2f s\r" %(step,time,BIN_TIME))
            sys.stderr.flush()

    # finally close file
    print ""
    libxdrfile.xdrfile_close(XTC)
    libxdrfile.xdrfile_close(XTC_write)


def For_allsolvent(top_file,trj_file,trjout_file,WAT_NUMBER=500):
    '''
    Save the WAT_NUMBER closest water molecules to a new trajectory file.
    '''
    START_TIME       =Time.time()
    
    Atoms            =Simple_atom.Get_atom_list(top_file)
    atom_list        =copy.deepcopy(Atoms)
    # index_list       =Index.Read_index_to_Inclass(index_file)
    # solute_atom_list =index_list[solute_index].group_list
    solvent_list     =Get_solvent_list(atom_list)

    if len(solvent_list) < WAT_NUMBER:
        print "Error: The number of water molecules (%d) is less than the critical number (%d)." %(len(solvent_list),WAT_NUMBER)

    natoms       = libxdrfile.read_xtc_natoms(trj_file)
    x            = numpy.zeros((natoms, libxdrfile.DIM), dtype=numpy.float32)
    box          = numpy.zeros((libxdrfile.DIM,libxdrfile.DIM), dtype=numpy.float32)
    XTC          = libxdrfile.xdrfile_open(trj_file, 'r')
    
    OUTPUT_ATOMS =3*WAT_NUMBER
    XTC_write    =libxdrfile.xdrfile_open(trjout_file,'w')
    x_out        =numpy.zeros((OUTPUT_ATOMS,libxdrfile.DIM),dtype=numpy.float32)

# loop through file until return status signifies end or a problem
# (it should become exdrENDOFFILE on the last iteration)
    status      = libxdrfile.exdrOK
    status2     = libxdrfile.exdrOK
    FIRST_FRAME =True
    # center=numpy.array([0.0,0.0,0.0])
    while status == libxdrfile.exdrOK and status2 == libxdrfile.exdrOK:
        status,step,time,prec = libxdrfile.read_xtc(XTC, box, x)
        # do something with x
        sol_dict=dict()
        sol_dist=list()

###############
        for i in atom_list:
            u_atom = MDPackage.Coor.unit_atom.unit_atom(atom_coor_x=x[i-1,0],atom_coor_y=x[i-1,1],atom_coor_z=x[i-1,2])
            atom_list[i]=u_atom

###############
        
        if FIRST_FRAME == True:
            center=numpy.array([box[0,0]/2,box[1,1]/2,box[2,2]/2])
#            FIRST_FRAME = False

        for solvent in solvent_list:
            dist=Dist(atom_list,center,solvent)
            sol_dist.append(dist)
            sol_dict[dist]=solvent


        sorted_sol_dist=sorted(sol_dist)
        STANDARD=sorted_sol_dist[WAT_NUMBER+1]
  
        for i in range(WAT_NUMBER):
            for j in range(3):
                x_out[3*i+j,0] =x[sol_dict[sorted_sol_dist[i]]-1+j,0]
                x_out[3*i+j,1] =x[sol_dict[sorted_sol_dist[i]]-1+j,1]
                x_out[3*i+j,2] =x[sol_dict[sorted_sol_dist[i]]-1+j,2]

        status2=libxdrfile.write_xtc(XTC_write,step,time,box,x_out,prec)

        if FIRST_FRAME == True:
            new_list=list()
            for i in range(WAT_NUMBER):
                new_list.append(Atoms[sol_dict[sorted_sol_dist[i]]])
                new_list.append(Atoms[sol_dict[sorted_sol_dist[i]]+1])
                new_list.append(Atoms[sol_dict[sorted_sol_dist[i]]+2])

            out_file=string.split(trjout_file,'.')[0]+".pdb"
            Simple_atom.Save_file(out_file,new_list)

            FIRST_FRAME = False

        NOW_TIME=Time.time()
        BIN_TIME=NOW_TIME-START_TIME
        if step % 1000 == 0:
            sys.stderr.write("step %10d, time %10.2f ps, time used: %6.2f s\r" %(step,time,BIN_TIME))
            sys.stderr.flush()

    # finally close file
    print ""
    libxdrfile.xdrfile_close(XTC)
    libxdrfile.xdrfile_close(XTC_write)



def Check_args():
    if len(sys.argv) == 6:
        top_file    =sys.argv[1]
        trj_file    =sys.argv[2]
        index_file  =sys.argv[3]
        trjout_file =sys.argv[4]
        WAT_NUMBER  =int(sys.argv[5])

        index_list=Index.Read_index_to_Inclass(index_file)
        Index.Print_Index(index_list)
        while True:
            try:
                solute_index=int(raw_input("Choose the solute index:"))
                break
            except:
                print "You should input a number."
                continue

        pRDF(top_file,trj_file,index_file,trjout_file,solute_index,WAT_NUMBER)

    elif len(sys.argv) == 5:
        top_file    =sys.argv[1]
        trj_file    =sys.argv[2]
        trjout_file =sys.argv[3]
        WAT_NUMBER  =int(sys.argv[4])
        For_allsolvent(top_file,trj_file,trjout_file,WAT_NUMBER)

    else: 
        print "Usage: "
        print "For solute,  using: Closest_solvent.py top_file trj_file index_file trjout_file WAT_NUMBER"
        print "For solvent, using: Closest_solvent.py top_file trj_file trjout_file WAT_NUMBER"



if __name__ == '__main__':
    Check_args()

