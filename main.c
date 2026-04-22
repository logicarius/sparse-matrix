#include <stdio.h> 
#include <stdlib.h> // for dynamic memory allocation
#include <string.h> // for searching words
#include "sparse_utils.h" // for using other files provided

int *values; // stores all non-zero frequencies
int *col_index; // stores which word each value belongs to (how many entries u store ,not range of values inside it therefore not 32)
int row_ptr[MAX_LINES + 1]; // 11 slots

int total = 0; // non-zero entries so far (counter)

void buildCSR()
{
    // counting loops for mallocing later
    int  total_nonzero = 0;
    for(int r = 0; r < lineCount; r++)
    {
        for(int c = 0; c < wordCount; c++)
        {
            if(matrix[r][c] != 0)
                total_nonzero++ ;
        }
    }
    // loop ended now malloc
    values = malloc(total_nonzero * sizeof(int));
    col_index = malloc(total_nonzero * sizeof(int));

    // basic body
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
        printf("\nSentence %d: [%s]\n", i, lines[i]);
        for(int j = row_ptr[i]; j < row_ptr[i+1]; j++)
        {
            printf("(%s , %d) ", words[col_index[j]], values[j]);
        }
        printf("\n");
    }
}

void searchWord(char *word)
{
    // find col index of word in words[]
    int target = -1;
    for(int i = 0; i < wordCount; i++)
        if(strcmp(words[i], word) == 0)
            target = i;
    
    if(target == -1)
    {
        printf("Word not found\n");
        return;
    }

    // loop through sentences
    printf("\n'%s' found in:\n", word);
    for(int i = 0; i < lineCount; i++)
        for(int j = row_ptr[i]; j < row_ptr[i+1]; j++)
            if(col_index[j] == target)
                printf("  Sentence %d: [%s] (freq: %d)\n", i, lines[i], values[j]);
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
            // using a dot for zeros makes sparsity visually obvious
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
    printAll(); // display results
    buildCSR(); // converts to your representation
    printCSR(); // display new matrix 

    // taking the search input from user
    char query[50];
    printf("\nEnter word to search: ");
    scanf("%s", query);
    searchWord(query);

    return 0;
}