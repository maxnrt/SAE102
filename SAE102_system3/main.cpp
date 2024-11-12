/**
 *  @date : 22 octobre 2024
 *  @author : Alain Casali
 *  @Brief : une prmière réponse à la SAE 1.02 de 24/25
**/
#include <iostream>
#include <vector>
//#include <algorithm>

using namespace std;

/*
sys de vote par ponderation ternaire

    dans ce sys on vote soit en positif (ce qui ajoute un vote au candidat), soit en négatif (ce qui enlève un vote au candidat)
    donc chaque vote est formatter de la manière suivante:
    NOM
    PRÉNOM
    x OU -x (avec x étant l'indice du candidat + 1)

*/

/**
 * @brief litUneString
 * @return la chaine lue sauf si :
 * (1) on une boulette sur l'entrée
 * (2) on trouve un commentaire sur l'entrée
 * le commentaire est matérialisé par la chaine "//"
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

bool compare2part (const participant & p1, const participant & p2){
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

vector <size_t> indexDesEgalites (const vector<candidate> & vCandidats, const int votesMax)
{
    vector<size_t> retVect;
    for (size_t i = 0; i < vCandidats.size(); ++i) {
        if (vCandidats[i].votes == votesMax) {
            retVect.push_back(i);
        }
    }
    return retVect;
}

void entreeDesVotes (vector<participant> & vParticipant) {
    // on prend les votes*
    string input;
    for (;;) {
        input = litUneString();
        if (input.size() == 0) break;
        vParticipant.push_back({input, litUneString(), litUnEntier()});
        // Ceci assume que le format des participants est le suivant:
        // NOM
        // PRENOM
        // X (numéro indiquant le vote)
    }
}

void choixGagnant (const vector<candidate> & vGlacePref, size_t & indexGagn, int & votesGagn) {
    votesGagn = 0;
    indexGagn = 0;
    for (size_t u=0 ; u < size(vGlacePref); ++u )
    {
        if (vGlacePref[u].votes > votesGagn)
        {
            indexGagn = u;
            votesGagn = vGlacePref[u].votes;
        }
    }
}

void traitementVotes (vector<candidate> & vGlacePref, const vector<participant> & vParticipant) {
    size_t voteIndice;
    for (const participant & part : vParticipant) {
        voteIndice = abs(part.glacePref);
        if (part.glacePref < 0)
            --vGlacePref[voteIndice-1].votes;
        else if (part.glacePref > 0)
            ++vGlacePref[voteIndice-1].votes;
    }
}

int main()
{
    vector <participant> vParticipant;
    vector <candidate> vGlacePref;

    // on vote sur x glace
    string input;
    for (;;) {
        input = litUneString();
        if (input.size() == 0) break;
        vGlacePref.push_back({input, 0});
    }

    entreeDesVotes(vParticipant);

    // on traite les votes
    traitementVotes(vGlacePref, vParticipant);



    // faut enlever cette partie qui ne sert à rien
    // fin

    // EN GROS ce qu'il faut faire:
    //     - prendre les candidats (fait)
    //     - prendre les voteurs et leur vote positif ou négatif (fait)
    //     - modifier le nombre de votes de chaque candidat (fait)
    //     - choisir un gagnant parmi les candidats, et traiter le cas si égalité



    //Choix du gagnant + cas egalité :
    // choix du gagnant :
    int votesGagnant = 0;
    size_t indexGagnant = 0;
    vector<size_t> indexEgalites;
    choixGagnant(vGlacePref, indexGagnant, votesGagnant);
    // cas de l'égalité :
    affichVectCand (vGlacePref);  // à enlever, uniquement pour debug
    vector<candidate> vGlacePrefDeux;
    for (;;) {
        indexEgalites = indexDesEgalites(vGlacePref, votesGagnant);
        if (indexEgalites.size() == 1) break;
        cout << endl << "Égalité!" << endl;
        vGlacePrefDeux = {};
        for (const size_t & ind : indexEgalites)
            vGlacePrefDeux.push_back(vGlacePref[ind]);
        vGlacePref = vGlacePrefDeux;
        for (candidate & cand : vGlacePref)
            cand.votes = 0;
        entreeDesVotes(vParticipant);
        traitementVotes(vGlacePref, vParticipant);
        choixGagnant(vGlacePref, indexGagnant, votesGagnant);
        affichVectCand(vGlacePref);
    }
    cout << "C'est la glace " << vGlacePref[indexGagnant].name << " qui a gagné avec " << votesGagnant << " votes." << endl;
    return 0;
}
