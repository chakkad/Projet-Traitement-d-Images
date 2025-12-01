#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
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

/** Une image 4x4 en teintes de gris pour les tests de renormalisation **/
ImageGris imgGrisRenorm = {
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
};


/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
ImageGris intensite(ImageGris img) {
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
            double h = (img[y-1][x-1] + 2*img[y][x-1] + img[y+1][x-1]) - (img[y-1][x+1] + 2*img[y][x+1] + img[y+1][x+1]);
            double v = (img[y-1][x-1] + 2*img[y-1][x] + img[y-1][x+1]) - (img[y+1][x-1] + 2*img[y+1][x] + img[y+1][x+1]);
            resultat[y][x] = sqrt(h*h+v*v);
        }
    }
    //

    return resultat;
}


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


/// BEGIN renormalise

/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 **/
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

void renormaliseTest() {
    CHECK( ImageGrisEgal(renormalise( imgGrisRenorm),
              ImageGris( {
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
              }),
              0.001) );

}
/// BEGIN seuillage

/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir  si teinte > seuil
 **/
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

/// BEGIN doubleSeuillage

/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/
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


/// BEGIN doubleSeuillageIteratif

/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    ImageGris imgContour = seuillage(imgIntensite, seuilFort);

    for (int i = 0; i < nbAmeliorations; i++) {
        ImageGris imgFinale = doubleSeuillage(imgIntensite, imgContour, seuilFaible);
        imgContour = imgFinale;
    }
    
    return imgContour;
}


void seuillageTest() {
    CHECK( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );
    CHECK( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 400, 80, 4 ),
                          ImageGris( {
                              {255, 255, 255, 255},
                              {255, 0, 0, 255},
                              {255, 255, 0, 255},
                              {255, 255, 255, 255}
                          }),
                          0.001) );


    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Billes.256.pgm")), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Willis.512.pgm"  )), 110), "seuillage/Willis.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;
}

void doubleSeuillageTest(){
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(lirePGM("images/Willis.512.pgm"), seuillage(intensite(lirePGM("images/Willis.512.pgm")), 100), 80), "seuillage_double/Willis.512.pgm");
    ecrirePGM(doubleSeuillage(lirePGM("images/Billes.256.pgm"), seuillage(intensite(lirePGM("images/Billes.256.pgm")), 100), 80), "seuillage_double/Billes.256.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;
}

void doubleSeuillageIteratifTest() {
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Willis.512.pgm")), 500, 80, 100), "seuillage_double/iteratif_Willis.512.pgm");

    cout << "\tProposer des seuils pour Billes.256.pgm, Embryos.512.pgm et House.256.pgm" << endl;
    
}


int main(){
    renormaliseTest();
    seuillageTest();
    doubleSeuillageTest();
    doubleSeuillageIteratifTest();
    return 0;
}

