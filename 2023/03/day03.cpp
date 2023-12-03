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

vector<string> splitString(string s, char delimiter){
    vector<string> res;
    int left = 0;
    int right = 0;
    for (char ch: s){
        if (ch==delimiter){
            string stringToAdd = s.substr(left,right-left);
            res.push_back(stringToAdd);
            left = right+1;
        }
        right++;
    }
    res.push_back(s.substr(left,right));
    return res;
}

vector<string> adjacents(string index){
    vector<string> adj;
    for (int i=-1;i<=1;i++){
        for (int j=-1;j<=1;j++){
            vector<string> indexSplitted = splitString(index, ',');
            adj.push_back(to_string(stoi(indexSplitted[0])+i) +","+ to_string(stoi(indexSplitted[1])+j));
        }
    }
    return adj;
}

int Part1(string fileContent){

    std::unordered_map<string, int> numbersDictionary;
    vector<string> symbols;

    vector<string> lines = splitString(fileContent, '\n');
    for (int i=0; i<lines.size(); i++){
        string line = lines[i];
        int j=0;
        while(j<line.size()){
            char ch = line[j];
            if (ch>=48 && ch<=57){
                int k = 0;
                string number;
                vector<string> indexes;
                while(line[j+k]>=48 && line[j+k]<=57 && j+k<line.size()){
                    indexes.push_back(to_string(i)+","+to_string(j+k));
                    number+=line[j+k];
                    k++;
                }
                j=j+k-1;
                int numberToInsert = stoi(number);
                for (string index: indexes){
                    numbersDictionary[index] = numberToInsert;
                }
            }
            else if (ch != '.') symbols.push_back(to_string(i)+","+to_string(j));
            j++;
        }
    }
    int sum = 0;

    for (string symbol: symbols){
        set<int> numbersAdjacent; // for the moment we assume every numbers adjacents to a symbols are unique
        vector<string> adjs = adjacents(symbol);
        for (string adj: adjs){
            auto it = numbersDictionary.find(adj);
            if (it != numbersDictionary.end()) numbersAdjacent.insert(it->second);
        }
        for (int value: numbersAdjacent) sum+=value;
    }
    return sum;
}

int Part2(string fileContent){

    std::unordered_map<string, int> numbersDictionary;
    vector<string> symbols;

    vector<string> lines = splitString(fileContent, '\n');
    for (int i=0; i<lines.size(); i++){
        string line = lines[i];
        int j=0;
        while(j<line.size()){
            char ch = line[j];
            if (ch>=48 && ch<=57){
                int k = 0;
                string number;
                vector<string> indexes;
                while(line[j+k]>=48 && line[j+k]<=57 && j+k<line.size()){
                    indexes.push_back(to_string(i)+","+to_string(j+k));
                    number+=line[j+k];
                    k++;
                }
                j=j+k-1;
                int numberToInsert = stoi(number);
                for (string index: indexes){
                    numbersDictionary[index] = numberToInsert;
                }
            }
            else if (ch != '.') symbols.push_back(to_string(i)+","+to_string(j));
            j++;
        }
    }
    int sum = 0;

    for (string symbol: symbols){
        set<int> numbersAdjacent;
        vector<string> adjs = adjacents(symbol);
        int gearRatio = 1;
        for (string adj: adjs){
            auto it = numbersDictionary.find(adj);
            if (it != numbersDictionary.end()) numbersAdjacent.insert(it->second);
        }
        if (numbersAdjacent.size()==2) {
            for(int value: numbersAdjacent) gearRatio*=value;
        }
        if (gearRatio != 1) sum+=gearRatio;
    }
    return sum;
}
int main(){
    cout << "--- DAY 03 ---" << "\n";
    // Part 1
    string fileName = "input-3-1.txt";
    string fileContent1 = Input(fileName);
    auto start = std::chrono::high_resolution_clock::now();
    int res1 = Part1(fileContent1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part1 is  "<< res1 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    // Part 2
    string fileName2 = "input-3-1.txt";
    string fileContent2 = Input(fileName2);
    start = std::chrono::high_resolution_clock::now();
    int res2 = Part2(fileContent2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part2 is  "<< res2 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    return 0;
}

