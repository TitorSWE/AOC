#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#include <chrono>

string Input(string fileName){
    ifstream inputFile(fileName);
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string fileContent = buffer.str();
    return fileContent;
}

int Part1(string fileContent){
    int left;
    int right;
    bool first = true;
    int sum = 0;
    for (char ch : fileContent){
        if (ch<=57 && ch>=48){
            if (first){
                left = 10 * (int(ch)-48);
                first = false;
            }
            right = int(ch)-48;
        }
        if (ch == '\n'){
            sum+= left+right;
            first = true;
        }
    }
    return sum + left + right;
}

int Part2(string fileContent){

    int left;
    int right;
    int first = true;
    int sum = 0;
    unordered_map<std::string, int> intDictionary;

    intDictionary["one"]   = 1;
    intDictionary["two"]   = 2;
    intDictionary["three"] = 3;
    intDictionary["four"]  = 4;
    intDictionary["five"]  = 5;
    intDictionary["six"]   = 6;
    intDictionary["seven"] = 7;
    intDictionary["eight"] = 8;
    intDictionary["nine"]  = 9;

    for (int i=0; i<fileContent.size(); i++){
        char ch = fileContent[i];
        if (ch<=57 && ch>=48){
            if (first){
                left = 10 * (int(ch)-48);
                first = false;
            }
            right = int(ch)-48;
        }
        if (ch == '\n'){
            sum+= left+right;
            first = true;
        }
        else {
            string window;
            window+= ch;
            for (int k=1;k<5;k++){
                if (fileContent[i+k]=='\n') break;
                window+=fileContent[i+k];
                if (k>=2){
                    auto it = intDictionary.find(window);
                    if (it != intDictionary.end()) {
                        if (first){
                            left = 10 * (it->second);
                            first = false;
                        }
                        right = (it->second);
                    }
                }   
            }
        } 
    }
    return sum + left + right;
}


int main(){
    cout << "--- DAY 01 ---" << "\n";

    // Part 1
    string fileName = "input-01-1.txt";
    string fileContent1 = Input(fileName);
    auto start = std::chrono::high_resolution_clock::now();
    int res1 = Part1(fileContent1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part1 is  "<< res1 << " : " << (float)duration.count()/1000 << " microseconds" << std::endl;

    //Part2
    string fileName2 = "input-01-2.txt";
    string fileContent2 = Input(fileName2);
    start = std::chrono::high_resolution_clock::now();
    int res2 = Part2(fileContent2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part2 is  "<< res2 << " : " << (float)duration.count()/1000 << " microseconds" << std::endl;

    return 0;
}