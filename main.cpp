//Super fast Boggle-Solver
#include <iostream>
#include <string>
#include "Board.h"
int main(int argc, char * argv[])
{
    std::cout << "Starting up testing functions..." << '\n';
    std::cout << "First running on a randomly created board" << '\n';
    //Change the first two numbers... Can be as big as you want and will
    //still run in reasonable time!!!
    Board board(10, 10, "Str", 10000); //Change this line to do what you want!!!!
    board.print();
    board.solve();

    //board.printSpaceUsed(); //Decomment to see size of TreeDictionary
    return 0;
}



