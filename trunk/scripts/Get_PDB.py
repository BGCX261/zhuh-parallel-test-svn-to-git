#!/usr/bin/env python
'''
Created on 2011-04-02.\n
@version: 0.1.0

'''

import sys
import os
import urllib
import datetime

def download(pdb_name):
    url="http://www.rcsb.org/pdb/files/"
    url_total=url+pdb_name
    try:
        print "try downloading file %s..." %pdb_name
        starttime =  datetime.datetime.now()
#        urllib.urlretrieve(url_total,pdb_name)
        os.system("wget %s" %url_total)
        endtime =  datetime.datetime.now()
        print 'you download the file use time %s s' % (endtime - starttime).seconds

    except:
        print "download failure"

def Checkargs():
    if len(sys.argv) == 2:
        download(sys.argv[1])
    else:
        Usage()


def Usage():
    print "Usage: Get_PDB.py <pdb_file>"

if __name__ =="__main__":
    Checkargs()
