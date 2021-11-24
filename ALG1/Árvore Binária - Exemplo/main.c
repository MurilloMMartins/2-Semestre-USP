#include <stdio.h>
#include <stdlib.h>
#include "ab.h"

int main(int argc, char *argv[]){
    arvore_t *a = criar();

    inserir_esq(a, 1, -1);
    inserir_esq(a, 2, 1);
    inserir_dir(a, 3, 1);
    inserir_esq(a, 4, 3);
    inserir_dir(a, 5, 3);
    inserir_esq(a, 6, 4);

    imprimir(a->raiz);
    printf("\n");
    return 0;
}