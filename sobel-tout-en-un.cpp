#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;



/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};



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


/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
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

/// BEGIN intensiteH

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
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


/// BEGIN intensiteV

/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 **/
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


/// BEGIN intensiteHV

/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
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


void testSobel() {
    CHECK( ImageGrisEgal(intensiteH(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -373.47, 227.507, 0},
                  {0, -22.1312, 323.866, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensiteV(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -15.1398, 150.501, 0},
                  {0, -9.0336, 273.023, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensite(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, 373.777, 272.782, 0},
                  {0, 23.9039, 423.593, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );

    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
    ecrirePGM(intensite(lirePGM("sobel/correction/Willis.512.pgm" )), "sobel/Willis.512.pgm");
    ecrirePGM(intensite(lirePGM("sobel/correction/Baboon.512.pgm" )), "sobel/Baboon.512.pgm");
    ecrirePGM(intensite(lirePGM("sobel/correction/Billes.256.pgm" )), "sobel/Billes.256.pgm");
    ecrirePGM(intensite(lirePGM("sobel/correction/Embryos.512.pgm")), "sobel/Embryos.512.pgm");
    ecrirePGM(intensite(lirePGM("sobel/correction/House.256.pgm"  )), "sobel/House.256.pgm");
}



int main(){

    testSobel();
    return 0 ;
}

