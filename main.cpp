#include <vector>
#include <iostream>
#include <string>
#include <string.h>

#include "algorithms.h"
#include "puzzle.h"
#include "input.h"

void callAlgorithm(int algID, char* init, int puzzleSize) {
    switch (algID)
    {
        case BFS:
            bfs(init);
            break;

        case IDFS:
            idfs(init);
            break;

        case ASTAR:
            astar(init, puzzleSize);
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

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "Please insert argument in specified format";
        return -1;
    }

    string alg(argv[1]);    //String has the type of algorithm used
    int algID = getAlgorithmID(alg);
    int inputPosition = 2;
    bool endOfInput = false;
    while (!endOfInput) {
        int nextPuzzleLimit = getPuzzleLimit(argc, argv, inputPosition);    //nextPuzzleLimit always has the number for the end of 9 entries, not including the comma
        int puzzleSize = nextPuzzleLimit - inputPosition;

        if(!isSizeValid(puzzleSize)) {
            cout << "Error - Wrong size";
            return -1;
        }
        
        char state[puzzleSize];
        createState(argv+inputPosition, puzzleSize, state);
        callAlgorithm(algID, state, puzzleSize);
        //cout << heuristic(makeNode(state, getPuzzleRoot(puzzleSize)), getPuzzleRoot(puzzleSize));

        if(argc == nextPuzzleLimit)
            endOfInput = true;

        inputPosition = nextPuzzleLimit + 1; //Skips comma
    }

    return 1;
}
