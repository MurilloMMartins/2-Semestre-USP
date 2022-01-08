#ifndef MY_SORT
#define MY_SORT

typedef struct reg {
    int key;
    int value;
} Regist;

void bubble_sort(int *v, int n);
void insertion_sort(int *vector, int tamanho);

void heap_sort(int *v, int end);
void merge_sort(int *v, int size);

void merge_sort_inv(int *v, int size);
void counting_sort(int *v, int size);

void print_reg(Regist *v, int size);
void counting_sort_regs(Regist *v, int size);
Regist *make_random_reg(int min, int max, int size);

void quick_sort(int *v, int size);
void bucket_sort(int *v, int size);
void radix_sort256(int *v, int size);

#endif