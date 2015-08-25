USR_PATH = /home/zhuh/bin

Distribution : main.o m_f.o
	g++ -o ../bin/Distribution main.o m_f.o
main.o : main.cpp
	g++ -c main.cpp 
m_f.o : m_f.cpp m_f.h constants.h
	g++ -c m_f.cpp
clean :
	rm m_f.o main.o
install :
	cp ../bin/Distribution ${USR_PATH}
