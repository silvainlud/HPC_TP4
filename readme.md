## Ludwig SILVAIN - M1 WedSci

# HPC : TP4

## Exercice 1

5) La méthode la plus rapide est la version `1.2` puis `1.3` puis `1.4b` puis `1.4a`.
On peut donc dire que la parallélisation des boucles imbriquées n'est pas la plus optimale de cette façon

6) Qu'il ne faut pas choisir un nombre de segments trop faible au risque de dégradé les performances.

7) Cela a pour effet de changer l'ordre des images. On peut donc en conclure que pour chaque binôme (x,y) obtenu 
au début de la seconde boucle, OpenMP lance un thread.  