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
    char state[16];
    int h;
    int g;
} PUZZLE_STATE;


void printState(char* state);
void printState15(char* state);
string stateToString(char* state, int puzzleSize);

PUZZLE_STATE makeNodeHeuristic(char* state, int puzzleRoot);
PUZZLE_STATE makeNode(char* state);

//Check functions
bool isGoal(char *state);
bool isGoal(char *state, int puzzleSize);
bool compareState(char *state, char *state2, int stateSize);
int getBlankPosition(char* state, int puzzleSize);

//Move Functions
bool move8(char* state, moveTo movement, int blankPosition, char* newState);
list<PUZZLE_STATE> succ(PUZZLE_STATE puzzle);
list<PUZZLE_STATE> succ(PUZZLE_STATE puzzle, int puzzleRoot); 

//Heuristic functions
int heuristic(PUZZLE_STATE puzzle, int puzzleRoot);
int getMarcoPoloDistance(int currentPosition, int desiredPosition, int puzzleRoot);
int getHorizontalPosition(int pos, int puzzleRoot);
int getVerticalPosition(int pos, int puzzleRoot);
int getPuzzleRoot(int puzzleSize);
int getF(PUZZLE_STATE node);

//Sorted list functor




#endif