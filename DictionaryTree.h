//
//  DictionaryTree.h
//  BoggleSolverTree
//
//  Created by Aaron Coppa on 2/17/13.
//  Copyright (c) 2013 Aaron Coppa. All rights reserved.
//

#ifndef BoggleSolverTree_DictionaryTree_h
#define BoggleSolverTree_DictionaryTree_h
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>

class DictionaryTree {
    private:
    int hash(char c);
    struct node {
            bool word;
            char let;
            node * next[26];
            // bool exist = false;
    };
    void loadDictionary();
    void printContentsHelp(std::string & str, node * a);
    void loadNode(std::string & string, int currChar, node * a);
    node * head[26];
    bool searchHelp(std::string & str, int currChar, node * a);
    bool prunableHelp(std::string str, int currChar, node * a);
    void freeTreeFromNode(node * a);
    public:
    long size;
    long entries;
    void printContents();
    void printSizeData();
    bool searchFor(std::string str);
    bool prunable(std::string str);
    void freeTree();
    DictionaryTree();
};



#endif
