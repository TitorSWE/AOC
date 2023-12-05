#include <iostream>
#include <fstream>    
#include <bits/stdc++.h> 
using namespace std;
#include <chrono>
#include <vector>
#include <unordered_map>
#include <tuple>

string Input(string fileName){
    ifstream inputFile(fileName);
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string fileContent = buffer.str();
    return fileContent;
}

vector<string> splitString(string s, string delimiter){
    vector<string> res;
    int left = 0;
    int right = 0;
    for (int i=0; i<s.size(); i++){
        char ch = s[i];
        if (ch == delimiter[0]){
            bool stringsEqual = true;
            for (int k=0; k<delimiter.size(); k++){
                if (s[i+k] != delimiter[k]) stringsEqual = false;
            }
            if (stringsEqual){
                string stringToAdd = s.substr(left,right-left);
                if (right>left) {
                    res.push_back(stringToAdd);
                    left = right+delimiter.size();
                }
            }
        }
        right++;
    }
    if (right>left) res.push_back(s.substr(left,right));
    return res;
}

vector<vector<long>> Parse(string sourceToDestination){
    vector<vector<long>> res;
    vector<string> lines = splitString(sourceToDestination, "\n");
    for (int i = 1; i<lines.size(); i++){
        vector<long> line_i;
        res.push_back(line_i);
        string line = lines[i];
        vector<string> lineToInsert = splitString(line," ");
        for (string num : lineToInsert) res[i-1].push_back(stol(num));
    }
    return res;
}

long Location(long location, vector<vector<long>> destionationSourceRange){
    for (vector<long> line : destionationSourceRange){
        long source = line[1];
        long destionation = line[0];
        long range = line[2];
        if (location>=source && location<source+range) return location - source + destionation;
    }
    return location;
}

long Part1(string fileContent){
    vector<long> locations;
    vector<string> splittedInput = splitString(fileContent, "\n\n");
    vector<string> seeds = splitString(splitString(splittedInput[0],": ")[1], " ");

    // Parsing 
    vector<vector<vector<long>>> listDestionationSourceRange;
    for (int i=1;i<splittedInput.size(); i++) listDestionationSourceRange.push_back(Parse(splittedInput[i]));
    
    // Conputing
    long location;
    long newLocation;
    long minLocation = 0;
    for (string seed: seeds){
        location = stol(seed);
        for (int i=1; i<splittedInput.size(); i++){
            newLocation = Location(location, listDestionationSourceRange[i-1]);
            location = newLocation;
        }
        if (minLocation == 0) minLocation=location;
        else minLocation = min(minLocation, location);
    }
    return minLocation;
}

long reciproque(long breaking, vector<vector<long>> listDestionationSourceRange){
    for (vector<long> line : listDestionationSourceRange){
        long destination = line[0];
        long source = line[1];
        long range = line[2];
        if (breaking>=destination && breaking < destination + range) return breaking - destination + source;
    }
    return breaking;
}

long Part2(string fileContent){
    vector<long> locations;
    vector<string> splittedInput = splitString(fileContent, "\n\n");
    vector<string> seeds = splitString(splitString(splittedInput[0],": ")[1], " ");

    // Parsing 
    vector<vector<vector<long>>> listDestionationSourceRange;
    for (int i=1;i<splittedInput.size(); i++) listDestionationSourceRange.push_back(Parse(splittedInput[i]));

    // Find breaks
    vector<set<long>> breaks;
    for (int i=1; i<splittedInput.size(); i++){
        breaks.push_back(set<long>());
    }
    int size = splittedInput.size()-1;
    long maxBreak = 0;
    for (vector<long> breaking: listDestionationSourceRange[size-1]) {
        breaks[size-1].insert(breaking[1]);
        maxBreak = max(maxBreak, breaking[1]+breaking[2]);
    }
    breaks[size-1].insert(0);
    breaks[size-1].insert(maxBreak);

    for (int k=size-2; k>=0 ;k--){
        maxBreak = 0;
        for (vector<long> breaking: listDestionationSourceRange[k]) {
            breaks[k].insert(breaking[1]);
            maxBreak = max(maxBreak, breaking[1]+breaking[2]);
        }
        breaks[k].insert(0);
        breaks[k].insert(maxBreak);
        for (long breaking: breaks[k+1]) breaks[k].insert(reciproque(breaking, listDestionationSourceRange[k]));
    }

    // Conputing
    long location;
    long newLocation;
    long minLocation = 0;
    for (int i=0; i<seeds.size()-2; i=i+2){
        vector<long> locationsFeasible = {};
        long minSeed = stol(seeds[i]);
        long maxSeed = minSeed + stol(seeds[i+1]);
        for (long breaking : breaks[0]){
            if (breaking >= minSeed && breaking < maxSeed){
                locationsFeasible.push_back(breaking);
            }
        }
        for (long locationFeasible: locationsFeasible){
            location = locationFeasible;
            for (int i=1; i<splittedInput.size(); i++){
                newLocation = Location(location, listDestionationSourceRange[i-1]);
                location = newLocation;
            }
            if (minLocation == 0) minLocation=location;
            else minLocation = min(minLocation, location);
        }
        
    }
    return minLocation;

}

int main(){
    cout << "--- DAY 05 ---" << "\n";
    // Part 1
    string fileName = "input-5-1.txt";
    string fileContent1 = Input(fileName);
    auto start = std::chrono::high_resolution_clock::now();
    long res1 = Part1(fileContent1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part1 is  "<< res1 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    // Part 2
    string fileName2 = "input-5-1.txt";
    string fileContent2 = Input(fileName2);
    start = std::chrono::high_resolution_clock::now();
    long res2 = Part2(fileContent2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part2 is  "<< res2 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    return 0;
}