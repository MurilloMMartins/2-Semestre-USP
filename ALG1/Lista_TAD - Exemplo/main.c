#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main(){
    lista_t *l = cria();
    insere(l, 5);
    insere(l, 2);
    insere(l, 3);
    insere(l, 7);
    insere(l, 8);
    insere(l, 1);
    imprimir(l);

    remover(l, 5);
    imprimir(l);

    remover(l, 1);
    imprimir(l);

    remover(l, 3);
    imprimir(l);

    liberar(l);

    return(0);
}