Boggle-Solver
=============

A program that finds all the words in a Boggle board of ANY SIZE...
Optimized via a multitude of methods to run EXTREMELY FAST:

For a ten by ten board it averages .1 seconds

However, a large amount of space is used... To see how much call
Board.printSpaceUsed();

1. A O(length of word) search time through a dictionary of over 20,000 words
    This is done using a search tree where every node is a letter, and its traversal
    makes a string. Each node is either a word or not a word, and has an array of 26
    nodes, one for each letter that could possibly follow it. Thus on searches, a traversal
    that reaches a null node returns false.
        For example, we are searching for "artzp"
        First we jump from the root to the 'a' node
        From that node we jump to the 'a' node's r node, which is not
        null because there are many words that start with 'ar'
        This continues on until the 'p' node is reached. The 'p' node
        will be null because there are no words that start with "artzp"
        Therefore we just found that the word didn't exist in O("artzp".size()).

2. A pruning technique 
    Using our DictionaryTree we can prune every combination of letters
    checking to see if there are any words that start with the current string.
    This is very similar to the search, but we check to see if the node is null,
    not whether the word field of the node is true

Replace dictionary.txt with any dictionary you want to get rid of some awkward
words.
Have faith! A lot of the words found don't seem like words, but if you check, they're
in the dictionary.

To input your own BoggleBoard change the arguments in main.c from:
Board board(5, 5, "str", 25);
to:
Board board(numColumns, numRows, numColumns * numRows);
//The str input makes the board create itself instead of asking for user input
