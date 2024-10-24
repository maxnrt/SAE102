#include <iostream>
#include <fstream>
#include <random>  // unused
#include <chrono>  // unused

using namespace std;

// NOTE: check if vote counts should stay unsigned or be something else. (unsigned should be enough but who knows)
//           replaced it with unsigned long because stou doesn't exist, whereas stoul does.

struct voters {
    string lName;
    string fName;
    unsigned vote;
};
struct candidate {
    string name;
    unsigned long votes;
};


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
        if (maxVal < Vect[i]) {  // if maxVal is belowinput[0] == '/' && input[1] == '/' the element
            maxVal = Vect[i];  // update maxVal
            maxInd = i;  // update the indice of maxVal
        }
    return maxInd;  // return the indice of maxVal
}

size_t getMaxVotes (const vector<candidate> & vCandidates) {
    size_t maxInd = 0;
    unsigned long maxVal = 0;
    for (size_t i = 0; i < vCandidates.size(); ++i)
        if (maxVal < vCandidates[i].votes) {
            maxVal = vCandidates[i].votes;
            maxInd = i;
        }
    return maxInd;
}

// isIn is a predicate that returns true if 'element' is present in 'vect'.
template <typename Y>
bool isIn(const Y & element, const vector<Y> & vect) {
    for (const Y & elem : vect)  // for every elements in vect,
        if (elem == element)  // if the element is equal to 'element',
            return true;
    return false;  // if we went through the whole list, it means the element wasn't present.
}


// printVotes just exists to make the main() code prettier lol
//     this version, unlike the version in system1, also shows vote percentage.
void printVotes(const vector<candidate> & vCandidates, const unsigned voterCount) {
    for (candidate cand : vCandidates)  // for every candidates,
        cout << cand.name << " : " << cand.votes
             << " " << cand.votes / double(voterCount) * 100 << "%" << endl;  // show their name, votes count and vote percentage.
}

// getMajority returns the index of the candidate with the majority (>50%) of votes.
//     if none, returns size of candidates/votes vector.
size_t getMajority(const vector<candidate> & vCandidates, const unsigned & voterCount) {
    for (size_t i = 0; i < vCandidates.size(); ++i)
        if (vCandidates[i].votes >= float(voterCount) * 0.5)
            return i;
    return vCandidates.size();
}

// This function sucks
vector<size_t> getTwoBest(const vector<candidate> & vCand) {
    vector<candidate> tmp = vCand;
    vector<size_t> ret;
    ret.push_back(getMaxVotes(tmp));
    tmp[getMaxVotes(tmp)].votes = 0;
    ret.push_back(getMaxVotes(tmp));
    return ret;
}



// inputCandidates lets the user input the candidates through the console. Made for Oracle Test
void inputCandidates(vector<string> & candidates) {
    string input;
    for (;;) {
        cout << "Type the name for candidate n°" << candidates.size() << ":" << endl;  // ToDo: see if first candidate should be n°0 or 1
        getline(cin, input);  // another getline if first name AND last name are both needed.
        if (input.size() == 0) break;
        candidates.push_back(input);
    }
}

// inputVotes lets the user vote for the candidates through the console. Made for Oracle Test
// ToDo: replace this without outputs
void inputVotes(vector<candidate> & vCandidates, vector<voters> & vVoters) {
    string temp;
    for (;;) {
        //cout << "Vote for one of the following candidates: " << endl;
        //for (const string & candidate : candidates)
        //    cout << "\t" << candidate << endl;

        // Note: probably should place comment and end check at every getline, but if input file is incorrect it's not my fault :p
        getline(cin, temp);
        if (temp.substr(0, 2) == "//") continue;  // if comment, ignore
        if (temp.size() == 0) break;
        vVoters.push_back(voters {"", "", 0});
        vVoters[vVoters.size()].lName = temp;  // get last name
        getline(cin, vVoters[vVoters.size()].fName);  // get first name
        getline(cin, temp);  // get vote
        vVoters[vVoters.size()].vote = stoul(temp);
        ++vCandidates[stoul(temp)].votes;
    }
}



int main() {
    vector<candidate> vCandidates;

    // ToDo: replace this without outputs and taking into account '//' from input file, also put it in a
    string input;
    for (;;) {
        //cout << "Type the name for candidate n°" << nbr << ": ";
        getline(cin, input);
        if (input[0] == '/' && input[1] == '/') continue;
        if (input.size() == 0) break;
        vCandidates.push_back(candidate {input, 0});;
    }


    vector<voters> vVoters;
    inputVotes(vCandidates, vVoters);
    unsigned voterCount = vVoters.size();

    // This is... hideous. Worse even than my hand writing. I regret ever writing this.
    // Whoever is reading this, I apologize to your very soul for laying eyes on this crime against humanity.
    printVotes(vCandidates, voterCount);
    size_t majorityInd = getMajority(vCandidates, voterCount);
    if (majorityInd != vCandidates.size())
        cout << vCandidates[majorityInd].name << " wins by majority with "
             << vCandidates[majorityInd].votes << " votes!" << endl;
    else {
        vCandidates = {vCandidates[getTwoBest(vCandidates)[0]],
                       vCandidates[getTwoBest(vCandidates)[1]]};  // I know I'm calling the function twice, but I didn't want to use a whole var
        cout << "Nobody has majority. Second round between "
             << vCandidates[0].name << " and "
             << vCandidates[1].name << " will now begin." << endl;
        //votes = {};
        inputVotes(vCandidates, vVoters);
        voterCount = vVoters.size();

        printVotes(vCandidates, voterCount);
        cout << vCandidates[getMajority(vCandidates, voterCount)].name << " wins in the second round!" << endl;
    }
    return 0;
}
