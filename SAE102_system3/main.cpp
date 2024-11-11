/**
 *  @date : 22 octobre 2024
 *  @author : Alain Casali
 *  @Brief : une prmière réponse à la SAE 1.02 de 24/25
**/
#include <iostream>
#include <vector>
#include <algorithm>

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

    // on prend les votes
    for (;;) {
        input = litUneString();
        if (input.size() == 0) break;
        vParticipant.push_back({input, litUneString(), litUnEntier()});
        // Ceci assume que le format des participants est le suivant:
        // NOM
        // PRENOM
        // X (numéro indiquant le vote)
    }

    // on traite les votes
    size_t voteIndice;
    for (const participant & part : vParticipant) {
        voteIndice = abs(part.glacePref);
        if (part.glacePref < 0)
            --vGlacePref[voteIndice].votes;
        else if (part.glacePref > 0)
            ++vGlacePref[voteIndice].votes;
        else
            cerr << "Erreur d'entrée! Le vote ne doit pas être 0!" << endl;
    }

    affichVectCand (vGlacePref);  // à enlever, uniquement pour debug

    // faut enlever cette partie qui ne sert à rien
    affichVectParticipants(vParticipant);
    cout << string (15, '-') << endl;
    sort (vParticipant.begin(), vParticipant.end(), compare2part);
    affichVectParticipants(vParticipant);
    // fin

    // EN GROS ce qu'il faut faire:
    //     - prendre les candidats (fait)
    //     - prendre les voteurs et leur vote positif ou négatif (fait)
    //     - modifier le nombre de votes de chaque candidat (fait)
    //     - choisir un gagnant parmi les candidats, et traiter le cas si égalité

    cout << "C'est la glace " << vGlacePref[0].name << " qui a gagné avec " << vGlacePref[0].votes << " votes." << endl;
    return 0;
}
