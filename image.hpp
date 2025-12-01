/** @file
 * Structures de données pour représenter des images
 **/

#ifndef _IMAGE_H
#define _IMAGE_H
#include <vector>
#include <string>
using namespace std;


// Typedef
typedef vector<vector<int>> ImageNB; //PBM Files
typedef vector<vector<double>> ImageGris; //PGM Files
//

//PBM Functions
ImageNB lirePBM(string source);
void ecrirePBM(ImageNB img, string cible);
void affichePBM(ImageNB img);
ImageNB inversePBM(ImageNB img);
//

//PGM Processing Functions
ImageGris lirePGM(string source);
void ecrirePGM(ImageGris img, string cible);
ImageGris inversePGM(ImageGris img);
//

//Sobel Filtering functions
ImageGris intensiteH(ImageGris img);
ImageGris intensiteV(ImageGris img);
ImageGris intensite(ImageGris img);
//

//Seuillage Functions
ImageGris renormalise(ImageGris img);
ImageGris seuillage(ImageGris img, int seuil);
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil);
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations);



/** Structure de donnees pour representer un pixel en couleur **/
struct Couleur {
    /** Intensite de rouge **/
    double r;
    /** Intensite de vert **/
    double g;
    /** Intensite de bleu **/
    double b;
};

/** Structure de donnees pour representer une image **/
typedef vector<vector<Couleur> > Image;

#endif

