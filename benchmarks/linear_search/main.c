
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "profiler.h"

#define N 140000
#define M 1000
#define STEP 200

int main()
{
    srand(time(NULL));

    printf("N menor maior media \n");

    for (int n = 1; n <= N + 1; n += STEP)
    {
        Vector *v = vector_construct();

        for (int i = 0; i < n; i++)
            vector_push_back(v, rand());

        double min = 0;
        double total = 0;
        double max = 0;

        for (int i = 0; i < M; i++)
        {
            int idx = rand() % n;

            int valor = vector_get(v, idx);

            double inicio = get_timestamp();

            vector_find(v, valor);

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
