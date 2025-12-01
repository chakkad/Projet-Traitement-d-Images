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

+++ {"deletable": false, "editable": false, "grade_id": "cell-abf3573b9f0262c3"}

# Partie 6 : Segmentation en régions par la méthode du super pixel

+++ {"deletable": false, "editable": false, "grade_id": "cell-ea728db28aafb860"}

Une des difficulté dans le traitement d'images est que le nombre de
pixels est important: même pour une petite image de 512x512, il y a
déjà 262144 pixels. Un autre problème est que chaque pixel porte
individuellement très peu d'information. Une technique très utilisée
pour réduire les effets de ces deux problèmes est la technique de segmentation en régions
par le principe des
*super pixels*, qui permet de regrouper les pixels en zones
homogènes à la fois d'un point de vue spatial et colorimétrique. Cela
aboutit ainsi à diminuer le nombre de régions tout en regroupant
l'information au sein d'une région. Pour cela, il est primordial que
les régions soient homogènes, ce qui fait par la même occasion
ressortir les contours. L'image
peut alors être traitée avec des méthodes classiques provenant par
exemple de traitements de texte qui ne pourraient pas marcher sur
l'ensemble des pixels.

::::{admonition} Exemple : calcul de zones de couleur uniforme avec l'algorithme SuperPixel.

:::{image} images/Willis.512.jpg
:alt: Portrait de Bruce Willis en couleur
:width: 30%
:::
:::{image} images/superpixel.jpg
:alt: Portrait de Bruce Willis découpé en zones de couleur uniforme
:width: 30%
:::

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-8092973621abf761"}

## L'algorithme des K-moyennes

Le cœur de la méthode des super pixels consiste à former des sous-ensembles *compacts* dans un ensemble de points. Il existe
différents algorithmes pour effectuer de tels regroupements. Le plus
utilisé est celui des K-moyennes car il est rapide et généralement
suffisamment performant.

L'entrée de cet algorithme est un ensemble de points `P` de
$\mathbb{R}^D$ qu'on veut décomposer ainsi qu'un ensemble de points
`C` (de $\mathbb{R}^D$ aussi) qui serviront de pilote à la
décomposition. Pour notre application au traitement d'image,
$\mathbb{R}^D$ sera l'espace spacio-colorimétrique (voir plus loin)
avec $D=5$.

L'algorithme consiste à effectuer *plusieurs fois* une
amélioration. Chaque amélioration est en deux phases:

1.  Chaque point est associé au point pilote le plus proche;

2.  Chaque point pilote est déplacé au barycentre de l'ensemble des
    points qui lui sont associés.

L'algorithme renvoie les positions finales des points pilotes. Dans
cet algorithme, chaque répétition des phases 1 et 2 permet de
compacter les sous ensembles.

Pour écrire cet algorithme, deux types sont définis dans
[superpixel.hpp](superpixel.hpp):

    /** Structure de donnee representant un point dans l'espace
    spacio colorimetrique **/
    typedef vector<double> Point;

    /** Structure de donnee representant un ensemble de points dans l'espace
        spacio colorimetrique **/
    typedef vector<Point> EnsemblePoints;

L'algorithme est découpé en plusieurs fonctions que vous écrirez
au fur et à mesure, avec des tests fournis dans
[superpixel-test.cpp](superpixel-test.cpp).

+++ {"deletable": false, "editable": false, "grade_id": "cell-b8dd78fd5bd6bce8"}

## Distance et plus proche voisin entre pixels

::::{admonition}  Exercice 6.1 (\*) Distance entre 2 points
Implanter dans [superpixel.cpp](superpixel.cpp) la fonction `distancePoints` dont la documentation
est donnée dans [superpixel.hpp](superpixel.hpp).


Tester votre fonction grâce à `distancePointsTest` dans [superpixel-test.cpp](superpixel-test.cpp).
::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-a6ceca39c2097a40"}

::::{admonition}  Exercice 6.2 (\*) Distance point -- ensemble
Implanter la fonction `distanceAEnsemble` dans [superpixel.cpp](superpixel.cpp)
dont la documentation est donnée dans [superpixel.hpp](superpixel.hpp).
Elle calcule la distance entre un point $p$ et
un ensemble de points $C$, c'est à dire le minimum des distances entre
$p$ et un point $c$ de $C$:

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-18b7a5d869618546"}

::::{admonition}  Exercice 6.3 (\*) plus proche voisin

Implanter la fonction `plusProcheVoisin`dans [superpixel.cpp](superpixel.cpp)
dont la documentation est donnée dans [superpixel.hpp](superpixel.hpp).

