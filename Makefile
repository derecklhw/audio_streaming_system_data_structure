# This is the Makefile for creating the executable and test program

# This is the g++ compiler
CXX = g++

# This is the compiler links
CXXLINKS = -g -Wall -Wextra -Wpedantic

# This is the compiler flag
CXXFLAG = -c

# This are the objects dependencies file
OBJS = track.o hashTable.o

# Produce the executable
.PHONY: all
all : music_library

music_library : main.cpp $(OBJS)
	@echo "---------------------------------------"
	@echo "Creating the executable for the program"
	@echo "---------------------------------------"
	$(CXX) $(CXXLINKS) -o $@ $^

# Produce the test
.PHONY: test
test : testing

testing: testing.cpp $(OBJS)
	$(CXX) $(CXXLINKS) -o $@ $^

%.o : %.cpp
	@echo "---------------------------------------"
	@echo "Compiling the file $<"
	@echo "---------------------------------------"
	$(CXX) $(CXXLINKS) $(CXXFLAG) $<

# For clean up
.PHONY : clean 
clean :
	@echo "---------------------------------------"
	@echo "Clean up $<"
	@echo "---------------------------------------"
	$(RM) *.o
	$(RM) music_library
	$(RM) testing

# Dependencies chains
track.o : track.cpp track.h
hashTable.o  : hashTable.cpp hashTable.h





