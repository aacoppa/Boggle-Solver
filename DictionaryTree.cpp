//
//  DictionaryTree.cpp
//  BoggleSolverTree
//
//  Created by Aaron Coppa on 2/17/13.
//  Copyright (c) 2013 Aaron Coppa. All rights reserved.
//

#include "DictionaryTree.h"


//return array index of different letters 'a' = 0, etc...
int DictionaryTree::hash(char c) {
    return (c - 19) % 26; 
}
DictionaryTree::DictionaryTree() {
    loadDictionary();
}
//Build up the tree from text file
void DictionaryTree::loadDictionary() {
    for(char a = 'a'; a <= 'z'; a++) {
        size += sizeof(node);
        head[hash(a)] = new node;
        head[hash(a)]->let = a;
        head[hash(a)]->word = false;
        //   head[hash(a)]->exist = true;
        //   for(int i = 0; i < 26; i++)
        //       head[hash(a)]->next[i] = new node;
    }

    std::ifstream myFile;
    myFile.open("data/dictionary.txt");
    if(myFile.is_open()) {
        while(!myFile.eof()) {
            std::string line;
            getline(myFile, line);
            for(int i = 0; i < line.size(); i++){
                line[i] = tolower(line[i]);
            }
            //Can't deal with weird charecters...
            if(line.find(" ") != std::string::npos ||
               line == "\n") continue;
            if(line.find("-") != std::string::npos) continue;
            entries++;
            //then load up a node
            if(line != "") loadNode(line,0, head[hash(line[0])]);
        }
    }
}
void DictionaryTree::printSizeData() {
    std::cout << "Entries: " << entries << "\n";
    std::cout << "Size: " << size << " bytes" << "\n";
}
//Loading node
void DictionaryTree::loadNode(std::string & string, int currChar, node * a) {
    //Set the current nodes letter
    a->let = string[currChar];
    if(currChar == string.size() - 1) {
        //if the word is done, then set word var to true and return
        a->word = true;
        return;
    }
    int val = hash(string[currChar + 1]); //Array index...
    //If node isnt made yet
    if(a->next[val] == NULL) {
        size += sizeof(node);
        a->next[val] = new node;
        //a->next[val]->let = string[currChar];
        a->next[val]->word = false;
    }
    //Else just go one deeper
    DictionaryTree::loadNode(string, currChar + 1, a->next[val]);
}
bool DictionaryTree::searchHelp(std::string & str, int currChar, node * a) {
    if(currChar == str.size() - 1) {
        //Here we are at the finishing node
        return a->word;
    }
    //Else go deeper
    int val = hash(str[currChar + 1]);
    if( a->next[val] == NULL) return false; //There ain't no word here
    return DictionaryTree::searchHelp(str, currChar + 1, a->next[val]);
}
//Similar to search but not checking for word, instead returning false
//Whenever the string doesn't exist in dictionary, return true, else
//Return false
bool DictionaryTree::prunableHelp(std::string str, int currChar, node * a) {
    if(currChar == str.size() - 1) return false;
    int val = hash(str[currChar + 1]);
    if( a->next[val] == NULL) return true;
    return DictionaryTree::prunableHelp(str, currChar + 1, a->next[val]);
}
void DictionaryTree::printContents() {
    for(char * ch = new char('a'); *ch <= 'z'; (*ch)++) {
        std::string str = "";
        str.append(ch);
        DictionaryTree::printContentsHelp(str, head[hash(*ch)]);
    }
}
//Recursively print dictionary...
void DictionaryTree::printContentsHelp(std::string & str, node * a) {
    if(a->word) std::cout << str << std::endl;
    for(char * ch = new char('a'); *ch <= 'z'; (*ch)++) {
        if(a->next[hash(*ch)] == NULL) continue;
        std::string hold = str;
        str.append(ch);
        DictionaryTree::printContentsHelp(str, a->next[hash(*ch)]);
        str = hold;
    }
}
bool DictionaryTree::prunable(std::string str) {
    if(str == "") return false;
    return prunableHelp(str, 0, head[hash(str[0])]);
}
bool DictionaryTree::searchFor(std::string str) {
    if(str == "") return false;
    return searchHelp(str, 0, head[hash(str[0])]);
}
void DictionaryTree::freeTreeFromNode(node * a) {
   if(a == NULL) return;
   for(char * ch = new char('a'); *ch <= 'z'; (*ch)++) {
       freeTreeFromNode(a->next[hash(*ch)]);
       free(a->next[hash(*ch)]);
   }
}
void DictionaryTree::freeTree() {
    for(char * ch = new char('a'); *ch <= 'z'; (*ch)++) {
    freeTreeFromNode(head[hash(*ch)]);
    }
}
