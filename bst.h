/*bst.h*/

//
// Binary Search Tree ADT header file.
//
// Omar Zorob
// U. of Illinois, Chicago
// CS251, Spring 2017
//

// make sure this header file is #include exactly once:
#pragma once


//
// BST type declarations:
//
typedef char*  BSTKey;
typedef struct BSTValue
{
   char* X;
   long long Y;
} BSTValue;
   
typedef struct BSTNode
{
  BSTKey    Key;
  BSTValue  Value;
  struct BSTNode  *Left;
  struct BSTNode  *Right;
} BSTNode;

typedef struct BST
{
  BSTNode *Root;
  int      Count;
} BST;


//
// BST API: function prototypes
//
BST *BSTCreate();
BST* TxtToTree(char* filename);
int  BSTCompareKeys(BSTKey key1, BSTKey key2);
BSTNode *BSTSearch(BST *tree, BSTKey key);
int  BSTInsert(BST *tree, BSTKey key, BSTValue value);
int BSTHeight(BST *tree);
int _BSTHeight(BSTNode *root);
BSTNode* SuggestRoot(BST *tree, char* prefix);
BST* CreateSubTree(BST *sub, BSTNode* root);
int NumSimilar(BSTNode *start, char* prefix);
BSTValue *BSTSort(BST *tree, int numMatches, char* prefix);