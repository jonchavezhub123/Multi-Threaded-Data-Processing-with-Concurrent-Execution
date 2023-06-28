#
# PROGRAM: Lab Training Exercise
# AUTHOR:  Jonathan Chavez
#

CXXFLAGS = -Wall -Werror -std=c++11

z1866268_project4: z1866268_project4.o
	g++ $(CXXFLAGS) -o z1866268_project4 z1866268_project4.o -lpthread

z1866268_project4.o: z1866268_project4.cc
	g++ $(CXXFLAGS) -c z1866268_project4.cc

clean:
	rm -f *.o z1866268_project4
