#include <deque>
#include <unordered_set>
#include <chrono>
#include <iostream>
#include "algorithms.h"

using namespace std::chrono;

// Breadth-First Search Algorithm 
int bfs(char *init) {
    auto start = steady_clock::now();
    int numNodesExpanded = 0, optimalSolutionLen = 0, solutionTime = 0, averageHeuristic = 0, initialHeuristic = 0;
    if (isGoal(init)) {
        cout << "GOAL" << endl;
        printState(init);
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
                cout << numNodesExpanded << "," << optimalSolutionLen << "," << solutionTime << "," << averageHeuristic << "," << initialHeuristic << endl;
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
    return 0;
}

int depthLimitedSearch(char *init, char *father, int depthLimited) {
    if (isGoal(init)) {
        cout << endl << endl << "GOAL" << endl;
        printState(init);
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
    int depthLimited = 1;
    int solution = 0;
    while(!solution){
        solution = depthLimitedSearch(init, NULL, depthLimited);
        depthLimited++;
    }
}


int astar(char *init){
    

}