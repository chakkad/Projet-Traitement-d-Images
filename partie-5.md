---
jupytext:
  notebook_metadata_filter: exports, myst
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
kernelspec:
  display_name: C++17
  language: C++17
  name: xcpp17
---

+++ {"deletable": false, "editable": false, "grade_id": "cell-e6a010b2eb37d093"}

# Partie 5 : Abordons maintenant les images en couleurs

+++ {"deletable": false, "editable": false, "grade_id": "cell-458124199ee4939e"}

## Description du format PPM

La page <http://fr.wikipedia.org/wiki/Portable_pixmap> détaille le
format général d'un fichier PPM non compressé. L'entête est de la forme:

    P3
    nbColonnes nbLignes
    255

suivi d'un certain nombre de lignes décrivant les pixels de haut en
bas et de gauche à droite (**Attention:** les lignes de l'image ne
sont pas forcément les mêmes que celles du fichier!) ayant le format
suivant:

    rouge vert bleu rouge vert bleu ...

Ce format est très similaire au format PGM; les commentaires faits
précédemment s'appliquent toujours.

+++ {"deletable": false, "editable": false, "grade_id": "cell-4546e76e685b2946"}

## La structure `Couleur` et le type `Image`

Tout comme pour les images en noir et blanc et pour les images en
niveau de gris, les images en couleur seront stockées dans un double
tableau.

Tout d'abord, on définit la structure suivante :

    /** Structure de donnees pour representer un pixel en couleur **/
    struct Couleur {
        /** Intensite de rouge **/
        double r;
        /** Intensite de vert **/
        double g;
        /** Intensite de bleu **/
        double b;
    };


Une fois la structure ainsi définie, les lignes suivantes
permettront par exemple de définir une variable de type
`Couleur` et de l'initialiser à un bleu cyan:

    Couleur cyan;
    cyan.r = 0;
    cyan.g = 255;
    cyan.b = 255;

Chaque pixel sera représenté par une variable de type `Couleur`.
Une `Image` est donc un double tableau de `Couleur`:

    /** Structure de donnees pour representer une image **/
    typedef vector<vector<Couleur> > Image;

Pour obtenir le niveau de bleu du pixel le plus en haut à gauche
d'une image convenablement lue et stockée dans une variable
`Image1` de type `Image`,
il suffira donc de taper `Image1[0][0].b`.

+++ {"deletable": false, "editable": false, "grade_id": "cell-bdb961eea97248ae"}

::::{admonition} Exercice 5.1 (\*\*) Lecture et écriture d'image PPM

Compléter le fichier [image.hpp](image.hpp) avec les types `Couleur` et `Image` donnés ci-dessus.

Implémentez les fonctions `lirePPM` et `ecrirePPM`dans [ppm.cpp](ppm.cpp).
La documentation est disponible dans le fichier [ppm.hpp](ppm.hpp)


Consulter le
programme [ppm-test.cpp](ppm-test.cpp), puis lancez-le pour vérifier vos
fonctions. Pour la compilation, procéder comme dans la [Partie 5](partie-5.md)

**N'oubliez pas de convertir les images jpg fournies en images ppm pour que les tests puissent fonctionner !**
::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-e4bc14b256237e11"}

::::{admonition} Exercice 5.2 (\*\*) De la couleur au niveau de gris

La méthode qui semble faire consensus pour transformer une image
couleur en image en niveaux de gris consiste à remplacer la couleur de
chaque pixel, codée généralement par 3 couleurs $r,g,b$, par le niveau
de gris
$$0.2126 * r + 0.7152 * g + 0.0722 * b.$$

Il s'agit donc d'une
simple moyenne pondérée des trois couleurs pour obtenir un niveau de
gris. Dans l'autre sens, étant donné un niveau de gris
`c`, on l'associe souvent à la couleur `(c,c,c)`
c'est à dire `r==c,g==c,b==c`.

Compléter [gris-couleurs.cpp](gris-couleurs.cpp) avec les fonctions `CouleurAuGris`
et `GrisACouleur` dont la documentation est donnée dans [gris-couleurs.hpp](gris-couleurs.hpp)

Lancer les tests comme précédemment.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-946d15dd15752126"}

## Aller plus loin

Dans le [préambule](partie-0.md), regardez comment vous pouvez créer de nouvelles images PGM et PPM

Convertir des images jpg de votre choix et tester vos fonctions

**Attention** nos programmes sont assez gourmands en mémoire car les images sont **non compressées**. Pensez à **réduire** la taille de vos jpeg pour obtenir des images en 512x512.

```{code-cell}

```
