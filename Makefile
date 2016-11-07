CXXFLAGS += -g -Wall -std=c++14 -Wshadow
CXX = g++

test: geometry.o test.o 
	$(CXX) $(CXXFLAGS) $^ -o $@
geometry.o: geometry.cc geometry.h
	$(CXX) $(CXXFLAGS) -c $<
test.o: test.cc
	$(CXX) $(CXXFLAGS) -c $<
	
	
