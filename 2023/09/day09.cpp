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


int Part1(string fileContent){
    vector<string> lines = splitString(fileContent,"\n");
    int sum = 0;
    for (string line: lines){
        vector<string> values = splitString(line," ");
        vector<vector<int>> pyramide;
        vector<int> firstLine;
        for (string val: values) firstLine.push_back(stoi(val));
        pyramide.push_back(firstLine);
        bool allZeros = false;

        // down
        while(allZeros == false){
            vector<int> difference;
            int len = pyramide[pyramide.size()-1].size()-1;
            int numberZeros = 0;
            for (int i=0; i<len; i++){
                int diffValue = pyramide[pyramide.size()-1][i+1]-pyramide[pyramide.size()-1][i];
                if (diffValue == 0) numberZeros++;
                difference.push_back(diffValue);
            }
            if (numberZeros == len) allZeros = true;
            pyramide.push_back(difference);
        }
        
        //up
        pyramide[pyramide.size()-1].push_back(0);
        for (int k=pyramide.size()-2; k>=0; k--){
            int index_k = pyramide[k].size()-1;
            int index_k_next = pyramide[k+1].size()-1;
            int calculus = pyramide[k][index_k]+ pyramide[k+1][index_k_next];
            pyramide[k].push_back( calculus);
            if (k==0) sum+= calculus;
        }
    }
    return sum;
}

int Part2(string fileContent){
    vector<string> lines = splitString(fileContent,"\n");
    int sum = 0;
    for (string line: lines){
        vector<string> values = splitString(line," ");
        vector<vector<int>> pyramide;
        vector<int> firstLine;
        for (string val: values) firstLine.push_back(stoi(val));
        pyramide.push_back(firstLine);
        bool allZeros = false;
        
        // down
        while(allZeros == false){
            vector<int> difference;
            int len = pyramide[pyramide.size()-1].size()-1;
            int numberZeros = 0;
            for (int i=0; i<len; i++){
                int diffValue = pyramide[pyramide.size()-1][i+1]-pyramide[pyramide.size()-1][i];
                if (diffValue == 0) numberZeros++;
                difference.push_back(diffValue);
            }
            if (numberZeros == len) allZeros = true;
            pyramide.push_back(difference);
        }
        
        //up
        int current = 0;
        for (int k=pyramide.size()-2; k>=0; k--){
            current = pyramide[k][0]-current;
            if (k==0) sum+= current;
        }
    }
    return sum;
}

int main(){
    cout << "--- DAY 09 ---" << "\n";
    // Part 1
    string fileName = "input-9-1.txt";
    string fileContent1 = Input(fileName);
    auto start = std::chrono::high_resolution_clock::now();
    int res1 = Part1(fileContent1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part1 is  "<< res1 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    // Part 2
    string fileName2 = "input-9-1.txt";
    string fileContent2 = Input(fileName2);
    start = std::chrono::high_resolution_clock::now();
    long res2 = Part2(fileContent2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part2 is  "<< res2 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;


    return 0;
}