
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "profiler.h"
#include "vector.h"

#define N 10000
#define M 1000
#define STEP 200

Vector *vector_randomly_sorted(int n) {
    // Following
    // https://stackoverflow.com/a/66366347/12511877

    Vector *v = vector_construct_i(n);

    int max = __INT_MAX__;

    for (int i = n; i > 0; i--) {
        max = max * pow(rand() / (double)RAND_MAX, 1 / (double)i);

        v->data[i - 1] = max;
        v->size++;
    }

    return v;
}

int main() {
    srand(time(NULL));

    printf("N menor maior media \n");

    for (int n = 1; n <= N + 1; n += STEP) {
        Vector *v = vector_randomly_sorted(n);

        double min = 0;
        double total = 0;
        double max = 0;

        for (int i = 0; i < M; i++) {
            int idx = rand() % n;

            int valor = vector_get(v, idx);

            double inicio = get_timestamp();

            vector_binary_search(v, valor);

            double fim = get_timestamp();

            double duracao = fim - inicio;

            min = mmin(min, duracao);
            max = mmax(max, duracao);
            total += duracao;
        }

        double media = total / M;

        printf("%d %g %g %g\n", n, min, max, media);

        vector_destroy(v);
    }

    return EXIT_SUCCESS;
}
