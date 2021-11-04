#ifndef NAME_H
#define NAME_H

#define TAM 100

typedef int elem;
typedef struct banco banco_t;

banco_t *criar();
int esta_vazio(banco_t *b);
int esta_cheio(banco_t *b);
int inserir(banco_t *b, elem x);
int remover(banco_t *b, elem *x);
void liberar(banco_t *b);


#endif