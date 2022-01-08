#include <stdlib.h>
#include <stdio.h>
#include "my_sort.h"

static void swap(int *a, int *b){ 
    int temp = *a; 
    *a = *b; 
    *b = temp;
}

static void max_heapify(int *v, int begin, int end) {
    int child = begin * 2 + 1;

    if (child >= end)
        return;

    if (v[child] > v[begin] || (child + 1 < end && v[child + 1] > v[begin])) {
        if (child + 1 < end && v[child + 1] > v[child])
            child += 1;

        swap(&v[child], &v[begin]);

        max_heapify(v, child, end);
    }
}

void heap_sort(int *v, int end) {
    end++;
    for (int i = (end / 2); i >= 0; --i)
        max_heapify(v, i, end);

    for (int i = end - 1; i > 0; i--) {
        swap(&v[0], &v[i]);
        max_heapify(v, 0, i);
    }
}

static void merge(int *arr, int start, int middle, int end){
    int size = end - start + 1;
    int *arr_copy = malloc(sizeof(int) * size);

    int p1 = start, p2 = middle + 1;
    for (int i = 0; i < size; ++i) {
        if (p1 <= middle && p2 <= end)
            arr_copy[i] = (arr[p1] > arr[p2]) ? arr[p2++] : arr[p1++];
        else
            arr_copy[i] = (p1 > middle) ? arr[p2++] : arr[p1++];
    }

    int j = start;
    for (int i = 0; i < size; i++)
        arr[j++] = arr_copy[i];

    free(arr_copy);
}

static void make_merge_sort(int *array, int start, int end) {
    if (start >= end) return;

    int middle = (end + start) / 2;

    make_merge_sort(array, start, middle);
    make_merge_sort(array, middle + 1, end);

    merge(array, start, middle, end);
}

void merge_sort(int *v, int size) {
    make_merge_sort(v, 0, size - 1);
}

void insertion_sort(int *vector, int tamanho) {
	for (int j = 1; j < tamanho; j++) {
		int chave = vector[j];
		int i = j - 1;

		while (i >= 0 && vector[i] > chave) {
			vector[i+1] = vector[i];
			i = i - 1;
		}

		vector[i + 1] = chave;
	}
}

void bubble_sort(int *v, int size){ 
    if (size < 1) return; 
 
    for (int i = 0; i < size; i++) 
        if (v[i] > v[i + 1]) 
            swap(&v[i], &v[ i+ 1]);

    bubble_sort(v, size-1); 
}

void countingSort(int *v, int size) {
    int max, min;
    max = min = v[0];
    for (int i = 1; i <= size; i++) {
        if (v[i] > max) max = v[i];
        if (v[i] < min) min = v[i];
    }

    int tamC = max - min + 1;
    int *count = calloc(tamC, sizeof(int));

    for (int i = 0; i <= size; i++)
        count[v[i] - min]++;

    int i = 0;
    for (int j = 0; j < tamC; j++){
        while(count[j] > 0){
            v[i] = j + min;
            i++;
            count[j]--;
        }
    }

    free(count);
}

Regist *make_random_reg(int min, int max, int size) {
    Regist *v = malloc(size * sizeof(Regist));

    for (int i = 0; i < size; i++) {
        v[i].key = (random() % (max - min)) + min;
        v[i].value = (random() % (max + min));
    }

    return v;
}

void print_reg(Regist *v, int size) {
    for (int i = 0; i < size; i++)
        printf("(%d %d) ", v[i].key, v[i].value);

    printf("\n");
}

void counting_sort_regs(Regist *v, int size) {
    Regist *v_copy = malloc(size * sizeof(Regist));

    int max, min;
    max = min = v[0].key;
    for (int i = 0; i < size; i++) {
        if (v[i].key > max) max = v[i].key;
        if (v[i].key < min) min = v[i].key;
        v_copy[i] = v[i];
    }

    int tamC = max - min + 1;
    int *count = calloc(tamC, sizeof(int));

    for (int i = 0; i < size; i++)
        count[v[i].key - min]++;

    int ant = count[0];
    count[0] = 0;
    for (int i = 1; i < tamC; i++) {
        int tmp = count[i];
        count[i] = ant;
        ant += tmp;
    }

    for (int j = 0; j < size; j++){
        int pos = v_copy[j].key - min;
        v[count[pos]] = v_copy[j];
        count[pos]++;
    }

    free(v_copy);
    free(count);
}

static void insertion_quick(int *vector, int begin, int end) {
	for (int j = begin; j <= end; j++) {
		int key = vector[j];
		int i = j - 1;

		while (i >= begin && vector[i] > key) {
			vector[i + 1] = vector[i];
			i = i - 1;
		}

		vector[i + 1] = key;
	}
}

static int partition(int *v, int begin, int end, int *lower) {
    int higher = end - 1;
    *lower = begin;
    int mid = begin;

    while (mid <= higher) {
        if (v[end] > v[mid]) 
            swap(&v[mid++], &v[(*lower)++]);
        else if (v[end] < v[mid]) 
            swap(&v[mid], &v[higher--]);
        else mid++;
    }

    swap(&v[end], &v[mid]);
    return mid;
}

static void make_quick_sort(int *v, int begin, int end, int (*pcs) ()) {
    if ((end - begin + 1) <= 10) {
        insertion_quick(v, begin, end);
        return;
    }

    int pivot = pcs != NULL ? pcs(v, begin, end) : 0;
    swap(&v[end], &v[pivot]);
    int lower;
    pivot = partition(v, begin, end, &lower);

    make_quick_sort(v, begin, lower - 1, pcs);
    make_quick_sort(v, pivot + 1, end, pcs);
}

void quick_sort(int *v, int size) {
    make_quick_sort(v, 0, size - 1, NULL);
}

typedef struct node {
    int elem;
    struct node *next;
} node_t;

typedef struct bucket {
    node_t *begin;
    node_t *end;
} bucket_t;


void bucket_sort(int *v, int size) {
    int max, min;
    max = min = v[0];
    for (int i = 1; i <= size; i++) {
        if (v[i] > max) max = v[i];
        if (v[i] < min) min = v[i];
    }

    int tamC = max - min + 1;
    bucket_t *b = calloc(tamC, sizeof(bucket_t));

    for (int i = 0; i <= size; i++) {
        int key = v[i] - min;

        node_t *newNode = malloc(sizeof(node_t));
        newNode->elem = v[i];
        newNode->next = NULL;

        if (b[key].begin == NULL)
            b[key].begin = newNode;
        else 
            b[key].end->next = newNode;

        b[key].end = newNode;
    }

    int i = 0;
    for (int j = 0; j < tamC; j++) {
        node_t *pos;
		pos = b[j].begin;
		while (pos != NULL) {
			v[i++] = pos->elem;

			node_t *del = pos;
			pos = pos->next;
			b[j].begin = pos;
			free(del);
		}
    }

    free(b);
}

void radix_sort256(int *v, int size) {
    int c[256] = {0};
    int pos[256];
    int *vcop = malloc(size * sizeof(int));

    for (int shift = 0; shift <= 24; shift += 8) {
        for (int j = 0; j < size; j++) {
            short k = (v[j] >> shift) & 255;
            c[k]++;
            vcop[j] = v[j];
        }

        pos[0] = 0;
        for (int i = 1; i < 256; i++) {
            pos[i] = pos[i - 1] + c[i - 1];
            c[i - 1] = 0;
        }

        for (int j = 0; j < size; j++) {
            short k = (vcop[j] >> shift) & 255;
            v[pos[k]] = vcop[j];
            pos[k]++;
        }
    }

    free(vcop);
}