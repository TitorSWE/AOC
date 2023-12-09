#include "../tools/utils.h"
using namespace std;
#include <iostream>
#include <fstream> 
#include <vector>
#include <unordered_map>
#include <chrono>
#include <set>

#include <iostream>
#include <cmath>

int Part1(string fileContent, string start, string target, int instruction){
    vector<string> splittedInput = splitString(fileContent, "\n\n");
    string instructions = splittedInput[0];

    unordered_map<string,vector<string>> path;
    vector<string> lines = splitString(splittedInput[1], "\n");
    for (string line: lines){
        vector<string> splittedLine = splitString(line, " = ");
        string source = splittedLine[0];
        vector<string> destinations = splitString(splittedLine[1].substr(1,splittedLine[1].size()-2),", ");
        path[source] = destinations;
    }

    int modulo = instructions.size();
    string current = start;
    int incr = instruction;
    int posInstruction;
    while(current != target || instruction==incr){
        posInstruction = incr%modulo;
        char instruction = instructions[posInstruction];
        if (instruction == 'L') current = path[current][0];
        if (instruction == 'R') current = path[current][1];
        incr++;
    }
    return incr;

}

long Part2(string fileContent){
    vector<string> splittedInput = splitString(fileContent, "\n\n");
    string instructions = splittedInput[0];

    unordered_map<string, string> pairsAtoZ;
    unordered_map<string, int> offsetCycle;
    unordered_map<string, int> cycleLength;

    // Parsing
    unordered_map<string,vector<string>> path;
    vector<string> lines = splitString(splittedInput[1], "\n");
    for (string line: lines){
        vector<string> splittedLine = splitString(line, " = ");
        string source = splittedLine[0];
        if (source[2] == 'A') {
            offsetCycle[source] = 0;
            pairsAtoZ[source] = source;
        }
        if (source[2] == 'Z') cycleLength[source] = 0;
        vector<string> destinations = splitString(splittedLine[1].substr(1,splittedLine[1].size()-2),", ");
        path[source] = destinations;
    }

    int incr = 0;
    int leftOrRight;
    bool keepGoing = true;
    int numberZeros;
    // Compute offsetCycle and pairsAtoZ
    int modulo = instructions.size();
    while(keepGoing){
        int indexInstruction = incr % modulo;
        numberZeros = 0;
        leftOrRight = ( instructions[indexInstruction] == 'L' ? 0 : 1 );
        for (auto it: pairsAtoZ){
            if (it.second[2] != 'Z'){
                pairsAtoZ[it.first] = path[it.second][leftOrRight];
                offsetCycle[it.first]++;
            } 
            else numberZeros++;
        }
        incr++;
        if (numberZeros == pairsAtoZ.size()) keepGoing = false;
    }



    // Compute Cycle length
    for (auto it: pairsAtoZ){
        bool keepComputeCycle = true;
        while(keepComputeCycle){
            int start = offsetCycle[it.first];
            int newCycleLength = Part1(fileContent, it.second, it.second, start) - start;
            int oldCycleLength = cycleLength[it.second];
            if (newCycleLength != oldCycleLength) {
                offsetCycle[it.first] += oldCycleLength;
                cycleLength[it.second] = newCycleLength;
            }
            else keepComputeCycle = false;
        }
    }

    vector<long> cycles;
    for (auto it: cycleLength) cycles.push_back((long)it.second);
    return lcmVector(cycles);
    
}

int main() {
    cout << "--- DAY 08 ---" << "\n";
    // Part 1
    string fileName = "input-8-1.txt";
    string fileContent1 = Input(fileName);
    auto start = std::chrono::high_resolution_clock::now();
    int res1 = Part1(fileContent1, "AAA", "ZZZ", 0);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part1 is  "<< res1 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    // Part 2
    string fileName2 = "input-8-1.txt";
    string fileContent2 = Input(fileName2);
    start = std::chrono::high_resolution_clock::now();
    long res2 = Part2(fileContent2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part2 is  "<< res2 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;


    return 0;
}