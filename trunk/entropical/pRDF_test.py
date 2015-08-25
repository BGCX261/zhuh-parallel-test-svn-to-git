#!/usr/bin/env python
'''
TODO:
    write all the atoms of the solvent molecule to the index file.
'''
import math
import sys
import os
import numpy
import MDAnalysis
from itertools import izip
from MDPackage import Index
from MDPackage import Simple_atom
from MDPackage import usage
import MDPackage

import time as Time
import matplotlib.pyplot as plt


def Min_dist(solute_atoms,solu_l,solv_coor):
    '''
    atom_l: A full atom list.
    solu_l: A solute atom index list.
    solv_i: Index for one solvent molecule.
    '''
    dist_temp=[(solute_atoms[i].atom_coor_x -solv_coor[0])**2 \
        + (solute_atoms[i].atom_coor_y - solv_coor[1])**2 \
        + (solute_atoms[i].atom_coor_z - solv_coor[2])**2 for i in solu_l]

    min_dist  =min(dist_temp)
    min_index =solu_l[dist_temp.index(min_dist)]

    return math.sqrt(min_dist),min_index

def Dist_Square(vect_1,vect_2):
    dist=(vect_2[0]-vect_1[0])**2 + (vect_2[1]-vect_1[1])**2 + (vect_2[2]-vect_1[2])**2
    return dist


def Get_solvent_list(atom_list):
    solvent_list = list()
    for atom in atom_list:
        if atom_list[atom].residue_name == "WAT" and atom_list[atom].atom_name == "O":
            solvent_list.append(atom)
        elif atom_list[atom].residue_name == "SOL" and atom_list[atom].atom_name == "OW":
            solvent_list.append(atom)
    return solvent_list

def hist(value_list,number_list,min_value, max_value, nbins=100):
    '''
    temp_list in the form [dist,number]
    '''
    bin       = (max_value - min_value) / nbins
    
    grid_list =[0 for i in range(nbins)]
    numb_list =[0 for i in range(nbins)]

    for i in range(len(value_list)):
        temp = int( (value_list[i] - min_value) / bin )
        if value_list[i] < max_value:
            grid_list [temp] += 1
            numb_list[temp] += number_list[i]
        else:
       #     print "continued as vaule=%f" %value_list[i]
            continue

    #print grid_list
    #print numb_list
    for i in range(nbins):
        if grid_list[i] > 0:
            numb_list[i] /= float(grid_list[i])
        else:
            continue

    return numb_list


def pRDF(traj_file,coor_file,index_file,solute_index,dmax=30,nbins=32):
    '''
    A simple pRDF test here.
    '''

    START_TIME       =Time.time()

    HAS_TRAJFILE = False
    if os.path.isfile(traj_file):
        HAS_TRAJFILE = True
    
    atom_list    =Simple_atom.Get_atom_list(coor_file)
    index_list   =Index.Read_index_to_Inclass(index_file)
    solute_list  =index_list[solute_index].group_list

    solvent_list =Get_solvent_list(atom_list)

    if HAS_TRAJFILE:
        U=MDAnalysis.Universe(coor_file,traj_file)
    else:
        U=MDAnalysis.Universe(coor_file)

    GR=numpy.zeros((100),dtype=numpy.float64)
    Data_file=open("datafile.xvg",'w')
    #step 1 
    # Get the center of the solute. 
    for ts in U.trajectory:

        print "Checking frame number: %d" %(ts.frame)
        solute_atoms = dict()
        
        coor_x=0.0
        coor_y=0.0
        coor_z=0.0
        for i in solute_list:
            coor_x += ts._x[i-1]
            coor_y += ts._y[i-1]
            coor_z += ts._z[i-1]
            u_atom = MDPackage.Coor.unit_atom.unit_atom(atom_coor_x=ts._x[i-1],atom_coor_y=ts._y[i-1],atom_coor_z=ts._z[i-1])
            solute_atoms[i]=u_atom
        coor_x /= len(solute_list)
        coor_y /= len(solute_list)
        coor_z /= len(solute_list)

        print "Step 1 finished."
        #print "center %f\t%f\t%f" %(coor_x,coor_y,coor_z)

        #step 2
        #Get the range of the box.
        X_min = coor_x - dmax
        Y_min = coor_y - dmax
        Z_min = coor_z - dmax
        X_max = coor_x + dmax
        Y_max = coor_y + dmax
        Z_max = coor_z + dmax
        bin   = dmax *2.0 / nbins

        #print "bin:",bin

        print "Step 2 finished."

        #step 3
        # Get the grids
        #grid_number=z*nbins*nbins + y*nbins + x

        print "Step 3 finished."

        #step 4 
        #assign each grid to solute atoms. 
        #grid_in_solute contains that each grid blongs to which solute atom.



