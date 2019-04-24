
#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include "puzzle.h"

char FINAL_STATE_8[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
char FINAL_STATE_15[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

bool isGoal(char *state) {
    return memcmp(state, FINAL_STATE_8, sizeof(FINAL_STATE_8)) == 0;
}

bool compareState(char *state, char *state2) {
    if (state2 == NULL || state == NULL) return false;
    return memcmp(state, state2, sizeof(state2)) == 0;
}

void printState(char* state) {
    if (state == NULL) {
        printf("NULL");
        return;
    }
    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", state[j + i * 3]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}


// given a state and heuristic value, return the puzzle state with this information
PUZZLE_STATE makeNode(char* state, int puzzleRoot) {
    PUZZLE_STATE puzzleState;
    memcpy(puzzleState.state, state, sizeof(puzzleState.state));
    puzzleState.h = heuristic(puzzleState, puzzleRoot);
    puzzleState.g = 0;
    return puzzleState;
}




// given the actual state, a movement and the blank position, return the new state after the movement
bool move8(char* state, moveTo movement, int blankPosition, char* newState) {
    memcpy(newState, state, 9);
    switch (movement)
    {
        case UP: {
            newState[blankPosition] = newState[blankPosition-3];
            newState[blankPosition-3] = BLANK_TILE;
            break;
        }
         case LEFT: {
            newState[blankPosition] = newState[blankPosition-1];
            newState[blankPosition-1] = BLANK_TILE;
            break;
        }
        case RIGHT: {
            newState[blankPosition] = newState[blankPosition+1];
            newState[blankPosition+1] = BLANK_TILE;
            break;
        }
        case DOWN: {
            newState[blankPosition] = newState[blankPosition+3];
            newState[blankPosition+3] = BLANK_TILE;
            break;
        }
        default:
            break;
    }
}
// given a state and the puzzleSize, return the position of blank tile
int getBlankPosition(char* state, int puzzleSize) {
    int blankPosition;
    for (blankPosition = 0; blankPosition < puzzleSize; blankPosition++)
        if (state[blankPosition] == BLANK_TILE)
            return blankPosition;
    return -1;
}


// given a state, return a list of successors states
list<PUZZLE_STATE> succ(char* state) {
    list<PUZZLE_STATE> succs;
    int puzzleSize = 9;
    int blankPosition = getBlankPosition(state, puzzleSize);
    PUZZLE_STATE puzzleStateUP;
    PUZZLE_STATE puzzleStateDOWN;
    PUZZLE_STATE puzzleStateLEFT;
    PUZZLE_STATE puzzleStateRIGHT;
    if (puzzleSize == 9) {
        if (blankPosition - 3 >= 0) {
            move8(state, UP, blankPosition, puzzleStateUP.state);
            succs.push_back(puzzleStateUP);
        }
        if (blankPosition != 0 && blankPosition != 3 && blankPosition != 6) {
            move8(state, LEFT, blankPosition, puzzleStateLEFT.state);
            succs.push_back(puzzleStateLEFT);
        }
        if (blankPosition != 2 && blankPosition != 5 && blankPosition != 8) {
            move8(state, RIGHT, blankPosition, puzzleStateRIGHT.state);
            succs.push_back(puzzleStateLEFT);
        }
        if (blankPosition + 3 <= 8) {
            move8(state, DOWN, blankPosition, puzzleStateDOWN.state);
            succs.push_back(puzzleStateDOWN);
        }

    }

    return succs;
}

// given a state, return a list of successors states with g and h calculated
list<PUZZLE_STATE> succ(PUZZLE_STATE puzzle, int puzzleRoot) {
    char* state = puzzle.state;
    int g = puzzle.g + 1;

    list<PUZZLE_STATE> succs;
    int puzzleSize = puzzleRoot * puzzleRoot;
    int blankPosition = getBlankPosition(state, puzzleSize);

    PUZZLE_STATE puzzleStateUP;
    PUZZLE_STATE puzzleStateDOWN;
    PUZZLE_STATE puzzleStateLEFT;
    PUZZLE_STATE puzzleStateRIGHT;

    if (puzzleSize == 9) {
        if (blankPosition - 3 >= 0) {
            move8(state, UP, blankPosition, puzzleStateUP.state);
            puzzleStateUP.g = g;
            puzzleStateUP.h = heuristic(puzzleStateUP, puzzleRoot);
            succs.push_back(puzzleStateUP);
        }
        if (blankPosition != 0 && blankPosition != 3 && blankPosition != 6) {
            move8(state, LEFT, blankPosition, puzzleStateLEFT.state);
            puzzleStateLEFT.g = g;
            puzzleStateLEFT.h = heuristic(puzzleStateLEFT, puzzleRoot);
            succs.push_back(puzzleStateLEFT);
        }
        if (blankPosition != 2 && blankPosition != 5 && blankPosition != 8) {
            move8(state, RIGHT, blankPosition, puzzleStateRIGHT.state);
            puzzleStateRIGHT.g = g;
            puzzleStateRIGHT.h = heuristic(puzzleStateRIGHT, puzzleRoot);
            succs.push_back(puzzleStateRIGHT);
        }
        if (blankPosition + 3 <= 8) {
            move8(state, DOWN, blankPosition, puzzleStateDOWN.state);
            puzzleStateDOWN.g = g;
            puzzleStateDOWN.h = heuristic(puzzleStateDOWN, puzzleRoot);
            succs.push_back(puzzleStateDOWN);
        }
    }
    return succs;
}

string stateToString(char* state) {
    string stateString = "";
    for (int i = 0; i < 9; i++)
        stateString += state[i]+48;
    return stateString;
}

//Calculates the heuristic value from a single state
int heuristic(PUZZLE_STATE puzzle, int puzzleRoot){
    int h = 0;
    for(int i = 0; i < puzzleRoot * puzzleRoot; i++){
        if((int)puzzle.state[i] != 0)
            h += getMarcoPoloDistance(i, (int) puzzle.state[i], puzzleRoot);
    }
    return h;
}

int getMarcoPoloDistance(int currentPosition, int desiredPosition, int puzzleRoot){
    int verticalDistance = abs(getVerticalPosition(currentPosition, puzzleRoot) - getVerticalPosition(desiredPosition, puzzleRoot));
    int horizontalDistance = abs(getHorizontalPosition(currentPosition, puzzleRoot) - getHorizontalPosition(desiredPosition, puzzleRoot));
    return verticalDistance + horizontalDistance;
}

int getVerticalPosition(int pos, int puzzleRoot){
    return pos/puzzleRoot;
}

int getHorizontalPosition(int pos, int puzzleRoot){
    return pos % puzzleRoot;
}

int getPuzzleRoot(int puzzleSize){
    if(puzzleSize == 9)
        return 3;
    else if (puzzleSize == 16)
        return 4;


    return -1;
}