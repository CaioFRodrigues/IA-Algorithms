#ifndef INPUT
#define INPUT

#include <string>
#include <string.h>


//Algorithms IDs
#define BFS 0
#define IDFS 1
#define ASTAR 2
#define IDASTAR 3
#define GBFS 4


using namespace std;


//Given the input string, returns the ID for it
int getAlgorithmID(string input);

//Given argv, finds the first comma from the position given as an int
//Returns -1 if there's no comma
char getPuzzleLimit(int argc, char **argv, int pos);

//Given an array from argv, a size, and an already allocated char array, fills the state with the values from the array, converted to int;
void createState(char **array, int size, char *state);

//given a string, transforms its value into a char
char getCharValue(char *string);

int isCharDoubleDigit(char *string);

bool isSizeValid(int size);

#endif