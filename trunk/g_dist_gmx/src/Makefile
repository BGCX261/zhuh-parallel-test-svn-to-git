HEAD=/home/zhuh/xdrfile/include/xdrfile/
LIB=/home/zhuh/xdrfile/lib/

g_dist_gmx : main.o function.o read_ndx.o read_pdb.o read_xtc.o string_operate.o
	g++ main.o function.o read_ndx.o read_pdb.o read_xtc.o string_operate.o -o ../bin/g_dist_gmx -lxdrfile -L${LIB}
fucntion.o : function.cpp function.h
	g++ -c function.cpp
read_ndx.o : read_ndx.cpp read_ndx.h
	g++ -c read_ndx.cpp
read_pdb.o :  read_pdb.cpp read_pdb.h string_operate.h
	g++ -c read_pdb.cpp
read_xtc.o :  read_xtc.cpp read_xtc.h function.h
	g++ -I${HEAD} -c read_xtc.cpp
string_operate.o : string_operate.cpp string_operate.h
	g++ -c string_operate.cpp
main.o : main.cpp
	g++ -I${HEAD} -c main.cpp

clean:
	rm *.o -f
