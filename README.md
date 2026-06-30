# Sparse Matrix Hackathon

## What is this?
This project stores a text-based sparse matrix efficiently by avoiding storing zero values.

## The Problem
The original matrix is 10x100 = 1000 slots, 4000 bytes.
Most entries are zero since each sentence only uses 6-7 words out of 33. 
Storing zeros wastes memory.

## The shared base (sparse_utils)
All three versions read from the same place. `sparse_utils.c` holds the 10 sentences and `buildMatrix()` turns them into the original word frequency matrix, while `sparse_utils.h` declares the shared variables. I kept this in one file so that main2.c, main3.c and main.c only differ in how they store the sparse matrix, not in how it gets built.

## My Journey

### main2.c — First Attempt (Array-based struct)
Used a struct Entry with col and val fields stored in a 2D array. 
Still allocates MAX_LINES x MAX_WORDS slots even if unused. 
Same memory problem as original.

### main3.c — Dynamic Malloc per Row
Fixed the waste by using malloc per row which allocates exactly rowSize[i] slots per sentence. 
Better, but uses a struct which adds overhead.

### main.c — Final Version (CSR + Dynamic Malloc + Search)
Used CSR namely 3 flat int arrays instead of a struct.
Counted non-zeros first, then malloced exactly that much.
Added word search which a user can find which sentences contain any word.

I chose CSR over my first array-based attempt (main2.c) because main2.c still allocated MAX_LINES × MAX_WORDS slots which is the same size as the original matrix. 
CSR with dynamic malloc allocates only total_nonzero slots, which in this dataset is ~60 instead of 1000. 
CSR also separates row boundaries using row_ptr[] which makes row access cleaner and faster

I chose CSR over a linked list because linked list access is O(n) since you have to traverse the whole list to find an entry. 
On the other hand CSR gives direct row access via row_ptr[] in O(1).

## Memory Comparison
Original: 10 x 100 x 4 = 4000 bytes
My CSR: ~60 entries x 4 x 2 arrays + 44 = ~524 bytes
Reduction: ~87%

## What I Learned
1. I learned how CSR works using 3 arrays instead of a struct
2. how malloc requires knowing size before allocating
3. why two passes are needed
4. how to search across a sparse structure without scanning the full matrix
5. how to ask the user for an input
