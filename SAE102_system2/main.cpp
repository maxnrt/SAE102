#include <iostream>
#include <fstream>
#include <random>  // unused
#include <chrono>  // unused

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
    // This is very unoptimized, but it works. It's not like they're gonna make us test 200000 votes, right...?
    for (const string & vote : votes)  // for every vote,
        for (size_t i = 0; i < candidates.size(); ++i)  // for every candidate in candidates,
            if (vote == candidates[i]) {  // if the vote equals the candidate,
                ++voteCounts[i];  // add one to that candidate's votes.
                break;  // go to the next vote.
            }
    return voteCounts;
}

// getMaxIndice returns the indice of the highest value in a vector
template <typename T>
size_t getMaxIndice (const vector<T> Vect) {
    size_t maxInd = 0;
    T maxVal = 0;
    for (size_t i = 0; i < Vect.size(); ++i)  // for every element in the vector
        if (maxVal < Vect[i]) {  // if maxVal is below the element
            maxVal = Vect[i];  // update maxVal
            maxInd = i;  // update the indice of maxVal
        }
    return maxInd;  // return the indice of maxVal
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
//     this version, unlike the version in system1, also shows vote percentage.
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
    for (size_t i = 0; i < votes.size(); ++i)
        if (votes[i] >= float(voterCount) * 0.5)
            return i;
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

// inputCandidates lets the user input the candidates through the console. Made for Oracle Test
void inputCandidates(vector<string> & candidates) {
    string input;
    for (;;) {
        cout << "Type the name for candidate n°" << candidates.size() << ":" << endl;  // ToDo: see if first candidate should be n°0 or 1
        getline(cin, input);
        if (input.size() == 0) break;
        candidates.push_back(input);
    }
}

// inputVotes lets the user vote for the candidates through the console. Made for Oracle Test
// ToDo: replace this without outputs
void inputVotes(const vector<string> & candidates, vector<string> & votes) {
    string input = "";
    for (;;) {
        cout << "Vote for one of the following candidates: " << endl;
        for (const string & candidate : candidates)
            cout << "\t" << candidate << endl;
        getline(cin, input);
        if (input.size() == 0) break;
        if (!isIn(input, candidates)) {
            cout << endl << input << " isn't a candidate!" << endl << endl;
            continue;
        }
        votes.push_back(input);
    }
}

// This thing is awesome thank you teach
struct voters {
    string lName;
    string fName;
    unsigned vote;
};
struct candidates {
    string lname;
    string fname;
    unsigned votes;
};

int main() {
    vector<string> candidates;
    unsigned nbr = 0;

    // ToDo: replace this without outputs and taking into account '//' from input file, also put it in a procedure
    string input;
    for (;;) {
        cout << "Type the name for candidate n°" << nbr << ": ";
        getline(cin, input);
        if (input.size() == 0) break;
        candidates.push_back(input);
        ++nbr;
    }


    vector<voters> vVoteurs;
    inputVotes(candidates, votes);
    unsigned voterCount = votes.size();

    vector<unsigned> candVotes = countVotes(candidates, votes);
    printVotes(candidates, candVotes, voterCount);
    size_t majorityInd = getMajority(candVotes, voterCount);
    if (majorityInd != candVotes.size())
        cout << candidates[majorityInd] << " wins by majority!" << endl;
    else {
        candidates = {candidates[getTwoBest(candVotes)[0]],
                      candidates[getTwoBest(candVotes)[1]]};  // I know I'm calling the function twice, but I didn't want to use a whole var
        cout << "Nobody has majority. Second round between "
             << candidates[0] << " and "
             << candidates[1] << " will now begin." << endl;
        votes = {};
        inputVotes(candidates, votes);
        voterCount = votes.size();

        candVotes = countVotes(candidates, votes);
        printVotes(candidates, candVotes, voterCount);
        cout << candidates[getMajority(candVotes, voterCount)] << " wins in the second round!" << endl;
    }
    return 0;
}
