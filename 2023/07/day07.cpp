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

class Hand {
public:
    string cards;
    int bid;
    int power;

    static int computeType1(string content){

        unordered_map<char,int> amounts;
        unordered_map<int,int> combins;

        combins[5]  = 0;
        combins[4]  = 0;
        combins[3]  = 0;
        combins[3]  = 0;
        combins[1]  = 0;

        for (char c: content){
            auto it = amounts.find(c);
            if (it == amounts.end()) amounts[c] = 1;
            else amounts[c]++;
        }

        for (auto it: amounts){
            int value = it.second;
            for (int i=1;i<=5;i++){
                if (value == i) combins[i]++;
            }
        }

        if (combins[5]==1) return 7;
        else if (combins[4]==1) return 6;
        else if (combins[3]==1 && combins[2]==1) return 5;
        else if (combins[3] == 1) return 4;
        else if (combins[2] == 2) return 3;
        else if (combins[2] == 1) return 2;
        else return 1;
    }

    static int computeType2(string content){

        unordered_map<char,int> amounts;
        unordered_map<int,int> combins;

        combins[5]  = 0;
        combins[4]  = 0;
        combins[3]  = 0;
        combins[3]  = 0;
        combins[1]  = 0;

        for (char c: content){
            auto it = amounts.find(c);
            if (it == amounts.end()) amounts[c] = 1;
            else amounts[c]++;
        }

        for (auto it: amounts){
            if (it.first !='J'){
                int value = it.second;
                for (int i=1;i<=5;i++){
                    if (value == i) combins[i]++;
                }
            }
        }

        if ((combins[5]==1) || (combins[4]==1 && amounts['J']==1) || (combins[3]==1 && amounts['J']==2) || (combins[2]==1 && amounts['J']==3) || amounts['J']>=4) return 7;
        else if ((combins[4]==1) || (combins[3]==1 && amounts['J']==1) || (combins[2]==1 && amounts['J']==2) || amounts['J']==3) return 6;
        else if ((combins[3]==1 && combins[2]==1) || (combins[2]==2 && amounts['J']==1)) return 5;
        else if ((combins[3] == 1) || amounts['J']==2 || (combins[2]==1 && amounts['J']==1)) return 4;
        else if ((combins[2] == 2) ) return 3;
        else if ((combins[2] == 1) || amounts['J']==1) return 2;
        else return 1;
    }

    void displayValues() {
        std::cout << "cards: " << cards << std::endl;
        std::cout << "bid: " << to_string(bid) << std::endl;
        std::cout << "power: " << to_string(power) << std::endl;
    }

    void setValues(string input,int part) {
        vector<string> splittedInput = splitString(input, " ");
        cards = splittedInput[0];
        bid = stoi(splittedInput[1]);
        // Compute Type
        if (part==1) power = computeType1(cards);
        else power = computeType2(cards);
    }
};

int Part1(string fileContent){
    unordered_map<char, int> powerCard;
    for (int i=2;i<=9; i++) powerCard[to_string(i)[0]]=i;
    powerCard['T']=10;
    powerCard['J']=11;
    powerCard['Q']=12;
    powerCard['K']=13;
    powerCard['A']=14;
    
    vector<string> handsContent = splitString(fileContent, "\n");
    vector<Hand> hands;
    for (string hand: handsContent) {
        Hand newHand;
        newHand.setValues(hand,1);
        hands.push_back(newHand);
    }
    // Sorting the vector based on the values
    std::sort(hands.begin(), hands.end(), [&powerCard](const auto& a, const auto& b) {
        if (a.power == b.power) {
            for (int i = 0; i < 5; i++) {
                if (a.cards[i] != b.cards[i]) {
                    return powerCard[a.cards[i]] < powerCard[b.cards[i]];
                }
            }
        }
        return a.power < b.power;
    });

    long sum = 0;
    for(int i=1; i<=hands.size(); i++) sum+=(long)i*(long)hands[i-1].bid;

    return sum;
}


int Part2(string fileContent){
    unordered_map<char, int> powerCard;
    for (int i=2;i<=9; i++) powerCard[to_string(i)[0]]=i;
    powerCard['T']=10;
    powerCard['J']=1;
    powerCard['Q']=12;
    powerCard['K']=13;
    powerCard['A']=14;
    
    vector<string> handsContent = splitString(fileContent, "\n");
    vector<Hand> hands;
    for (string hand: handsContent) {
        Hand newHand;
        newHand.setValues(hand,2);
        hands.push_back(newHand);
    }
    // Sorting the vector based on the values
    std::sort(hands.begin(), hands.end(), [&powerCard](const auto& a, const auto& b) {
        if (a.power == b.power) {
            for (int i = 0; i < 5; i++) {
                if (a.cards[i] != b.cards[i]) {
                    return powerCard[a.cards[i]] < powerCard[b.cards[i]];
                }
            }
        }
        return a.power < b.power;
    });

    long sum = 0;
    for(int i=1; i<=hands.size(); i++) sum+=(long)i*(long)hands[i-1].bid;

    return sum;
}

int main(){
    cout << "--- DAY 07 ---" << "\n";
    // Part 1
    string fileName = "input-7-1.txt";
    string fileContent1 = Input(fileName);
    auto start = std::chrono::high_resolution_clock::now();
    long res1 = Part1(fileContent1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part1 is  "<< res1 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    // Part 2
    string fileName2 = "input-7-1.txt";
    string fileContent2 = Input(fileName2);
    start = std::chrono::high_resolution_clock::now();
    long res2 = Part2(fileContent2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "The result for Part2 is  "<< res2 << " : " << (float)duration.count()/1000 << " miliseconds" << std::endl;

    return 0;
}