#include <deque>
#include <unordered_set>
#include <chrono>
#include <iostream>
#include <set>
#include <map>
#include <ostream>
#include <fstream>
#include <string>
#include <tuple>
#include "algorithms.h"


using namespace std;
using namespace std::chrono;
int numNodesExpanded = 0;
int heuristicAcc = 0;
int heuristicCount = 0;
bool writeInCsv = true;

void writeCsv(string filename, string line) {
    ofstream csv;
    csv.open (filename, ios_base::app);
    csv << line.c_str() << "\n";
    csv.close();
}

// Breadth-First Search Algorithm 
int bfs(char *init) {
    auto start = steady_clock::now();
    int optimalSolutionLen = 0, solutionTime = 0;
    numNodesExpanded = 0;

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
    closed.insert(stateToString(init, 9));
    
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
            
            string stateString = stateToString(nChild.state, 9);
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
            if (!compareState(father, it->state, 9)) {
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
    numNodesExpanded = 0;

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
    auto start = steady_clock::now();
    int optimalSolutionLen = 0, solutionTime = 0;
    numNodesExpanded = 0;
    heuristicAcc = 0;
    heuristicCount = 0;

    multiset<PUZZLE_STATE, cmpASTAR> open;

    PUZZLE_STATE initialPuzzle = makeNodeHeuristic(init, getPuzzleRoot(puzzleSize));
    int heuristicInitial = initialPuzzle.h;
    open.insert(initialPuzzle);
    map<string, int> distances;

    while(!open.empty()){
        multiset<PUZZLE_STATE, cmpASTAR>::iterator it = open.begin();
        PUZZLE_STATE currentPuzzle = *it;
        open.erase(it);
        string stateString= stateToString(currentPuzzle.state, puzzleSize);    
        if (distances.find(stateString) == distances.end() || currentPuzzle.g < distances[stateString]){ //Short-circuit, be careful changing this
            distances[stateString] = currentPuzzle.g;
            if(isGoal(currentPuzzle.state, puzzleSize)){
                auto end = steady_clock::now();
                solutionTime = (int) duration_cast<milliseconds>(end-start).count();
                optimalSolutionLen = currentPuzzle.g;
                string output = to_string(numNodesExpanded) + "," + to_string(optimalSolutionLen) + "," + to_string((float) solutionTime/1000) + "," + to_string((float) heuristicAcc/heuristicCount) + "," + to_string(heuristicInitial);
                cout << output << endl;
                if (writeInCsv) writeCsv("astar.csv", output);
                return currentPuzzle.g;
            }
            numNodesExpanded++;
            list<PUZZLE_STATE> succs = succ(currentPuzzle, getPuzzleRoot(puzzleSize), &heuristicAcc);
            heuristicCount += succs.size();
            for(list<PUZZLE_STATE>::iterator iter = succs.begin(); iter != succs.end(); iter++){
                open.insert(*iter); //No need to check if it is infinite because it will never be
            }
        }
    }

    return -1;

}

int idastar(char *init, int puzzleSize){
    int puzzleRoot = getPuzzleRoot(puzzleSize);
    PUZZLE_STATE node = makeNodeHeuristic(init, puzzleRoot);
    int limit = getF(node);
    heuristicAcc = 0;
    heuristicCount = 0;

    while(limit < -1){
        tuple<int, PUZZLE_STATE> result = recursiveSearch(node, limit);
        limit = get<0>(result);

        if(isGoal(get<1>(result).state) == true)
            return get<1>(result).g;

        

    }
    return -1;


}

tuple<int,PUZZLE_STATE> recursiveSearch(PUZZLE_STATE node, int limit){

    if(getF(node) > limit)
        return make_tuple(getF(node), node);
    
    if (isGoal(node.state))
        return make_tuple(-1, node);
    
    int nextLimit = 2147483647; //highest int

    list<PUZZLE_STATE> succs = succ(node, 3, &heuristicAcc); //Size is always 3 with idastar
    heuristicCount += succs.size();
    for (list<PUZZLE_STATE>::iterator iter = succs.begin(); iter != succs.end(); iter++){
        tuple<int, PUZZLE_STATE> solution = recursiveSearch(*iter, limit);

        if (isGoal(get<1>(solution).state)){
            return make_tuple(-1, get<1>(solution));
        }

        // nextLimit = min(nextLimit, get<0>(solution));
    }

    return make_tuple(nextLimit, node);
}

int gbfs(char *init, int puzzleSize){
    auto start = steady_clock::now();
    int optimalSolutionLen = 0, solutionTime = 0;
    numNodesExpanded = 0;
    heuristicAcc = 0;
    heuristicCount = 0;

    multiset<PUZZLE_STATE, cmpGBFS> open;
    PUZZLE_STATE initialPuzzle = makeNodeHeuristic(init, getPuzzleRoot(puzzleSize));
    int heuristicInitial = initialPuzzle.h;
    open.insert(initialPuzzle);
    unordered_set<string> closed;

    while(!open.empty()){
        multiset<PUZZLE_STATE,cmpGBFS>::iterator it = open.begin();
        PUZZLE_STATE currentPuzzle = *it;
        open.erase(it);
        string stateString = stateToString(currentPuzzle.state, 9);
        unordered_set<string>::const_iterator found = closed.find(stateString);
        if (found == closed.end()) {
            closed.insert(stateString);
            
            if(isGoal(currentPuzzle.state)) {
                auto end = steady_clock::now();
                solutionTime = (int) duration_cast<milliseconds>(end-start).count();
                optimalSolutionLen = currentPuzzle.g;
                string output = to_string(numNodesExpanded) + "," + to_string(optimalSolutionLen) + "," + to_string((float) solutionTime/1000) + "," + to_string((float) heuristicAcc/heuristicCount) + "," + to_string(heuristicInitial);
                cout << output << endl;
                if (writeInCsv) writeCsv("gbfs.csv", output);
                return currentPuzzle.g;
            }

            numNodesExpanded++;
            list<PUZZLE_STATE> succs = succ(currentPuzzle, getPuzzleRoot(puzzleSize), &heuristicAcc);
            heuristicCount += succs.size();
            for(list<PUZZLE_STATE>::iterator iter = succs.begin(); iter != succs.end(); iter++){
                open.insert(*iter); //No need to check if it is infinite because it will never be
            }
        }
    }
}

