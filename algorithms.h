#ifndef ALGORITHMSH
#define ALGORITHMSH

#include <deque>
#include <unordered_set>
#include <chrono>

#include "puzzle.h"

// Algorithms implemented
int bfs(char *init);
int idfs(char *init);
// int depthLimitedSearch(char *init, char *father, int depthLimited);
int idfs(char *init);

#endif
