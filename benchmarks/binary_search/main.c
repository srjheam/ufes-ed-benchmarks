
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "profiler.h"
#include "vector.h"

#define N 140000
#define M 1000
#define STEP 200

double duracao_caso(Vector *v, int idx) {
    int valor = vector_get(v, idx);

    double inicio = get_timestamp();

    vector_binary_search(v, valor);

    double fim = get_timestamp();

    double duracao = fim - inicio;

    return duracao;
}

int bsearch_pior_idx(Vector *v) {
    int n = log2l(v->size);;

    double l = 1 - pow(2, -n);

    double ref = l * v->size;

    int idx = ceill(ref);

    return idx;
}

int main() {
    srand(time(NULL));

    printf("N menor maior media melhorElem piorElem\n");

    for (int n = 1; n <= N + 1; n += STEP) {
        Vector *v = vector_randomly_sorted(n);

        double min = 0;
        double total = 0;
        double max = 0;

        for (int i = 0; i < M; i++) {
            int idx = rand() % n;

            double duracao = duracao_caso(v, idx);

            min = mmin(min, duracao);
            max = mmax(max, duracao);
            total += duracao;
        }

        double media = total / M;
        
        double duracao_primeiro = duracao_caso(v, (v->size - 1) / 2);

        double duracao_ultimo = duracao_caso(v, bsearch_pior_idx(v));

        printf("%d %g %g %g %g %g\n", n, min, max, media, duracao_primeiro, duracao_ultimo);

        vector_destroy(v);
    }

    return EXIT_SUCCESS;
}
