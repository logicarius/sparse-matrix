#include <stdio.h>
#include <stdlib.h>
#include "sparse_utils.h"

struct Entry {
    int col;
    int val;
};

struct Entry* dynamic_matrix[MAX_LINES];  // array of pointers
int rowSize[MAX_LINES] = {0};

void buildDynamic()
{
    int row, col;
    
    //count and malloc
    for(row = 0; row < lineCount; row++)
    {
        for(col = 0; col < wordCount; col++)
        {
            if(matrix[row][col] != 0)
                rowSize[row]++;
        }
        dynamic_matrix[row] = malloc(rowSize[row] * sizeof(struct Entry));
    }
    
    // Pass 2 - store entries
    // rowSize[row] is already full from Pass 1. If you use it again as a counter, it will be overwritten
    int pos[MAX_LINES] = {0};  // current position in each row

    for(row = 0; row < lineCount; row++)
    {
        for(col = 0; col < wordCount; col++)
        {
            if(matrix[row][col] != 0)
            {
                dynamic_matrix[row][pos[row]].col = col;
                dynamic_matrix[row][pos[row]].val = matrix[row][col];
                pos[row]++;
            }
        }
    }
}

void printDynamic() 
{
    for(int i = 0; i < lineCount; i++)
        {
            printf("\nSentence %d: ",i);
            for(int j = 0; j<rowSize[i]; j++)
            {
                printf("%s - %d  ", words[dynamic_matrix[i][j].col], dynamic_matrix[i][j].val);
            }
            printf("\n");
        }
}

void printAll() {
    printf("--- Original Text ---\n");
    for(int i = 0; i < lineCount; i++)
        printf("[%d] %s\n", i, lines[i]);

    printf("\n--- Vocabulary Index ---\n");
    for(int i = 0; i < wordCount; i++)
        printf("%d: %s\t", i, words[i]);

    printf("\n\n--- Sparse Matrix (Frequencies) ---\n");
    for(int i = 0; i < lineCount; i++) {
        for(int j = 0; j < wordCount; j++) {
            // Using a dot for zeros makes sparsity visually obvious
            if (matrix[i][j] == 0) printf(". ");
            else printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() 
{
    buildMatrix();
    printAll(); 
    buildDynamic(); 
    printDynamic(); 

    return 0;
}