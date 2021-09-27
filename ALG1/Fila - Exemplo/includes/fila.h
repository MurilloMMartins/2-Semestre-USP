#ifndef FILA_H
#define FILA_H

#define TamFila 100

typedef int elem;
typedef struct fila fila_t;

fila_t *criar();
int isEmpty(fila_t *f);
int isFull(fila_t *f);
int inserir(fila_t *f, elem x);
int remover(fila_t *f, elem *x);
void destruir(fila_t *f);

#endif