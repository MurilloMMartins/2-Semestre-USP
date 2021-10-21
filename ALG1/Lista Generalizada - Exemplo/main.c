#include <stdio.h>
#include "listagen.h"

int main(int argc, char *argv[]){
    no_t *l1 = concat(atomo(3), atomo(4));
    no_t *l2 = sublista(l1);
    l2 = concat(l2, atomo(2));
    no_t *l = concat(atomo(1), l2);
    imprimir(l);

    libera(l);
    return 0;
}