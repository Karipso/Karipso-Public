binary_search_tree: main.o anil_binary_search_tree.o
	g++ main.o anil_binary_search_tree.o -o binary_search_tree

main.o: main.cpp
	g++ -c -g -std=c++11 main.cpp

anil_binary_search_tree.o: anil_binary_search_tree.cpp anil_binary_search_tree.h
	g++ -c -g -std=c++11 anil_binary_search_tree.cpp

clean:
	rm *.o binary_search_tree binary_search_tree_log.txt