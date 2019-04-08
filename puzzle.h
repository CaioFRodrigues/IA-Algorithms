#ifndef PUZZLEH
#define PUZZLEH


#include <list>
#define BLANK_TILE 0

using namespace std;
enum moveTo
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef struct
{
    char state[9];
    int h;
} PUZZLE_STATE;



bool isGoal(char *state);
void printState(char* state);
PUZZLE_STATE makeNode(char* state, int h);
bool move8(char* state, moveTo movement, int blankPosition, char* newState);
int getBlankPosition(char* state, int puzzleSize);
list<PUZZLE_STATE> succ(char* state);

#endif