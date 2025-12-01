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

+++ {"deletable": false, "editable": false, "grade_id": "cell-1780d26010a51676"}

# Partie 0 : Conversion et visualisation des images PBM, PGM et PPM

+++ {"deletable": false, "editable": false, "grade_id": "cell-557f8cac6c596ec2"}

Dans le dossier `images`, nous vous avons fourni une collection
d'images sur lesquelles vous allez travailler. La plupart des images
fournies sont au format `JPEG` (extension `.jpg`).

+++ {"deletable": false, "editable": false, "grade_id": "cell-557f8cac6c596ec3"}

1.  Consultez maintenant le contenu du dossier avec le navigateur de
    fichier de JupyterLab et ouvrez quelques unes de ces images.

+++ {"deletable": false, "editable": false, "grade_id": "cell-557f8cac6c596ec4"}

Le format `JPEG` est un format binaire compressé, bien adapté pour des
photos par exemple. Avec ce que nous avons vu ce semestre, nous
n'avons pas encore les éléments requis pour manipuler de tels fichiers
en C++. Aussi, nous aller travailler, comme dans le TP 8, sur des
images aux formats `PBM` (images binaires en noir et blanc), `PGM`
(images en niveau de gris) et `PPM` (images en couleur). Comme nous
avons vu, ces formats permettent d'**encoder des images dans des
fichiers textes** lisibles par un humain, et relativement faciles à
lire et écrire en C++. Le détail de chaque format est donné dans les
différentes parties de ce projet.

+++

## Ouvrir une image PBM, PGM ou PPM comme un fichier texte

+++

1.  Naviguez avec Jupyter dans le dossier `images` et ouvrez une image
    au format PBM, PGM, ou PPM, comme par exemple,
    [](images/illusion.pgm). Vous constaterez que le fichier s'ouvre
    en mode texte.

+++

2.  Ouvrez de même d'autres images

+++

:::{tip} Astuce

Dans un explorateur de fichier classique, par exemple sur les machines
Linux de l'université, l'image s'ouvre en général en tant
qu'image. Pour voir le fichier texte associé, il faut faire

    bouton droit >> Ouvrir avec une autre application

Et choisir un éditeur de texte (ou l'ouvrir directement depuis votre
éditeur, par exemple avec `geany`)

:::

+++

## Visualiser une image PBM, PGM ou PPM

+++

Le code (python) ci-dessous permet d'afficher les images `PBM`, `PGM`
et `PPM` directement dans Jupyter.

1.  Copiez et adaptez la cellule ci-dessous pour afficher toutes les
    images aux formats `PBM`, `PGM` ou `PPM`.

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/Willis.512.pgm")         # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

:::{tip} Alternatives
-   Sous Windows, vous pouvez utiliser l’application `irfanview`.
-   Sous Linux, vous pouvez utiliser l’application `xviewer` :
    utilisez «Control +» et «Control -» pour zoomer /
    dezoomer. Vous remarquerez que l’image est lissée / floutée. Allez
    dans le menu «Edit -> Preferences» et décochez «Smooth images when
    zoomed in» pour mieux voir les pixels.
:::

+++

## Convertir des images

+++

Afin d'économiser de la place lors la transmission Les photos qui vous
ont été fournies dans le dossier `image` sont au format `JPEG`. Pour
pouvoir les manipuler, vous devrez donc au préalable les convertir au
format `PGM` ou `PPM`. Pour cela, nous allons utiliser la commande
`convert` de la suite logicielle ImageMagick.

+++

1.  Dans le terminal, allez dans le dossier image,
    ```
    cd ~/ProgImperative/Projet-Image/images
    ```
    puis convertissez l'image `Baboon.512.jpg` au format `PGM` avec la
    commande suivante :
    ```
    magick -compress None Baboon.512.jpg Baboon.512.pgm
    ```

+++

2.  Ouvrez ci-dessous l'image pour vérifier que tout c'est bien passé;
    vous noterez que l'image obtenue est en niveau de gris.

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("images/Baboon.512.pgm")       # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

3.  Convertissez de même cette image au format `ppm`, et vérifiez le
    résultat.

+++

Au fur et à mesure du projet, vous convertirez de même les autres
photos fournies en fonction des besoins. Vous pourrez aussi utiliser
ces conversions pour travailler sur des photos de votre cru.

+++

4.  Importez une image de votre choix dans le dossier `images`. Vous
    pouvez par exemple naviguer dans le dossier `images` de Jupyter et
    utiliser le bouton «Charger des fichiers» ou «Upload» en haut vers
    la gauche.

+++

5.  Convertissez cette image au format `PPM` et vérifiez le résultat.

+++

:::{tip} Alternatives

Il est aussi possible d'effectuer ces conversions via des applications
graphiques comme GIMP (GNU/Linux, Windows, MacOs) ou irfanview
(Windows), en utilisant les format PGM ou PPM **non compressés**. Dans GIMP,
c'est dans le menu :

    Fichier -> Exporter vers -> mon_image.pgm -> Format ASCII

:::
