
//
//  Board.cpp
//  BoggleSolver
//
//  Created by Aaron Coppa on 8/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
#include "Board.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "math.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"

//Two constructors... random generation versus user inputted build
Board::Board(int w, int h, int maxlength) {
    dict = new DictionaryTree();
    std::cout <<"Loading..." << '\n';
    MAXLENGTH = maxlength;
    width = w + 2;
    height = h + 2;
    board = new Tile[width * height];
    build();
    std::cout << "Done building...";
}
Board::Board(int w, int h, std::string, int maxlength) {
    dict = new DictionaryTree();

    std::cout <<"Loading..." << '\n'; 
    MAXLENGTH = maxlength;
    width = w + 2;
    height = h + 2;
    board = new Tile[width * height];
    buildRandom();
    std::cout << "Done building...";
}
//Build, but use random charecters....
void Board::buildRandom() {
    srand(time(NULL));
    char ch;
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            board[j*width + i].alive = false;   
            board[j*width + i].x = i;
            board[j*width + i].y = j;
        }
    }
    for(int i=1; i<width-1; i++) {
        
        for(int j=1; j<height-1; j++) {
            ch = (char) (rand() % 26 + 'a');
            board[j*width + i].name=ch;
            board[j*width + i].alive=true;
        }
    }
    for(int i = 1; i < width - 1; i++) {
        for(int j = 1; j < height - 1; j++) {
            findNeighbors(i, j);
        }
    }
}

void Board::build() {
    char ch;
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            board[j*width + i].alive = false;   
            board[j*width + i].x = i;
            board[j*width + i].y = j;
        }
    }
    //initted the array
    for(int i=1; i<width-1; i++) {
        
        for(int j=1; j<height-1; j++) {
            
            //Read in each charecter...
            while(true) {
                std::cin>>ch;
                if(isalpha(ch) != 0) {
                    break;
                }
            }
            board[j*width + i].name=ch;
            board[j*width + i].alive=true;
        }
    }
    //Then init the neighbors for each...
    for(int i = 1; i < width - 1; i++) {
        for(int j = 1; j < height - 1; j++) {
            findNeighbors(i, j);
        }
    }
}

void Board::print() {
    std::cout<<" "<<std::endl;
    for(int i = 1; i < height - 1; i++) {
        for(int j = 1; j < width - 1; j++) {
            std::cout<<board[i * width + j].name<<" ";
        }
        std::cout<<" "<<std::endl;
    }
    std::cout<<" "<<std::endl;
}
//For initting...
void Board::findNeighbors(int x, int y) {
    //Get all the board neighbors...
    board[y*width + x].neighbors[0] = &board[(y - 1) * width + x];
    board[y*width + x].neighbors[1] = &board[y * width + x + 1];
    board[y*width + x].neighbors[2] = &board[(y + 1) * width + x];
    board[y*width + x].neighbors[3] = &board[y * width + x - 1];
    board[y*width + x].neighbors[4] = &board[(y - 1) * width + x - 1];
    board[y*width + x].neighbors[5] = &board[(y - 1) * width + x + 1];
    board[y*width + x].neighbors[6] = &board[(y + 1) * width + x - 1];
    board[y*width + x].neighbors[7] = &board[(y + 1) * width + x + 1];
}
void Board::printNeighbors(int x, int y) {
    x += 1;
    y += 1;
    for(int i = 0; i < 8; i++) {
        if(board[y*width + x].neighbors[i]->alive) std::cout<<board[y*width + x].neighbors[i]->name;
    }
}
void Board::printSpaceUsed() {
    std::cout << "Printing used space by DictionaryTree..." << std::endl;
    dict->printSizeData();
}
//Check to see if we can prune...
bool Board::pruneable(std::string str) {
    return dict->prunable(str);
}
//Recursive function for sovling... uses curr and x,y to mark
//Position and string
void Board::solver(int x, int y) {
    //curr is a instance variable that has the current string
    if(dict->searchFor(curr)) {
        contents.insert(curr); //If its a word add it
    } 
    if(curr.size() < MAXLENGTH) { //Somewhat deprecated if, from when this was too slow
        if(!pruneable(curr)){ //Prunes if we are too far
            board[y * width + x].alive = false;
            std::string hold = curr;
            curr.append(&board[y * width + x].name);
            //Loop through each possible neighbor
            for(int i = 0; i < 8; i++) {
                if(board[y * width + x].neighbors[i]->alive) {
                    solver(board[y * width + x].neighbors[i]->x,board[y * width + x].neighbors[i]->y); 
                }
            }
            //Reset after the recursion...
            curr = hold;
            board[y * width + x].alive = true;
        }
    }
}
//Will solve using initted board
void Board::solve() {
    std::cout << "Getting ready to start algorithm..." << std::endl;
    std::cout<<"Starting clock and going!"<<std::endl;
    t1 = clock(); //Start clocking...
    for(int i = 1; i < width - 1; i++) { 
        for(int j = 1; j < height - 1; j++) {
            //START WITH EACH LETTER         
            //std::cout << "Doing letter: " << i * height + j << std::endl;
            solver(i, j);     
        }
    }
    t2 = clock(); //Stop clocking...
    std::cout << "Clock stopped. Printing words found..." << std::endl;
    std::set<std::string>::iterator it;
        for(it = contents.begin(); it!=contents.end(); it++) {
            std::string str = *it;
            if(str.size() > 2) std::cout<<*it<<std::endl;
        }
    //Calculate the time...
    float diff = ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    std::cout<<"Total time elapsed: " << seconds << " seconds" << "\n";
}
