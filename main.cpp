#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include <deque>

#include "puzzle.h"
#include "input.h"

char extern FINAL_STATE_8[9];
char extern FINAL_STATE_15[16];

char *bfs(char *init)
{
    if (isGoal(init))
    {
        return init;
    }
    return 0;
}


void callAlgorithm(int algID){
            switch (algID)
        {
        case BFS:
            cout << "Não implementado ainda";
            break;
        case IDFS:
            cout << "Não implementado ainda";
            break;

        case ASTAR:
            cout << "Não implementado ainda";
            break;

        case IDASTAR:
            cout << "Não implementado ainda";

            break;

        case GBFS:
            cout << "Não implementado ainda";
            break;

        default:
            cout << "Não implementado ainda";
            break;
        }
}


int main(int argc, char *argv[])
{
    PUZZLE_STATE initialState;

    deque<PUZZLE_STATE> open;
    initialState.state[0] = 1;
    initialState.h = 10;

    if (argc == 0)
    {
        cout << "Please insert argument in specified format";
        return -1;
    }

    string alg(argv[1]); //String has the type of algorithm used
    int algID = getAlgorithmID(alg);
    int inputPosition = 2;
    bool endOfInput = false;
    while (!endOfInput)
    {

        
        int nextPuzzleLimit = getPuzzleLimit(argc, argv, inputPosition); //nextPuzzleLimit always has the number for the end of 9 entries, not including the comma
        int puzzleSize = nextPuzzleLimit - inputPosition;


        if(!isSizeValid(puzzleSize)){
            cout << "Error - Wrong size";
            return -1;
        }
        
        char state[puzzleSize];
        createState(argv+inputPosition, puzzleSize, state);

        printState(state);
        
        if(argc == nextPuzzleLimit)
            endOfInput = true;

        inputPosition = nextPuzzleLimit + 1; //Skips comma
        
        
    }


}
