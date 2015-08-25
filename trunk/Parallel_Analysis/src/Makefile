#XDRINCLUDE = /usr/local/xdrfile/include/xdrfile
#XDRLIB = 
#USR_PATH = /home/zhuh/bin/
CXXFLAGS := -I/usr/local/xdrfile/include/xdrfile
LDFLAGS  :=	-O2 -lxdrfile -L/usr/local/xdrfile/lib

SRCDIRS :=./src

CXX		= g++

EXEC=Parallel_Analysis

OBJECTS = \
		main.o m_f.o matrix.o pdb.o \
		read_xtc.o string_operate.o \
		structure.o 
		

$(EXEC): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LIBRARIES) $(LDFLAGS)

#install :
#	cp ../bin/g_pig_gmx ${USR_PATH}


# Rules for creating the dependency files (.d).
#---------------------------------------------------
%.d : %.c
	@$(CC) -MM -MD $(CFLAGS) $<

%.d : %.C
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.cc
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.cpp
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.CPP
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.c++
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.cp
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.cxx
	@$(CC) -MM -MD $(CXXFLAGS) $<

# Rules for producing the objects.
#---------------------------------------------------
objs : $(OBJS)

%.o : %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $<

%.o : %.C
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

%.o : %.cc
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

%.o : %.cpp
	$(CXX) -c -O2 $(CPPFLAGS) $(CXXFLAGS) $<

%.o : %.CPP
	$(CXX) -c -O2 $(CPPFLAGS) $(CXXFLAGS) $<

%.o : %.c++
	$(CXX -c $(CPPFLAGS) $(CXXFLAGS) $<

%.o : %.cp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

%.o : %.cxx
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

# Rules for producing the executable.
#----------------------------------------------
$(PROGRAM) : $(OBJS)
ifeq ($(strip $(SRCEXTS)), .c) # C file
	$(CC) -o $(PROGRAM) $(OBJS) $(LDFLAGS)
else # C++ file
	$(CXX) -o $(PROGRAM) $(OBJS) $(LDFLAGS)
endif

-include $(DEPS)

rebuild: clean all

clean :
	@$(RM) *.o *.d

cleanall: clean
	@$(RM) $(PROGRAM) $(PROGRAM).exe

install:
	cp Parallel_Analysis ~/bin/
