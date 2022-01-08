/* Nome: Fellip Silva Alves
 * Numero USP: 12543551
 * SCC-0201
 * 
 * Espaço para a descrição do programa
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "my_sort.h"

#define MAX_VALUE 100000
typedef void (*sort_f) (int *, int);

int *make_random_vector(int size, int max, int min) {
    int *v = malloc(size * sizeof(int));

    for (int i = 0; i < size; ++i)
        v[i] = (rand() % (max - min)) + min;

    return v;
}

int *make_copy_vector(int *v, int size) {
    int *vCopy = malloc(size * sizeof(int));

    for (int i = 0; i < size; ++i)
        vCopy[i] = v[i];

    return vCopy;
}

void print_v(int *v, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void make_sort(sort_f sort, int *v, int size, FILE *f) {
    clock_t c1, c2;

    c1 = clock();
    sort(v, size - 1);
    c2 = clock();

    double time = (c2-c1) / (double) CLOCKS_PER_SEC;

    fprintf(f, ",%lf", time);

    free(v);
}

int main() {
    int vecSizes[12] = {100, 500, 1000, 2500, 5000, 7500, 10000, 15000, 25000, 50000, 75000, 100000};

    FILE *fp = fopen("data.csv", "w");
    fprintf(fp, "size,counting,bucket,radix256,heap,quick\n");

    for (int i = 0; i < 12; i++) {
        int size = vecSizes[i];
        int *v = make_random_vector(size, 0, MAX_VALUE);

        for (int j = 0; j < 10; j++) {
            fprintf(fp, "%d", size);

            make_sort(counting_sort, make_copy_vector(v, size), size, fp);
            make_sort(bucket_sort, make_copy_vector(v, size), size, fp);
            make_sort(radix_sort256, make_copy_vector(v, size), size, fp);
            make_sort(heap_sort, make_copy_vector(v, size), size, fp);
            make_sort(quick_sort, make_copy_vector(v, size), size, fp);

            fprintf(fp, "\n");
        }

        free(v);
    }

    fclose(fp);

    FILE *fp1 = fopen("bw.csv", "w");
    fprintf(fp1, "case,counting,bucket,radix\n");
    int size = 1000;
    int *v_counting = make_random_vector(size, 0, 100);
    int *v_bucket = make_random_vector(size, 0, 100);
    int *v_radix = make_random_vector(size, 0, 100);

    for (int i = 0; i < 10; ++i) {
        fprintf(fp1, "b");

        make_sort(counting_sort, make_copy_vector(v_counting, size), size, fp1);
        make_sort(bucket_sort, make_copy_vector(v_bucket, size), size, fp1);
        make_sort(radix_sort256, make_copy_vector(v_radix, size), size, fp1);

        fprintf(fp1, "\n");
    }

    free(v_counting);
    free(v_bucket);
    free(v_radix);
    v_counting = make_random_vector(size, 0, 10000000);
    v_bucket = make_random_vector(size, 0, 10000000);
    v_radix = make_random_vector(size, 10000000, 20000000);

    for (int i = 0; i < 10; ++i) {
        fprintf(fp1, "w");

        make_sort(counting_sort, make_copy_vector(v_counting, size), size, fp1);
        make_sort(bucket_sort, make_copy_vector(v_bucket, size), size, fp1);
        make_sort(radix_sort256, make_copy_vector(v_radix, size), size, fp1);

        fprintf(fp1, "\n");
    }

    free(v_counting);
    free(v_bucket);
    free(v_radix);

    fclose(fp1);

    return 0;
}