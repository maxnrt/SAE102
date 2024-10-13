#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;


// generateRandvotes generates a text file (votes.txt) with every singles votes in the form of the names of the candidates.
void generateRandVotes(vector<string> & candidates, unsigned & voters_cnt) {
    mt19937 mt1(chrono::high_resolution_clock::now().time_since_epoch().count());  // seed RNG with nanosecond clock
    ofstream votes_file ("votes.txt");  // open votes.txt as an output file stream (writing to it)
    for (unsigned i = 0; i < voters_cnt; ++i) {  // for every voter,
        //cout << "candidates.size() = " << candidates.size() << endl;
        votes_file << (candidates[(mt1() % candidates.size())]) << endl;  // add a random vote to votes.txt
    }
    votes_file.close();  // close votes.txt
}

// countVotes returns a list of how many votes each candidate got
vector<unsigned> countVotes (vector<string> & candidates) {
    ifstream votes_file ("votes.txt");  // open votes.txt as an input file stream (reading from it)
    vector<unsigned> voteCounts;  // declare a vector that will hold the amout of votes for each candidates
    for (size_t i = 0; i < candidates.size(); ++i)  // init vector with 0s
        voteCounts.push_back(0);

    string line;
    while (getline(votes_file, line)) {  // for every line in votes.txt
        for (size_t i = 0; i < candidates.size(); ++i) {  // for every candidate in candidates
            if (line == candidates[i]) {  // if the line equald the candidate
                ++voteCounts[i];  // add one to that candidate's votes
            }
        }
    }
    return voteCounts;
}

// getMaxIndice returns the indice of the highest value in a vector
template <typename T>
size_t getMaxIndice (vector<T> Vect) {
    size_t maxInd = 0;
    T maxVal = 0;
    for (size_t i = 0; i < Vect.size(); ++i) {  // for every element in the vector
        if (maxVal < Vect[i]) {  // if maxVal is below the element
            maxVal = Vect[i];  // update maxVal
            maxInd = i;  // update the indice of maxVal
        }
    }
    return maxInd;  // return the indice of maxVal
}

// getMaxValue returns the highest value in a vector
template <typename T>
unsigned getMaxValue(vector<T> Vect) {
    T maxVal = 0;
    for (T & elem : Vect) {  // for every element in the vector
        if (maxVal < elem) {  // if maxVal is below the element
            maxVal = elem;  // update maxVal
        }
    }
    return maxVal;  // return maxVal itself
}

// isTied is a predicate that returns true if two candidates have both the same value of votes
//     and if that value is also the highest value in the list
// Note: this function is not used! Why keep it? Because I'm the boss here, I made this code lmao.
//       Make a pull request on Github to remove it and I'll think about it :)
bool isTied(vector<unsigned> & voteCounts, unsigned & max) {
    for (size_t i = 0; i < voteCounts.size(); ++i)  // for every candidates' vote count,
        for (size_t y = i+1; y < voteCounts.size(); ++y)  // for every following candidates' vote count,
            if ((voteCounts[i] == voteCounts[i]) && voteCounts[i] == max)  // if they are both the same and are also equal to max,
                return true;
    return false;  // return false after going through the whole list
}

// isIn is a predicate that returns true if 'element' is present in 'vect'.
template <typename Y>
bool isIn(const Y & element, const vector<Y> & vect) {
    for (const Y & elem : vect)  // for every elements in vect,
        if (elem == element)  // if the element is equal to 'element',
            return true;
    return false;  // if we went through the whole list, it means the element wasn't present.
}

template <typename T>
double getPercentage(const T & total, const T & elem) {
    return elem / double(total) * 100;
}

// printVotes just exists to make the main() code prettier lol
void printVotes(const vector<string> & candidates,
                const vector<unsigned> & votes,
                const unsigned & voterCount) {
    for (size_t i = 0; i < candidates.size(); ++i)  // for every candidates,
        cout << candidates[i] << " : " << votes[i]
             << " " << getPercentage(voterCount, votes[i]) << "%" << endl;  // show their name, votes count and vote percentage.
}

// getMajority returns the index of the candidate with the majority (>50%) of votes.
//     if none, returns size of candidates/votes vector.
size_t getMajority(const vector<unsigned> & votes, const unsigned & voterCount) {
    for (size_t i = 0; i < votes.size(); ++i) {
        if (getPercentage(voterCount, votes[i]) > 50) {
            return i;
        }
    }
    return votes.size();
}

// This function sucks
vector<size_t> getTwoBest(const vector<unsigned> & votes) {
    vector<unsigned> tmp = votes;
    vector<size_t> ret;
    ret.push_back(getMaxIndice(tmp));
    tmp[getMaxIndice(tmp)] = 0;
    ret.push_back(getMaxIndice(tmp));
    return ret;
}

// band-aid for the previous function lol
bool hasNone(vector<string> & vect) {
    for (string & elem : vect)
        if (elem == "None")
            return true;
    return false;
}

int main()
{
    vector<string> candidates = {"Maxime Noiret",
                                 "Hugo Brest-Lestrade",
                                 "Hugo Heng",
                                 "Wissem Dahmouche",
                                 "Martin Demange"};
    //vector<unsigned> votes = {49, 10, 29, 8, 4};
    if (hasNone(candidates)) {
        cout << "candidates vector has element 'None'. Exiting..." << endl;
        return 1;
    }
    unsigned voterCount = 250000;
    generateRandVotes(candidates, voterCount);
    vector<unsigned> votes = countVotes(candidates);
    printVotes(candidates, votes, voterCount);
    size_t majorityInd = getMajority(votes, voterCount);
    if (majorityInd != votes.size())
        cout << candidates[majorityInd] << " wins by majority!" << endl;
    else {
        candidates = {candidates[getTwoBest(votes)[0]],
                      candidates[getTwoBest(votes)[1]]};
        cout << "Nobody has majority. Second round between "
             << candidates[0] << " and "
             << candidates[1] << " will now begin." << endl;
        generateRandVotes(candidates, voterCount);
        votes = countVotes(candidates);
        printVotes(candidates, votes, voterCount);
        cout << candidates[getMajority(votes, voterCount)] << " wins in the second round!" << endl;
    }
    return 0;
}