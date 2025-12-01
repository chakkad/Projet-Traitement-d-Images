#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include "image.hpp"
#include "seuillage.hpp"
#include "sobel.hpp"

ImageGris renormalise(ImageGris img) {
    //Initialise a 2d vector
    int hauteur = img.size();
    int largeur = img[0].size();
    ImageGris resultat;
    for (int y = 0; y < hauteur; y++) {
        vector<double> temp_row;
        for (int x = 0; x < largeur; x++ ) {
            temp_row.push_back(0.0);
        }
        resultat.push_back(temp_row);
    }
    //

    //Finding max value
    double max_val = 0.0;
    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            if (img[y][x] > max_val) {
                max_val = img[y][x];
            }
        }
    }
    //

    //Error handling
    if (max_val == 0) {
        return resultat;
    }
    //

    //Applying the formula
    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            resultat[y][x] = (img[y][x]/max_val) * 255.0;
        }
    }
    //

    return resultat;
}

ImageGris seuillage(ImageGris img, int seuil) {
    //Initialise a 2d vector
    int hauteur = img.size();
    int largeur = img[0].size();
    ImageGris resultat;
    for (int y = 0; y < hauteur; y++) {
        vector<double> temp_row;
        for (int x = 0; x < largeur; x++ ) {
            temp_row.push_back(0.0);
        }
        resultat.push_back(temp_row);
    }
    //

    //Applying the logic
    double original_pixel = 0.0;
    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            original_pixel = img[y][x];
            if (original_pixel > seuil) {
                resultat[y][x] = 0.0;
            } else {
                resultat[y][x] = 255.0;
            }
        }
    }
    return resultat;
}

ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    //Initialising the 2d vector
    int hauteur_intensite = imgIntensite.size();
    int largeur_intensite = imgIntensite[0].size();
    ImageGris resultat;
    for (int y = 0; y < hauteur_intensite; y++) {
        vector<double> temp_row;
        for (int x = 0; x < largeur_intensite; x++) {
            temp_row.push_back(255.0); //Initialise the vector to all white
        }
        resultat.push_back(temp_row);
    }
    //

    //Checking conditions
    for(int y = 1; y < hauteur_intensite-1; y++) { //Ignoring the edges
        for (int x = 1; x < largeur_intensite-1; x++) { //Ignoring the edges
            //Check the first Condition
            if (imgIntensite[y][x] > seuil) {
                bool dark_enough = false;

                //Checking the neighbours of the pixel
                for (int ny = y-1; ny <= y+1; ny++) {
                    for (int nx = x-1; nx <= x+1; nx++){
                        //Only 1 pixel found is enough
                        if (imgContour[ny][nx] == 0.0) {
                            dark_enough = true;
                            break; //We only need one, so after finding one just exit the loop
                        }
                    }
                    if (dark_enough) {
                        break;
                    }
                }
                if (dark_enough) {
                    resultat[y][x] = 0.0;
                }
            }
        }
    }

    return resultat;
}

ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    ImageGris imgContour = seuillage(imgIntensite, seuilFort);

    for (int i = 0; i < nbAmeliorations; i++) {
        ImageGris imgFinale = doubleSeuillage(imgIntensite, imgContour, seuilFaible);
        imgContour = imgFinale;
    }
    
    return imgContour;
}

