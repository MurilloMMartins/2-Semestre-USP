#ifndef LIST_H
#define LIST_H

typedef int elem;
typedef struct lista lista_t;

lista_t *criar();
void liberar(lista_t *l);
int inserir(lista_t *l, elem x);
int remover(lista_t *l, elem x);
void imprimir(lista_t *l);
void imprimir_inv(lista_t *l);


#endif