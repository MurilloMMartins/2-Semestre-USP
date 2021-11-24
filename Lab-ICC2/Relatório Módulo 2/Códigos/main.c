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

void quicksort(int* v, int ini, int fim);
void makeQuick(int *v, int n);
void maxHeapify(int* v, int p, int N);
void buildMaxheap(int* v, int N);
void heapsort(int* v, int N);

int main(){
    srand(time(NULL));
    int tam[] = {25, 100, 1000, 5000, 10000, 12500, 15000, 17500, 20000};


    FILE *f = fopen("data1.csv", "w");
    FILE *fd = fopen("worst_best1.csv", "w");

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

    fclose(f);
    fclose(fd);

    int tam2[] = {25, 100, 1000, 5000, 10000, 25000, 50000, 75000, 100000};

    f = fopen("data2.csv", "w");
    fd = fopen("worst_best2.csv", "w");

    fprintf(f, "TAM,QUICK_SORT,HEAP_SORT\n");
    for(int i = 0; i < TAM_MAX; i++){
        for(int j = 0; j < ITERACOES; j++){
            int *v = criarArray(tam2[i]);

            int *v_q = copiarArray(v, tam2[i]);
            int *v_h = copiarArray(v, tam2[i]);

            fprintf(f, "%d,", tam2[i]);

            double tempo;
            tempo = calcularTempo(makeQuick, v_q, tam2[i]-1);
            fprintf(f, "%lf,", tempo);

            tempo = calcularTempo(heapsort, v_h, tam2[i]-1);
            fprintf(f, "%lf\n", tempo);

            free(v);
            free(v_q);
            free(v_h);
        }
    }

    fprintf(fd, "TIPO,QUICKSORT,HEAPSORT\n");

    for(int j = 0; j < ITERACOES; j++){
        int *v = (int *)malloc(sizeof(int) * 1000);
        for(int i = 0; i < 1000; i++){
            v[i] = 1000 - i;
        }

        int *v_q = copiarArray(v, 1000);
        int *v_h = copiarArray(v, 1000);

        fprintf(fd, "pior,");

        double tempo;
        tempo = calcularTempo(makeQuick, v_q, 1000-1);
        fprintf(fd, "%lf,", tempo);

        tempo = calcularTempo(heapsort, v_h, 1000-1);
        fprintf(fd, "%lf\n", tempo);

        free(v);
        free(v_q);
        free(v_h);
    }

    for(int j = 0; j < ITERACOES; j++){
        int *v_h = (int *)malloc(sizeof(int) * 1000);
        for(int i = 0; i < 1000; i++){
            v_h[i] = i;
        }

        int *v_q = criarArray(1000);

        fprintf(fd, "melhor,");

        double tempo;
        tempo = calcularTempo(makeQuick, v_q, 1000-1);
        fprintf(fd, "%lf,", tempo);

        tempo = calcularTempo(heapsort, v_h, 1000-1);
        fprintf(fd, "%lf\n", tempo);

        free(v_q);
        free(v_h);
    }

    fclose(f);
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

void quicksort(int* v, int ini, int fim) {

	if (ini >= fim) return;                     //c
	
    int tmp;
    int p = ini;
	int i = ini+1;                              //a
	int j = fim;

	while (i <= j) {
		while (i <= fim && v[i] <= v[p]) i++;   //a
		while (v[j] > v[p]) j--;                //a

		if (j > i) {                            //c
			tmp = v[i];
			v[i] = v[j];
			v[j] = tmp;
		}
	}
	tmp = v[p];
	v[p] = v[j];
	v[j] = tmp;
	p = j;

	quicksort(v, ini, p-1);                     //a
	quicksort(v, p+1, fim);                     //a
}

void makeQuick(int *v, int n){
    quicksort(v, 0, n-1);
}

void maxHeapify(int* v, int p, int N) {

	int f = p*2 + 1;                                        //2a

	if (f > N) return;                                      //c

	if (v[f] > v[p] || (f+1 <= N && v[f+1] > v[p]) ) {      //3c + 2a 
	
		if (f+1 <= N && v[f+1] > v[f])                      //2c + 2a
			f = f+1;                                        //a

		int tmp = v[p];
		v[p] = v[f];
		v[f] = tmp;

		maxHeapify(v, f, N);
	}

}

void buildMaxheap(int* v, int N) {
	int m = (int) N/2.0;               //a

	for (int p = m; p >= 0; p--) {
		maxHeapify(v, p, N);
	}
}

void heapsort(int* v, int N) {

	buildMaxheap(v, N);        //f_max()

	while (N >= 1) {
		int maior = v[0];
		v[0] = v[N];
		v[N] = maior;

		N--;                    //a

		maxHeapify(v, 0, N);   //f_h()
	}
}