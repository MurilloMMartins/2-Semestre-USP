#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct ponto{
    int x, y;
} ponto_t;

int main(int argc, char *argv[]){
    pilha_t *p;

    p = create(sizeof(ponto_t));

    ponto_t ponto;
    for(int i = 0; i < 10; i++){
        ponto.x = i;
        ponto.y = -i;
        push(p, &ponto);
    }

    while(!isEmpty(p)){
        pop(p, &ponto);
        printf("(%d, %d) ", ponto.x, ponto.y);
    }
    printf("\n");

    destroy(p);

    return 0;
}