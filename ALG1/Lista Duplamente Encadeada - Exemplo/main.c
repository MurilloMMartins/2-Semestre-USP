#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main(int argc, char *argv[]){
    lista_t *l = criar();

    inserir(l, 5);
    inserir(l, 2);
    inserir(l, 7);
    inserir(l, 4);
    inserir(l, 1);
    inserir(l, 8);

    imprimir(l);
    imprimir_inv(l);

    remover(l, 1);
    imprimir(l);
    remover(l, 8);
    imprimir(l);
    remover(l, 5);
    imprimir(l);

    liberar(l);

    return 0;
}