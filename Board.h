//
//  Board.h
//  BoggleSolver
//
//  Created by Aaron Coppa on 8/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BoggleSolver_Board_h
#define BoggleSolver_Board_h
#include <set>
#include <vector>
#include "time.h"
#include "DictionaryTree.h"
class Board {
private:
    DictionaryTree * dict;
    void build();
    int MAXLENGTH;
    std::set<std::string> contents;
    std::vector<std::string> dictionary;
    std::vector<std::string> prunelist;
    std::vector<std::string> prunelist12;
    bool contains(std::string key, int min, int max);
    void solver(int x, int y);
    void findNeighbors(int x, int y);
    std::string curr;
    void load();
    void buildRandom();
    bool prune(std::string test, int max, int min);
    bool prune12(std::string test, int max, int min);
    bool pruneLinear(std::string test);
    bool pruneable(std::string str);
    clock_t t1, t2;
public:
    int width;
    int height;
    struct Tile {
        int xCor;
        int yCor;
        int x;
        int y;
        char name;
        bool alive;
        Tile * neighbors[8];
    };
    Board(int w, int h, int maxlength = 25);
    Board(int w, int h, std::string me, int maxlength = 25);
    void printSpaceUsed();
    void print();
    void solve();
    void printNeighbors(int x, int y);
    void display(Board::Tile * tile, float a = 1);
    void boardDisplay();
    Tile *board;
    private:
    //void reCor(Tile & tile); 


};


#endif
