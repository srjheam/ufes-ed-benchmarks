#include "math.h"
#include "stdlib.h"
#include "string.h"

#include "vector.h"

Vector *vector_construct() { return vector_construct_i(25); }

Vector *vector_construct_i(int n) {
    if (n < 1)
        return NULL;

    Vector *v = calloc(1, sizeof *v);

    v->data = calloc(n, sizeof v->data);
    v->allocated = n;

    return v;
}

Vector *vector_randomly_constructed(int n) {
    Vector *v = vector_construct();

    for (int i = 0; i < n; i++)
        vector_push_back(v, rand());

    return v;
}

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

Vector *vector_randomly_reversed(int n) {
    Vector *v = vector_construct_i(n);

    int max = __INT_MAX__;

    for (int i = n; i > 0; i--) {
        max = max * pow(rand() / (double)RAND_MAX, 1 / (double)i);

        v->data[n - i] = max;
        v->size++;
    }

    return v;
}

void vector_push_back(Vector *v, data_type val) {
    if (v->size == v->allocated) {
        v->allocated *= 2;
        v->data = realloc(v->data, v->allocated * sizeof v->data);
    }

    v->data[v->size++] = val;
}

data_type vector_get(Vector *v, int i) { return v->data[i]; }

void vector_set(Vector *v, int i, data_type val) { v->data[i] = val; }

int vector_size(Vector *v) { return v->size; }

int datacmp(const data_type *a, const data_type *b) { return *a == *b; }

int vector_find(Vector *v, data_type val) {
    for (int i = 0; i < v->size; i++)
        if (v->data[i] == val)
            return i;

    return -1;
}

void vector_destroy(Vector *v) {
    free(v->data);

    free(v);
}

// Remove o i-ésimo elemento do vetor.
data_type vector_remove(Vector *v, int i) {
    data_type tmp = v->data[i];

    memmove(v->data + i, v->data + i + 1,
            (v->size - i - 1) * sizeof(data_type));

    v->size--;

    return tmp;
}

// Remove o primeiro elemento
data_type vector_pop_front(Vector *v) { return vector_remove(v, 0); }

// Remove o ultimo elemento
data_type vector_pop_back(Vector *v) { return vector_remove(v, v->size - 1); }

// Insere o elemento na i-esima posicao
void vector_insert(Vector *v, int i, data_type val) {
    if (v->size == v->allocated) {
        v->allocated *= 2;
        v->data = realloc(v->data, v->allocated * sizeof v->data);
    }

    memmove(v->data + i + 1, v->data + i, (v->size - i) * sizeof(data_type));

    v->data[i] = val;

    v->size++;
}

void vector_replace(Vector *v, int i, data_type val) { v->data[i] = val; }

// Troca os elementos das posições i e j (i vira j e j vira i)
void vector_swap(Vector *v, int i, int j) {
    data_type tmp = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = tmp;
}

typedef int (*cmp_fn)(const void *, const void *);

static int dt_cmp(const data_type *a, const data_type *b) { return *a - *b; }

// Ordena o vetor in-place (sem criar um novo vetor)
void vector_sort(Vector *v) {
    int swop = 1;
    for (int i = 0; i < v->size && swop; i++) {
        swop = 0;
        for (int j = 1; j < v->size - i; j++)
            if (dt_cmp(&v->data[j - 1], &v->data[j]) > 0) {
                vector_swap(v, j - 1, j);
                swop = 1;
            }
    }
}

void jswap(void *a, void *b, size_t size) {
    void *tmp = malloc(size);
    tmp = memcpy(tmp, a, size);

    memcpy(a, b, size);
    memcpy(b, tmp, size);

    free(tmp);
}

int partition(char *base, size_t size, cmp_fn compar, int e, int d) {
    void *pivot = base + d * size;
    int i = (e - 1);

    for (int j = e; j <= d - 1; j++) {
        if (compar(base + j * size, pivot) <= 0) {
            i++;
            jswap(base + i * size, base + j * size, size);
        }
    }
    jswap(base + (i + 1) * size, pivot, size);

    return (i + 1);
}

void quickSort(void *base, size_t size, cmp_fn compar, int e, int d) {
    if (e < d) {
        int pivot = partition(base, size, compar, e, d);

        quickSort(base, size, compar, e, pivot - 1);
        quickSort(base, size, compar, pivot + 1, d);
    }
}

void jqsort(void *base, size_t nmemb, size_t size, cmp_fn compar) {
    quickSort(base, size, (cmp_fn)compar, 0, nmemb - 1);
}

void vector_qsort(Vector *v) {
    //qsort(v->data, v->size, sizeof(data_type), (cmp_fn)dt_cmp);
    jqsort(v->data, v->size, sizeof(data_type), (cmp_fn)dt_cmp);
}

// Retorna o indice de val usando busca binaria. Retorna -1 se nao encontrado.
int vector_binary_search(Vector *v, data_type val) {
    int r = v->size - 1;
    int l = 0;

    while (l <= r) {
        int m = (l + r) / 2;

        if (dt_cmp(&v->data[m], &val) == 0)
            return m;
        else if (dt_cmp(&v->data[m], &val) < 0)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}

// Inverte o vetor in-place (sem criar um novo vetor)
void vector_reverse(Vector *v) {
    for (int i = 0; i < v->size / 2; i++)
        vector_swap(v, i, v->size - i - 1);
}

// Cria uma cópia do vector e dos valores de seus atributos.
Vector *vector_copy(Vector *v) {
    Vector *nv = vector_construct();

    nv->size = v->size;
    nv->allocated = v->allocated;

    nv->data = calloc(nv->allocated, sizeof nv->data);

    memcpy(nv->data, v->data, v->size * sizeof v->data);

    return nv;
}

// Remove todos os elementos de v
void vector_clear(Vector *v) {
    v->size = 0;
    v->data = realloc(v->data, sizeof v->data * 25);
    v->allocated = 25;
}

void *vector_find_all(Vector *v, data_type val) {
    Vector *nv = vector_construct();

    for (int i = 0; i < v->size; i++)
        if (dt_cmp(&val, &v->data[i]) == 0)
            vector_push_back(nv, v->data[i]);

    return nv;
}