Indication: On pourra utiliser la fonction `distanceAEnsemble`.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-f193fcb3d339f897"}

### Sous ensemble par regroupement de pixels

::::{admonition}  Exercice 6.4 (\*)

Implanter la fonction `sousEnsemble` dans [superpixel.cpp](superpixel.cpp)
dont la documentation est donnée dans [superpixel.hpp](superpixel.hpp).

% :::{literalinclude} superpixel.hpp
% :start-after: BEGIN sousEnsemble
% :end-before: END sousEnsemble
% :::

::::

Indication: il suffit de parcourir les points `p` de
`P` avec une boucle `for` et d'utiliser
l'opération `push_back` dans le cas où
`k==plusProcheVoisin(p,C)` pour mettre `p` dans
l'ensemble qui sera renvoyé.

+++ {"deletable": false, "editable": false, "grade_id": "cell-7231a9a174f7faad"}

### Barycentre d'un ensemble de pixels (\*)

::::{admonition}  Exercice 6.5 (\*)

Implanter la fonction `barycentre` dans [superpixel.cpp](superpixel.cpp)
dont la documentation est donnée dans [superpixel.hpp](superpixel.hpp).

% :::{literalinclude} superpixel.hpp
% :start-after: BEGIN barycentre
% :end-before: END barycentre
% :::

::::

Indication: Chaque coordonnée du barycentre est la moyenne des
coordonnées correspondantes des points de `C`.

+++ {"deletable": false, "editable": false, "grade_id": "cell-114cbfbefb8335b6"}

### Combinons toutes ces fonctions

En utilisant les fonctions définies précédemment, on peut écrire
l'algorithme K-moyenne. Pour simplifier, l'utilisateur de la fonction
devra spécifier le nombre de fois que l'opération d'amélioration doit
être effectuée. De même, dans le cas où un point de `C` ne
serait associé à aucun point de `P` à la fin d'une étape de
regroupement, alors ce point est laissé à sa position au lieu d'être
déplacé.

::::{admonition}  Exercice 6.6 (\*\*\*)

Implanter la fonction `kMoyenne` dans [superpixel.cpp](superpixel.cpp)
dont la documentation est donnée dans [superpixel.hpp](superpixel.hpp).

% :::{literalinclude} superpixel.hpp
% :start-after: BEGIN kMoyenne
% :end-before: END kMoyenne
% :::

La fonction que vous allez écrire est trop lente pour la suite,
principalement à cause des copies des vecteurs entre les différents
appels de fonction. Aussi on fournit une fonction `FAST_kMoyenne`
qui fait la même chose en un seul tenant et dont vous ne devez pas
vous inspirer.

% :::{literalinclude} superpixel.hpp
% :start-after: BEGIN FASTkMoyenne
% :end-before: END FASTkMoyenne
% :::


Utiliser la fonction `KMoyenneTest` dans [superpixel-test.cpp](superpixel-test.cpp) pour vérifier que les
deux fonctions fournissent quand même bien un unique résultat (à
quelques centièmes près).

::::

+++

### Aller plus loin (\*\*)

Utilisez la bibliothèque SFML vue en TP pour afficher les différents
points ainsi que les différents sous-ensembles au cours de
l'algorithme. Par exemple, sur l'exemple de test, coloriez en cyan,
magenta ou jaune les points selon qu'ils appartiennent au premier sous
ensemble, au deuxième ou au troisième. De plus, changez
`KMoyenne` pour continuer les améliorations tant que les
ensembles évoluent.

+++

## Application au regroupement de pixels


Chaque pixel d'une image a une couleur; ainsi, une image
`img` est un tableau 2D, et le pixel `(i,j)` a la
couleur `(r,g,b)` car `img[i][j]==(r,g,b)`. On
peut voir les choses différemment en considérant le **point** en
dimension 5 `(i,j,r,g,b)` ! De cette façon, une image n'est
plus qu'un ensemble de points dans $\mathbb{R}^5$ ! Bien sûr cette
façon de voir oublie la structure de l'image. Mais cela invite à
utiliser la technique des K-moyennes pour regrouper des pixels en sous
ensembles !

Dans le point $(i,j,r,g,b)$, on mélange naïvement couleur et
espace. Or, la distance euclidienne standard de $\mathbb{R}^5$ va être
utilisée et elle agit de la même façon sur les cinq dimensions,
ce qui semble inadapté pour des données n'ayant rien à voir les
unes avec les autres.

