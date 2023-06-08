#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_SIZE 10000000
#define MAX_PAT_SIZE 3000
char pat[MAX_PAT_SIZE], str[MAX_STR_SIZE];

int find(char*, char*, int*);

int main() {

    int cnt;
    int loc[MAX_PAT_SIZE];

    FILE* fileS = fopen("string.txt", "r");
    FILE* fileP = fopen("pattern.txt", "r");

    if (fileS == NULL) {
        printf("File Open Error!\n");
        return 1;
    }
    if (fileP == NULL) {
        printf("File Open Error!\n");
        return 1;
    }

    fgets(str, MAX_STR_SIZE-1, fileS);
    fgets(pat, MAX_PAT_SIZE-1, fileP);

    cnt = find(str, pat, loc);

    if (cnt == 0) {
        printf("The string file does not exist.");
    }
    else {
        FILE* pFile = fopen("result_naive.txt", "w");

        fprintf(pFile, "%d\n", cnt);
        for (int i = 0; i < cnt; i++) {
            fprintf(pFile, "%d ", loc[i]);
        }
        fclose(pFile);

    }

    fclose(fileS);
    fclose(fileP);

    return 0;
}

int find(char* str, char* pat, int* Loc) {
    int i, j = 0, start = 0, count = 0;
    int lstr = strlen(str) - 1;
    int lpat = strlen(pat) - 1;
    int end = lpat;
    for (i = 0; end <= lstr; end++, start++) {
        if (str[end] == pat[lpat])
            for (j = 0, i = start; j < lpat && str[i] == pat[j]; i++, j++)
                ;
        if (j == lpat) {
            Loc[count] = start;
            count++;
            j = 0;
        }
    }
    return count;
}
