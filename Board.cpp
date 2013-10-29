
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
//#include "DictionaryTree.h"
#include "math.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"

Board::Board(int w, int h, int maxlength) {
    dict = new DictionaryTree();
    std::cout <<"Loading..." << '\n';
    MAXLENGTH = maxlength;
    width = w + 2;
    height = h + 2;
    board = new Tile[width * height];
    load();
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
    load();
    buildRandom();
    std::cout << "Done building...";
}
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
            //Here we draw the last letter before moving on
            //std::cout<<board[i][j].name+" ";
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
    for(int i=1; i<width-1; i++) {
        
        for(int j=1; j<height-1; j++) {
            
            //board[i][j].name=std::
            while(true) {
                std::cin>>ch;
                if(isalpha(ch) != 0) {
                    break;
                }
            }
            board[j*width + i].name=ch;
            board[j*width + i].alive=true;
            //Here we draw the last letter before moving on
            //std::cout<<board[i][j].name+" ";
        }
        //std::cout<<"\n";
    }
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
void Board::load() {
    std::ifstream myFile, myFile2, myFile3;
    myFile.open("data/dictionary.txt");
    if(myFile.is_open()) {
        while(!myFile.eof()) {
            std::string line;
            getline(myFile, line);
            dictionary.push_back(line);
        }
        myFile.close();
    }
    myFile2.open("data/prunelist4.txt");
    if(myFile2.is_open()) {
        while(!myFile2.eof()) {
            std::string line;
            getline(myFile2, line);
            prunelist.push_back(line);
        }
        myFile2.close();
    }
    myFile3.open("data/prunelist12.txt");
    if(myFile3.is_open()) {
        while(!myFile3.eof()) {
            std::string line;
            getline(myFile3, line);
            prunelist12.push_back(line);
        }
        myFile3.close();
    }
}
void Board::findNeighbors(int x, int y) {
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
bool Board::contains(std::string key, int min, int max) {
    int half;
    half = (max + min) / 2;
    //std::cout<<half<<std::endl;
    if(key == dictionary[half]) return true;
    if(max - min < 2) return false;
    if(key > dictionary[half] ) {
        return contains(key, half + 1, max);
    }
    else {
        return contains(key, min, half - 1);
    }
    
}
/*bool Board::prune(std::string test, int min, int max) {
    int half;
    half = (max + min) / 2;
    //std::cout<<half<<std::endl;
    if(test == prunelist[half]) return true;
    if(max - min < 2) return false;
    if(test > prunelist[half] ) {
        return prune(test, half + 1, max);
    }
    else {
        return prune(test, min, half - 1);
    }
    return false;  
}
bool Board::prune12(std::string test, int min, int max) {
    int half;
    half = (max + min) / 2;
    if(test == prunelist12[half]) return true;
    if(max - min < 2) return false;
    if(test > prunelist12[half] ) {
        return prune12(test, half + 1, max);
    }
    else {
        return prune12(test, min, half - 1);
    }
    return false;  
}
bool Board::pruneLinear(std::string test) {
    for(int i = 0; i < prunelist.size(); i++) {
        if(test.find(prunelist[i])!=std::string::npos) return true;
    }
    return false;  
}*/
bool Board::pruneable(std::string str) {
    return dict->prunable(str);
}
void Board::solver(int x, int y) {
   // std::cout<<curr.size()<<std::endl;
   //s std::cout<<curr<<std::endl;
    if(dict->searchFor(curr)) {
        contents.insert(curr);
    } 
    if(curr.size() < MAXLENGTH) {
        std::string holder;
        if(curr.size() > 4) {
            holder = curr.substr(curr.size() - 4, 4); 
        } else {
            holder = curr;
        }
        /*if(curr.size() >= 12) {
            std::cout<<"ASD"<<std::endl;
            std::string a = curr.substr(0, 12); 
            if(!prune12(a, 0, prunelist12.size())) return;
        }*/
        if(!pruneable(holder)){
            board[y * width + x].alive = false;
            std::string hold = curr;
            curr.append(&board[y * width + x].name);
            for(int i = 0; i < 8; i++) {
                if(board[y * width + x].neighbors[i]->alive) {
                    solver(board[y * width + x].neighbors[i]->x,board[y * width + x].neighbors[i]->y); 
                }
            }
            curr = hold;
            board[y * width + x].alive = true;
        }
    }
}
void Board::solve() {
    std::cout<<"Starting clock..."<<std::endl;
    t1 = clock();
    for(int i = 1; i < width - 1; i++) {
        
        for(int j = 1; j < height - 1; j++) {
            //START WITH EACH LETTER 
            
            solver(i, j);     
        }
    }
    t2 = clock();
    std::cout << "Clock stopped. Printing words found..." << std::endl;
    std::set<std::string>::iterator it;
        for(it = contents.begin(); it!=contents.end(); it++) {
            std::string str = *it;
            if(str.size() > 2) std::cout<<*it<<std::endl;
        }
    float diff = ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    std::cout<<"Total time elapsed: " << seconds << " seconds" << "\n";
    //std::cout<<"Done";
}
