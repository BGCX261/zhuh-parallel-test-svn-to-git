XDRINCLUDE = /home/zhuh/xdrfile/include/xdrfile
XDRLIB = /home/zhuh/xdrfile/lib
USR_PATH = /home/zhuh/bin/
g_pig_gmx : main.o m_f.o matrix.o pdb.o read_ndx.o read_xtc.o string_operate.o structure.o read_trr.o
	g++ -o ../bin/g_pig_gmx main.o m_f.o matrix.o pdb.o read_ndx.o read_xtc.o read_trr.o string_operate.o structure.o  -lxdrfile -L${XDRLIB}
main.o : main.cpp matrix.h read_xtc.h
	g++ -I${XDRINCLUDE} -c main.cpp
m_f.o : m_f.cpp m_f.h
	g++ -c m_f.cpp
matrix.o :  matrix.cpp matrix.h 
	g++ -c matrix.cpp
pdb.o : pdb.cpp pdb.h
	g++ -c pdb.cpp
read_ndx.o : read_ndx.cpp read_ndx.h
	g++ -c read_ndx.cpp
read_xtc.o : read_xtc.cpp read_xtc.h
	g++ -I${XDRINCLUDE} -c read_xtc.cpp
read_trr.o : read_trr.cpp read_trr.h
	g++ -I${XDRINCLUDE} -c read_trr.cpp
string_operate.o : string_operate.cpp string_operate.h
	g++ -c string_operate.cpp
structure.o : structure.cpp structure.h 
	g++ -c structure.cpp
clean:
	rm main.o m_f.o matrix.o pdb.o read_ndx.o read_xtc.o string_operate.o structure.o read_trr.o
install :
	cp ../bin/g_pig_gmx ${USR_PATH}
