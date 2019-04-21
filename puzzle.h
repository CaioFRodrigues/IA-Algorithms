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


void printState(char* state);
string stateToString(char* state);

PUZZLE_STATE makeNode(char* state, int puzzleSize);

//Check functions
bool isGoal(char *state);
bool compareState(char *state, char *state2);
int getBlankPosition(char* state, int puzzleSize);

//Move Functions
bool move8(char* state, moveTo movement, int blankPosition, char* newState);
list<PUZZLE_STATE> succ(char* state);

//Heuristic functions
int heuristic(PUZZLE_STATE puzzle, int puzzle_size);
int getMarcoPoloDistance(int currentPosition, int desiredPosition, int puzzle_size);
int getHorizontalPosition(int pos, int puzzle_size);
int getVerticalPosition(int pos, int puzzle_size);



#endif