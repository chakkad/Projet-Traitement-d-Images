---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
---

# Rapport de projet Image

*Les paragraphes en italique comme celui-ci vous donnent des
indications sur le contenu attendu; ils sont à supprimer une fois
votre rapport rédigé*

*Ce rapport pourra servir de support pour votre présentation orale*

*Soyez objectifs et factuels! Vous ne serez pas évalué sur ce que vous
affirmez, mais sur la pertinence et la justesse de ce que vous
affirmez.*

+++

## Auteurs

- Nom, prénom, courriel, groupe
- Nom, prénom, courriel, groupe

+++

## Résumé du travail effectué

*Pour chaque partie du sujet, décrire brièvement l'avancement de votre
projet. Exemples de réponses: «non traitée», «réalisée, documentée,
testée», «réalisée, sauf 2.3», «réalisée mais non testée», «réalisée
sauf 2.4 pour lequel notre programme ne compile pas». Pour les
questions «Aller plus loin» plus ouvertes, décrire plus en détail ce
que vous avez choisi de réaliser.*

*En plus du rapport, la documentation de chaque fonction dans le code
devra préciser son auteur et votre degré de confiance dans
l'implantation et les éléments factuels motivant cette confiance:
présence de tests, bogues et limitations connus, etc.*

- Partie 1: traitée
- Partie 2: traitée
- Partie 3: Non traitée
- Partie 4: Non traitée
- Partie 5: Non traitée
- Partie 6: Non traitée

+++

## Démonstration

*Soutenez ce que vous affirmez dans la section précédente au moyen de
quelques exemples **bien choisis**. Vous pourrez par exemple compiler et
lancer certains de vos programmes, lancer des tests, afficher des images.*

*Ci-dessous, nous vous proposons un début de démonstration pour les différentes
parties*

*Ne gardez que des exemples pertinents qui mettent en valeur votre
travail. Inutile de perdre du temps sur le premier programme si vous
avez fait les suivants plus compliqués; l'auditeur se doutera bien que
vous avez réussi à le faire.*

+++

### Partie 1

*Les cellules commençant par `%%bash` sont interprétées comme des
commandes bash, comme dans un terminal* :

```{code-cell} ipython3
%%bash --login
clang++ pbm-affiche.cpp -o pbm-affiche
```

```{code-cell} ipython3
%%bash --login
./pbm-affiche
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pbm/smiley-inverse.pbm")      # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
%%bash --login
clang++ pbm-tout-en-un.cpp -o pbm-tout-en-un
```

```{code-cell} ipython3
%%bash --login
./pbm-tout-en-un
```

```{code-cell} ipython3
# Vérification d'une des images obtenues
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/code.pbm")               # charge l'image
im.resize((160, 160))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/smiley.pbm")               # charge l'image
im.resize((80, 80))                         # affiche l'image avec une taille donnée
```

### Partie 2

```{code-cell} ipython3
%%bash --login
clang++ pgm-tout-en-un.cpp -o pgm-tout-en-un
```

```{code-cell} ipython3
%%bash --login
./pgm-tout-en-un
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain.pgm")               # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

### Partie 3

```{code-cell} ipython3
%%bash --login
clang++ sobel-tout-en-un.cpp -o sobel-tout-en-un
```

```{code-cell} ipython3
! ./sobel-tout-en-un
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

*Ajoutez des cellules et complétez avec les autres programmes implantés et images réalisées*

```{code-cell} ipython3

```

### Partie 4

```{code-cell} ipython3
%%bash --login
make pgm-test
```

```{code-cell} ipython3
%%bash --login
./pgm-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

*Ajoutez des cellules et complétez avec les autres programmes implantés et images réalisées*

```{code-cell} ipython3

```

### Partie 5

*A compléter*

+++

### Partie 6

*A compléter*

+++

## Organisation du travail

*Décrire en quelques phrases comment vous vous êtes organisés pour
travailler sur le projet: nombre d'heures consacrées au projet,
répartition du travail dans le binôme, moyens mis en œuvre pour
collaborer, etc. Si vous avez bénéficié d'aide (en dehors de celle
de vos enseigants), précisez le.*

+++

## Prise de recul

*Décrire en quelques phrases les difficultés rencontrées, ce que vous
avez appris à l'occasion du projet, le cas échéant comment vous vous y
prendriez si vous aviez à le refaire.*
