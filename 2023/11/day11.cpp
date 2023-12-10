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

long Part1_2(string fileContent, int dilatation){

    // Parsing
    int lineLength = fileContent.find('\n')+1;
    int indexGalaxy = 1;
    unordered_map<int,vector<int>> galaxies;
    unordered_map<int, bool> notEmptyColumn;
    unordered_map<int, bool> notEmtyLine;
    vector<int> cumulateEmptyColumn;
    vector<int> cumulateEmptyLine;
    for (int i=0; i<fileContent.size(); i++){
        char c = fileContent[i];
        if (c == '#'){
            vector<int> coord = {i/lineLength,i%lineLength};
            notEmptyColumn[i%lineLength] = true;
            notEmtyLine[i/lineLength] = true;
            galaxies[indexGalaxy] = coord;
            indexGalaxy++;
        }
    }

    // Cumulate empty col and line
    int numberEmptyCol = 0;
    int numberEmptyLine = 0;
    for (int i=0; i<lineLength; i++){
        if (notEmptyColumn[i] == false) numberEmptyCol++;
        cumulateEmptyColumn.push_back(numberEmptyCol);
    }
    for (int j=0; j<=fileContent.size()/lineLength; j++){
        if (notEmtyLine[j] == false) numberEmptyLine++;
        cumulateEmptyLine.push_back(numberEmptyLine);
    }

    // Compute
    long sum = 0;
    for (auto it1: galaxies){
        for (auto it2: galaxies){
            if (it1.first != it2.first){
                int diffColumn = abs(it1.second[1] - it2.second[1]);
                int diffLine = abs(it1.second[0] - it2.second[0]);
                diffColumn += (dilatation-1)* abs(cumulateEmptyColumn[it1.second[1]] - cumulateEmptyColumn[it2.second[1]]);
                diffLine += (dilatation-1) * abs(cumulateEmptyLine[it1.second[0]] - cumulateEmptyLine[it2.second[0]]);
                sum += diffColumn + diffLine;
            } 
        }
    }
    return sum/2;
}

int main(){
    cout << "--- DAY 09 ---" << "\n";
    // Part 1
    string fileName = "input-11-1.txt";
    string fileContent1 = Input(fileName);
    auto start = std::chrono::high_resolution_clock::now();
    long res1 = Part1_2(fileContent1,2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part1 is  "<< res1 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    long res2 = Part1_2(fileContent1,1000000);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part2 is  "<< res2 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;
}