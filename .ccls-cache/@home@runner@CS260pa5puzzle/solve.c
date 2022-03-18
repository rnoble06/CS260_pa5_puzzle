#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DENOM 7
//-------------------------------------------------------------------------
// define functions
// Node for HT and BFS and LinkedList
typedef struct node{
  int move;               // int moved to get to this board
  int *board;            // board
  struct node *parent;    // tracks for BFS
  struct node *nextHT;    // tracks for HT
} Node;

// Node for PQ
typedef struct nodePQ{
  struct node *htNode;   // HT node
  struct nodePQ *next;      // tracks for linkedList PQ
} NodePQ;

// linked list acting as priority queue
typedef struct listPQ{
  NodePQ *head;
  NodePQ *tail;
} PQ;

//linkedList for HT
typedef struct linkedList{
  Node *head;
}LinkedList;

// open hash table for storing boards
typedef struct openHashTable{
  int size;
  Node **table;
} openHT;

int checkGoal(int *ptrBoard, int *goalState, int k){
  int flag = 0;
  for(int i = 0; i < k*k; i++){
      if (ptrBoard[i] != goalState[i]){
        flag = 1;
      }
    }
  if(flag==0)
    return 1;
  else return 0;
}

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
NodePQ  *initializeNodePQ(Node *htNode, NodePQ *next){
  NodePQ *newNode = malloc(sizeof(NodePQ));
  newNode->htNode = htNode;
  newNode->next = next;
  return newNode;
}

// priority queue for creating next board
PQ *initializelistPQ() {
	PQ *newList = malloc(sizeof(PQ));
  newList->head = NULL;
  newList->tail = NULL;
  return newList;
}

// initialize list for HT
LinkedList *init(){
  LinkedList *newList = malloc(sizeof(LinkedList));
  newList->head = NULL;
  return newList;
}

// HT for storing previous boards
openHT *initializeopenHashTable(int size) {
	openHT *hashTable = malloc(sizeof(openHT));
  hashTable->size = size;
  hashTable->table = malloc(sizeof(Node*)*size);
  for(int i=0; i<size; i++){
    LinkedList *myList = init();
    hashTable->table[i] = myList->head;
  }
  return hashTable;
}

