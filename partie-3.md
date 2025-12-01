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

+++ {"deletable": false, "editable": false, "grade_id": "cell-9644772d46423127"}

# Partie 3 : Extraction de contours

*Note : cette partie n'est pas nécessaire pour la suite du projet*


Les formes des objets présents dans une image constituent
une information privilégiée en traitement d'image. Ces formes peuvent
être obtenues en détectant les contours (frontières) des objets.
Dans beaucoup d'algorithmes, la recherche d'un objet dans une image se
ramène souvent à la recherche d'un contour ayant une certaine forme.

Pour voir le contour, il faut une différence (gradient) de
couleurs.

Si, dans une image, un objet A touche un objet B, c'est que des pixels
de A touchent des pixels de B. Or il y a alors de fortes chances pour
que la couleur des pixels de A soit différente de la couleur des
pixels de B. Ainsi, les contours semblent intuitivement inclus dans les
zones qui présentent de fortes disparités (gradients) de couleur.

On voit donc l'intérêt de rechercher dans les images les zones qui
présentent de fortes disparités de couleurs, puisqu'elles contiennent les
contours. Ces zones peuvent être obtenues par des opérations simples
et efficaces sur l'image comme dans l'exemple ci-dessous

::::{admonition} Exemple : détection de contours sur une image en niveau de gris

:::{image} images/Willis_gris.png
:alt: Portrait de Bruce Willis en noir et blanc
:width: 30%
:::
:::{image} images/gradient.jpg
:alt: Les contours de l'image dessinés en blanc sur fond noir
:width: 30%
:::

Illustration de l'intérêt de rechercher les zones à forte
disparité. On constate que les contours corrèlent relativement bien
aux zones à fortes disparités.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-b6e1bd522aca7023"}

## Le filtre de Sobel pour estimer le gradient


Le filtre de Sobel est classiquement utilisé pour estimer la valeur
de la disparité des intensités. En assimilant l'image à une fonction
à deux variables, ce filtre peut s'interpréter comme des calculs d'une
version discrète de la dérivée. À vous de réfléchir pourquoi
la dérivée est forte lors d'un brusque saut de valeur, comme
lorsque l'on traverse un contour.

Pour ce qui nous concerne, ce filtre consiste juste à calculer des
différences au niveau du voisinage (horizontal et vertical) de chaque pixel.

L'intensité des
différences d'intensité horizontales au niveau du pixel
`(i,j)` dans l'image `img` est donnée par:

    img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1]
    - img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1]

L'intensité des différences d'intensité verticales est de même donnée
par:

    img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1]
    - img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1]

L'intensité totale est la norme des intensités horizontale et verticale (voir le rappel plus loin).

+++ {"deletable": false, "editable": false, "grade_id": "cell-6e8e1b79e0746fd3"}

::::{admonition} Exercice 3.1 (\*) : implantation du filtre de Sobel


Dans [sobel-tout-en-un.cpp](sobel-tout-en-un.cpp), copier les fonctions `lirePGM` et `ecrirePGM` qui seront utilisées pour les tests.

Ensuite, implanter dans [sobel-tout-en-un.cpp](sobel-tout-en-un.cpp) les trois fonctions `intensiteH`, `intensiteV` et `intensite`
qui prennent une image en entrée et renvoient une nouvelle image de même
taille, dans laquelle chaque pixel a pour valeur respectivement
l'intensité horizontale, verticale et totale au niveau du pixel dans
l'image d'origine (une pseudo image en fait, car ces intensités
peuvent être négatives).

**Attention**: la formule du filtre utilise les lignes / colonnes précédentes et suivantes de la case courante. On ne peut donc pas utiliser cette formule sur les bords de l'image : dans ce cas, on mettra simplement 0.

Indication: `intensiteH` et `intensiteV` sont là
pour vous aider, il n'est pas obligatoire de s'en servir pour faire
`intensite`. On rappelle que la norme d'un vecteur
$\left(h,v\right)$ est $\sqrt{h^2+v^2}$. La fonction `sqrt`
permet de calculer la racine.

**Les tests sont écrits sur les images suivantes :**
 * Willis.512.pgm
 * Baboon.512.pgm
 * Billes.256.pgm
 * Embryos.512.pgm
 * House.256.pgm

Ces images vous sont fournies au format jpg, **vous devez les convertir au format pgm** en suivant les indications de [Partie 0](partie-0.md).

N'oubliez pas de compiler et d'exécuter le fichier [sobel-tout-en-un.cpp](sobel-tout-en-un.cpp) pour vérifier que vos fonctions
sont bien implantées. Pensez à vérifier que vos images sont semblables
à celles du dossier `sobel/correction`.

::::

+++

## Seuillage des gradients

Copier dans [seuillage-tout-en-un.cpp](seuillage-tout-en-un.cpp) les fonctions `lirePGM` et `ecrirePGM` qui seront utilisées pour les tests
et la fonction `intensite` qui sera utilisée pour le seuillage des gradients.

+++ {"deletable": false, "editable": false, "grade_id": "cell-34a86c523b4dfc8f"}

::::{admonition} Exercice 3.2 (\*) Renormalisation des gradients

Implantez dans [seuillage-tout-en-un.cpp](seuillage-tout-en-un.cpp) la fonction `renormalise`.

