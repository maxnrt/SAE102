#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;



// Premièrement, si tu modifies pas ta variable dans la fonction, met la comme CONSTANTE je t'en SUPPLI
// Deuxièmement, si t'as une variable d'index, met la de type SIZE_T!! Le prof l'a dit 800 fois (au moins)

unsigned rng (const unsigned max)
{
    std::srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    return rand() % max;
}


// Cette fonction ne doit plus être utilisé car on prend les input de la console pour que ce soit compatible avec test Oracles!!
void generateRandVotes(const vector<string> & candidats, const unsigned & voters_cnt, vector<unsigned> & votes_eus)
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
    for (size_t a = 0; a < size(votes_eus); ++a)
    {
        cout << "Le candidat " << candidats[a] << " a obtenu " << votes_eus[a] << " votes !" << endl;
    }
    cout << endl ;
}


size_t QuiALaMajorite(const size_t & nombreCandidats, const vector<unsigned> & votes_eus)  // constante
{
    for (size_t y = 0; y < size(votes_eus); ++y)  // size_t
    {
        if (votes_eus[y] >= nombreCandidats/2 )
            return  y;
        else
            return size(votes_eus);
    }
    return false;
}

size_t quiALeMoinsDeVotes (const vector<string> & candidats, const vector<unsigned> & vote_eus)  // constante
{
    vector<string> candidats2;
    unsigned tmp = vote_eus[0];
    size_t indice_tmp = 0;  // size_t
    for (size_t u = 0; u < size(candidats); ++u)  // size_t
    {
        if (vote_eus[u] < tmp)
        {
            tmp = vote_eus[u];
            indice_tmp = u;
        }
    }
    for (size_t z = 0; z < size(candidats); ++z)  // size_t
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
    for (size_t i = 0; i < size(candidats); ++i )  // constante
    {
        cout << candidats[i] << endl ;
    }
}

vector<unsigned> metAJourLesVotes (const vector<string> & candidats)  // constante
{
    vector<unsigned> vote2;
    for (size_t b = 0 ; b < size(candidats)-1 ; ++b)  // size_t
    {
            vote2.push_back(0);
    }
    return vote2;
}

vector<string> metAJourLesCandidats (size_t & tmp, vector<string> & candidats)
{
    vector<string> candidats2;
    for (size_t c = 0 ; c < size(candidats) ; ++c)  // size_t
    {
        if (c == tmp)
        {
            cout << "le candidat " << candidats[tmp] << "  est éliminé" << endl << endl;
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
                                "Marc Assain"};  // doit être enlevé et être remplacé par input console
    // oi Hugo, utilise ça pour entrer les candidats avec la console pour que ça marche avec fichier Oracle
    // vector<string> candidats = inputCandidates();
    size_t nombreCandidats = size(candidats) ;
    vector<unsigned> vote_eus = {0,0,0,0,0,0,0,0} ;  // doit être enlevé et être remplacé par input console
//  afficherVecteur(candidats);
    unsigned nombreVoteurs = 100 ;
    generateRandVotes(candidats, nombreVoteurs, vote_eus) ;  // doit être enlevé et être remplacé par input console
    string nomGagnant ;  // à quoi sert cette string? dans le message tu peux juste mettre genre candidats[gagnant] comme tu fais avec les votes
    size_t tmp;  // size_t
    size_t gagnant = 0;  // size_t
    unsigned compteurTour = 0;
    cout << compteurTour + 1 << "tour ! " << endl << endl ;  // euh... commence le à 1 au pire? Et puis il est pas dans la boucle...?
    while (true)
    {

        tmp = quiALeMoinsDeVotes(candidats,vote_eus); // Donne l'indice du mec avec le moins de votes

        vote_eus = metAJourLesVotes(candidats);        //On met a jour les votes

        candidats = metAJourLesCandidats(tmp, candidats);   //On met a jour les candidats

        gagnant = QuiALaMajorite(nombreCandidats, vote_eus);

        cout << gagnant << endl << endl ;
        cout << size(vote_eus) << endl << endl;
        afficherVecteur(candidats);
        cout << candidats[0] << endl;
        cout << candidats[1] << endl;
        if (size(vote_eus) == 2)
        {
            

        
            
            if (vote_eus[0] > vote_eus[1])
            {
                cout << "Le candidat" << candidats[0] << "A gagné" << endl;
                break;
            }
            else 
            {
                cout << "le candidat" << candidats[1] << "a gagné" << endl;
                break;
            }
            //JE MET CEUX LA EN COMMENTAIRE POUR TEST UN TRUC
            //gagnant = QuiALaMajorite(nombreVoteurs, vote_eus);
            //nomGagnant = candidats[gagnant];                                 // ICI çA CRASH A 2, REPRENDRE D'ICI
            //cout << "Le candidat " << nomGagnant << " est élu avec " << vote_eus[gagnant] << " votes !" << endl;
        }
        else
        {
            nomGagnant = candidats[gagnant];
            cout << "Le candidat " << nomGagnant << " est élu avec " << vote_eus[gagnant] << " votes !" << endl;
            break;
        }
        generateRandVotes(candidats, nombreVoteurs, vote_eus);



    }


    return 0;
}



















