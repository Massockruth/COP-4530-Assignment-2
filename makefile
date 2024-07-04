#Ruth Massock
#06/24/2024
#Assignment 2
all:
	g++ -std=c++11 -c test_list.cpp
	 List.h
	g++ -std=c++11 test_list.o -o proj2.x
clean:
	rm *.h.gch *.x *.o 
