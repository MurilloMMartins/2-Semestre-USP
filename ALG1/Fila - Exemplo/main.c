#include <stdio.h>
#include "fila.h"

int main(int argc, char *argv[]){
    fila_t *f;
    elem x;
    f = criar();
    for(int i = 0; i < 10; i++){
        inserir(f, i);
    }

    while(!isEmpty(f)){
        remover(f, &x);
        printf("%d ", x);
    }
    printf("\n");
    return 0;
}