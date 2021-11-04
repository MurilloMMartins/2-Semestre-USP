#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_MAX 9
#define ITERACOES 10

void bubbleSort(int *v, int n);
void insertionSort(int* v, int n);
void mergeSort(int* v, int ini, int fim);
void merge(int* v, int ini, int cent, int fim);
void makeMerge(int *v, int n);

int *criarArray(int tam);
int *copiarArray(int *v, int tam);
double calcularTempo(void (*func) (int*, int), int *v,  int tam);

int main(){
    int tam[] = {25, 100, 1000, 5000, 10000, 12500, 15000, 17500, 20000};

    srand(time(NULL));

    FILE *f = fopen("data.csv", "w");
    FILE *fd = fopen("worst_best.csv", "w");

    fprintf(f, "TAM,BUBBLE_SORT,INSERTION_SORT,MERGE_SORT\n");

    for(int i = 0; i < TAM_MAX; i++){
        for(int j = 0; j < ITERACOES; j++){
            int *v = criarArray(tam[i]);

            int *v_b = copiarArray(v, tam[i]);
            int *v_i = copiarArray(v, tam[i]);
            int *v_m = copiarArray(v, tam[i]);

            fprintf(f, "%d,", tam[i]);

            double tempo;
            tempo = calcularTempo(bubbleSort, v_b, tam[i]);
            fprintf(f, "%lf,", tempo);

            tempo = calcularTempo(insertionSort, v_i, tam[i]);
            fprintf(f, "%lf,", tempo);

            tempo = calcularTempo(makeMerge, v_m, tam[i]-1);
            fprintf(f, "%lf\n", tempo);

            free(v);
            free(v_b);
            free(v_i);
            free(v_m);
        }
    }

    fprintf(fd, "TIPO,BUBBLE_SORT,INSERTION_SORT,MERGE_SORT\n");

    for(int j = 0; j < ITERACOES; j++){
        int *v = (int *)malloc(sizeof(int) * 1000);
        for(int i = 0; i < 1000; i++){
            v[i] = 1000 - i;
        }

        int *v_b = copiarArray(v, 1000);
        int *v_i = copiarArray(v, 1000);
        int *v_m = copiarArray(v, 1000);

        fprintf(fd, "pior,");

        double tempo;
        tempo = calcularTempo(bubbleSort, v_b, 1000);
        fprintf(fd, "%lf,", tempo);

        tempo = calcularTempo(insertionSort, v_i, 1000);
        fprintf(fd, "%lf,", tempo);

        tempo = calcularTempo(makeMerge, v_m, 1000-1);
        fprintf(fd, "%lf\n", tempo);

        free(v);
        free(v_b);
        free(v_i);
        free(v_m);
    }

    for(int j = 0; j < ITERACOES; j++){
        int *v = (int *)malloc(sizeof(int) * 1000);
        for(int i = 0; i < 1000; i++){
            v[i] = i;
        }

        int *v_b = copiarArray(v, 1000);
        int *v_i = copiarArray(v, 1000);
        int *v_m = copiarArray(v, 1000);

        fprintf(fd, "melhor,");

        double tempo;
        tempo = calcularTempo(bubbleSort, v_b, 1000);
        fprintf(fd, "%lf,", tempo);

        tempo = calcularTempo(insertionSort, v_i, 1000);
        fprintf(fd, "%lf,", tempo);

        tempo = calcularTempo(makeMerge, v_m, 1000-1);
        fprintf(fd, "%lf\n", tempo);

        free(v);
        free(v_b);
        free(v_i);
        free(v_m);
    }

    fclose(fd);
    
    return 0;
}

void bubbleSort(int *v, int n){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1; j++){
            if (v[j] > v[j + 1]){       //a + c
                int tmp = v[j];
                v[j] = v[j + 1];        //a
                v[j + 1] = tmp;         //a
            }
        }
    }
}

void insertionSort(int* v, int n){
	int i = 1;

	while(i < n){
		int tmp = v[i];
		int j = i-1;                    //a

		while (j >= 0 && tmp < v[j]){
			v[j+1] = v[j];              //a
			j--;                        //a
		}
		v[j+1] = tmp;                   //a
		i++;                            //a
	}
}

void mergeSort(int* v, int ini, int fim){
	if (fim <= ini) return;

	int cent = (int)((ini+fim)/2.0);        //2a
	mergeSort(v, ini, cent);
	mergeSort(v, cent+1, fim);              //a

	merge(v, ini, cent, fim);
}

void merge(int* v, int ini, int cent, int fim){
	int* vAux = (int*)malloc(sizeof(int) * ((fim-ini)+1));  //2a

	int i = ini;
	int j = cent+1;                                         //a
	int k = 0;

	while(i <= cent && j <= fim){
		if (v[i] <= v[j]){                                  //c
			vAux[k] = v[i];
			i++;                                            //a
		}
		else{
			vAux[k] = v[j];
			j++;                                            //a
		}
		k++;                                                //a
	}

	while(i <= cent){
		vAux[k] = v[i];
		i++;                                                //a
		k++;                                                //a
	}

	while(j <= fim){
		vAux[k] = v[j];
		j++;                                                //a
		k++;                                                //a
	}

	for(i = ini, k = 0; i <= fim; i++,k++)
		v[i] = vAux[k];
	free(vAux);
}

void makeMerge(int *v, int n){
    mergeSort(v, 0, n);
}

int* criarArray(int tam){
    int *v = (int *)malloc(sizeof(int) * tam);

    for(int i = 0; i < tam; i++){
        v[i] = rand() % tam;
    }

    return v;
}

int *copiarArray(int *v, int tam){
    int *copy = (int *)malloc(sizeof(int) * tam);
    for(int i = 0; i < tam; i++){
        copy[i] = v[i];
    }

    return copy;
}

double calcularTempo(void (*func) (int*, int), int *v,  int tam){
    clock_t c1, c2;

    c1 = clock();
    func(v, tam);
    c2 = clock();

    double tempo = (c2 - c1)/(float)CLOCKS_PER_SEC;
    return tempo;
}