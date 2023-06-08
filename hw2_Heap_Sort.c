#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ELEMENTS 1000000
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
    int key;
} element;
element max_heap[MAX_ELEMENTS];
element min_heap[MAX_ELEMENTS];

int max_n = 0;
int min_n = 0;

void insert_max_heap(element item, int* n);
element delete_max_heap(int* n);
void insert_min_heap(element item, int* n);
element delete_min_heap(int* n);
element* copy_heap(element* src, int size);

int main(int argc, char *argv[]) {

    clock_t start = clock();

    element item;
    char line[50];

    if (argc != 2) {
        printf("usage: ./hw2 input_filename\n");
        exit(1);
    }

    const char* filename = argv[1];

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "The input file does not exist.\n");
        exit(1);
    }

    FILE* pFile = fopen("hw2_result.txt", "w");

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "INSERT") != NULL) {
            sscanf(line, "INSERT %d", &item.key);
            insert_max_heap(item, &max_n);
            insert_min_heap(item, &min_n);
        }
        if (strstr(line, "DESCEND") != NULL){
            element* max_heap_copy = copy_heap(max_heap, max_n);
            int copy_n = max_n;
            while (copy_n > 0) {
                item = delete_max_heap(&copy_n);
                fprintf(pFile, "%d ", item.key);
            }
            fprintf(pFile, "\n");
            free(max_heap_copy);
        }
        if (strstr(line, "ASCEND") != NULL) {
            element* min_heap_copy = copy_heap(min_heap, min_n);
            int copy_n = min_n;
            while (copy_n > 0) {
                item = delete_min_heap(&copy_n);
                fprintf(pFile, "%d ", item.key);
            }
            fprintf(pFile, "\n");
            free(min_heap_copy);
        }
    }

    fclose(file);
    fclose(pFile);

    clock_t end = clock();

    printf("output written to hw2_result.txt.\n");
    printf("running time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}

void insert_max_heap(element item, int* n) {
    int i;
    if (HEAP_FULL(*n)) {
        fprintf(stderr, "The heap is full.\n");
        exit(1);
    }
    i = ++(*n);
    while ((i != 1) && (item.key > max_heap[i / 2].key)) {
        max_heap[i] = max_heap[i / 2];
        i /= 2;
    }
    max_heap[i] = item;
}

element delete_max_heap(int* n) {
    int parent, child;
    element item, temp;
    if (HEAP_EMPTY(*n)) {
        fprintf(stderr, "The heap is empty");
        exit(1);
    }
    item = max_heap[1];
    temp = max_heap[(*n)--];
    parent = 1;
    child = 2;
    while (child <= *n) {
        if ((child < *n) && (max_heap[child].key < max_heap[child + 1].key)) child++;
        if (temp.key >= max_heap[child].key) break;
        max_heap[parent] = max_heap[child];
        parent = child;
        child *= 2;
    }
    max_heap[parent] = temp;
    return item;
}

void insert_min_heap(element item, int* n) {
    int i;
    if (HEAP_FULL(*n)) {
        fprintf(stderr, "The heap is full.\n");
        exit(1);
    }
    i = ++(*n);
    while ((i != 1) && (item.key < min_heap[i / 2].key)) {
        min_heap[i] = min_heap[i / 2];
        i /= 2;
    }
    min_heap[i] = item;
}

element delete_min_heap(int* n) {
    int parent, child;
    element item, temp;
    if (HEAP_EMPTY(*n)) {
        fprintf(stderr, "The heap is empty");
        exit(1);
    }
    item = min_heap[1];
    temp = min_heap[(*n)--];
    parent = 1;
    child = 2;
    while (child <= *n) {
        if ((child < *n) && (min_heap[child].key > min_heap[child + 1].key)) child++;
        if (temp.key <= min_heap[child].key) break;
        min_heap[parent] = min_heap[child];
        parent = child;
        child *= 2;
    }
    min_heap[parent] = temp;
    return item;
}

element* copy_heap(element* src, int size) {
    element* dest = malloc(sizeof(element) * (size + 1));
    for (int i = 1; i <= size; i++) {
        dest[i] = src[i];
    }
    return dest;
}