###############begin this new algorithm#################################
#         grid_map = numpy.zeros([nbins**3,2],dtype=numpy.int)
#         occpiad_dict=dict()

#         for so in solute_list:
#             x_temp = int((solute_atoms[so].atom_coor_x - X_min)/bin+0.5)
#             y_temp = int((solute_atoms[so].atom_coor_y - Y_min)/bin+0.5)
#             z_temp = int((solute_atoms[so].atom_coor_z - Z_min)/bin+0.5)
#             ind= z_temp*nbins*nbins + y_temp*nbins + x_temp
#             if grid_map[ind,0] !=0:
#             #    print "conflict. %d" %so
#                 pass
#             else:
#                 grid_map[ind,0]     =so
#                 occpiad_dict[ind] =1
#             #print "map %d to grid id %d" %(so,ind)
#         cycle = 0
#         while True:
#             occpiad_dict=dict()
#             for i in range(nbins**3):
#                 if grid_map[i,0] != 0:
#                     occpiad_dict[i]=1
#                 #new_dict = list()
#             print "cycle %d, len(occ) = %d" %(cycle,len(occpiad_dict))

#             if len(occpiad_dict) > nbins **3 -1:
#                 break

#             for i in occpiad_dict:
#                 z_temp = i / nbins**2
#                 y_temp = (i % nbins**2) / nbins 
#                 x_temp = i % nbins

#                 for step_x in range(-1,2):
#                     for step_y in range(-1,2):
#                         for step_z in range(-1,2):
#                             if abs(step_x)+abs(step_y)+abs(step_z)==0:
#                                 continue
#                             if (step_x+x_temp > nbins-1) or (step_x+x_temp <0):
#                                 continue
#                             if (step_y+y_temp > nbins-1) or (step_y+y_temp <0):
#                                 continue
#                             if (step_z+z_temp > nbins-1) or (step_z+z_temp <0):
#                                 continue

#                             new_value=(z_temp+step_z)*nbins*nbins + (y_temp+step_y)*nbins + (x_temp+step_x)

#                             if grid_map[new_value,0]== 0:
#                                 grid_map[new_value,0]   = grid_map[i,0]
#                         #        new_dict.append(new_value)

#                             else:
#                                 grid_site=[X_min+(x_temp+step_x+0.5)*bin,\
#                                  Y_min+(y_temp+ step_y + 0.5)*bin, \
#                                  Z_min+(z_temp+ step_z + 0.5)*bin]
#                                 old_atom =solute_atoms[grid_map[i,0]]
#                                 new_atom =solute_atoms[grid_map[new_value,0]]
#                                 old_vect =[old_atom.atom_coor_x,old_atom.atom_coor_y,old_atom.atom_coor_z]
#                                 new_vect =[new_atom.atom_coor_x,new_atom.atom_coor_y,new_atom.atom_coor_z]
#                                 dist1    = Dist_Square(grid_site,old_vect)
#                                 dist2    = Dist_Square(grid_site,new_vect)
#                             #    print dist1, dist2
#                                 if dist1 < dist2:
#                                     grid_map[new_value,0]   = grid_map[i,0]
#                             #        new_dict.append(new_value)

# #                grid_map[i]=0
            
#             if len(occpiad_dict) < nbins **3 :
# #                for i in occpiad_dict:
# #                    grid_map[i,0]=0
# #                    grid_map[i,1]=0
#                 del occpiad_dict
#                 cycle += 1
# #                print "cycle %d, len(occ) = %d" %(cycle,len(new_dict))
# #       print occpiad_dict
# #
# #        sys.exit()
#         solute_contain_grids  =dict()
#         for i in range(nbins**3):
#             try:
#                 solute_contain_grids[grid_map[i,0]].append(i)
#             except:
#                 solute_contain_grids[grid_map[i,0]]=list()
#                 solute_contain_grids[grid_map[i,0]].append(i)

#             z_temp = i / nbins**2
#             y_temp = (i % nbins**2) / nbins 
#             x_temp = i % nbins
#             grid_site=[X_min+(x_temp+0.5)*bin,\
#             Y_min+(y_temp+ 0.5)*bin, \
#             Z_min+(z_temp+ 0.5)*bin]    
#             old_atom =solute_atoms[grid_map[i,0]]
#             old_vect =[old_atom.atom_coor_x,old_atom.atom_coor_y,old_atom.atom_coor_z]
#             dist1    = Dist_Square(grid_site,old_vect)
#             grid_map[i,1]=math.sqrt(dist1)

#         grids_in_which_solute=grid_map
#         for i in solute_contain_grids:
#             print i,len(solute_contain_grids[i])
#         sys.exit()

