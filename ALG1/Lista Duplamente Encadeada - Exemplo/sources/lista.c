#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lista.h"

typedef struct no no_t;

struct no{
    elem info;
    no_t *ant, *prox;
};

struct lista {
    no_t *inicio, *fim;
};

lista_t *criar(){
    lista_t *p;
    p = (lista_t *)malloc(sizeof(lista_t));
    p->inicio = NULL;
    p->fim = NULL;

    return p;
}

void liberar(lista_t *l){
    if(l != NULL){
        no_t *aux = l->inicio;
        while(aux != NULL){
            l->inicio = l->inicio->prox;
            free(aux);
            aux = l->inicio;
        }
        free(l);
    }
}

int inserir(lista_t *l, elem x){
    assert(l != NULL);

    no_t *p = (no_t *)malloc(sizeof(no_t));
    p->info = x;
    p->prox = NULL;
    p->ant = NULL;

    no_t *aux, *ant;
    ant = NULL;
    aux = l->inicio;

    while(aux != NULL && x > aux->info){
        ant = aux;
        aux = aux->prox;
    }

    //caso onde x já existe
    if(aux != NULL && x == aux->info){
        free(p);
        return 0;
    }

    if(ant == NULL){ //inserindo no início, lista vazia ou lista com elementos
        p->prox = l->inicio;
        if(l->inicio != NULL) l->inicio->ant = p;
        l->inicio = p;
    } 
    else{
        p->prox = ant->prox;
        ant->prox = p;
        if(p->prox != NULL) p->prox->ant = p;
        else l->fim = p;
        p->ant = ant;
    }
    
    return 1;
}

int remover(lista_t *l, elem x){
    assert( l != NULL);

    no_t *p = l->inicio;
    no_t *ant = NULL;

    while(p != NULL && x > p->info){
        ant = p;
        p = p->prox;
    }

    if(p == NULL){
        return 0;
    }

    if(ant == NULL){ //remocao do primeiro elemento
        l->inicio = l->inicio->prox;
        if(l->inicio != NULL) l->inicio->ant = NULL;
        else l->fim = NULL;
        free(p);
    }
    else{ //remocao de elemento no meio ou no fim
        if(p->prox == NULL){ //remover do fim da lista
            l->fim = p->ant;
            ant->prox = NULL;
            free(p);
        }
    }

    return 1;
}

void imprimir(lista_t *l){
    assert(l != NULL);
    no_t *p = l->inicio;

    while(p != NULL){
        printf("%d ", p->info);
        p = p->prox;
    }
    printf("\n");
}

void imprimir_inv(lista_t *l){
    assert(l != NULL);
    no_t *p = l->fim;

    while(p != NULL){
        printf("%d ", p->info);
        p = p->ant;
    }
    printf("\n");
}
