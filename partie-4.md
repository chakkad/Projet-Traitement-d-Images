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

+++ {"deletable": false, "editable": false, "grade_id": "cell-e2126ec8111a8dce"}

# Partie 4 : Vers une bibliothèque de traitement d'images

+++ {"deletable": false, "editable": false, "grade_id": "cell-800a6b5cc54b8f17"}

Jusqu'ici, nous avons implémenté plusieurs fonctionalités de
traitement d'images. Néanmoins, nous avons dû dupliquer beaucoup de
code d'un fichier à l'autre, comme par exemple les fonctions
`lirePGM`. De plus les fichiers commencent à être longs,
avec des fonctions main ayant plusieurs rôles simultanés (lancer les
tests et faire une autre action).

Nous allons maintenant restructurer le code afin d'éviter ces
inconvénients grâce à la compilation séparée. Il ne s'agit pas ici de
de créer de nouvelles fonctions; simplement d'organiser le code
différemment.

+++ {"deletable": false, "editable": false, "grade_id": "cell-d793550e9b624051"}

::::{admonition} Exercice 4.1 (\*) Types d'image

Durant le projet plusieurs types pour stocker et manipuler des images
ont été définis. Regrouper tous ces types dans le fichier
[image.hpp](image.hpp) Par la suite, tous les modules qui auront besoin de
ces types devront inclure `image.hpp`.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-c2a8d74ecb6c1120"}

::::{admonition} Exercice 4.2 (\*) Module `pgm`

Plusieurs fonctions de base sur images PGM ont été implémentées et
réutilisées dans plusieurs programmes, notamment pour les tests. Afin
d'éviter cette duplication de code, nous allons regrouper ces
fonctions dans le module pgm.

1.  Consulter le fichier [pgm.hpp](pgm.hpp); il a été prérempli avec les
    entêtes des fonctions. **Attention, c'est un fichier `.hpp`, il ne
    doit pas contenir le code des fonctions**

3.  Compléter le fichier [pgm.cpp](pgm.cpp) avec vos fonctions
    `lirePGM`, `ecrirePGM`, `inversePGM`.

4.  Compléter le fichier [pgm-test.cpp](pgm-test.cpp) avec les tests
    de ces fonctions.

5.  Utiliser la compilation séparée pour produire
    `pgm-test` à partir de [pgm.cpp](pgm.cpp) et
    [pgm-test.cpp](pgm-test.cpp).

6.  Exécuter `pgm-test`, et vérifier que les tests
    passent.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-d3d4a16683a432e9"}

::::{admonition} Exercice 4.3 (\*) Modules `sobel` et `seuillage`
Procéder de même que dans la section précédente pour compléter les
modules [sobel.cpp](sobel.cpp) et [seuillage.cpp](seuillage.cpp), avec leur
fichier d'entête et leurs tests. Vérifier que ces tests passent.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-85d468394d359839"}

::::{admonition} Exercice 4.4 (\*) Automatisation avec `make`
Compiler à la main devient vite fastidieux avec la compilation
séparée, puisque à chaque fois on doit se souvenir de toutes les
dépendantes: quels sont tous les fichiers qui doivent être compilés en
même temps.

`make` est un des outils permettant d'automatiser le
processus. Ouvrez le fichier `Makefile` avec un éditeur type
`gedit`; vous verrez que les dépendances sont indiquées.
(Remarque: vous n'avez pas besoin d'éditer ce fichier).

Avec ce `Makefile`, pour compiler `pgm-test` (par
exemple), vous n'avez plus qu'à taper la commande suivante dans le
terminal:

      make pgm-test

Pour compiler tous les programmes du projet, vous pouvez faire:

      make all

Pour lancer tous les tests du projet, vous pouvez faire:

      make tests
::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-149a5bb97fb871c5"}

::::{admonition} Exercice 4.5 (\*) Utilisation de la bilbiothèque
Le programme [TIN.cpp](TIN.cpp) implante un petit «couteau suisse» de
traitement d'image permettant d'appliquer tous les filtres que vous
avez implanté dans la bibliothèque à des images. Par exemple:

      ./TIN -e entree.pgm sortie.pgm

applique le filtre de Sobel à l'image dans
`entree.pgm`. Pour voir toutes les options:

      ./TIN -h

Pour utiliser la bibliotheque, vous devez au préalable la compiler en
tapant la commande suivante dans le terminal:

      make TIN
::::

```{code-cell}

```
