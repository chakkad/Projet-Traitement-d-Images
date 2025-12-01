#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/// BEGIN ImageNB
/** Structure de données pour représenter une image binaire **/
typedef vector<vector<int> > ImageNB;
/// END ImageNB

/// BEGIN lirePBM

/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 **/
ImageNB lirePBM(string source) {
    ifstream fluxin;
    fluxin.open(source);
    if (!fluxin.is_open()) {
        cout << "Error opening the file " << endl;
        return ImageNB();
    }

    //Elements
    string type_pbm; //Contains P1
    int largeur;
    int hauteur;
    int temp;
    ImageNB tableau;
    //

    //Read 
    fluxin >> type_pbm;
    fluxin >> largeur >> hauteur;
    for (int y = 0; y < hauteur; y++) {
        vector<int> temp_row;
        for (int x = 0; x < largeur; x++) {
            int pixel;
            fluxin >> pixel;
            temp_row.push_back(pixel);
        }
        tableau.push_back(temp_row);
    }
    //Flux close
    fluxin.close();
    //

    return tableau;
}

/// BEGIN ecrirePBM

/** Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 **/
void ecrirePBM(ImageNB img, string cible) {
    //Stream declarations
    ofstream fluxout;
    fluxout.open(cible);
    //

    //Error handling
    if (!fluxout.is_open()) {
        cout << "Error creating the file" << endl;
        return;
    }

    //Headers
    int largeur = img[0].size();
    int hauteur = img.size();
    fluxout << "P1" << endl;
    fluxout << largeur << " " << hauteur << endl;
    //
    
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            fluxout << img[i][j] << " ";
        }
        fluxout << endl;
    }
    //Flux close
    fluxout.close();
}


/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 **/
void affichePBM(ImageNB img) {
    //Sizes and Variables
    int hauteur = img.size();
    int largeur = img[0].size();
    int temp = 0;
    //

    //Read Function (nested loop to read 2d vectors)
    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            temp = img[y][x];
            if (temp == 0) {
                cout << " ";
            } else if (temp == 1) {
                cout << "@";
            }
        }
        cout << endl;
    }
    
}

/// BEGIN inversePBM

/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 **/
ImageNB inversePBM(ImageNB img) {
    //Sizes and Variables
    int hauteur = img.size();
    int largeur = img[0].size();
    int original_pixel =  0;
    int inversed_pixel = 0;
    ImageNB inversed;
    //

    for (int y = 0; y < hauteur; y++) {
        vector<int> temp_row; //Creates a new row everytime the inner loop is done
        for (int x = 0; x < largeur; x++) {
            original_pixel = img[y][x];
            if (original_pixel == 0) {
                inversed_pixel = 1;
            } else if (original_pixel == 1) {
                inversed_pixel = 0;
            }
            temp_row.push_back(inversed_pixel);
        }
        inversed.push_back(temp_row);
    }
    return inversed;
}

void testLirePBM(){ //Provided by the documents
    cout << "--- Test de EcrirePBM et LirePBM ---" << endl;
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("images/smiley.pbm"),  "pbm/smiley.pbm");
    ecrirePBM(lirePBM("images/cercle.pbm"),  "pbm/cercle.pbm");
    ecrirePBM(lirePBM("images/code.pbm"), "pbm/code.pbm");
    ecrirePBM(lirePBM("images/damier.pbm"), "pbm/damier.pbm");
    cout << "SUCCESS" << endl;
    cout << "--- Fin du Test ---" << endl;
}

//My personal tests for each funtion

void testAffichePBM() {
    cout << "--- Test de affichePBM ---" << endl;
    cout << "Vous devriez voir un petit damier de 4x4 ci-dessous :" << endl;
    
    ImageNB testImage = {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1}
    };
    

    affichePBM(testImage);
    
    cout << "--- Fin du Test ---" << endl << endl;
}

void testInversePBM() {
    cout << "--- Test de inversePBM ---" << endl;
    
    
    ImageNB inputImage = {
        {1, 0, 1, 0},
        {0, 1, 0, 1}
    };
    
    
    ImageNB expectedImage = {
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    
    
    ImageNB actualResult = inversePBM(inputImage);
    

    if (actualResult == expectedImage) {
        cout << "SUCCESS: inversePBM a produit le resultat attendu." << endl;
    } else {
        cout << "FAILURE: inversePBM n'a pas produit le resultat attendu." << endl;
        cout << "Image attendue :" << endl;
        affichePBM(expectedImage);
        cout << "Image obtenue :" << endl;
        affichePBM(actualResult);
    }
    
    cout << "--- Fin du Test ---" << endl << endl;
}

int main(){
    testLirePBM();
    testAffichePBM();
    testInversePBM();
    return 0;
}


