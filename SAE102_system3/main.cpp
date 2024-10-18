#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;



unsigned rng (unsigned max)
{
    std::srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    return rand() % max;
}



void generateRandVotes(vector<string> & candidats, unsigned & voters_cnt, vector<unsigned> & votes_eus)
{
    ofstream votes_file ("votes.txt");  // open votes.txt
    for (size_t i = 0; i < voters_cnt; ++i) {  // for every voter,
        votes_file << (candidats[rng(unsigned(candidats.size()))]) << endl;  // add a random vote to votes.txt
        this_thread::sleep_for(chrono::milliseconds(5));  // wait a few milliseconds to increase randomness
    }
    votes_file.close();  // close votes.txt
    ifstream votes_fileout ("votes.txt");
    string line ;
    while (getline(votes_fileout, line))
    {
        for (size_t j = 0; j < size(candidats); ++j)
        {
            if (line == candidats[j])
                ++votes_eus[j];

        }
    }
    for (unsigned a = 0; a < size(votes_eus); ++a)
    {
        cout << "Le candidat " << candidats[a] << " a obtenu " << votes_eus[a] << " votes !" << endl;
    }
    cout << endl ;
}


size_t QuiALaMajorite(unsigned & nombreVoteurs, vector<unsigned> & votes_eus)
{
    for (unsigned y = 0; y < size(votes_eus); ++y)
    {
        if (votes_eus[y] >= nombreVoteurs/2 )
            return  y;
        else
            return size(votes_eus);
    }
    return false;
}

size_t quiALeMoinsDeVotes (vector<string> & candidats, vector<unsigned> & vote_eus)
{
    vector<string> candidats2;
    unsigned tmp = vote_eus[0];
    unsigned indice_tmp = 0;
    for (unsigned u = 0; u < size(candidats); ++u)
    {
        if (vote_eus[u] < tmp)
        {
            tmp = vote_eus[u];
            indice_tmp = u;
        }
    }
    for (unsigned z = 0; z < size(candidats); ++z)
    {
        if (z == indice_tmp)continue;
        else
        {
            candidats2.push_back(candidats[z]);
        }
    }
    return indice_tmp;


}


void afficherVecteur (const vector<string> & candidats)
{
    for (unsigned i = 0; i < size(candidats); ++i )
    {
        cout << candidats[i] << endl ;
    }
}

vector<unsigned> metAJourLesVotes (vector<string> & candidats)
{
    vector<unsigned> vote2;
    for (unsigned b = 0 ; b < size(candidats)-1 ; ++b)
    {
            vote2.push_back(0);
    }
    return vote2;
}

vector<string> metAJourLesCandidats (unsigned & tmp, vector<string> & candidats)
{
    vector<string> candidats2;
    for (unsigned c = 0 ; c < size(candidats) ; ++c)
    {
        if (c == tmp)
        {
            cout << "le candidat " << candidats[tmp] << "  se fait tej" << endl << endl;
            continue;
        }
        else
            candidats2.push_back(candidats[c]);
    }
    return candidats2;
}

vector<string> inputCandidates() {
    vector<string> ret;
    string input;
    for (;;) {
        cout << "Entrez le candidat n°" << ret.size()+1 << ": ";
        getline(cin, input);
        if (input.size() == 0) break;
        ret.push_back(input);
    }
    return ret;
}

// isIn is a predicate that returns true if 'element' is present in 'vect'.
template <typename Y>
bool isIn(const Y & element, const vector<Y> & vect) {
    for (const Y & elem : vect)  // for every elements in vect,
        if (elem == element)  // if the element is equal to 'element',
            return true;
    return false;  // if we went through the whole list, it means the element wasn't present.
}

// Oi Hugo, voila une fonction cool, mais jte laisse trouver comment l'utiliser pour que ça fonctionne bien
vector<string> inputVotes(const vector<string> & candidates) {
    vector<string> votes;
    string input;
    for (;;) {
        cout << "Vote for one of the following candidates: " << endl;
        for (const string & candidate : candidates)
            cout << "\t" << candidate << endl;
        getline(cin, input);
        if (input.size() == 0) break;
        if (!isIn(input, candidates)) {
            cout << "\"" << input << "\" n'est pas dans la liste des candidats!" << endl;
            continue;
        }
        votes.push_back(input);
    }
    return votes;
}




// Système de vote alternatif
int main()
{
    vector<string> candidats = {"Zoro",
                                "Jacques Ouzi",
                                "Larry Golade",
                                "Remi Fasol",
                                "Sacha Hutte" ,
                                "Yvan Dulé",
                                "Huberts Eats",
                                "Marc Assain"};
    // oi Hugo, utilise ça pour entrer les candidats avec la console pour que ça marche avec fichier Oracle
    // vector<string> candidats = inputCandidates();
    vector<unsigned> vote_eus = {0,0,0,0,0,0,0,0} ;
//  afficherVecteur(candidats);
    unsigned nombreVoteurs = 100 ;
    generateRandVotes(candidats, nombreVoteurs, vote_eus) ;
    string nomGagnant ;
    unsigned tmp;
    unsigned gagnant = 0;
    unsigned compteurTour = 0;
    cout << compteurTour + 1 << "tour ! " << endl << endl ;
    while (true)
    {

        tmp = quiALeMoinsDeVotes(candidats,vote_eus); // Donne l'indice du mec avec le moins de votes

        vote_eus = metAJourLesVotes(candidats);        //On met a jour les votes

        candidats = metAJourLesCandidats(tmp, candidats);   //On met a jour les candidats

        gagnant = QuiALaMajorite(nombreVoteurs, vote_eus);

        cout << gagnant << endl << endl ;
        cout << size(vote_eus) << endl << endl;
        if (size(vote_eus) == 2)
        {
            gagnant = QuiALaMajorite(nombreVoteurs, vote_eus);
            nomGagnant = candidats[gagnant];                                 // ICI çA CRASH A 2, REPRENDRE D'ICI
            cout << "Le candidat " << nomGagnant << " est élu avec " << vote_eus[gagnant] << " votes !" << endl;
        }
        else if (gagnant == size(candidats))
            generateRandVotes(candidats, nombreVoteurs, vote_eus);

        else
        {
            nomGagnant = candidats[gagnant];
            cout << "Le candidat " << nomGagnant << " est élu avec " << vote_eus[gagnant] << " votes !" << endl;
            break;
        }


    }


    return 0;
}



















