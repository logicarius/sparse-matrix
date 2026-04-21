#include <string.h>
#include "sparse_utils.h"

// Define the variables here
char lines[MAX_LINES][200] = {
    "data structures are fun and data is powerful",
    "algorithms and data structures are important",
    "learning data structures takes time and practice",
    "practice makes concepts in data structures strong",
    "algorithms solve problems and data helps",
    "understanding structures and algorithms is useful",
    "data data data makes patterns visible",
    "practice and patience improve problem solving",
    "structures help organize data efficiently",
    "algorithms and structures go hand in hand"
};

char words[MAX_WORDS][20];
int matrix[MAX_LINES][MAX_WORDS] = {0}; // Initialize to zero
int lineCount = 10;
int wordCount = 0;

int findWord(char *w) {
    for(int i = 0; i < wordCount; i++) {
        if(strcmp(words[i], w) == 0) return i;
    }
    return -1;
}

int addWord(char *w) {
    int idx = findWord(w);
    if(idx != -1) return idx;

    strcpy(words[wordCount], w);
    wordCount++;
    return wordCount - 1;
}

void buildMatrix() {
    char temp[200];
    char *token;

    for(int i = 0; i < lineCount; i++) {
        strcpy(temp, lines[i]);
        token = strtok(temp, " ");
        while(token != NULL) {
            int col = addWord(token);
            matrix[i][col]++;
            token = strtok(NULL, " ");
        }
    }
}