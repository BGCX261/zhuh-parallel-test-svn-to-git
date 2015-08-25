#!/usr/bin/env python

'''
author: zhuh
date: 2012.08.16
version: 0.0.1
'''

import sys
import os
import math
import getopt
import struct
import numpy as np
import MDAnalysis
import MDAnalysis.core.qcprot as qcp
from entropical import libentropical
from MDPackage import Index

import time as Time

K= 1.3806504e-23
'''It's the Boltzmann constant'''
HBA= 1.05457148e-34
'''It's the Planck constant'''
R= 8.3145
'''It's the idea gas constant'''
E= 2.71828183
'''natural exp poment e'''
MP=1.66055402e-27
'''1 a.m.u. = Proton mass [kg] '''
NA=6.0221415e23        
''' Avogadro's Number  [1/gmol] '''

def QH_entro(top_file,traj_file,index_file,temperature=300,skip=1,begin=0,end=-1,WRITE_EIGENVECTOR=False):
    '''
    Add some words here.
    '''
    #step 1: reading the trajectory.    
    BEGIN_TIME=Time.time()
    print "step 1: Reading trajectory"
    U       =MDAnalysis.Universe(top_file,traj_file)
    index   =Index.Read_index_to_Inclass(index_file)
    Index.Print_Index(index)
    while True:
        try:
            solute_index=int(raw_input("Choose the group for entropy calculation:"))
            break
        except:
            print "You should input a number."
            continue
    chose_group=index[solute_index].group_list

    if end== -1:
        nframes=U.trajectory.numframes-begin
    elif end > begin:
        nframes=end-begin
    else:
        print "The begin and the end of the frame seem not correct."
        sys.exit()

    natoms  =len(chose_group)
    print "\t Reading %d frames from trajectory file: %s" %(nframes,traj_file)

    
    #step 2: put data to traj_data matrix. get eigenvalues and eigenvectors.
    
    traj_data =np.zeros((nframes,natoms,3),dtype=np.float32)
    traj_data2=np.zeros((nframes,3*natoms),dtype=np.float32)
    traj_ave  =np.zeros((3*natoms),dtype=np.float32)
    covar_mat = np.zeros((3*natoms,3*natoms),dtype=np.float32)

    sqrt_mass = [ math.sqrt(U.atoms[i].mass) for i in range(U.trajectory.numatoms)]

    

    POINT=0
    ##  POINT used to replace the U.trajectory.frame in this part.
    for ts in U.trajectory:
#        temp_vect = np.zeros(3*natoms,dtype=np.float32)
        POINT += 1
        if POINT > begin and (POINT-begin)<nframes+1: 
            pass
        elif POINT < begin:
            continue
        elif POINT > end and end > 0:
            break
        else:
            print "Note: reach here. begin=%6d,end=%6d,POINT=%6d" %(begin,end,POINT)
            sys.exit()

        sys.stderr.write("\t Reading frame %8d\r" %POINT)
        sys.stderr.flush()


        for i,ai in list(enumerate(chose_group)):
            traj_data[POINT-begin-1,i,0] = ts._x[ai-1] * sqrt_mass[ai-1]
            traj_data[POINT-begin-1,i,1] = ts._y[ai-1] * sqrt_mass[ai-1]
            traj_data[POINT-begin-1,i,2] = ts._z[ai-1] * sqrt_mass[ai-1]

 ########################
 #Add fitting code here. from matrix traj_data to a new matrix.
    print "\nstep 2: Fitting the trajectory."

    ref_coor=traj_data[0,:,:]

    for k in range(natoms):
        for l in range(3):
            traj_data2[0,3*k+l]=ref_coor[k,l]

    ref_com = np.array([sum(ref_coor[:,0])/nframes,sum(ref_coor[:,1])/nframes,sum(ref_coor[:,2])/nframes])
    #ref_com means center of coordinate the reference.
    ref_coordinates = ref_coor - ref_com

    # traj_coordinates = traj_atoms.coordinates().copy()

    # nframes = len(frames)
    rmsd = np.zeros((nframes,))

    rot = np.zeros(9,dtype=np.float64)      # allocate space for calculation
    R = np.matrix(rot.reshape(3,3))

    for k in range(1,nframes):
        # shift coordinates for rotation fitting
        # selection is updated with the time frame

        sys.stderr.write("\t Fitting frame %8d\r" %(k+1))
        sys.stderr.flush()

        traj_coor=traj_data[k,:,:]
        x_com = np.array([sum(traj_coor[:,0])/nframes,sum(traj_coor[:,1])/nframes,sum(traj_coor[:,2])/nframes])
        traj_coordinates = traj_coor - x_com

        rmsd[k] = qcp.CalcRMSDRotationalMatrix(ref_coordinates.T.astype(np.float64),
                                               traj_coordinates.T.astype(np.float64),
                                               natoms, rot, None)
        R[:,:] = rot.reshape(3,3)

        # Transform each atom in the trajectory (use inplace ops to avoid copying arrays)
        # (Marginally (~3%) faster than "ts._pos[:] = (ts._pos - x_com) * R + ref_com".)
        # ts._pos   -= x_com
        # ts._pos[:] = ts._pos * R # R acts to the left & is broadcasted N times.
        # ts._pos   += ref_com
        new_coor=np.array(np.matrix(traj_coordinates)*np.matrix(R))+ref_com

        for i in range(natoms):
            for j in range(3):
                traj_data2[k,3*i+j]=ref_coor[i,j]

    del traj_data
 ########################
    print "\nstep 3: Creating covariance matrix"
    print "\t Generazing the (%d X %d) covariance matrix" %(3*natoms,3*natoms)

