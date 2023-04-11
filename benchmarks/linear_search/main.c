
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

    vector_find(v, valor);

    double fim = get_timestamp();

    double duracao = fim - inicio;

    return duracao;
}

int main() {
    srand(time(NULL));

    printf("N menor maior media primeiroElem ultimoElem\n");

    for (int n = 1; n <= N + 1; n += STEP) {
        Vector *v = vector_construct();

        for (int i = 0; i < n; i++)
            vector_push_back(v, rand());

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

        double duracao_primeiro = duracao_caso(v, 0);

        double duracao_ultimo = duracao_caso(v, n - 1);

        printf("%d %g %g %g %g %g\n", n, min, max, media, duracao_primeiro, duracao_ultimo);

        vector_destroy(v);
    }

    return EXIT_SUCCESS;
}
