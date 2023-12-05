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
                }
                left = right+delimiter.size();
            }
        }
        right++;
    }
    if (right>left) res.push_back(s.substr(left,right));
    return res;
}

int Part1(string fileContent){
    vector<string> lines = splitString(fileContent,"\n");
    vector<string> Time = splitString(splitString(lines[0],": ")[1], " ");
    vector<string> Distance = splitString(splitString(lines[1], ": ")[1], " ");
    int numberRaces = Time.size();
    vector<int> recordsBreaked;
    for (int i=0; i<numberRaces;i++){
        int time = stoi(Time[i]);
        int distance = stoi(Distance[i]);
        int breaks = 0;
        for (int k=0; k<time ; k++){
            int timeLeft = time-k;
            int newDistance = k*timeLeft;
            if (newDistance>distance) breaks++;
        }
        recordsBreaked.push_back(breaks);
    }
    int res = 1;
    for (int breaks: recordsBreaked) res*=breaks;
    return res;
}

std::vector<double> FindRoots(double a, double b, double c) {
    std::vector<double> roots;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        // Pas de racines réelles
    } else if (discriminant == 0) {
        // Une racine réelle
        double racine = -b / (2 * a);
        roots.push_back(racine);
    } else {
        // Deux racines réelles
        double racine1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double racine2 = (-b - std::sqrt(discriminant)) / (2 * a);
        roots.push_back(racine1);
        roots.push_back(racine2);
    }
    return roots;
}

int Part2(string fileContent){
    vector<string> lines = splitString(fileContent,"\n");
    vector<string> Time = splitString(splitString(lines[0],": ")[1], " ");
    vector<string> Distance = splitString(splitString(lines[1], ": ")[1], " ");
    int numberRaces = Time.size();
    string timeString;
    string distanceString;
    for (int i=0; i<numberRaces; i++){
        timeString+=Time[i];
        distanceString+=Distance[i];
    }
    double time = stol(timeString);
    double distance = stol(distanceString);
    vector<double> roots = FindRoots((double)(-1), time, -distance);
    return static_cast<int>(std::floor(roots[1]))-static_cast<int>(std::floor(roots[0]));

}

int main(){
    cout << "--- DAY 05 ---" << "\n";
    // Part 1
    string fileName = "input-6-1.txt";
    string fileContent1 = Input(fileName);
    auto start = std::chrono::high_resolution_clock::now();
    long res1 = Part1(fileContent1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part1 is  "<< res1 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    // Part 2
    string fileName2 = "input-6-1.txt";
    string fileContent2 = Input(fileName2);
    start = std::chrono::high_resolution_clock::now();
    long res2 = Part2(fileContent2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part1 is  "<< res2 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;


    return 0;
}