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

## Exercice 2

Avec Scene 02 et 512*512

| Nb. Threads | V1        | V2        | parall´elisation statique de la boucle externe | parall´elisation statique de la boucle interne | parall´elisation statique des deux boucles | parall´elisations dynamiques |   
|-------------|-----------|-----------|------------------------------------------------|------------------------------------------------|--------------------------------------------|------------------------------|
| 1           | 1.83724s  | 0.481618s | 0.478889s                                      | 0.54438s                                       | 0.484884s                                  | 0.486436s                    |
| 2           | 1.30274s  | 0.241572s | 0.294879s                                      | 0.268339s                                      | 0.341628s                                  | 0.254446s                    |
| 3           | 1.03348s  | 0.179169s | 0.232888s                                      | 0.243284s                                      | 0.252445s                                  | 0.174011s                    |
| 4           | 0.706164s | 0.133421s | 0.185225s                                      | 0.220878s                                      | 0.177527s                                  | 0.136369s                    |
| 5           | 0.605245s | 0.129717s | 0.193319s                                      | 0.226889s                                      | 0.166236s                                  | 0.127918s                    |
| 6           | 0.511354s | 0.120854s | 0.155561s                                      | 0.224896s                                      | 0.168229s                                  | 0.125876s                    |
| 7           | 0.555076s | 0.127063s | 0.187205s                                      | 0.238072s                                      | 0.162138s                                  | 0.124342s                    | 
| 8           | 0.491189s | 0.113918s | 0.140312s                                      | 0.16331s                                       | 0.131898s                                  | 0.112735s                    |
