
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "profiler.h"
#include "vector.h"

#define N 14000
#define M 15
#define STEP 1400

double duracao_caso_l(Vector *v) {
    double inicio = get_timestamp();

    vector_qsort(v);

    double fim = get_timestamp();

    double duracao = fim - inicio;

    return duracao;
}

int main() {
    srand(time(NULL));

    printf("N menor maior media\n");

    for (int n = 1; n <= N + 1; n += STEP) {
        double min = 0;
        double total = 0;
        double max = 0;

        for (int i = 0; i < M; i++) {
            Vector *v = vector_randomly_constructed(n);

            double duracao = duracao_caso_l(v);

            min = mmin(min, duracao);
            max = mmax(max, duracao);
            total += duracao;

            vector_destroy(v);
        }

        double media = total / M;

        printf("%d %g %g %g\n", n, min, max, media);
    }

    return EXIT_SUCCESS;
}
