CXX		 = g++
CFLAGS   = -g -Wall
CXXFLAGS = $(CFLAGS) -std=c++17
RM		 = rm -rf
EXE		 = 

EXEC = main
EXECSPP = $(EXEC)$(EXE)

all :: $(EXECSPP)

$(EXECSPP) : $(EXEC).o Image.o
	$(CXX) $(CXXFLAGS) -o $(EXECSPP) $(EXEC).o Image.o

$(EXEC).o : $(EXEC).cpp Image.hpp
	$(CXX) $(CXXFLAGS) -c $(EXEC).cpp

Image.o : Image.cpp Image.hpp
	$(CXX) $(CXXFLAGS) -c Image.cpp

clean ::
	-$(RM) *.o core

distclean :: clean
	-$(RM) $(EXECSPP) data/tests/GrayImage/* data/tests/ColorImage/* documentation