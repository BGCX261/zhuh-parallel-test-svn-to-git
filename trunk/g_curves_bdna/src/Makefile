XDRLIB=/home/zhuh/xdrfile/lib 
INCLUDEXDR=/home/zhuh/xdrfile/include/xdrfile/ 
SOURCE=main.o matrix.o m_f.o pdb.o read_ndx.o read_xtc.o string_operate.o structure.o
g_curves_bdna : ${SOURCE}
	g++    -o ../bin/g_curves_bdna  ${SOURCE} -L${XDRLIB} -lxdrfile
main.o : main.cpp
	g++    -c main.cpp -I${INCLUDEXDR} 
matrix.o : matrix.cpp matrix.h
	g++    -c matrix.cpp
read_xtc.o : read_xtc.cpp read_xtc.h
	g++    -c read_xtc.cpp read_xtc.h -I${INCLUDEXDR}
install:
	cp ../bin/g_curves_bdna /home/zhuh/bin/
clean: 
	rm *.o 
