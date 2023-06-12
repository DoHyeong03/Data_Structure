#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_VERTICES 10000
#define MAX_EDGES 50000000
#define HEAP_FULL(n) (n == MAX_EDGES - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
    int key;
    int left;
    int right;
} element;

element min_heap[MAX_EDGES];
element edge[MAX_EDGES];

int parent[MAX_EDGES];
int ele[MAX_EDGES];
int ele_C[MAX_EDGES];

int min_n = 0;
int vertex;
int edge_n;

void insert_min_heap(element item, int a, int b, int* n);
element delete_min_heap(int* n);

void init(void);
void Union(int, int);
int find(int);

int main(int argc, char* argv[]) {

    clock_t start = clock();

    element item;
    char line[50];
    int i = 0;
    int total = 0;
    int chk = 0;

    if (argc != 2) {
        printf("usage: ./hw3 input_filename\n");
        exit(1);
    }

    const char* filename = argv[1];

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "The input file does not exist.\n");
        exit(1);
    }

    FILE* pFile = fopen("hw3_result.txt", "w");

    fgets(line, sizeof(line), file);
    sscanf(line, "%d", &vertex);

    fgets(line, sizeof(line), file);
    sscanf(line, "%d", &edge_n);

    while (fgets(line, sizeof(line), file)) {
        int a = 0, b = 0, c = 0;
        sscanf(line, "%d %d %d", &a, &b, &c);
        item.key = c;
        insert_min_heap(item, a, b, &min_n);
    }

    while (min_n > 0) {
        item = delete_min_heap(&min_n);
        edge[i].key = item.key;
        edge[i].left = item.left;
        edge[i].right = item.right;
        i++;
    }

    init();

    Union(edge[0].left, edge[0].right);
    fprintf(pFile, "%d %d %d\n", edge[0].left, edge[0].right, edge[0].key);
    total = total + edge[0].key;

    for (int i = 1; i < edge_n; i++) {
        int u = edge[i].left, v = edge[i].right;
        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v) {
            Union(root_u, root_v);
            fprintf(pFile, "%d %d %d\n", edge[i].left, edge[i].right, edge[i].key);
            total = total + edge[i].key;
            ele_C[i]++;
        }
        if (u == v) {
            chk++;
        }
    }

    fprintf(pFile, "%d\n", total);
    if (chk == 0) {
        fprintf(pFile, "CONNECTED");
    }
    else {
        fprintf(pFile, "DISCONNECTED");
    }

    fprintf(pFile, "\n");

    fclose(file);
    fclose(pFile);

    clock_t end = clock();

    printf("output written to hw3_result.txt.\n");
    printf("running time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}

void insert_min_heap(element item, int a, int b, int* n) {
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
    min_heap[i].key = item.key;
    min_heap[i].left = a;
    min_heap[i].right = b;
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
        if ((child < *n) && (min_heap[child].key > min_heap[child + 1].key))
            child++;
        if (temp.key <= min_heap[child].key)
            break;
        min_heap[parent] = min_heap[child];
        parent = child;
        child *= 2;
    }
    min_heap[parent] = temp;
    return item;
}

void init(void) {
    for (int i = 0; i < MAX_EDGES; i++) {
        parent[i] = -1;
        ele[i] = 0;
    }
}

void Union(int s1, int s2) {
    int root1 = find(s1);
    int root2 = find(s2);

    if (root1 == root2)
        return;

    if (ele[root1] > ele[root2]) {
        parent[root2] = root1;
        ele[root1] += ele[root2];
    } else {
        parent[root1] = root2;
        ele[root2] += ele[root1];
    }
}

int find(int x) {
    if (parent[x] == -1)
        return x;

    return parent[x] = find(parent[x]);
}

