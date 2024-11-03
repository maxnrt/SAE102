#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

// NOTE: check if vote counts should stay unsigned or be something else. (unsigned should be enough but who knows)

// NOTE: this function is not used and is only kept to preserve the history of this project.
// generateRandvotes generates a text file (votes.txt) with every single votes in the form of the names of the candidates.
void generateRandVotes(const vector<string> & candidates, const unsigned & voters_cnt) {
    mt19937 mt1(chrono::high_resolution_clock::now().time_since_epoch().count());  // seed RNG with nanosecond clock
    ofstream votes_file ("votes.txt");  // open votes.txt as an output file stream (writing to it)
    for (unsigned i = 0; i < voters_cnt; ++i)  // for every voter,
        votes_file << (candidates[(mt1() % candidates.size())]) << endl;  // add a random vote to votes.txt
    votes_file.close();  // close votes.txt
}

// countVotes returns a list of how many votes each candidate got
vector<unsigned> countVotes (const vector<string> & candidates, const vector<string> & votes) {
    vector<unsigned> voteCounts;  // declare a vector that will hold the amout of votes for each candidates
    for (size_t i = 0; i < candidates.size(); ++i)  // init vector with 0s
        voteCounts.push_back(0);

    string line;
    for (const string & vote : votes)  // for every vote,
        for (size_t i = 0; i < candidates.size(); ++i)  // for every candidate in candidates,
            if (vote == candidates[i])  // if the vote equals the candidate,
                ++voteCounts[i];  // add one to that candidate's votes.
    return voteCounts;
}

// getMaxIndice returns the indice of the highest value in a vector
// NOTE: This function is not used anymore and should be removed.
template <typename T> // T is like a variable type
size_t getMaxIndice (const vector<T> Vect) {
    size_t maxInd;
    T maxVal = 0;
    for (size_t i = 0; i < Vect.size(); ++i)  // for every element in the vector
        if (maxVal < Vect[i]) {  // if maxVal is below the element
            maxVal = Vect[i];  // update maxVal
            maxInd = i;  // update the indice of maxVal
        }
    return maxInd;  // return the indice of maxVal
}

// getMaxValue returns the highest value in a vector
template <typename T>
T getMaxValue(const vector<T> Vect) {
    T maxVal = 0;
    for (const T & elem : Vect) // for every element in the vector
        if (maxVal < elem)  // if maxVal is below the element
            maxVal = elem;  // update maxVal
    return maxVal;  // return maxVal itself
}

// isTied is a predicate that returns true if two candidates have both the same value of votes
//     and if that value is also the highest value in the list
// Note: this function is not used! Why keep it? Because I'm the boss here, I made this code lmao.  (PS 22/10: I don't remember writing this.)
//       Make a pull request on Github to remove it and I'll think about it :)
bool isTied(const vector<unsigned> & voteCounts, const unsigned & max) {
    for (size_t i = 0; i < voteCounts.size(); ++i)  // for every candidates' vote count,
        for (size_t y = i+1; y < voteCounts.size(); ++y)  // for every following candidates' vote count,
            if ((voteCounts[i] == voteCounts[i]) && voteCounts[i] == max)  // if they are both the same and are also equal to max,
                return true;
    return false;  // return false after going through the whole list
}

// isIn is a predicate that returns true if 'element' is present in 'vect'.
template <typename T>
bool isIn(const T & element, const vector<T> & vect) {
    for (const T & elem : vect)  // for every elements in vect,
        if (elem == element)  // if the element is equal to 'element',
            return true;
    return false;  // if we went through the whole list, it means the element wasn't present.
}

// getTies returns a vector of strings containing every candidates that both tied and had the highest value of votes.
vector<string> getTies(const vector<string> & candidates, const vector<unsigned> & voteCounts, const unsigned & max) {
    vector<string> ties;
    for (size_t i = 0; i < voteCounts.size()-1; ++i)  // for every candidates' vote count,
        for (size_t y = i+1; y < voteCounts.size(); ++y)  // for every following candidates' vote count,
            if ((voteCounts[i] == voteCounts[y]) && (voteCounts[i] == max)) {  // if they are both the same and are also equal to max,
                if (isIn(candidates[i], ties) == 0) ties.push_back(candidates[i]);  // add them in the list of tied candidates
                if (isIn(candidates[y], ties) == 0) ties.push_back(candidates[y]);  //     if they aren't already present.
            }
    return ties;
}

// printVotes just exists to make the main() code prettier lol
void printVotes(const vector<string> & candidates, const vector<unsigned> & votes) {
    for (size_t i = 0; i < candidates.size(); ++i)  // for every candidates,
        cout << candidates[i] << " : " << votes[i] << endl;  // show their name and votes count.
}

// inputCandidates lets the user input the candidates through the console. Made for Oracle Test
void inputCandidates(vector<string> & candidates) {
    string input;
    for (;;) {
        //cout << "Type the name for candidate n°" << candidates.size() << ":" << endl;  // ToDo: see with teammates if first candidate should be n°0 or 1
        getline(cin, input);
        if (input.substr(2) == "//") continue;  // if comment, ignore. Used for input files.
        if (input.size() == 0) break;
        candidates.push_back(input);
    }
}

// inputVotes lets the user vote for the candidates through the console. Made for Oracle Test
void inputVotes(const vector<string> & candidates, vector<string> & votes) {
    string input = "";
    for (;;) {
        // cout << "Vote for one of the following candidates: " << endl;
        // for (const string & candidate : candidates)
        //     cout << "\t" << candidate << endl;
        getline(cin, input);
        if (input.substr(2) == "//") continue;  // if comment, ignore. Used for input files.
        if (input.size() == 0) break;
        if (!isIn(input, candidates)) {
            cout << endl << input << " isn't a candidate!" << endl << endl;
            continue;
        }
        votes.push_back(input);
    }
}

int main() {
    // init candidates
    vector<string> candidates;
    inputCandidates(candidates);

    // init votes
    vector<string> votes;
    inputVotes(candidates, votes);

    // make votes usable
    vector<unsigned> candVotes = countVotes(candidates, votes);

    unsigned maxVote = getMaxValue(candVotes);
    //printVotes(candidates, candVotes);
    while (getTies(candidates, candVotes, maxVote).size() > 1) {    // while there are ties,
        cout << endl << "Tied!" << endl;
        candidates = getTies(candidates, candVotes, maxVote);       // only keep the candidates that are tied and
        votes = {};
        inputVotes(candidates, votes);                              // vote again.
        candVotes = countVotes(candidates, votes);
        maxVote = getMaxValue(candVotes);
        //printVotes(candidates, candVotes);
    }
    cout << "Winner is " << candidates[0] << "!!!" << endl;
}
