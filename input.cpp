

#include "input.h"
#include <iostream>

//Given the input string, returns the ID for it
int getAlgorithmID(string input)
{
    if (input.compare("-bfs"))
        return BFS;
    else if (input.compare("-idfs"))
        return IDFS;
    else if (input.compare("-astar"))
        return ASTAR;
    else if (input.compare("-idastar"))
        return IDASTAR;
    else if (input.compare("-gbfs"))
        return GBFS;

    return -1;
}

//Given argv, finds the first comma from the position given as an int
//Returns -1 if there's no comma
char getPuzzleLimit(int argc, char **argv, int pos)
{
    int i;
    for (i = pos; i < argc; i++)
    {  
        
        if (argv[i][0] == ',')
        {
            return i;
        }
    }
    return i;
}

//Given an array from argv, a size, and an already allocated char array, fills the state with the values from the array, converted to int;
void createState(char **array, int size, char *state)
{
    for(int i = 0; i < size; i++){
        state[i] = getCharValue(array[i]);
    }
}

//given a string, transforms its value into a char
char getCharValue(char *string){
    if(!isCharDoubleDigit(string))
        return (*string) - 48;
    
    char secondDigit = string[1];
    return secondDigit - 38;

}


int isCharDoubleDigit(char *string){
    if(string[1] == '\0')
        return 0;
    else return 1;
}

bool isSizeValid(int size){
    if (size == 9 || size == 16)
        return true;
    else return false;
}
