
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "profiler.h"
#include "vector.h"

#define N 1000
#define M 10000
#define STEP 10

double duracao_caso_l(Vector *v, int idx) {
    int valor = vector_get(v, idx);

    double inicio = get_timestamp();

    vector_find(v, valor);

    double fim = get_timestamp();

    double duracao = fim - inicio;

    return duracao;
}

double duracao_caso_b(Vector *nv, int idx) {
    int valor = vector_get(nv, idx);

    double inicio = get_timestamp();

    vector_binary_search(nv, valor);

    double fim = get_timestamp();

    double duracao = fim - inicio;

    return duracao;
}

int main() {
    srand(time(NULL));

    printf("M lsearch_min lsearch_max lsearch_avg qsort_bsearch_min "
           "qsort_bsearch_max qsort_bsearch_avg\n");

    Vector *v = vector_randomly_constructed(N);

    Vector *nv = vector_copy(v);
    double bsinicio = get_timestamp();
    vector_qsort(nv);
    double bsfim = get_timestamp();
    double bsduracao = bsfim - bsinicio;

    for (int m = 1; m <= M + 1; m += STEP) {
        double lmin = 0;
        double lmax = 0;
        double ltotal = 0;

        double bmin = 0;
        double bmax = 0;
        double btotal = bsduracao;

        for (int i = 0; i < m; i++) {
            int idx = rand() % N;

            double lduracao = duracao_caso_l(v, idx);

            lmin = mmin(lmin, lduracao);
            lmax = mmax(lmax, lduracao);
            ltotal += lduracao;

            double bduracao = duracao_caso_b(nv, idx);

            bmin = mmin(bmin, bduracao);
            bmax = mmax(bmax, bduracao);
            btotal += bduracao;
        }

        double lavg = ltotal / m;
        double bavg = btotal / m;

        printf("%d %g %g %g %g %g %g\n", m, lmin, lmax, lavg, bmin, bmax, bavg);
    }

    vector_destroy(v);

    vector_destroy(nv);

    return EXIT_SUCCESS;
}
