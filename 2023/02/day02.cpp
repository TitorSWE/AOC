#include <iostream>
#include <fstream>    
#include <bits/stdc++.h> 
using namespace std;
#include <chrono>
#include <vector>

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

int Part1(string fileContent){
    vector<int> res;
    vector<string> lines = splitString(fileContent, '\n');
    for (int i=0; i<lines.size(); i++){
        string line = lines[i];
        vector<string> game = splitString(line, ':');
        string right = game[1];
        vector<string> sets = splitString(right, ';');
        bool gameOK = true;
        for (string rgb: sets){
            vector<string> colors = splitString(rgb, ',');
            for (string color: colors){
                int index = 1;
                while(color[index] != ' ') index++;
                string type = color.substr(index+1, color.size()-index);
                int value = stoi(color.substr(1,index));
                if (type.compare("red") == 0 && value>12) gameOK = false;
                if (type.compare("green") == 0 && value>13) gameOK = false;
                if (type.compare("blue") == 0 && value>14) gameOK = false;
            }
            if (gameOK==false) break;
        }
        if (gameOK) res.push_back(i+1);
    }
    int sum = 0;
    for (int i:res) sum+=i;
    return sum;
}

int Part2(string fileContent){
    vector<int> res;
    vector<string> lines = splitString(fileContent, '\n');
    for (int i=0; i<lines.size(); i++){
        string line = lines[i];
        vector<string> game = splitString(line, ':');
        string right = game[1];
        int redMax = 0;
        int greenMax = 0;
        int blueMax = 0;
        vector<string> sets = splitString(right, ';');
        for (string rgb: sets){
            vector<string> colors = splitString(rgb, ',');
            for (string color: colors){
                int index = 1;
                while(color[index] != ' ') index++;
                string type = color.substr(index+1, color.size()-index);
                int value = stoi(color.substr(1,index));
                if (type.compare("red") == 0) redMax = max(redMax,value);
                if (type.compare("green") == 0) greenMax = max(greenMax, value);
                if (type.compare("blue") == 0) blueMax = max(blueMax, value) ;
            }
        }
        res.push_back(redMax * greenMax * blueMax);
    }
    int sum = 0;
    for (int i:res) sum+=i;
    return sum;
}


int main(){
    cout << "--- DAY 02 ---" << "\n";
    // Part 1
    string fileName = "input-2-1.txt";
    string fileContent1 = Input(fileName);
    auto start = std::chrono::high_resolution_clock::now();
    int res1 = Part1(fileContent1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part1 is  "<< res1 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    //Part2
    string fileName2 = "input-2-1.txt";
    string fileContent2 = Input(fileName2);
    start = std::chrono::high_resolution_clock::now();
    int res2 = Part2(fileContent2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part2 is  "<< res2 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    return 0;
}