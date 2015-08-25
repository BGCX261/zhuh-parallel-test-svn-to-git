#!/usr/bin/env python
import sys
import os
import re
import getopt
import math
import numpy 



def Check_args():
    if len(sys.argv)==1:
        Usage()
        sys.exit()
    else:
        filename=sys.argv[1]
        column=1
        begin_row=0
        end_row=-1
        rebuild=False
        if len(sys.argv)>2:
            try:
                opts,args=getopt.getopt(sys.argv[2:],"n:b:e:",["rebuild"])
            except getopt.GeeoptError,e:
                print e
                sys.exit()
            for a,b in opts:
                if a=="-n":
                    column=int(b)
                elif a=="-b":
                    begin_row=int(b)
                elif a=="-e":
                    end_row=int(b)
                elif a=="--rebuild":
                    rebuild=True
                 
        data=numpy.genfromtxt(filename)

        if rebuild==True:
            Rebuild(data[begin_row:end_row],column)
        else:
            Average,err=Get_average(data[begin_row:end_row,column-1])
            print "%8.4f  +/-  %8.4f" %(Average,err)

    


def Usage():
    print "Usage: Average.py filename [-n column] [-b begin_row] [-e end_row] [--rebuild]"


def Get_average(data):
    NUM=len(data)
    err=0.0
    Average=numpy.average(data)
    for aa in data:
        err=err+(Average-aa)**2
    err=math.sqrt(err/NUM)
    return Average,err

def Rebuild(data,column):
    Average,err=Get_average(data[:,column-1])
    new_data=list()
    (a,b)=numpy.shape(data)
#    print a,b
    for i in range(a):
        if abs(data[i,column-1]-Average) > err:
            pass
        else:
            new_data.append(data[i])

    new_data=numpy.array(new_data)
#    print new_data
#    print type(new_data)
    (a,b)=numpy.shape(new_data)
    for i in range(b):
        Average,err=Get_average(new_data[:,i])
        print "%10.4f  +/-  %8.4f" %(Average,err)


if __name__=="__main__":
    Check_args()

    