L'idée est d'utiliser toutes les teintes possibles dans le cas où
toutes les valeurs seraient comprises dans un petit intervalle $[0,v]$
avec $v\leq 255$.

Indication: Il peut être pertinent de chercher le max des valeurs.

Testez votre fonction avec la fonction de test proposée.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-7e7b9c077bf03097"}

::::{admonition} Exercice 3.3 (\*\*) Seuillage de l'intensité

Vous allez remarquer que l'on détecte beaucoup de contours. Il serait bon
de ne garder que ceux qui semblent correspondre aux contours des objets.
Les pixels avec une forte réponse au filtre de Sobel corrèlent bien
avec les pixels des contours.

Implanter la fonction `seuillage` dans [seuillage-tout-en-un.cpp](seuillage-tout-en-un.cpp)


Utiliser `seuillageTest` pour tester vos résultats.
Notamment, proposer plusieurs valeurs de seuil pour les images indiquées.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-6fa1db13b31c8259"}

## Double seuillage de l'intensité du gradient

Même en réglant manuellement le seuil, des pixels peuvent être
indûment considérés comme des contours. Une façon de diminuer ce
nombre d'erreurs consiste à appliquer un seuil très élevé pour
extraire des graines puis d'appliquer un seuil plus faible mais de ne
garder que les pixels connectés aux graines.

+++ {"deletable": false, "editable": false, "grade_id": "cell-6ee14ee3b6b2d96c"}

::::{admonition} Exercice 3.4 (\*\*\*) Croissance du contour de 1 pas

Implantez la première fonction `doubleSeuillage` "Filtre de double seuillage"
dans [seuillage-tout-en-un.cpp](seuillage-tout-en-un.cpp) qui prend en argument une image d'intensité `imgIntensite`
et une image `imgContour`, qui code un ensemble de pixels
sélectionnés (0 si sélectionné, 255 sinon) et qui renvoie une image
dans laquelle les pixels sont à 0 si et seulement si d'une part ils
ont une intensité supérieure à `seuil` et d'autre part
ils sont voisins d'un pixel sélectionné dans `imgContour`
(255 sinon).

Utilisez la fonction `doubleSeuillageTest` pour vérifier
vos résultats et proposer des paramètres pour les exemples indiqués.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-7230a0e7ccdbe367"}

::::{admonition} Exercice 3.5 (\*\*\*) Croissance du contour de plusieurs pas et visualisation

Implantez la deuxième fonction `doubleSeuillage` «Filtre de
double seuillage iteratif» dans
[seuillage-tout-en-un.cpp](seuillage-tout-en-un.cpp) qui prend en
argument une image `img` et qui renvoie une image dans laquelle un
pixel est à 0 si et seulement si il a dans l'image une intensité
supérieure à `seuilFort`, ou bien une intensité supérieure à
`seuilFaible` tout en étant connecté à un pixel d'intensité supérieure
à `seuilFort` par un chemin de taille inférieure à `nbAmelioration`
(255 sinon). (Remarque : les deux fonctions `doubleSeuillage` ont le
même nom mais prennent des arguments différents ce qui est acceptable en
C++ : le compilateur choisit la fonction à exécuter en fonction des
arguments).

:::{hint} Indication

Utilisez la fonction `seuillage` pour calculer les pixels d'intensité
supérieure à `seuilFort`; puis appliquer `nbAmelioration` fois la
fonction `doubleSeuillage` précédente pour successivement calculer
leurs voisins d'intensité supérieure à `seuilFaible`, puis les voisins
de ces voisins, et ainsi de suite.

:::

Utiliser la fonction `doubleSeuillageIteratifTest` pour vérifier
vos résultats et proposer des paramètres pour les exemples indiqués.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-e3da4a9e314a4e8b"}

## Aller plus loin

+++

::::{admonition} Exercice 3.6 (\*\*) Lissage

Afin de diminuer l'influence du bruit dans l'intensité, il peut être
intéressant de lisser l'image avant de calculer le filtre de Sobel.
Une façon de faire est de remplacer la valeur de chaque pixel par la
moyenne des quatre pixels voisins, ou des 8 voisins.
::::

+++

::::{admonition} Exercice 3.7 (\*\*\*) Améliorer l'algorithme
Dans `doubleSeuillage`, on parcourt l'image en entier pour chercher des pixels connectés
aux pixels déjà sélectionnés. Il serait plus efficace de n'explorer
que le voisinage des pixels déjà sélectionnés. De plus, il serait
intéressant de continuer ce processus tant que de nouveaux pixels sont
sélectionnés. Implémenter ces deux améliorations.
::::

+++

## Aller beaucoup plus loin


Quelques références sur les techniques d'extraction de contours et son
utilisation:

-   <http://fr.wikipedia.org/wiki/Filtre_de_Sobel>

-   <http://en.wikipedia.org/wiki/Sobel_operator>

-   un article référence sur le sujet de l'extraction de contour : Scale-space and edge detection using anisotropic diffusion, Pietro Perona and Jitendra Malik, *Pattern Analysis and Machine Intelligence, IEEE Transactions on* 12 (7), 629--639, 1990.

-   ce domaine de recherche est encore très actif, on peut citer par
    exemple la publication : Hierarchical segmentation and identification of thoracic vertebra using learning-based edge detection and coarse-to-fine deformable model, Jun Ma and Le Lu, Computer Vision and Image Understanding, 2013