#        traj_data[ts.frame-1]=temp_vect
    for i in range(nframes):
        traj_ave += traj_data2[i]

    traj_ave = traj_ave / nframes

    for i in range(nframes):
        delta_vect=[traj_data2[i][j]-traj_ave[j] for j in range(3*natoms)]
        covar_mat += np.array(np.matrix(delta_vect).T * np.matrix(delta_vect))
    
#    covar_mat = covar_mat / ( nframes -1 )   # be careful!
    covar_mat = covar_mat / nframes

    TIME1=Time.time()
    print "\t Time used %6.2f s" %(TIME1 - BEGIN_TIME)


    print "step 4: Diagnoalizing the covariance matrix"
    eigenvalues,eigenvectors = np.linalg.eig(covar_mat)
    print eigenvalues

    TIME2=Time.time()


    print "\t Time used %6.2f s" %(TIME2 - TIME1)

#    sys.exit()


    #step 3: get the number of classical mode eigenvalues.
#    eigenvalues=sorted(eigenvalues,reverse=True)
#    np.savetxt("eigen.xvg",eigenvalues)

    eigen_thr = 1e-6
    truncate_num = 0
    for i in range(3*natoms):
        if eigenvalues[i] < eigen_thr:
            truncate_num = i
            break
        elif eigenvalues[-1] > eigen_thr:
            truncate_num = 3*natoms
    print "\t Using %d eigenvalues to calculate entropy." %truncate_num


    print "step 5: Calculating the quasiharmonic entropy"
    global HBA
    global K
    global MP
    # global R
    alpha_const  =HBA*(1e10)/math.sqrt(K*temperature*MP)
    eigval_class = eigenvalues[:truncate_num]
    eigvec_class = eigenvectors[:truncate_num]


    alpha     =[alpha_const/math.sqrt(eigval_class[i]) for i in range(truncate_num)]
    s_quantum =[alpha[i]/(math.exp(alpha[i])-1) - math.log(1-math.exp(-alpha[i])) for i in range(truncate_num)]
    print s_quantum

    total_entropy=sum(s_quantum)*R
    print "\t Entopy: %8.2f J/mol/K, %8.2f Kcal/mol." %(total_entropy,total_entropy/4186.8*temperature)


######################################################################



def Main_func(top_file,traj_file, temperature = 300, skip=1):
    '''
    Add some words here.
    '''
    #step 1: reading the trajectory.    
    BEGIN_TIME=Time.time()
    print "step 1: Reading trajectory"
    U       =MDAnalysis.Universe(top_file,traj_file)
    nframes =U.trajectory.numframes
    natoms  =U.trajectory.numatoms
    print "\t Reading %d frames from trajectory file: %s" %(nframes,traj_file)

    
    #step 2: put data to traj_data matrix. get eigenvalues and eigenvectors.
    print "step 2: Creating covariance matrix"
    traj_data =np.zeros((nframes,3*natoms),dtype=np.float32)
    traj_ave  =np.zeros((3*natoms),dtype=np.float32)
    covar_mat = np.zeros((3*natoms,3*natoms),dtype=np.float32)

    sqrt_mass = [ math.sqrt(U.atoms[i].mass) for i in range(natoms)]

    print "\t Generazing the (%d X %d) covariance matrix" %(3*natoms,3*natoms)

    for ts in U.trajectory:
#        temp_vect = np.zeros(3*natoms,dtype=np.float32)
        for i in range(natoms):
            traj_data[ts.frame-1,3*i]   = ts._x[i] * sqrt_mass[i]
            traj_data[ts.frame-1,3*i+1] = ts._y[i] * sqrt_mass[i]
            traj_data[ts.frame-1,3*i+2] = ts._z[i] * sqrt_mass[i]


#        traj_data[ts.frame-1]=temp_vect
        traj_ave += traj_data[ts.frame-1]

    traj_ave = traj_ave / nframes

    for i in range(nframes):
        delta_vect=[traj_data[i][j]-traj_ave[j] for j in range(3*natoms)]
        covar_mat += np.array(np.matrix(delta_vect).T * np.matrix(delta_vect))
    
#    covar_mat = covar_mat / ( nframes -1 )   # be careful!
    covar_mat = covar_mat / nframes

    TIME1=Time.time()
    print "\t Time used %6.2f s" %(TIME1 - BEGIN_TIME)


    print "step 3: Diagnoalizing the covariance matrix"
    eigenvalues,eigenvectors = np.linalg.eig(covar_mat)

    TIME2=Time.time()


    print "\t Time used %6.2f s" %(TIME2 - TIME1)

#    sys.exit()


    #step 3: get the number of classical mode eigenvalues.
#    eigenvalues=sorted(eigenvalues,reverse=True)
#    np.savetxt("eigen.xvg",eigenvalues)

    eigen_thr = 1e-6
    truncate_num = 0
    for i in range(3*natoms):
        if eigenvalues[i] < eigen_thr:
            truncate_num = i
            break
        elif eigenvalues[-1] > eigen_thr:
            truncate_num = 3*natoms
    print "\t Using %d eigenvalues to calculate entropy." %truncate_num


    print "step 4: Calculating the quasiharmonic entropy"
    global HBA
    global K
    global MP
    global R
    alpha_const  =HBA*(1e10)/math.sqrt(K*temperature*MP)
    eigval_class = eigenvalues[:truncate_num]
    eigvec_class = eigenvectors[:truncate_num]


    alpha     =[alpha_const/math.sqrt(eigval_class[i]) for i in range(truncate_num)]
    s_quantum =[alpha[i]/(math.exp(alpha[i])-1) - math.log(1-math.exp(-alpha[i])) for i in range(truncate_num)]
    num_class=0
    for i in range(truncate_num):
        if alpha[i] < 1:  # be careful to this value, which is 1 in nutama's program. As I think 1 is to large.
            num_class=i
        else:
            break
#    num_class=int(0.3*nframes)

    vector_eigS = np.zeros((nframes,num_class),dtype=np.float32)
    for i in range(nframes):
        delta_vect = [traj_data[i][j]-traj_ave[j] for j in range(3*natoms)]
        for j in range(num_class):
            vector_eigS[i,j] = np.matrix(eigvec_class[j]) * np.matrix(traj_data[i]).T /math.sqrt(eigval_class[j]) #be careful!
    temp_file="temp_filename"
#    np.savetxt("temp2",vector_eigS,fmt="%10.5f")
    fp=open(temp_file,'wb')
    for i in range(nframes):
        for j in range(num_class):
            data=struct.pack('d',vector_eigS[i,j])
            fp.write(data)
    fp.close()

    TIME3=Time.time()
    print "\t Time used %6.2f s" %(TIME3 - TIME2)
#    sys.exit()
    print "step 5: Calculating the anharmonic corrections"
#    s_RelativeGaussian = [(1+math.log(2*math.pi*eigval_class[i]))/2 for i in range(num_class)]
#    s_RelativeGaussian = [0.5*math.log(1+(math.e/alpha[i])**2) for i in range(num_class)]   #schltter
    s_RelativeGaussian = [-math.log(alpha[i])+0.5*math.log(2*math.pi*math.e) for i in range(num_class)]  #gaussian_1
