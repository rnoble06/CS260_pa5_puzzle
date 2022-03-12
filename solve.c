#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DENOM 7
//-------------------------------------------------------------------------
// define functions
// Node for HT and BFS
typedef struct node
{
  int move;               // int moved to get to this board
  int *board;            // board
  struct node *parent;    // tracks for BFS
  struct node *nextHT;    // tracks for HT
} Node;

typedef struct nodePQ
{
  struct node *htNode;   // HT node
  struct nodePQ *next;      // tracks for linkedList PQ
  struct nodePQ *prev;      // tracks for linkedList PQ
} NodePQ;


// linked list acting as priority queue
typedef struct listPQ
{
  NodePQ *head;
} PQ;

// DONE open hash table for storing boards
typedef struct openHashTable
{
  int size;
  Node **table;
} openHT;

//-------------------------------------------------------------------------
// initialize functions
// Node for BFS and HT
Node  *initializeNode(int move, int *board, Node *parent, Node *nextHT){
  Node *newNode = malloc(sizeof(Node));
  newNode->move = move;
  newNode->board = board;
  newNode->parent = parent;
  newNode->nextHT = nextHT;
  return newNode;
}
// Node for PQ
NodePQ  *initializeNodePQ(Node *htNode, NodePQ *next, NodePQ *prev){
  NodePQ *newNode = malloc(sizeof(NodePQ));
  newNode->htNode = htNode;
  newNode->next = next;
  newNode->prev = prev;
  return newNode;
}

// priority queue for creating next board
PQ *initializelistPQ() {
	PQ *newList = malloc(sizeof(PQ));
  newList->head = NULL;
  return newList;
}

// DONE HT for storing previous boards
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

// DONE hash function
int hash(int *board, unsigned int size, int k)
{
  unsigned int total=0;
  int i;
  int j;
  int m=0;
  for(i=0; i<k; i++){
      for(j=0; j<k; j++){
        total = total + board[i*(k-1)+j]*m;
          m++;
      }
    }
  return (total % size);
}

// DONE hashsize, k value above 4 too large for factorial. (test cases later)
unsigned int htSize(int k){
  int i = k*k;
  unsigned int size = 0;
  while(i!=0){
    size = size + (i * i);
    i--;
  }
  return size;
}

// DONE?? insert to HT
void insertHT(openHT *myHT, Node *nd, int position){
  Node *ptr = myHT->table[position];
  while(ptr!=NULL){
    ptr=ptr->nextHT;
  }
  myHT->table[position] = nd;
}

// insert to PQ
void insertPQ(PQ *myPQ, NodePQ *ndPQ){
    NodePQ *last = myPQ->head;
 
    if (myPQ->head == NULL) {
      ndPQ->prev = NULL;
      myPQ->head = ndPQ;
      return;
    }
  
    while (last->next != NULL)
      last = last->next;
  
    last->next = ndPQ;
    ndPQ->prev = last;
 
    return;
}

// dequeue head from PQ
Node *dequeuePQ(PQ *myPQ){
  NodePQ *ptrPQ;
  Node *ptr;
  if(myPQ->head!=NULL){
    ptrPQ = myPQ->head;
    myPQ->head = myPQ->head->next;
  }
  ptr = ptrPQ->htNode;
  free(ptrPQ);
  return ptr;
}

// DONE printBoard array
void printBoard(int *initial_board, int k){
  for(int i=0; i<k*k;i++){
    printf("%d ",initial_board[i]);
  }
  printf("\n");
}

// DONE get position of zero in array
int getZeroPos(int *board,int k){
  int zeroPos=0;
  for(int i=0; i<k*k;i++){
    if(board[i]==0){
      zeroPos=i;
    }
  }
  return zeroPos;
}

int *createBoard(Node *parent, int *newBoard, int k){
  for(int i=0; i<k*k; i++){
    newBoard[i]=parent->board[i];
  }
  return newBoard;
}

void generateNeighbors(Node *parent, int k){
  // for array, to mimic matrix: array(index) = array(i*k+j)
  int zeroPos = getZeroPos(parent->board, k);
  int zeroRow = (int)zeroPos/k;
  int zeroCol = zeroPos%k;
  int maxRow = k*(k-1);
  int maxCol = (k-1);
  int move;
  int newBoard[k*k];
  printf("%d\n",zeroPos);
  if((zeroRow*k-k)>=0){
    move = parent->board[(zeroRow*k-k)+zeroCol];
    //check HT
    createBoard(parent, newBoard, k);
    newBoard[zeroPos] = move;
    newBoard[(zeroRow*k-k)+zeroCol] = 0;
    printBoard(newBoard, k);
    // if not in HT
    if(){
      
    }
      // insert to HT
      // insert to PQ
  }

  // find neighbor row+1, get move
  if((zeroRow*k+k)<=maxRow){
    move = parent->board[(zeroRow*k+k)+zeroCol];
    //check HT
    createBoard(parent, newBoard, k);
    newBoard[zeroPos] = move;
    newBoard[(zeroRow*k+k)+zeroCol] = 0;
    printBoard(newBoard, k);
    // if not in HT
      // insert to HT
      // insert to PQ
  }

  // find neighbor col-1, get move
  if((zeroCol-1)>=0){
    move = parent->board[(zeroRow)*k+zeroCol-1];
    //check HT
    createBoard(parent, newBoard, k);
    newBoard[zeroPos] = move;
    newBoard[(zeroRow)*k+zeroCol-1] = 0;
    printBoard(newBoard, k);
    // if not in HT
      // insert to HT
      // insert to PQ
  }

  // find neighbor col+1, get move
  if((zeroCol+1)<=maxCol){
    move = parent->board[(zeroRow)*k+zeroCol+1];
    //check HT
    createBoard(parent, newBoard, k);
    newBoard[zeroPos] = move;
    newBoard[(zeroRow)*k+zeroCol+1] = 0;
    printBoard(newBoard, k);
    // if not in HT
      // insert to HT
      // insert to PQ
  }
  
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
	//printBoard(initial_board, k);  // check board input properly
	fclose(fp_in);
  
	////////////////////
	// do the rest to solve the board
	////////////////////
  
  //-------------------------------------------------------------------------
  //create goalState for board
  int goalState[k*k];
  for(int i=0;i<(k*k)-1;i++)
    {
		  goalState[i]=(i+1);
    }
  goalState[(k*k)-1] = 0;
  //printBoard(goalState, k);  //check goalState
  size = htSize(k);
  // get zero position
  zeroPos=getZeroPos(initial_board,k);
  //printf("%d\n",zeroPos);
  //-------------------------------------------------------------------------
  
  PQ *myPQ = initializelistPQ();
  openHT *myHT = initializeopenHashTable(size);


  //insert initial_board
  Node *nd = initializeNode(0, initial_board, NULL, NULL);
  int position = hash(nd->board,size,k);
  insertHT(myHT, nd, position);
  NodePQ  *ndPQ = initializeNodePQ(nd, NULL, NULL);
  insertPQ(myPQ,ndPQ);
  
  // BFS rotation, while loop
  while(1){
    Node *ptr = dequeuePQ(myPQ);
    if(ptr->board == goalState)
      printBoard(ptr->board, k);
    else
      generateNeighbors(ptr, k);
  }
  
  // print solution via printing array in reverse
  
  //-------------------------------------------------------------------------
  //-------------------------------------------------------------------------

	//once you are done, you can use the code similar to the one below to print the output into file
	//if the board is NOT solvable use something as follows
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
