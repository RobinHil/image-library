CXX		 = g++
CFLAGS = -g -Wall
CXXFLAGS = $(CFLAGS) -std=c++17
RM		 = rm -f
EXE		 = 

EXEC = main
EXECSPP = $(EXEC)$(EXE)

all :: $(EXECSPP)

$(EXECSPP) : $(EXEC).o GrayImage.o
	$(CXX) $(CXXFLAGS) -o $(EXECSPP) $(EXEC).o GrayImage.o

$(EXEC).o : $(EXEC).cpp GrayImage.hpp
	$(CXX) $(CXXFLAGS) -c $(EXEC).cpp

GrayImage.o : GrayImage.cpp GrayImage.hpp
	$(CXX) $(CXXFLAGS) -c GrayImage.cpp

clean ::
	-$(RM) *.o core

distclean :: clean
	-$(RM) $(EXECSPP)