#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include "image.hpp"
#include "sobel.hpp"

ImageGris intensiteH(ImageGris img) {
    //Initiating an empty 2d vector
    int hauteur = img.size();
    int largeur = img[0].size();
    ImageGris resultat;
    for (int y = 0; y < hauteur; y++) {
        vector<double> temp_row;
        for (int x = 0; x < largeur; x++) {
            temp_row.push_back(0.0);
        }
        resultat.push_back(temp_row);
    }
    //

    //The sobel formula
    for (int y = 1; y < hauteur-1; y++) { //Starting from the second row and stopping before the last row
        for (int x = 1; x < largeur-1; x++) {//Starting from the second column and stopping before the last column
            double h = (img[y-1][x-1] + 2*img[y][x-1] + img[y+1][x-1]) - (img[y-1][x+1] + 2*img[y][x+1] + img[y+1][x+1]); //Sobels formula to count the difference of intenstiy for horizontal pixels
            resultat[y][x] = h;
        }
    }
    return resultat;
}

ImageGris intensiteV(ImageGris img) {
    //Initiating an empty 2d vector
    int hauteur = img.size();
    int largeur = img[0].size();
    ImageGris resultat;
    for (int y = 0; y < hauteur; y++) {
        vector<double> temp_row;
        for (int x = 0; x < largeur; x++) {
            temp_row.push_back(0.0);
        }
        resultat.push_back(temp_row);
    }
    //

    //Sobel's Formula
    for (int y = 1; y < hauteur-1; y++) {
        for (int x = 1; x < largeur-1; x++) {
            double h = (img[y-1][x-1] + 2*img[y-1][x] + img[y-1][x+1]) - (img[y+1][x-1] + 2*img[y+1][x] + img[y+1][x+1]);
            resultat[y][x] = h;
        }
    }
    return resultat;
}

ImageGris intensite(ImageGris img) {
    //Calling the previous functions
    ImageGris image_h = intensiteH(img);
    ImageGris image_v = intensiteV(img);
    //

    //initiating the 2d vector
    int hauteur = img.size();
    int largeur = img[0].size();
    ImageGris resultat;
    for (int y = 0; y < hauteur; y++) {
        vector<double> temp_row;
        for (int x = 0; x < largeur; x++) {
            temp_row.push_back(0.0);
        }
        resultat.push_back(temp_row);
    }
    //

    //Applying the formula
    for (int y = 1; y < hauteur-1; y++) {
        for (int x = 1; x < largeur-1; x++) {
            double h = image_h[y][x];
            double v = image_v[y][x];
            resultat[y][x] = sqrt(h*h+v*v);
        }
    }
    //

    return resultat;
}

