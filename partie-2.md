---
jupytext:
  notebook_metadata_filter: exports, myst
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
---

+++ {"deletable": false, "editable": false, "grade_id": "cell-de0a7b66e0f7d60b"}

# Partie 2 : Attaquons les images en niveau de gris

+++ {"deletable": false, "editable": false, "grade_id": "cell-c910520f2621f95d"}

Description du format PGM non compressé
---------------------------------------

La page <http://fr.wikipedia.org/wiki/Portable_pixmap> détaille le
format général d'un fichier PGM non compressé. L'entête est de la
forme:

    P2
    nbColonnes nbLignes
    255

suivi d'une liste d'entiers, séparés par des espaces ou des sauts de
lignes, décrivant les pixels de haut en bas et de gauche à droite
(**Attention:** les lignes de l'image ne sont pas forcément les
mêmes que celles du fichier!).

Prenez le temps d'ouvrir (comme fichier texte et comme image) les fichiers PBM qui sont fournis dans le projet (cf [Visualisation des images PBM PGM et PPM](partie-0.md) )

En principe, les spécifications du format de fichier PGM indiquent de
plus qu'aucune ligne du fichier ne doit dépasser 70 caractères;
cependant la plupart des logiciels s'en sortent même si cette
contrainte n'est pas respectée. Les spécifications indiquent aussi
qu'un fichier PGM peut contenir des commentaires, sous la forme de
lignes commençant par un '\#'.

+++ {"deletable": false, "editable": false, "grade_id": "cell-a577b80d4dff1d76"}

## Le type `ImageGris`

Tout comme les images en noir et blanc, on va stocker les images en niveau de gris
dans un double tableau. On définit le type suivant dans [pgm-tout-en-un.cpp](pgm-tout-en-un.cpp).

    /** Structure de donnees pour representer une image en teintes de gris **/
    typedef vector<vector<double> > ImageGris;

Lors de la lecture ou de l'écriture d'un fichier image, toutes les valeurs sont des entiers
`int`. Cependant il sera commode d'utiliser un type `double` pour ne pas rencontrer de
problème de conversion lors des opérations que l'on effectuera sur les
images.

+++ {"deletable": false, "editable": false, "grade_id": "cell-0875faab2f5c7d55"}

::::{admonition} Exercice 2.1 (\*) Lecture d'une image PGM 

Implantez la fonction `lirePGM` du fichier [pgm-tout-en-un.cpp](pgm-tout-en-un.cpp)


Rappel: utilisez les instructions suivantes pour ouvrir un
fichier, et émettre un message d'erreur si celui-ci n'existe pas:

    ifstream pgm;
    pgm.open(source);
    if (not pgm)
        throw runtime_error("Fichier non trouve: "+source);

*Optionnel :* gérer les fichiers contenant des commentaires; si vous ne
le faites pas, il vous faudra vérifier que les fichiers PGM que vous
utilisez sont effectivement sans commentaires et les supprimer le cas
échéant.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-c127a47ebbe43cdf"}

::::{admonition}  Exercice 2.2 (\*) Écriture d'une image PGM 

Implantez la fonction `ecrirePGM` du fichier [pgm-tout-en-un.cpp](pgm-tout-en-un.cpp)

Indications:

-   Pour tronquer une valeur `x` de type
    `double` en entier, il suffit d'utiliser l'opération
    `((int)x)`. Par exemple `((int)2.5)==2`.
    Ainsi, `((int)img[2][10])` transforme en entier le pixel
    (2,10) de l'image `img`.

-   Pour l'écriture, il est acceptable de ne mettre qu'un pixel par
    ligne (c'est moins lisible pour l'humain mais plus facile à
    programmer et équivalent pour l'ordinateur).

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-55ae4da1d23b8baf"}

## Tests des fonctions de lecture et d'écriture 

Des tests sont fournis dans le fichier
[pgm-tout-en-un.cpp](pgm-tout-en-un.cpp). Par défaut, le programme lance ces tests. Compilez et exécutez le programme [pgm-tout-en-un.cpp](pgm-tout-en-un.cpp)
et vérifiez que vos codes sont corrects.

**N'oubliez pas de vérifier les images crées en vous servant des explications du [préambule](partie-0.md)**

+++

## Inversion des niveaux de gris pour créer des images cliché

+++ {"deletable": false, "editable": false, "grade_id": "cell-dbd9e4429a50b732"}

Une image cliché s'obtient en inversant les valeurs des niveaux de gris dans une image PGM.

-   la valeur 0 devient 255

-   la valeur 1 devient 254

-   la valeur 2 devient 253

-   ...

-   la valeur 255 devient 0

::::{admonition} Exercice 2.3 (\*)  

Implantez la fonction `inversePGM` du fichier [pgm-tout-en-un.cpp](pgm-tout-en-un.cpp) et testez le résultat. 

*Remarque: cette question est indépendante de la suite du projet.*
::::

+++

Ouvrez le fichier [rapport.md](rapport.md) et complétez ce qui correspond à la Partie 2. En particulier, vérifier que l'exécution et les tests proposés dans la démonstration fonctionnent. Rajoutez des cellules pour visualiser les autres images.

**Bravo ! Vous avez maintenant quelques outils de manipulation d'images PGM** Vous pouvez passer à la [Partie 3](partie-3.md) pour développer des fonctions de traitement d'images PGM ou à la [Partie 4](partie-4.md) pour voir la compilation séparée et la création d'une bibliothèque.

```{code-cell} ipython3

```
