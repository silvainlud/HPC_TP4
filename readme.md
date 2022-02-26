## Ludwig SILVAIN - M1 WedSci

# HPC : TP4

## Exercice 1

5) La méthode la plus rapide est la version `1.2` puis `1.3` puis `1.4b` puis `1.4a`. On peut donc dire que la
   parallélisation des boucles imbriquées n'est pas la plus optimale de cette façon

6) Qu'il ne faut pas choisir un nombre de segments trop faible au risque de dégradé les performances.

7) Cela a pour effet de changer l'ordre des images. On peut donc en conclure que pour chaque binôme (x,y) obtenu au
   début de la seconde boucle, OpenMP lance un thread.

## Exercice 2

2)

| N Threads | Tp2    | Tp4       |
|-----------|--------|-----------|
| 1         | 1.044s | 1.25371s  |
| 2         | 0.544s | 0.659462s |
| 3         | 0.597s | 0.504543s |
| 4         | 0.433s | 0.460571s |
| 5         | 0.452s | 0.46242s  |
| 6         | 0.342s | 0.4087s   |
| 7         | 0.298s | 0.478032s |
| 8         | 0.288s | 0.447289s |