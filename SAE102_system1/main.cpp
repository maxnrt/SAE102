#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;


void generateRandVotes(vector<string> & candidates, unsigned & voters_cnt) {
    mt19937 mt1(chrono::high_resolution_clock::now().time_since_epoch().count());  // seed RNG with nanosecond clock
    ofstream votes_file ("votes.txt");  // open votes.txt
    for (unsigned i = 0; i < voters_cnt; ++i) {  // for every voter,
        //cout << "candidates.size() = " << candidates.size() << endl;
        votes_file << (candidates[(mt1() % candidates.size())]) << endl;  // add a random vote to votes.txt
    }
    votes_file.close();  // close votes.txt
}

vector<unsigned> countVotes (vector<string> & candidates) {
    ifstream votes_file ("votes.txt");
    vector<unsigned> voteCounts;
    for (size_t i = 0; i < candidates.size(); ++i)
        voteCounts.push_back(0);

    string line;
    while (getline(votes_file, line)) {
        for (size_t i = 0; i < candidates.size(); ++i) {
            if (line == candidates[i]) {
                ++voteCounts[i];
            }
        }
    }
    return voteCounts;
}

template <typename T>
size_t getMaxIndice (vector<T> Vect) {
    size_t maxInd;
    T maxVal = 0;
    for (size_t i = 0; i < Vect.size(); ++i) {
        if (maxVal < Vect[i]) {
            maxVal = Vect[i];
            maxInd = i;
        }
    }
    return maxInd;
}

template <typename T>
unsigned getMaxValue(vector<T> Vect) {
    T maxVal = 0;
    for (T & elem : Vect) {
        if (maxVal < elem) {
            maxVal = elem;
        }
    }
    return maxVal;
}

bool isTied(vector<unsigned> & voteCounts, unsigned & max) {
    for (size_t i = 0; i < voteCounts.size(); ++i)
        for (size_t y = i+1; y < voteCounts.size(); ++y)
            if ((voteCounts[i] == voteCounts[i]) && voteCounts[i] == max)
                return true;
    return false;
}

template <typename Y>
bool isIn(const Y & element, const vector<Y> & vect) {
    for (const Y & elem : vect)
        if (elem == element)
            return true;
    return false;
}

vector<string> getTies(vector<string> & candidates, vector<unsigned> & voteCounts, unsigned & max) {
    vector<string> ties;

    for (size_t i = 0; i < voteCounts.size()-1; ++i) {
        for (size_t y = i+1; y < voteCounts.size(); ++y) {
            if ((voteCounts[i] == voteCounts[y]) && (voteCounts[i] == max)) {
                if (isIn(candidates[i], ties) == 0) ties.push_back(candidates[i]);
                if (isIn(candidates[y], ties) == 0) ties.push_back(candidates[y]);
            }
        }
    }
    return ties;
}

void printVotes(const vector<string> & candidates, const vector<unsigned> & votes) {
    for (size_t i = 0; i < candidates.size(); ++i)
        cout << candidates[i] << " : " << votes[i] << endl;
}

int main() {
    vector<string> candidates = {"Maxime Noiret", "Hugo Brest-Lestrade", "Hugo Heng", "Wissem Dahmouche", "Martin Demange"};
    unsigned voterCount = 100000;
    generateRandVotes(candidates, voterCount);
    vector<unsigned> votes = countVotes(candidates);
    unsigned maxVote = getMaxValue(votes);
    printVotes(candidates, votes);
    while (getTies(candidates, votes, maxVote).size() > 1) {
        cout << endl << "Tied!" << endl;
        candidates = getTies(candidates, votes, maxVote);
        generateRandVotes(candidates, voterCount);
        votes = countVotes(candidates);
        maxVote = getMaxValue(votes);
        printVotes(candidates, votes);
    }
    cout << "winner is " << candidates[getMaxIndice(votes)] << "!!!" << endl;
}
