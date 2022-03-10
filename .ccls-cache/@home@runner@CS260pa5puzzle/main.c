#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------------------------------
// define functions
// Node for puzzles
typedef struct node
{
  int move;
  int *puzzle;
  struct node *parent;
} Node;



// priority queue for creating next puzzle linked list would be better for easier enqueue and dequeue
typedef struct priorityQueue
{
  int capacity;
	int size;    
  struct node *PQptr;
} PQ;


// open hash table for storing puzzles
typedef struct openHashTable
{
  
} HT;

//-------------------------------------------------------------------------
// initialize functions
// Node for puzzles
Node  *initializeNode(){
  
}

// priority queue for creating next puzzle
PQ *initializepriorityQueue() {
	
}

// priority queue for creating next puzzle linked list would be better for easier enqueue and dequeue
PQ *initializeopenHashTable() {
	
}

//-------------------------------------------------------------------------
// helper functions
// get adj tiles


// hash function
int hashWord()
{
  unsigned int total=0;
  
  return (total % size);
}



//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


int main(int argc, char **argv)
{
	FILE *fp_in,*fp_out;
	
	fp_in = fopen(argv[1], "r");
	if (fp_in == NULL){
		printf("Could not open a file.\n");
		return -1;
	}
	
	fp_out = fopen(argv[2], "w");
	if (fp_out == NULL){
		printf("Could not open a file.\n");
		return -1;
	}
	
	char *line = NULL;
	size_t lineBuffSize = 0;
	ssize_t lineSize;
	int k;
	
	getline(&line,&lineBuffSize,fp_in);//ignore the first line in file, which is a comment
	fscanf(fp_in,"%d\n",&k);//read size of the board
	//printf("k = %d\n", k); //make sure you read k properly for DEBUG purposes
	getline(&line,&lineBuffSize,fp_in);//ignore the second line in file, which is a comment

	int initial_board[k*k];//get kxk memory to hold the initial board
	for(int i=0;i<k*k;i++)
		fscanf(fp_in,"%d ",&initial_board[i]);
	//printBoard(initial_board, k);//Assuming that I have a function to print the board, print it here to make sure I read the input board properly for DEBUG purposes
	fclose(fp_in);

	////////////////////
	// do the rest to solve the puzzle
	////////////////////

  //-------------------------------------------------------------------------

  // BFS rotation, while loop

  //------------------------------------------------------------------------- //-------------------------------------------------------------------------

	//once you are done, you can use the code similar to the one below to print the output into file
	//if the puzzle is NOT solvable use something as follows
	fprintf(fp_out, "#moves\n");
	fprintf(fp_out, "no solution\n");
	
	//if it is solvable, then use something as follows:
	fprintf(fp_out, "#moves\n");
	//probably within a loop, or however you stored proper moves, print them one by one by leaving a space between moves, as below
	for(int i=0;i<numberOfMoves;i++)
		fprintf(fp_out, "%d ", move[i]);

	fclose(fp_out);

	return 0;

}
