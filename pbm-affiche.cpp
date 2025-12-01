#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 **/
void affichePBM(string source)  {
    ifstream fluxin;
    fluxin.open(source);
    if (!fluxin.is_open()) {
        cout << "Error opening the file " << endl;
    }
    //ELEMENTS
    string type_pbm;//Contains P1
    int hauteur;
    int largeur;
    int pixel;
    //
    fluxin >> type_pbm; //Reads P1
    fluxin >> largeur; //Reads 10
    fluxin >> hauteur; //Reads 10
    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            fluxin >> pixel;
            if (pixel == 1) {
                cout << "@";
            } else if (pixel == 0) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

            

/** Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 **/
void inversePBM(string source, string cible) {
    //File stream declarations
    ifstream fluxin;
    ofstream fluxout;
    fluxin.open(source);
    fluxout.open(cible);
    //

    //Error testing
    if (!fluxin.is_open()) {
        cout << "Error opening the file" << endl;
    }

    if (!fluxout.is_open()) {
        cout << "Error creating the file" << endl;
    }
    //

    //Elements
    string type_pbm;
    int hauteur, largeur;
    int pixel;
    //

    //File reading and output
    fluxin >> type_pbm;
    fluxin >> largeur >> hauteur;

    fluxout << type_pbm << endl;
    fluxout << largeur << " " << hauteur << endl;

    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            fluxin >> pixel;
            if (pixel == 1) {
                fluxout << 0 << " ";
            }
            else if (pixel == 0) {
                fluxout << 1 << " ";
            }
        }
        cout << endl;
    }

    //Flux close
    fluxin.close();
    fluxout.close();
}


int main(){
    cout << "Affichage du smiley " << endl;
    affichePBM("./images/smiley.pbm");
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dossier pbm/smiley-inverse.pbm" << endl;
    inversePBM("images/smiley.pbm","pbm/smiley.pbm");
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm");
    return 0;
}

