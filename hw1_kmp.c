#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_SIZE 10000000
#define MAX_PAT_SIZE 3000
char pat[MAX_PAT_SIZE], str[MAX_STR_SIZE];
int failure[MAX_STR_SIZE] = { -1 };
int loc[MAX_STR_SIZE];

void fail(char* pat);
int match(char* string, char* pat);

int main() {

    int cnt;

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

    fgets(str, MAX_STR_SIZE - 1, fileS);
    fgets(pat, MAX_PAT_SIZE - 1, fileP);

    cnt = match(str, pat);

    if (cnt == 0) {
        printf("The string file does not exist.");
    }
    else {
        FILE* pFile = fopen("result_kmp.txt", "w");

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

void fail(char* pat) {
    int i, j, n = strlen(pat);
    failure[0] = -1;
    for (j = 1; j < n; j++) {
        i = failure[j - 1];
        while ((pat[j] != pat[i + 1]) && (i >= 0)) i = failure[i];
        if (pat[j] == pat[i + 1]) failure[j] = i + 1;
        else failure[j] = -1;
    }
}

int match(char* string, char* patt) {
 int i=0, j=0, count=0;
int lens = strlen(string);
int lenp = strlen(patt); // 배열 초기화 생략

while(i < lens) {
    if(string[i] == patt[j]) {
        i++; j++;
        if(j == lenp) { // 패턴 찾음
            loc[count++] = i-lenp;
            j = failure[j-1] + 1;
        }
    }
    else if(j == 0) i++;
    else j = failure[j-1] + 1;
}

return count;
}
