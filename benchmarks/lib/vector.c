#include "stdlib.h"
#include "string.h"

#include "vector.h"

Vector *vector_construct() {
    Vector *v = calloc(1, sizeof *v);

    v->data = calloc(25, sizeof v->data);
    v->allocated = 25;

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
        v->data = realloc(v->data, v->allocated);
    }

    memmove(v->data + i + 1, v->data + i, (v->size - i) * sizeof(data_type));

    v->data[i] = val;

    v->size++;
}

// Troca os elementos das posições i e j (i vira j e j vira i)
void vector_swap(Vector *v, int i, int j) {
    data_type tmp = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = tmp;
}

typedef int (*cpy_fn)(const void *, const void *);

static int dt_cmp(const data_type *a, const data_type *b) { return *a - *b; }

// Ordena o vetor in-place (sem criar um novo vetor)
void vector_sort(Vector *v) {
    int swop = 0;
    do {
        swop = 0;
        for (int j = 1; j < v->size; j++)
            if (dt_cmp(&v->data[j - 1], &v->data[j]) > 0) {
                vector_swap(v, j - 1, j);
                swop = 1;
            }
    } while (swop);
}

// Retorna o indice de val usando busca binaria. Retorna -1 se nao encontrado.
int vector_binary_search(Vector *v, data_type val) {
    data_type *found =
        bsearch(&val, v->data, v->size, sizeof(data_type), (cpy_fn)dt_cmp);

    if (!found)
        return -1;

    return found - v->data;
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
