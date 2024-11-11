/**
 *  @date : 22 octobre 2024
 *  @author : Alain Casali
 *  @Brief : une prmière réponse à la SAE 1.02 de 24/25
**/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief litUneString
 * @return la chaine lue sauf si :
 * (1) on une boulette sur l'entrée
 * (2) on trouve un commentaire sur l'entrée
 * le commentaire est matérialisé par la chaine "//"
 */

/*
sys de vote par ponderation ternaire

    dans ce sys on vote en disant l'option qu'on aime le moin ( on met -1 ) ou celle qu'on aime ( +1) -> le canditat a un ratio like et dislike et est elue si il a un ratio avantageu.

*/
string litUneString (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//")) break;
    }
    return uneChaine;
}

int litUnEntier (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//")) break;
    }
    return stoi(uneChaine);
}

struct participant { // sruct pour les voteurs
    string nom;
    string prenom;
    int glacePref;
};

struct candidate { // pour les candidats
    string name;
    int votes;
};

// void inputVotes(vector<voters> & vVoters) { // bloc venant du sys 2
//     string temp;
//     for (;;) {
//         // cout << "Vote for one of the following candidates: " << endl;
//         // for (const candidate & ccandidate : vCandidates)
//         //     cout << "\t" << ccandidate.name << endl;

//         // Note: probably should place comment and end check at every getline, but if input file is incorrect it's not my fault :p
//         getline(cin, temp);
//         if (temp.substr(0, 2) == "//") continue;  // if comment, ignore
//         if (temp.size() == 0) break;
//         vVoters.push_back(voters {"", "", 0});
//         vVoters[vVoters.size()-1].lName = temp;  // get last name
//         getline(cin, vVoters[vVoters.size()-1].fName);  // get first name
//         getline(cin, temp);  // get vote
//         vVoters[vVoters.size()-1].vote = stoul(temp);
//     }
// }

// à quoi sert cette fonction?
bool c0ompare2part (const participant & p1, const participant & p2){
    return p1.prenom < p2.prenom;
}

void affichVectString (const vector<string> & v){
    for (const string & val : v)
        cout << val << '\t';
    cout << endl;
}

void affichVectCand (const vector<candidate> & v){
    for (const candidate & cand : v)
        cout << cand.name << " : " << cand.votes << endl;
}

void affichVectParticipants (const vector<participant> & vPart){
    for (const participant & part : vPart){
        cout << part.nom << endl;
        cout << part.prenom << endl;
        cout << part.glacePref << endl;
    }
}

int main()
{
    //candidat1 = participant("Robert", "Maxence", 0);
    //vector<participant> vParticipant (19);
    /* on va detecter les glaces preférées des votants
    * tout en virant les commentaires
    */

    vector <participant> vParticipant;
    vector <candidate> vGlacePref;

    // on vote sur 4 glace
    // Max: Pas sure de cette boucle perso, il va pas avoir les 4 glaces à cause des commentaires.
    for (unsigned i (0); i < 4; ++i)
        vGlacePref.push_back({litUneString(), 0});

/* debug */
    affichVectCand (vGlacePref);
    //On lit les datas du clavier, et on les stocke
/*    vector<participant> vParticipant;

    for (unsigned i (0); i < 10; ++i){
        string nom (litUneString());
        string prenom  (litUneString());
        int numGlace (litUnEntier());
        //cout << nom << endl << prenom << endl << numGlace << endl;
        vParticipant.push_back(participant{nom, prenom, numGlace});
              //  vJoueur[numEquipe-1].push_back(joueur {nom, prenom, numEquipe});
    }

    affichVectParticipants(vParticipant);
    cout << string (15, '-') << endl;
    sort (vParticipant.begin(), vParticipant.end(), compare2part);
    affichVectParticipants(vParticipant);
*/

        cout << "c'est la glace " << vGlacePref[0].name << " qui a gagne" << endl;
    return 0;
}