// hash function
int hash(int *board, unsigned int size, int k){
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

// insert to HT
void insertHT(openHT *myHT, Node *nd, int position, int k){
  Node *ptr = malloc(sizeof(Node *));
  ptr = myHT->table[position];
  while(ptr!=NULL){
    if(checkGoal(ptr->board, nd->board, k)==1)
      return;
    else
      ptr=ptr->nextHT;
  }
  nd->nextHT = myHT->table[position];
  myHT->table[position] = nd;
}

// insert to PQ
void insertToTailPQ(PQ *myPQ, Node *nd){
  if(myPQ->head==NULL){
    NodePQ *ndPQ = initializeNodePQ(nd, NULL);
    myPQ->head = ndPQ;
    myPQ->tail = ndPQ;
    return;
  }
  else{
    NodePQ *ndPQ = initializeNodePQ(nd, myPQ->tail->next);
    myPQ->tail->next = ndPQ;
    myPQ->tail = ndPQ;
    return;
  }
}

// dequeue head from PQ
Node *dequeuePQ(PQ *myPQ){
  NodePQ *headPQ;
  Node *headNode;
  if(myPQ->head!=NULL){
    headPQ = myPQ->head;
    myPQ->head = myPQ->head->next;
    headNode = headPQ->htNode;
    return headNode;
  }
  return NULL;
}

// printBoard array
void printBoard(int *initial_board, int k){
  for(int i=0; i<k*k;i++){
    printf("%d ",initial_board[i]);
  }
  printf("\n");
}

// get position of zero in array
int getZeroPos(int *board,int k){
  int zeroPos=0;
  for(int i=0; i<k*k;i++){
    if(board[i]==0){
      zeroPos=i;
    }
  }
  return zeroPos;
}

// create neighbor board
int *createBoard(Node *parent, int k){
  int *newBoard = malloc(sizeof(int)*k*k);
  for(int i=0; i<k*k; i++){
    newBoard[i]=parent->board[i];
  }
  //printBoard(parent->board, k);
  return newBoard;
}

// create new nodes and insert
void createNode(int *newBoard, openHT *myHT, int size, int k, PQ *myPQ, Node *parent, int move){
  int position = hash(newBoard, size, k);
  // insert to HT
  Node *nd = initializeNode(move, newBoard, parent, NULL);
  insertHT(myHT, nd, position, k);
  // insert to PQ
  insertToTailPQ(myPQ,nd);
}

// find board in HT
int findHT(int *newBoard, openHT *myHT, int size, int k){
  int position = hash(newBoard, size, k);
  Node *ptr = myHT->table[position];
  while(ptr!=NULL){
    int flag = 0;
    for(int i = 0; i < k*k; i++){
      if (newBoard[i] != ptr->board[i]){
        flag = 1;
      }
    }
    if(flag == 0){
      return 1;
    }
    ptr = ptr->nextHT;
  }
  return 0;
}

void generateNeighbors(Node *parent, int k, openHT *myHT, PQ *myPQ, int size){
  // for array, to mimic matrix: array(index) = array(i*k+j)
  int zeroPos = getZeroPos(parent->board, k);
  int zeroRow = (int)zeroPos/k;
  int zeroCol = zeroPos%k;
  int maxRow = k*(k-1);
  int maxCol = (k-1);
  int move;
  int *newBoard = malloc(sizeof(int)*k*k);
  
  
  if((zeroRow*k-k)>=0){
    int *newBoard = malloc(sizeof(int)*k*k);
    move = parent->board[(zeroRow*k-k)+zeroCol];
    //check HT
    newBoard = createBoard(parent, k);
    newBoard[zeroPos] = move;
    newBoard[(zeroRow*k-k)+zeroCol] = 0;
    
    // if not in HT
    if(findHT(newBoard, myHT, size, k)==0){
      //printBoard(newBoard, k);
      //printf("newBoard^\n");
      createNode(newBoard, myHT, size, k, myPQ, parent, move);
    } 
  }

  // find neighbor row+1, get move
  if((zeroRow*k+k)<=maxRow){
    move = parent->board[(zeroRow*k+k)+zeroCol];
    //check HT
    newBoard = createBoard(parent, k);
    newBoard[zeroPos] = move;
    newBoard[(zeroRow*k+k)+zeroCol] = 0;
    // if not in HT
    if(findHT(newBoard, myHT, size, k)==0){
      //printBoard(newBoard, k);
      //printf("newBoard 4^\n");
      createNode(newBoard, myHT, size, k, myPQ, parent, move);
    }
  }

  // find neighbor col-1, get move
  if((zeroCol-1)>=0){
    move = parent->board[(zeroRow)*k+zeroCol-1];
    //check HT
    newBoard = createBoard(parent, k);
    newBoard[zeroPos] = move;
    newBoard[(zeroRow)*k+zeroCol-1] = 0;
    // if not in HT
    if(findHT(newBoard, myHT, size, k)==0){
      //printBoard(newBoard, k);
      //printf("newBoard 4^\n");
      createNode(newBoard, myHT, size, k, myPQ, parent, move);
    }
  }

  // find neighbor col+1, get move
  if((zeroCol+1)<=maxCol){
    move = parent->board[(zeroRow)*k+zeroCol+1];
    //check HT
    newBoard = createBoard(parent, k);
    newBoard[zeroPos] = move;
    newBoard[(zeroRow)*k+zeroCol+1] = 0;
    
    // if not in HT
    if(findHT(newBoard, myHT, size, k)==0){
      //printBoard(newBoard, k);
      //printf("newBoard 4^\n");
      createNode(newBoard, myHT, size, k, myPQ, parent, move);
    }
  }
}

void printHashTable(openHT *myHT, int k){
  for (int i=0; i<myHT->size;i++){
    printf("Row %d: [",i);
    Node *ptr = myHT->table[i];
    while(ptr!=NULL){
      printBoard(ptr->board, k);
      ptr = ptr->nextHT;
    }
    printf(" ]\n");
  }
}

void deleteHashTable(openHT *myHT){
  for (int i=0; i<myHT->size;i++){
    Node *ptr = myHT->table[i];
    Node *freeMe = ptr;
    while(ptr!=NULL){
      freeMe = ptr;
      ptr = ptr->nextHT;
      free(freeMe);
    }
    free(ptr);
  }
}

void printPQ(PQ *myPQ, int k){
  NodePQ *ptr = myPQ->head;
    while(ptr!=NULL){
      printBoard(ptr->htNode->board, k);
      ptr = ptr->next;
    }
}

void deletePQ(PQ *myPQ){
  NodePQ *ptr = myPQ->head;
  NodePQ *freeMe = ptr;
    while(ptr!=NULL){
      freeMe = ptr;
      ptr = ptr->next;
      free(freeMe);
    }
  free(ptr);
}

int solCheck(int *board, int k){
  int polarity;
  int i, j;
  for(i=0;i<k*k;i++){
    if(board[i]==0)
      i++;
    for(j=i+1;j<k*k;j++){
      if(board[j]==0)
        j++;
      if(board[i]>board[j])
        polarity++;
    }
  }
  polarity = polarity%2;
  return polarity;
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
	getline(&line,&lineBuffSize,fp_in);//ignore the second line in file, which is a comment
	int initial_board[k*k];//get kxk memory to hold the initial board
	for(int i=0;i<k*k;i++){
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
  for(int i=0;i<(k*k)-1;i++){
		goalState[i]=(i+1);
  }
  goalState[(k*k)-1] = 0;
  size = htSize(k);
  PQ *myPQ = initializelistPQ();
  openHT *myHT = initializeopenHashTable(size);

  //insert initial_board
  Node *nd = initializeNode(0, initial_board, NULL, NULL);
  int position = hash(nd->board,size,k);
  insertHT(myHT, nd, position, k);
  insertToTailPQ(myPQ,nd);
  
  // BFS rotation, while loop. Currently iterating fixed length until issues fixed.
  int i=0;
  int flag = 0;
  while(1){
    //printPQ(myPQ, k);
    //printf("PQ ^\n");
    
    if(flag==0){
      flag = 1;
      if(solCheck(initial_board, k)==1){
        fprintf(fp_out, "#moves\n");
  	    fprintf(fp_out, "no solution\n");
        break;
      }
    }
    
    Node *ptr = dequeuePQ(myPQ);
    if(ptr==NULL){
      printf("Empty List!!\n");
      //free(ptr);
      break;
    }

    
    if(checkGoal(ptr->board, goalState, k)==1){
      //printf("Check board\n");
      int moves=0;
      Node *start = ptr;
      while(ptr->move!=0){
        ptr=ptr->parent;
        moves++;
      }
      int solution[moves];
      int i=0;
      while(start->move!=0){
        solution[i] = start->move;
        start=start->parent;
        i++;
      }
      //print solution to file
      fprintf(fp_out, "#moves\n");
      for(int i = moves-1; i>=0; i--){
        fprintf(fp_out, "%d ",solution[i]);
      }
      fprintf(fp_out, "\n");
      fclose(fp_out);
      //free(ptr);
      break;
    }
    else{
      generateNeighbors(ptr, k, myHT, myPQ, size);
    }
  }
  deleteHashTable(myHT);
  deletePQ(myPQ);
  free(myHT);
  free(myPQ);
  //-------------------------------------------------------------------------
	return 0;
}
