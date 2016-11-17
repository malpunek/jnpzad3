CXXFLAGS += -g -Wall -std=c++14 -Wshadow
CXX = g++

test: geometry.o test.o 
	$(CXX) $(CXXFLAGS) $^ -o $@
geometry.o: geometry.cc geometry.h
	$(CXX) $(CXXFLAGS) -c $<
test.o: test.cc geometry.h
	$(CXX) $(CXXFLAGS) -c $<
	
test_forum: geometry.o test_forum.o
	$(CXX) $(CXXFLAGS) $^ -o $@
test_forum.o: test_forum.cc geometry.h
	$(CXX) $(CXXFLAGS) -c $<
