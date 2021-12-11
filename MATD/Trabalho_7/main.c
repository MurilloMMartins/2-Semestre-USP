#include <stdio.h>
#include <stdlib.h>

unsigned int exponenciacao_modular(unsigned int base, unsigned int expoente, unsigned int modulo);

int main(int argc, char *argv[]){

    if(argc != 4){
        printf("Formatação Incorreta\n");
        return 1;
    }
    
    unsigned int base = atoi(argv[1]);
    unsigned int expoente = atoi(argv[2]);
    unsigned int modulo = atoi(argv[3]);

    int resultado = exponenciacao_modular(base, expoente, modulo);
    printf("\n\n%u∧%u (mod %u) = %u\n", base, expoente, modulo, resultado);

    return 0;
}

/**
 * @brief essa função realiza a exponenciacao modular baseado nos inputs. Ela funciona da seguinte maneira:
 * Primeiramente ela vê se nosso expoente é ímpar, caso ele seja, usamos a seguinte relação:
 * Sendo 'B' uma base, 'E' o expoente e 'M' o módulo temos:
 * B∧E (mod M) = B*B∧(E-1) (mod M).
 * Assim a função passa o 'B' de fora (que não possui "∧(E-1)") para o resultado, guardando ele em uma variável,
 * e faz com que o expoente vire par. Após isso, garantindo que o expoente é par, Usamos a seguinte propriedade:
 * B∧E (mod M) = (B∧2)∧(E/2) (mod M) = (B∧2 (mod M))∧(E/2) (mod M).
 * Assim reduzindo o nosso expoente pela metade e geramos uma nova base baseada na base antiga ao quadrado módulo 'M' 
 * (o que não altera nosso resultado final).
 * Com essa nova base, a função repete os passos acima até que o expoente seja menor que 1.
 * 
 * @param base base B
 * @param expoente expoente E
 * @param modulo modulo M
 * @return unsigned int resultado de 'B∧E (mod M)'
 */
unsigned int exponenciacao_modular(unsigned int base, unsigned int expoente, unsigned int modulo){

    //inicializando a variável de resultado
    unsigned int resultado = 1;

    while(expoente > 0){
        //isso é feito somente se o expoente é ímpar
        if(expoente % 2 == 1){
            printf("%u*%u∧%u (mod %u)\n", base, base, expoente-1, modulo);
            printf("Res = %u*%u (mod %u)", resultado, base, modulo);

            //aqui nós "retiramos" um elemento do expoente (que é passado para o resultado)
            //assim nosso expoente sempre será par a partir daqui
            resultado = (resultado * base) % modulo;
            expoente--;

            printf("= %u\n", resultado);
            
        }

        if(expoente != 0)
            printf("%u∧%u (mod %u) = ", base, expoente, modulo);
        
        //aqui o expoente é dividido por 2
        expoente = expoente/2;
        
        if(expoente != 0)
            printf("(%u∧2 (mod %u))∧%u (mod %u) = ", base, modulo, expoente, modulo);

        //aqui nós fazemos a base ao quadrado e tiramos o módulo desse resultado
        base = (base * base) % modulo;

        if(expoente != 0)
            printf("%u∧%u (mod %u)\n", base, expoente, modulo);

    }

    return resultado;
}