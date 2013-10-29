main: main.cpp Board.o
	g++ main.cpp Board.o DictionaryTree.o
	make clean
Board.o: Board.cpp Board.h DictionaryTree.o
	g++ -c Board.cpp DictionaryTree.o
DictionaryTree.o: DictionaryTree.cpp DictionaryTree.h
	g++ -c DictionaryTree.cpp
clean:
	rm *.o
