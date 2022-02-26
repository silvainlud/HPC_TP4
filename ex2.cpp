#include <iostream>
#include <cmath>
#include <omp.h>

// compilation : g++ -std=c++11 -pthread exo1.cpp -o exo1

#define N 100000000
#define NBT 10000


double resSomme;
double resSommeSqrt;
double resSommeSqrtLog;


// fonction calculant la somme des racines carrées multipliées par le logarithme des entiers entre i0 et i1
void sommeSqrtLog(int i0, int i1) {
    double begin = omp_get_wtime();
    double res = 0;
    for (int i = i0; i < i1; i++) {
        if (i == 0)
            continue;
        res += std::sqrt(i) * std::log(i);
    }
    double end = omp_get_wtime();

#pragma omp critical
    {
        resSommeSqrtLog += res;

        std::cout << "fin thread somme (racines x logs) - res = " << res << " en "
                  << (end - begin) << "s"
                  << std::endl;
    }

}

// fonction calculant la somme des racines carrées des entiers entre i0 et i1
void sommeSqrt(int i0, int i1) {
    double begin = omp_get_wtime();
    double res = 0;
    for (int i = i0; i < i1; i++)
        res += std::sqrt(i);
    double end = omp_get_wtime();

#pragma omp critical
    {
        resSommeSqrt += res;
        std::cout << "fin thread somme racines - res = " << res << " en "
                  << (end - begin) << "s"
                  << std::endl;
    }
}

// fonction calculant la somme des entiers entre i0 et i1
void somme(int i0, int i1) {
    double begin = omp_get_wtime();
    double res = 0;
    for (int i = i0; i < i1; i++)
        res += i;


    double end = omp_get_wtime();

#pragma omp critical
    {
        resSomme += res;

        std::cout << "fin thread somme - res = " << res << " en "
                  << (end - begin) << "s"
                  << std::endl;
    }
}

void sommes(int i0, int i1) {
    somme(i0, i1);
    sommeSqrt(i0, i1);
    sommeSqrtLog(i0, i1);
}

int main(int argc, char *argv[]) {

    // lancer les threads

    resSomme = 0;
    resSommeSqrt = 0;
    resSommeSqrtLog = 0;

    std::cout << "Parallèle " << std::endl;

    double begin = omp_get_wtime();


#pragma omp parallel for num_threads(8)
    for (int i = 0; i < NBT; ++i) {
        sommes(N / NBT * i, N / NBT * (i + 1));
    }

    double end = omp_get_wtime();


    std::cout << "somme - res = " << resSomme << std::endl;
    std::cout << "somme racines - res = " << resSommeSqrt << std::endl;
    std::cout << "somme (racines x logs) - res = " << resSommeSqrtLog << std::endl;
    std::cout << "tps de calcul parallèle : "
              << (end - begin)
              << "s" << std::endl;


    return 1;
}