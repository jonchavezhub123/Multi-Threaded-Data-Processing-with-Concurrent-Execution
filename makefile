#
# PROGRAM: Lab Training Exercise
# AUTHOR:  Jonathan Chavez
#

CXXFLAGS = -Wall -Werror -std=c++11

multi_threads: multi_threads.o
	g++ $(CXXFLAGS) -o multi_threads multi_threads.o -lpthread

multi_threads.o: multi_threads.cc
	g++ $(CXXFLAGS) -c multi_threads.cc

clean:
	rm -f *.o multi_threads
