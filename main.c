#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DENOM 7
//-------------------------------------------------------------------------
// define functions
// Node for puzzles
typedef struct node
{
  int move;               // int moved to get to this puzzle
  int *puzzle;            // puzzle
  struct node *parent;    // tracks for BFS
  struct node *nextHT;    // tracks for HT
  struct node *next;      // tracks for linkedList PQ
  struct node *prev;      // tracks for linkedList PQ
} Node;


// linked list acting as priority queue
typedef struct listPQ
{
  int size;
  Node *head;
  Node *tail;
} PQ;

// open hash table for storing puzzles
typedef struct openHashTable
{
  int size;
  Node **table;
} openHT;

//-------------------------------------------------------------------------
// initialize functions
// Node for BFS and HT
Node  *initializeNode(int move, int *puzzle, Node *parent, Node *nextHT, Node *next, Node *prev){
  Node *newNode = malloc(sizeof(Node));
  newNode->move = move;
  newNode->puzzle = puzzle;
  newNode->parent = parent;
  newNode->nextHT = nextHT;
  newNode->next = next;
  newNode->prev = prev;
  return newNode;
}

// priority queue for creating next puzzle
PQ *initializelistPQ() {
	PQ *newList = malloc(sizeof(PQ));
  newList->size = 0;
  newList->head = NULL;
  newList->tail = NULL;
  return newList;
}

// HT for storing previous puzzles
openHT *initializeopenHashTable(int size) {
	openHT *hashTable = malloc(sizeof(openHT));
  hashTable->size = size;
  hashTable->table = malloc(sizeof(Node*)*size);
  for(int i=0; i<size; i++){
    hashTable->table[i] = NULL;
  }
  return hashTable;
}

//-------------------------------------------------------------------------
// helper functions
// generate neighbors


// hash function
int hashPuzzle(int *puzzle, unsigned int size, int k)
{
  unsigned int total=0;
  int i;
  int j;
  int m=0;
  for(i=0; i<k; i++){
      for(j=0; j<k; j++){
        total = total + puzzle[i*(k-1)+j]*m;
          m++;
      }
    }
  return (total % size);
}

// hashsize, k value above 4 too large for factorial. (test cases later)
unsigned int htSize(int k){
  int i = k*k;
  unsigned int size = 0;
  while(i!=0){
    size = size + (i * i);
    i--;
  }
  return size;
}

//printBoard array

void printBoard(int *initial_board, int k){
  for(int i=0; i<k*k;i++){
    printf("%d ",initial_board[i]);
  }
  printf("\n");
}

int getZeroPos(int *puzzle,int k){
  int zeroPos=0;
  for(int i=0; i<k*k;i++){
    if(puzzle[i]==0){
      zeroPos=i;
    }
  }
  return zeroPos;
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
  unsigned int size;
  int zeroPos=0;
	
	getline(&line,&lineBuffSize,fp_in);//ignore the first line in file, which is a comment
	fscanf(fp_in,"%d\n",&k);//read size of the board
	//printf("k = %d\n", k); //make sure you read k properly for DEBUG purposes
	getline(&line,&lineBuffSize,fp_in);//ignore the second line in file, which is a comment

	int initial_board[k*k];//get kxk memory to hold the initial board
	for(int i=0;i<k*k;i++)
    {
		  fscanf(fp_in,"%d ",&initial_board[i]);
    }
	printBoard(initial_board, k);//Assuming that I have a function to print the board, print it here to make sure I read the input board properly for DEBUG purposes
	fclose(fp_in);
  
	////////////////////
	// do the rest to solve the puzzle
	////////////////////
  //-------------------------------------------------------------------------
  size = htSize(k);
  // get zero position
  zeroPos=getZeroPos(initial_board,k);
  //printf("%d\n",zeroPos);
  
  
  
  
  // BFS rotation, while loop

  //------------------------------------------------------------------------- //-------------------------------------------------------------------------

	//once you are done, you can use the code similar to the one below to print the output into file
	//if the puzzle is NOT solvable use something as follows
	fprintf(fp_out, "#moves\n");
	fprintf(fp_out, "no solution\n");
	
	//if it is solvable, then use something as follows:
	fprintf(fp_out, "#moves\n");
	//probably within a loop, or however you stored proper moves, print them one by one by leaving a space between moves, as below
  /*
	for(int i=0;i<numberOfMoves;i++)
		fprintf(fp_out, "%d ", move[i]);

	fclose(fp_out);
*/
	return 0;

}
