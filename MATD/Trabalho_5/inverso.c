/**
 * @file inverso.c
 * @author Murillo Moraes Martins (NºUSP 12701599)
 * @brief Esse programa calcula o inverso de um número em uma base Zd e avisa caso
 * esse número não seja invertível em Zd
 * @version 0.1
 * @date 2021-10-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int AlgoritmoDeEuclidesEstendido(int base, int n, int *a, int *b);

int main(int argc, char *argv[]){

    //verificando que há argumentos suficientes
    if(argc < 3){
        printf("Não há argumentos suficientes\n");
        return 1;
    }

    //transformando os inputs in inteiros
    int base = atoi(argv[1]);
    int valor = atoi(argv[2]);

    //verificando se os inputs tem o formato correto
    if(base < 0 || valor < 0){
        printf("Os números devem ser maiores ou iguais a 0\n");
        return 1;
    }

    //realizando o algoritmo de euclides estendido
    int i,j;
    int MCD = AlgoritmoDeEuclidesEstendido(base, valor, &j, &i);
    //esse while é feito para garantir que teremos um número positivo de i
    //ele pode ser feito pois um número negativo em Zd é equivalente a d + esse número
    //por exemplo: em Z9: [-2] = [7]
    while(i < 0) i += base;

    printf("\n%d*%d + (%d)*%d = %d", i, valor, j, base, MCD);

    //verificando se o número possui um inverso e avisando caso ele não tenha
    if(MCD == 1)
        printf("\n\nO inverso de %d em Z%d é: %d\n", valor, base, i);
    else
        printf("\n\n%d não é invertível em Z%d\n", valor, base);

    return 0;
}

/**
 * @brief função que calcula o inverso de um número através do algoritmo de euclides estendido
 * 
 * @param base base de Zd (nesse caso é o d)
 * @param valor valor que será avaliado
 * @param j numero que multiplica a base
 * @param i numero que multiplica o valor
 * @return int MCD entre a base e o valor 
 */
int AlgoritmoDeEuclidesEstendido(int base, int valor, int *j, int *i){
    int mcd;
    
    //verificando se entramos no caso base(quando base%valor = 0)
    if(valor == 0){
        *j = 1;
        *i = 0;
        printf("\n\nO MCD final foi: %d\n\n", base);
        return base;
    }
    int tempj, tempi;

    printf("\n%d = %d*%d + %d", base, base/valor, valor, base%valor);

    //passo recursivo
    mcd = AlgoritmoDeEuclidesEstendido(valor, base % valor, &tempj, &tempi);

    //substituindo i e j, assim chegando mais perto do inverso
    //substituimos da seguinte forma:

    //MCD(a, b) = MCD(b, a%b)
    //e como MCD(b, a%b) = i*b + j*(a%b):
    //MCD(a, b) = i*b + j*(a%b)

    //além disso, pelo fato de realizarmos divisões inteiras, sabemos que:
    //a = (a//b)*b + (a%b)
    //isolando a%b temos:
    //a%b = a - (a//b)*b

    //substituindo na equação inicial temos:
    //MCD(a, b) = i*b + j*(a - (a//b)*b)
    //MCD(a, b) = i*b + j*a - (a//b)*b*j
    //MCD(a, b) = a*j + b*(i - (a//b)*j)
    *j = tempi;
    *i = tempj - tempi*(base/valor);

    if(mcd == 1)
        printf("1 = %d*%d + %d*%d\n", *i, valor, *j, base);

    return mcd;
}