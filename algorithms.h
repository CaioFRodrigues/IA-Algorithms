#ifndef ALGORITHMSH
#define ALGORITHMSH

#include <deque>
#include <unordered_set>
#include <chrono>

#include "puzzle.h"

 struct cmp {
    bool operator() (PUZZLE_STATE a, PUZZLE_STATE b) const {
        return a.h < b.h;
    }
};

// Algorithms implemented
int bfs(char *init);
int idfs(char *init);
// int depthLimitedSearch(char *init, char *father, int depthLimited);
int astar(char *init, int puzzleSize);


#endif
