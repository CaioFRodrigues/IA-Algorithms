#ifndef ALGORITHMSH
#define ALGORITHMSH

#include <deque>
#include <unordered_set>
#include <chrono>

#include "puzzle.h"

struct cmpGBFS {
    bool operator() (PUZZLE_STATE a, PUZZLE_STATE b) const {
        return a.h <= b.h;
    }
};

struct cmpASTAR {
    bool operator() (PUZZLE_STATE a, PUZZLE_STATE b) const {
        if (a.h + a.g == b.h + b.g)
            return a.h <= b.h;
        else 
            return a.h + a.g < b.h + b.g;
    }
};


// Algorithms implemented
int bfs(char *init);
int idfs(char *init);
int astar(char *init, int puzzleSize);
int gbfs(char *init, int puzzleSize);
int idastar(char *init);
tuple<int,PUZZLE_STATE> recursiveSearch(PUZZLE_STATE node, int limit);


#endif
