#include <stdio.h>
#include <stdlib.h>
#include "banco.h"

int main(int argc, char *argv[]){
    banco_t *b = criar();
    elem x;
    
    inserir(b, 1);
    inserir(b, 2);
    inserir(b, 3);
    inserir(b, 4);
    inserir(b, 5);
    inserir(b, 6);

    while(!esta_vazio(b)){
        remover(b, &x);
        printf("%d ", x);
    }
    printf("\n");

    liberar(b);

    return 0;
}