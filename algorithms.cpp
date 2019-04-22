#include <deque>
#include <unordered_set>
#include <chrono>
#include <iostream>
#include <set>
#include <map>
#include "algorithms.h"

using namespace std;
using namespace std::chrono;

// Breadth-First Search Algorithm 
int bfs(char *init) {
    auto start = steady_clock::now();
    int numNodesExpanded = 0, optimalSolutionLen = 0, solutionTime = 0;
    if (isGoal(init)) {
        return 1;
    }

    deque<PUZZLE_STATE> open;
    open.push_back(makeNode(init, 9));
    
    unordered_set<string> closed;
    closed.insert(stateToString(init));
    
    while(!open.empty()) {
        PUZZLE_STATE n = open.front();
        open.pop_front();
        list<PUZZLE_STATE> succs = succ(n.state);
        numNodesExpanded++;
        for (list<PUZZLE_STATE>::iterator it = succs.begin(); it != succs.end(); ++it) {
            PUZZLE_STATE nChild = makeNode(it->state, 9);
            if (isGoal(nChild.state)) {
                auto end = steady_clock::now();
                solutionTime = (int) duration_cast<milliseconds>(end-start).count();
                cout << numNodesExpanded << "," << optimalSolutionLen << "," << (float) solutionTime/1000 << ",-,-" << endl;
                return 1;            
            }
            string stateString = stateToString(nChild.state);
            unordered_set<string>::const_iterator found = closed.find(stateString);
            if (found == closed.end()) {
                closed.insert(stateString);
                open.push_back(nChild);
            }
            
        }
    }
    auto end = steady_clock::now();
    solutionTime = (int) duration_cast<milliseconds>(end-start).count();
    cout << numNodesExpanded << "," << optimalSolutionLen << "," << (float) solutionTime/1000 << ",-,-" << endl;
    cout << "unsolvable" << endl;
    return 0;
}

int depthLimitedSearch(char *init, char *father, int depthLimited) {
    if (isGoal(init)) {
        return 1;            
    }

    if (depthLimited > 0) {
        list<PUZZLE_STATE> succs = succ(init);
        for (list<PUZZLE_STATE>::iterator it = succs.begin(); it != succs.end(); ++it) {
            if (!compareState(father, it->state)) {
                int solution = depthLimitedSearch(it->state, init, depthLimited-1);
                if (solution)
                    return 1;
            }
        }
    }
    return 0;
}

int idfs(char *init) {
    auto start = steady_clock::now();
    int numNodesExpanded = 0, optimalSolutionLen = 0, solutionTime = 0;
    int depthLimited = 1;
    int solution = 0;
    while(!solution){
        solution = depthLimitedSearch(init, NULL, depthLimited);
        depthLimited++;
    }
    auto end = steady_clock::now();
    solutionTime = (int) duration_cast<milliseconds>(end-start).count();
    cout << numNodesExpanded << "," << optimalSolutionLen << "," << (float) solutionTime/1000 << ",-,-" << endl;
}


int astar(char *init, int puzzleSize){
    multiset<PUZZLE_STATE, cmpASTAR> open;
    open.insert(makeNode(init, getPuzzleRoot(puzzleSize)));
    map<string, int> distances;

    while(!open.empty()){
        // cout <<"Looping \n";
        multiset<PUZZLE_STATE, cmpASTAR>::iterator it = open.begin();
        PUZZLE_STATE currentPuzzle = *it;
        open.erase(it);
        string stateString= stateToString(currentPuzzle.state);
        // printState(currentPuzzle.state);
        if (distances.find(stateString) == distances.end() || currentPuzzle.g < distances[stateString]){ //Short-circuit, be careful changing this
            distances[stateString] = currentPuzzle.g;
            
            if(isGoal(currentPuzzle.state)){
                cout << "GOAL" << endl;
                printState(currentPuzzle.state);
                return currentPuzzle.g;
            }

            list<PUZZLE_STATE> succs = succ(currentPuzzle, getPuzzleRoot(puzzleSize));
            for(list<PUZZLE_STATE>::iterator iter = succs.begin(); iter != succs.end(); iter++){
                // cout <<"New state generated -> H: " << iter->h << " G:" << iter->g << endl;
                // printState(iter->state);
                // cout <<"INSERTED - SIZE OF SET BEFORE: " << open.size() << endl;
                open.insert(*iter); //No need to check if it is infinite because it will never be
                // cout <<"INSERTED - SIZE OF SET AFTER: " << open.size() << endl << endl;
            }
        }
        else{
            // cout <<"SKIPPED - SIZE OF SET: " << open.size() << endl;
        }
    }

}

int gbfs(char *init, int puzzleSize){
    multiset<PUZZLE_STATE, cmpGBFS> open;
    open.insert(makeNode(init, getPuzzleRoot(puzzleSize)));
    map<string, int> distances;

    while(!open.empty()){
        // cout <<"Looping \n";
        multiset<PUZZLE_STATE,cmpGBFS>::iterator it = open.begin();
        PUZZLE_STATE currentPuzzle = *it;
        open.erase(it);
        string stateString = stateToString(currentPuzzle.state);
        // printState(currentPuzzle.state);
        if (distances.find(stateString) == distances.end()){
            distances[stateString] = currentPuzzle.g;
            
            if(isGoal(currentPuzzle.state)){
                cout << "GOAL" << endl;
                printState(currentPuzzle.state);
                return currentPuzzle.g;
            }

            list<PUZZLE_STATE> succs = succ(currentPuzzle, getPuzzleRoot(puzzleSize));
            for(list<PUZZLE_STATE>::iterator iter = succs.begin(); iter != succs.end(); iter++){
                // printState(iter->state); 
                open.insert(*iter); //No need to check if it is infinite because it will never be
            }
        }
    }
}