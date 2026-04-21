#ifndef SPARSE_UTILS_H
#define SPARSE_UTILS_H

#define MAX_LINES 10
#define MAX_WORDS 100

// Shared variables (declared as extern)
extern char lines[MAX_LINES][200];
extern char words[MAX_WORDS][20];
extern int matrix[MAX_LINES][MAX_WORDS];
extern int wordCount;
extern int lineCount;

// Function declarations
int findWord(char *w);
int addWord(char *w);
void buildMatrix();

#endif