###############end this algorithm######################################

        grids_in_which_solute =list()
        solute_contain_grids  =dict()

        for i in range(nbins**3):
            z_temp = i / nbins**2
            y_temp = (i % nbins**2) / nbins 
            x_temp = i % nbins

            grid_site=[X_min+(x_temp+0.5)*bin, Y_min+(y_temp+0.5)*bin, Z_min+(z_temp+0.5)*bin]
            #print grid_site
            min_dist, min_index= Min_dist(solute_atoms,solute_list,grid_site)
            if i % 3000 ==0:
                NOW_TIME=Time.time()
                BIN_TIME=NOW_TIME-START_TIME
                sys.stderr.write("grid ID %10d, time used: %6.2f s\r" %(i,BIN_TIME))
                sys.stderr.flush()
            grids_in_which_solute.append([min_index,min_dist])
            try:
                solute_contain_grids[min_index].append(i)
            except:
                solute_contain_grids[min_index]=list()
                solute_contain_grids[min_index].append(i)
                #print solute_contain_grids

        # for i in solute_contain_grids:
        #     print i,len(solute_contain_grids[i])
        # sys.exit()

        print "\nStep 4 finished."

        #step 5.
        #assign each solvent atom to grids.
        grid_in_solvent=[list() for i in range(nbins**3)]
        for i in solvent_list:
            SV_x = ts._x[i-1]
            SV_y = ts._y[i-1]
            SV_z = ts._z[i-1]

            if SV_x > X_min and SV_x < X_max:
                x_temp = int( (SV_x - X_min) / bin )
            else:
                continue
            if SV_y > Y_min and SV_y < Y_max:    
                y_temp = int( (SV_y - Y_min) / bin )
            else:
                continue
            if SV_z > Z_min and SV_z < Z_max:
                z_temp = int( (SV_z - Z_min) / bin )
            else:
                continue
            grid_in_solvent[z_temp*nbins*nbins + y_temp*nbins + x_temp].append(i)
            # print "append solvent %d" %i

        print "Step 5 finished."
         # step 6.
        #calculating the g(r) for each solute atom.
 
        TOTAL_ATOMS = 0
        for i in solute_list:
            try:
                temp_grids=solute_contain_grids[i]
                #print "solute %d, grids number %d" %(i,len(temp_grids))
            except:
                continue
        #rdf_atom=[0 for i in range(50)]
            bin       =float(dmax)/nbins
            density   = MDAnalysis.core.units.convert(1.0, 'water', 'Angstrom^{-3}')*math.pow(10,3)
            unit_conc =1/ ((float(dmax) *2 / nbins)**3 * density) #unit solvent atom density.
            temp1     =list() #A list used to contain grid_dist.
            temp2     =list() #A list used to contain sol number for each grad.
        
            for grid in temp_grids:

                sol_number=len(grid_in_solvent[grid])
                #print "   %d" %sol_number,
                blabla,dist=grids_in_which_solute[grid]
            
                temp1.append(dist)
                temp2.append(sol_number)
        #print temp1
        #print temp2
        #if i == 10:
        #    sys.exit()
            rdf_atom=hist(temp1, temp2, 0.0, 12.0, 100)
        #print rdf_atom
            if sum(rdf_atom) > 0:
                TOTAL_ATOMS += 1
            rdf_atom=numpy.array(rdf_atom) *unit_conc


            GR += rdf_atom
#        print GR
        plt.clf()
        ax = plt.gca()
        ax.set_xlabel("Distance (nm)")
        ax.set_ylabel("pRDF(r)")
        x_label=[i/50.0 for i in range(100)]
        y_label=[GR[i]/ts.frame for i in range(100)]
        ax.plot(x_label,y_label,'b',)
        plt.draw()
        temp_filename="temp"+"%d"%(ts.frame)+".png"
        plt.savefig(temp_filename)
        for i in range(100):
            Data_file.write("%12.4f" %y_label[i])
        Data_file.write("\n")
        

    GR = GR / TOTAL_ATOMS / U.trajectory.numframes
    Data_file.close()
#   print TOTAL_ATOMS
#        print len(solute_index)
    for i in range(32):
        print "%f\t%f" %(2.0/32*(i+0.5),GR[i])

  #  print GR


def Check_args():
    if len(sys.argv) != 5:
        print "Usage: pRDF_test.py coor_file traj_file index_file solute_index"
    else:
        coor_file    = sys.argv[1]
        traj_file    = sys.argv[2]
        index_file   = sys.argv[3]
        solute_index = int(sys.argv[4])
        pRDF(traj_file,coor_file,index_file,solute_index,20,25)

if __name__ == '__main__':
    plt.ion()
    Check_args()

