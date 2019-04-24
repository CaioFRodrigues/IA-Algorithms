#include <deque>
#include <unordered_set>
#include <chrono>
#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <string>
#include "algorithms.h"

using namespace std;
using namespace std::chrono;
int numNodesExpanded = 0;
bool writeInCsv = false;

void writeCsv(string filename, string line) {
    ofstream csv;
    csv.open (filename);
    csv << line.c_str() << "\n";
    csv.close();
}

// Breadth-First Search Algorithm 
int bfs(char *init) {
    auto start = steady_clock::now();
    int optimalSolutionLen = 0, solutionTime = 0;

    if (isGoal(init)) {
        auto end = steady_clock::now();
        solutionTime = (int) duration_cast<milliseconds>(end-start).count();
        string output = to_string(numNodesExpanded) + "," + to_string(optimalSolutionLen) + "," + to_string((float) solutionTime/1000) + ",-,-";
        cout << output << endl;
        if (writeInCsv) writeCsv("bfs.csv", output);
        return optimalSolutionLen;
    }

    deque<PUZZLE_STATE> open;
    open.push_back(makeNode(init));
    
    unordered_set<string> closed;
    closed.insert(stateToString(init));
    
    while(!open.empty()) {
        PUZZLE_STATE currentPuzzle = open.front();
        open.pop_front();

        numNodesExpanded++;
        list<PUZZLE_STATE> succs = succ(currentPuzzle);
        
        for (list<PUZZLE_STATE>::iterator it = succs.begin(); it != succs.end(); ++it) {
            PUZZLE_STATE nChild = *it;

            if (isGoal(nChild.state)) {
                auto end = steady_clock::now();
                solutionTime = (int) duration_cast<milliseconds>(end-start).count();
                optimalSolutionLen = nChild.g;
                string output = to_string(numNodesExpanded) + "," + to_string(optimalSolutionLen) + "," + to_string((float) solutionTime/1000) + ",-,-";
                cout << output << endl;
                if (writeInCsv) writeCsv("bfs.csv", output);
                return optimalSolutionLen;            
            }
            
            string stateString = stateToString(nChild.state);
            unordered_set<string>::const_iterator found = closed.find(stateString);
            if (found == closed.end()) {
                closed.insert(stateString);
                open.push_back(nChild);
            }
        }
    }
    return -1;
}

// Depth Limited Search
int depthLimitedSearch(PUZZLE_STATE currentPuzzle, char *father, int depthLimited) {
    if (isGoal(currentPuzzle.state)) {
        return currentPuzzle.g;
    }

    if (depthLimited > 0) {
        numNodesExpanded++;
        list<PUZZLE_STATE> succs = succ(currentPuzzle);
        for (list<PUZZLE_STATE>::iterator it = succs.begin(); it != succs.end(); ++it) {
            if (!compareState(father, it->state)) {
                int solution = depthLimitedSearch(*it, currentPuzzle.state, depthLimited-1);
                if (solution >= 0) {
                    return solution;
                }
            }
        }
    }
    return -1;
}

// Iterative Deepening
int idfs(char *init) {
    auto start = steady_clock::now();
    int optimalSolutionLen = 0, solutionTime = 0;
    int depthLimited = 1;
    int solution = -1;

    PUZZLE_STATE initialPuzzle = makeNode(init);
    while(solution == -1){
        solution = depthLimitedSearch(initialPuzzle, NULL, depthLimited);
        depthLimited++;
    }
    optimalSolutionLen = solution;
    auto end = steady_clock::now();
    solutionTime = (int) duration_cast<milliseconds>(end-start).count();
    string output = to_string(numNodesExpanded) + "," + to_string(optimalSolutionLen) + "," + to_string((float) solutionTime/1000) + ",-,-";
    cout << output << endl;
    if (writeInCsv) writeCsv("idfs.csv", output);
}


int astar(char *init, int puzzleSize) {
    multiset<PUZZLE_STATE, cmpASTAR> open;
    open.insert(makeNodeHeuristic(init, getPuzzleRoot(puzzleSize)));
    map<string, int> distances;

    while(!open.empty()){
        multiset<PUZZLE_STATE, cmpASTAR>::iterator it = open.begin();
        PUZZLE_STATE currentPuzzle = *it;
        open.erase(it);
        string stateString= stateToString(currentPuzzle.state);
        if (distances.find(stateString) == distances.end() || currentPuzzle.g < distances[stateString]){ //Short-circuit, be careful changing this
            distances[stateString] = currentPuzzle.g;
            
            if(isGoal(currentPuzzle.state)){
                return currentPuzzle.g;
            }

            list<PUZZLE_STATE> succs = succ(currentPuzzle, getPuzzleRoot(puzzleSize));
            for(list<PUZZLE_STATE>::iterator iter = succs.begin(); iter != succs.end(); iter++){
                open.insert(*iter); //No need to check if it is infinite because it will never be
            }
        }
    }

}

int gbfs(char *init, int puzzleSize){
    multiset<PUZZLE_STATE, cmpGBFS> open;
    open.insert(makeNodeHeuristic(init, getPuzzleRoot(puzzleSize)));
    map<string, int> distances;

    while(!open.empty()){
        multiset<PUZZLE_STATE,cmpGBFS>::iterator it = open.begin();
        PUZZLE_STATE currentPuzzle = *it;
        open.erase(it);
        string stateString = stateToString(currentPuzzle.state);
        if (distances.find(stateString) == distances.end()){
            distances[stateString] = currentPuzzle.g;
            
            if(isGoal(currentPuzzle.state)){
                cout << "GOAL" << endl;
                printState(currentPuzzle.state);
                return currentPuzzle.g;
            }

            list<PUZZLE_STATE> succs = succ(currentPuzzle, getPuzzleRoot(puzzleSize));
            for(list<PUZZLE_STATE>::iterator iter = succs.begin(); iter != succs.end(); iter++){
                open.insert(*iter); //No need to check if it is infinite because it will never be
            }
        }
    }
}