#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct sequencia{
    int numeros[100];
    int tamanho;
} sequencia_t;

void numerosNaSequencia(sequencia_t seq);

int main(){
    sequencia_t seqDeNumeros;
    seqDeNumeros.tamanho = 0;

    int fimDaLinha = 0;
    do{
        fimDaLinha = scanf(" %d", &seqDeNumeros.numeros[seqDeNumeros.tamanho]);
        seqDeNumeros.tamanho++;
    }while(fimDaLinha != EOF);
    seqDeNumeros.tamanho--;

    numerosNaSequencia(seqDeNumeros);

}

void numerosNaSequencia(sequencia_t seq){
    sequencia_t numerosNaSequencia;
    numerosNaSequencia.tamanho = 1;

    for(int i = 0; i < seq.tamanho; i++){
        int numeroAtual = seq.numeros[i];
        int contador = 0;

        int apareceuAntes = FALSE;
        for(int k = 0; k < numerosNaSequencia.tamanho; k++){
            if(numeroAtual != numerosNaSequencia.numeros[k]){
                apareceuAntes = FALSE;
            }
            else{
                apareceuAntes = TRUE;
                break;
            }
        }

        if(apareceuAntes == FALSE){
            numerosNaSequencia.numeros[numerosNaSequencia.tamanho] = numeroAtual;
            numerosNaSequencia.tamanho++;

            for(int j = 0; j < seq.tamanho; j++){
                if(numeroAtual == seq.numeros[j]){
                    contador++;
                }
            }

            printf("%d (%d)\n", numeroAtual, contador);
        }
    }
}