#include <stdio.h>
#include "sparse_utils.h"

struct Entry
{
    int col;
    int val;
};

int rowSize[MAX_LINES] = {0}; //global

struct Entry new_matrix[MAX_LINES][MAX_WORDS]; //global

void buildSparse() 
{
    int row;
    int column; 
    
    for(row=0; row<lineCount; row++) //sentence - row
    {
        for(column=0; column<wordCount; column++) //word - column
        {
            if(matrix[row][column] != 0)
            {
                new_matrix[row][rowSize[row]].col = column; // storing
                new_matrix[row][rowSize[row]].val = matrix[row][column]; //storing
                
                rowSize[row]++; // increment
            }
        }
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

void printSparse() 
{
    for(int i = 0; i<MAX_LINES; i++)
        {
            printf("\nSentence %d: ",i);
            for(int j = 0; j<rowSize[i]; j++)
            {
                printf("col: %d val: %d  ", new_matrix[i][j].col, new_matrix[i][j].val);
            }
            printf("\n");
        }
}

int main() {
    
    // Logic is hidden away in sparse_utils
    
    buildMatrix(); // builds original matrix
    buildSparse(); // converts to your representation
    printAll(); // Display results
    printSparse(); //Display new matrix

    return 0;
}