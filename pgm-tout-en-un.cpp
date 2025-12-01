#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/// BEGIN ImageGris

/** Structure de donnees pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;
/// END ImageGris

/// BEGIN lirePGM

/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
ImageGris lirePGM(string source) {
    //Flux declarations
    ifstream fluxin;
    fluxin.open(source);
    //

    //Error handling
    if (!fluxin.is_open()) {
        cout << "Error opening the file" << endl;
        return ImageGris();
    }

    //Variables
    string file_type;
    int largeur, hauteur;
    int max_gris;
    int pixel;
    ImageGris new_vector;
    //

    //Header read
    fluxin >> file_type;
    fluxin >> largeur >> hauteur;
    fluxin >> max_gris;
    //

    //File read
    for (int y = 0; y < hauteur; y++) {
        vector<double> temp_row;
        for (int x = 0; x < largeur; x++) {
            fluxin >> pixel;
            temp_row.push_back(pixel);
        }
        new_vector.push_back(temp_row);
    }

    //Flux close
    fluxin.close();
    //

    return new_vector;
}

/// BEGIN ecrirePGM

/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
void ecrirePGM(ImageGris img, string cible) {
    //Flux declarations
    ofstream fluxout;
    fluxout.open(cible);
    //

    //Error handling
    if (!fluxout.is_open()) {
        cout << "Error creating the file" << endl;
        return;
    }
    //

    //Variables
    int largeur = img[0].size();
    int hauteur = img.size();
    int integer_value = 0;
    double double_value = 0;
    //

    //Header printing
    fluxout << "P2" << endl;
    fluxout << largeur << " " << hauteur << endl;
    fluxout << 255 << endl;
    //

    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            double_value = img[y][x];
            integer_value = (int)double_value;
            fluxout << integer_value << " ";
        }
        fluxout << endl;    
    }

    //Flux close
    fluxout.close();
}

/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/
ImageGris inversePGM(ImageGris img) {
    //Variables
    int largeur = img[0].size();
    int hauteur = img.size();
    double original_value = 0;
    double inverted_value = 0;
    ImageGris inverted; //Initialised at 0
    //

    //Inverting pixels
    for (int y = 0; y < hauteur; y++) {
        vector<double> temp_row;
        for (int x = 0; x < largeur; x++) {
            original_value = img[y][x];
            inverted_value = 255 - original_value; //inverted = MAX(255) - original value
            temp_row.push_back(inverted_value);
        }
        inverted.push_back(temp_row);
    }

    return inverted;
    
}

void lirePGMTest(){
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    ecrirePGM(lirePGM("images/brain.pgm"),  "pgm/brain.pgm");
    ecrirePGM(lirePGM("images/illusion.pgm"),  "pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    imageOriginale = lirePGM("images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/brain-inverse.pgm");
    imageOriginale = lirePGM("images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/illusion-inverse.pgm");
}

int main() {
    lirePGMTest();
    inversePGMTest();
    return 0;
}