Aussi, on formera plutôt $(i,j,\lambda r,\lambda g, \lambda b)$, ce
qui permet de privilégier soit l'aspect spatial ($\lambda$ petit) soit
l'aspect colorimétrique ($\lambda$ grand). Le cas extrême $\lambda=0$
correspond à oublier la couleur: appliquer les K-moyennes créera des
cercles dans l'image. Le cas extrême $\lambda=\infty$ correspond à
oublier les positions: appliquer les K-moyennes regroupera les
couleurs indépendamment de leur position.

+++

### Quels points pivots ?

Avant d'appliquer les K-moyennes, il faut définir les points pivots.
L'objectif étant de décomposer l'image en régions compactes en couleur
et en espace, il est classique de prendre comme points pivots les
points de l'image correspondant à une grille spatiale.

::::{admonition}  Exercice 6.7 (\*\*)

Implanter la fonction `pivotSuperPixel` dans [superpixel.cpp](superpixel.cpp)
dont la documentation est donnée dans [superpixel.hpp](superpixel.hpp).

% :::{literalinclude} superpixel.hpp
% :start-after: BEGIN pivotSuperPixel
% :end-before: END pivotSuperPixel
% :::

Elle renvoie l'ensemble des points
`mu`$\times$`a`,`mu`$\times$`b`,`lambda`$\times$`img[``mu`$\times$`a``][``mu`$\times$`b``]`
où `a` et `b` sont des entiers valant
0,1,2,... jusqu'à ce que l'on sorte de l'image.

::::

Indications:

-   La commande `push_back` peut être utile.

-   Cette fonction est simple: il s'agit simplement d'une boucle
    `for` dans une boucle `for` comme pour parcourir
    l'image, sauf qu'au lieu de se déplacer de 1 on se déplace de
    `mu`.

+++

### Les super pixels

::::{admonition}  Exercice 6.8 (\*\*)

Implanter la fonction `superPixels` dans [superpixel.cpp](superpixel.cpp)
dont la documentation est donnée dans [superpixel.hpp](superpixel.hpp).

% :::{literalinclude} superpixel.hpp
% :start-after: BEGIN superPixels
% :end-before: END superPixels
% :::

Elle applique l'algorithme des K-moyennes (en faisant
`nbAmeliorations` améliorations) sur les points
correspondant à l'image (avec le coefficient $\lambda$) et avec les
points pivots correspondant à la grille $\mu$ et renvoie

::::

+++

### Visualisation de super pixels

Cette fonction construit les super pixels; cependant à ce stade, on
peut difficilement contrôler le résultat. Afin de visualiser le
résultat, on va produire une nouvelle image dans laquelle tous les
pixels associés à un pixel pivot prendront sa couleur. Cela permettra
d'observer les super pixels.

::::{admonition}  Exercice 6.9 (\*\*\*)

Implanter la fonction `superPixel` "Filtre SuperPixel" dans [superpixel.cpp](superpixel.cpp)
dont la documentation est donnée dans [superpixel.hpp](superpixel.hpp).

% :::{literalinclude} superpixel.hpp
% :start-after: BEGIN SuperPixel
% :end-before: END SuperPixel
% :::


Elle renvoie une image dans laquelle la couleur de chaque pixel est
remplacée par celle de son pixel pivot.
::::

Utiliser la fonction `superPixelTest` de [superpixel-test.cpp](superpixel-test.cpp) pour vérifier vos
résultats et proposez des paramètres pour les exemples indiqués.

+++

### Visualisation des bords des sous ensembles

::::{admonition}  Exercice 6.10 (\*\*)

Rajouter un bord de 1 pixel bleu à la frontière de chaque super pixel,
comme dans l'image donnée en illustration, afin d'améliorer la
visualisation dans la fonction précédente.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-0367c9b259bd485d"}

### Pour aller beaucoup plus loin

Quelques références sur les techniques des K-moyennes, des super
pixels et leur utilisation:

-   <http://fr.wikipedia.org/wiki/Algorithme_des_k-moyennes>

-   <http://en.wikipedia.org/wiki/K-means>

-   <http://fr.wikipedia.org/wiki/Segmentation_d'image>

-   <http://en.wikipedia.org/wiki/Image_segmentation>

-   un article qui fait référence sur l'utilisation de l'algorithme des K-moyennes : Data clustering: 50 years beyond K-means, Anil K. Jain, *Pattern Recognition Letters* 31(8), 651--666, 2010.

-   ce domaine de recherche est encore très actif, on peut citer par
    exemple la publication : Slic superpixels, Radhakrishna Achanta, Appu Shaji, Kevin Smith, Aurelien Lucchi, Pascal Fua, et Sabine Süsstrunk, EPFL Tech. Rep. 149300, 2010.

```{code-cell}

```
