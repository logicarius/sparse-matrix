#include <stdio.h>
#include "sparse_utils.h"

int values[MAX_LINES * 10]; // all frequencies - 10 sentences x 10 words
int col_index[MAX_LINES * 10]; // which word (how many entries u store ,not range of values inside it therefore not 32)
int row_ptr[MAX_LINES + 1]; // 11 slots

int total = 0; // non-zero entries so far (counter)

void buildCSR()
{
    int row,col;
    for(row = 0; row < lineCount; row++) // loops over every sentence
    {
        row_ptr[row] = total; // before processing sentence row, puts checkpoint
        for(col = 0; col < wordCount; col++) // loops every word in vocabulary for this sentence
        {
            if(matrix[row][col] != 0) // only cares about words that actually appear 
            {
                values[total] = matrix[row][col];
                col_index[total] = col;
                total++;
                // store the frequency, store which word, move to next slot
            }
        }
    }
    row_ptr[lineCount] = total; // mark the end when the last sentence is done
}

void printCSR()
{
    for(int i = 0; i < lineCount; i++)
    {
        printf("Sentence %d: ", i);
        for(int j = row_ptr[i]; j < row_ptr[i+1]; j++)
        {
            printf("(%s , %d) ", words[col_index[j]], values[j]);
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
    // Logic is hidden away in sparse_utils
    
    buildMatrix(); // builds original matrix
    printAll(); // Display results
    buildCSR(); // converts to your representation
    printCSR(); //Display new matrix

    return 0;
}