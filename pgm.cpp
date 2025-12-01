#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/

#include <iostream>
#include <fstream>
#include "image.hpp"
#include "pgm.hpp"



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

bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}

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

