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
            if (right>left) res.push_back(stringToAdd);
            left = right+1;
        }
        right++;
    }
    if (right>left) res.push_back(s.substr(left,right));
    return res;
}

int Part1(string fileContent){
    vector<string> lines = splitString(fileContent, '\n');
    int score = 0;
    for (string line: lines){
        vector<string> cards = splitString(line, ':');
        string lists = cards[1];
        vector<string> listsSplitted = splitString(lists, '|');
        string winningString = listsSplitted[0];
        vector<string> winningVector = splitString(winningString, ' ');
        string haveString = listsSplitted[1];
        vector<string> haveVector = splitString(haveString, ' ');
        int winningHash[100] = {};
        int power = -1; 
        for (string w: winningVector) {
            winningHash[stoi(w)] = 1;
        }
        for (string h: haveVector){
            if (winningHash[stoi(h)] == 1) power++;
        }
        if (power!=-1) score+=(int)(pow(2,power));
    }
    return score;
}

void updateCopies(int* copies, int start, int numberCopies, int numberCards){
    int index = 1;
    int scoreStart = copies[start];
    while(index<=numberCopies && start+index<numberCards) {
        copies[start+index]+=scoreStart;
        index++;
    }
}

int Part2(string fileContent){
    vector<string> lines = splitString(fileContent, '\n');
    int score = 0;
    int numberCards = lines.size();
    int* copiesArray = new int[numberCards];
    for (int i=0;i<numberCards; i++) copiesArray[i]=1;
    for (int i=0; i<numberCards; i++){
        string line = lines[i];
        vector<string> cards = splitString(line, ':');
        string lists = cards[1];
        vector<string> listsSplitted = splitString(lists, '|');
        string winningString = listsSplitted[0];
        vector<string> winningVector = splitString(winningString, ' ');
        string haveString = listsSplitted[1];
        vector<string> haveVector = splitString(haveString, ' ');
        int winningHash[100] = {};
        int numberCopies = 0; 
        for (string w: winningVector) {
            winningHash[stoi(w)] = 1;
        }
        for (string h: haveVector){
            if (winningHash[stoi(h)] == 1) numberCopies++;
        }
        updateCopies(copiesArray, i, numberCopies, numberCards);
    }
    for (int i=0; i<numberCards; i++) score+=copiesArray[i];
    return score;
}


int main(){
    cout << "--- DAY 04 ---" << "\n";
    // Part 1
    string fileName = "input-4-1.txt";
    string fileContent1 = Input(fileName);
    auto start = std::chrono::high_resolution_clock::now();
    int res1 = Part1(fileContent1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part1 is  "<< res1 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    // Part 2
    string fileName2 = "input-4-1.txt";
    string fileContent2 = Input(fileName2);
    start = std::chrono::high_resolution_clock::now();
    int res2 = Part2(fileContent2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part2 is  "<< res2 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    return 0;
}