#    s_RelativeGaussian = [-math.log(alpha[i])-1 for i in range(num_class)]   #classical_thermo
    Srescale           = [0.5*math.log(eigval_class[i])             for i in range(num_class)]
#    Srescale           = [math.log(eigval_class[i])                  for i in range(num_class)]

#    print "1D nearest-neighbor entropy for single modes (normalized, in nats): "
    s_kann_scale=[libentropical.kann("temp_filename", num_class,nframes,1,i,0) for i in range(num_class)]
    s_kann =[s_kann_scale[i] + Srescale[i] for i in range(num_class)]
    s_anharmonic=[s_RelativeGaussian[i]-s_kann[i] for i in range(num_class)]
    for i in range(num_class):
        #print "%5d  %10.5f  %10.5f  %10.5f" %(i,s_quantum[i],s_RelativeGaussian[i],Srescale[i]+s_kann[i])
        print "%5d  %10.5f  %10.5f  %10.5f  %10.5f" %(i,s_quantum[i],s_RelativeGaussian[i],s_kann[i],s_anharmonic[i])
    TIME4=Time.time()
    print "\t Time used %6.2f s" %(TIME4 - TIME3)

    print "step 6: Calculating mutual information corrections"
    mi=np.zeros((num_class,num_class),dtype=np.float32)
    for i in range(num_class):
        for j in range(i+1,num_class):
            if s_anharmonic[j]/s_quantum[j] > 0.000:
                mi[i,j]=s_kann_scale[i]+s_kann_scale[j]-libentropical.kann("temp_filename",num_class,nframes,2,i,j)
                if mi[i,j]<0 :
                    pass
            #        print "Warning: negative, but small M.I. for pair (%d, %d)" %(i,j)
            elif s_anharmonic[j]/s_quantum[j] < -0.1:
            #{// Test if nearest neighbor entropy is larger than Gaussian (theoretical maximum)
            #    print "Warning: negative and large Sanh. Mode pair (%d,%d) ignored for M.I. Time resolution may be too high or too low!" %(i,j)
                mi[i,j]=0.0
            #    //        s_anharmonic[j]=0.0;
            else :
                mi[i,j]= 0.0    #Mode is approximately harmonic. Do not calculate M.I.
                s_anharmonic[j]=0.0

    sum_s_quantum      = R * sum(s_quantum) /4186.8
    s_anharmonic_total = R * sum(s_anharmonic) /4186.8
    mi_total           = R * sum(sum(mi)) /4186.8

    if truncate_num<6:
        print "Warning. Only %d eigenvalue(s) were vanishing. This could indicate that \
        translation and rotation were not fully removed from the trajectory. A non-linear \
        molecule should have exactly 6 vanishing eigenvalues." %truncate_num 

    print "Entropies S in [kcal/(mol K)] and [Kcal/mol]"
    print " Frames:         %10d  " %(nframes)
    print " Squasiharmonic: %10.5f   %10.5f  " %(sum_s_quantum,temperature*sum_s_quantum)
    print " Sqh-Sanh:       %10.5f   %10.5f  " %(sum_s_quantum-s_anharmonic_total,temperature*(sum_s_quantum-s_anharmonic_total))
    print " Sqh-Sanh-MI:    %10.5f   %10.5f  " %(sum_s_quantum-s_anharmonic_total- mi_total,temperature*(sum_s_quantum-s_anharmonic_total- mi_total))
#    os.remove(temp_file)
#    print "delete file", temp_file


def Usage():
    print "Entro_Analysis.py -f <traj_file> -p <top_file> -t [temperature] -k [skip]"

def CheckArgs():
    if len(sys.argv) > 1:
        traj_file   =""
        top_file    =""
        temperature =300
        skip        =1
        opts,args=getopt.getopt(sys.argv[1:],"f:p:t:k:")
        for a,b in opts :
            if a =="-f":
                traj_file = b
            elif a == "-p":
                top_file = b
            elif a == "-t":
                temperature=int(b)
            elif a == "-k":
                skip = int(b)

        if os.path.isfile(traj_file) and os.path.isfile(top_file):
            Main_func(top_file,traj_file,temperature,skip)
    else:
        Usage()
        sys.exit()

if __name__=="__main__":
    QH_entro("traj-closest.pdb","permute.xtc","index.ndx")
#    CheckArgs()
