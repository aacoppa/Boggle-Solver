//
//  main.cpp
//  BoggleSolver
//
//  Created by Aaron Coppa on 8/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
#include "Board.h"
int main(int argc, char * argv[])
{
    std::cout << "Starting up testing functions..." << '\n';
    std::cout << "First running on a randomly created board" << '\n';
    Board board(5, 5, "Str", 10000);
    board.print();
    std::cout << "Solving and printing words..." << '\n';
    board.solve();
    return 0;
}



