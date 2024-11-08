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

struct participant {
    string nom;
    string prenom;
    int glacePref;
};

bool compare2part (const participant & p1, const participant & p2){
    return p1.prenom < p2.prenom;
}

void affichVectString (const vector<string> & v){
    for (const string & val : v)
        cout << val << '\t';
    cout << endl;
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
    //cout << "Hello World!" << endl;
    //vector<participant> vParticipant (19);
    /* on va detecter les glaces preférées des votants
    * tout en virant les commentaires
    */

    /* on vote sur 4 glaces */
    vector <string> vGlacePref;
    for (unsigned i (0); i < 4; ++i)
        vGlacePref.push_back(litUneString());

/* debug */
    affichVectString (vGlacePref);

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

        cout << "c'est la glace " << vGlacePref[0] << " qui a gagne" << endl;
    return 0;
}
