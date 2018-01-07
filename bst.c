/*bst.c*/

//
// Binary Search Tree ADT implementation file.
//
// Omar Zorob
// U. of Illinois, Chicago
// CS251, Spring 2017
//

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "bst.h"

//
// BSTCreate: dynamically creates and returns an empty
// binary search tree:
//
BST *BSTCreate()
{
  BST *tree;

  tree = (BST *)malloc(sizeof(BST));
  tree->Root = NULL;
  tree->Count = 0;

  return tree;
}


//
// BSTCompareKeys: compares key1 and key2, returning
//   value < 0 if key1 <  key2
//   0         if key1 == key2
//   value > 0 if key1 >  key2
//
int BSTCompareKeys(BSTKey key1, BSTKey key2)
{
  if (strcmp(key1, key2) < 0)
    return -1;
  else if (strcmp(key1, key2) == 0)
    return 0;
  else
    return 1;
}

//
// BSTSearch: searches the binary search tree for a node containing the
// same key.  If a match is found, a pointer to the node is returned, 
// otherwise NULL is returned.
//
BSTNode *BSTSearch(BST *tree, BSTKey key)
{
  BSTNode *cur = tree->Root;

  //
  // search the tree to see if it contains a matching key:
  //
  while (cur != NULL)
  {
    if (BSTCompareKeys(key, cur->Key) == 0)  // found!
      return cur;
    else if (BSTCompareKeys(key, cur->Key) < 0)  // smaller, go left:
    {
      cur = cur->Left;
    }
    else  // larger, go right:
    {
      cur = cur->Right;
    }
  }

  // if we get here, we fell out of the tree, and didn't find it:
  return NULL;
}


//
// BSTInsert: inserts the given (key, value) pair into the binary search
// tree.  Returns true (non-zero) if the insert was successful, returns 
// false (0) if the given key is already in the tree -- in which case the
// given (key, value) pair is not inserted.
//
int BSTInsert(BST *tree, BSTKey key, BSTValue value)
{
  BSTNode *prev = NULL;
  BSTNode *cur = tree->Root;

  //
  // first we search the tree to see if it already contains key:
  //
  while (cur != NULL)
  {
    if (BSTCompareKeys(key, cur->Key) == 0)  // already in tree, failed:
      return 0;
    else if (BSTCompareKeys(key, cur->Key) < 0)  // smaller, go left:
    {
      prev = cur;
      cur = cur->Left;
    }
    else  // larger, go right:
    {
      prev = cur;
      cur = cur->Right;
    }
  }

  // 
  // If we get here, tree does not contain key, so insert new node
  // where we fell out of tree:
  //
  BSTNode *T = (BSTNode *)malloc(sizeof(BSTNode));
  T->Key = key;
  T->Value = value;
  T->Left = NULL;
  T->Right = NULL;

  //
  // link T where we fell out of tree -- after prev:
  //
  if (prev == NULL)  // tree is empty, insert @ root:
  {
    tree->Root = T;
  }
  else if (BSTCompareKeys(key, prev->Key) < 0)  // smaller, insert to left:
  {
    prev->Left = T;
  }
  else  // larger, insert to right:
  {
    prev->Right = T;
  }

  tree->Count++;

  return 1;  // success:
}

//Returns max of two ints
int max2(int x, int y)
{
   return (x>y) ? x : y;
}

//
//Recursively adds height of tree
//
int _BSTHeight(BSTNode *root)
{
   if (root == NULL)
      return -1;
      
   else
   {
      return 1 + max2(_BSTHeight(root->Left), _BSTHeight(root->Right));
   }
}

//returns height of tree
int BSTHeight(BST *tree)
{
   int height = _BSTHeight(tree->Root);
   return height;
}

//Fills subTree with node from full tree
BST* CreateSubTree(BST *sub, BSTNode* root)
{
  if (root == NULL)  // base case: empty tree
    return sub;
  else  // recursive case: non-empty tree
  {
    BSTInsert(sub, root->Key, root->Value);
    sub = CreateSubTree(sub, root->Left);
    sub = CreateSubTree(sub, root->Right);
  }
  return sub;
}

//
//Finds first node to fit condition of being
//similar to the prefix given by user
//returns that node
//
BSTNode* SuggestRoot(BST *tree, char* prefix)
{
  BSTNode *cur = tree->Root;
  while (cur != NULL)
  {
    int suggest = 1;
    int i = 0;
    for(; i < strlen(prefix); i++){
    if (prefix[i] != cur->Key[i]){
       suggest = 0;
       break;}
    }
       
    if(suggest == 1)
    {
      return cur;
    }
      
    if (strcmp(prefix, cur->Key) < 0)  // smaller, go left:
    {
      cur = cur->Left;
    }
    else  // larger, go right:
    {
      cur = cur->Right;
    }
  }
  return NULL;
}

//
//Returns number of similar nodes to a certain prefix starting at a certain node
//
int NumSimilar(BSTNode *start, char* prefix)
{
   if(start == NULL)
   return 0;
   else{
    int suggest = 1;
    int i = 0;
    for(; i < strlen(prefix); i++)
    if (prefix[i] != start->Key[i])
       suggest = 0;
       
    if(suggest == 1)
    {
      return 1 + NumSimilar(start->Left, prefix) + NumSimilar(start->Right, prefix);
    }
    else
    {
      return NumSimilar(start->Left, prefix) + NumSimilar(start->Right, prefix);
    }
   }
}

//
// BSTSort: traverses the tree inorder so as to yield the (key, value)
// pairs in sorted order by key.  Returns a dynamically-allocated array
// of size N, containing a copy of the value in each tree node.  The
// value N can be obtained by calling BSTCount().
//
// Helper Functions insertValues and _BSTSort
// NOTE: the caller is responsible for freeing the returning array.
//

int InsertValues(BSTNode* root, BSTValue* values, int i, char* prefix)
{
  if (root == NULL)
    return i;
  else
  {
    i = InsertValues(root->Left, values, i, prefix);
    
    int suggest = 1;
    int p = 0;
    for(; p < strlen(prefix); ++p)
    if (prefix[p] != root->Key[p])
       suggest = 0;
       
    if(suggest == 1){
    values[i] = root->Value;
    i++;}
    
    i = InsertValues(root->Right, values, i, prefix);

    return i;
  }
}

      

BSTValue* _BSTSort(BSTNode* root, BSTValue* values, int count, char* prefix)
{
  InsertValues(root, values, 0, prefix);
  int i;
  int j;
  BSTValue temp;
  for(i = 0; i  < count;i++)//goes through every element in array 
    {
      j = i;
      while(j > 0 && values[j].Y > values[j-1].Y)//continually checks if element greater than prev element
      {
      	temp = values[j];
      	values[j] = values[j-1];//flips elements spots
      	values[j-1] = temp;
      	j--;
   	  }
    }
    return values;
}

BSTValue *BSTSort(BST *tree, int numMatches, char* prefix)
{
   
  BSTValue *values = (BSTValue *)malloc(numMatches * sizeof(BSTValue));
  
  values = _BSTSort(tree->Root, values, numMatches, prefix);

  return values;
}

/*Takes txt file of format weight (tab) name and insterts it into tree*/
BST* TxtToTree(char* filename)
{
  FILE *file;
  char  line[512];
  int   linesize = sizeof(line) / sizeof(line[0]);
  char *token;
  
  BSTValue value;
  BST *tree = BSTCreate();
  
  file = fopen(filename, "r");
  while (fgets(line, linesize, file) != NULL)
  {
    line[strcspn(line, "\r\n")] = '\0';//Strips EOL Char
    
    /*First part of txt is the weight*/
    token = strtok(line, "\t");
    assert(token != NULL);
    value.Y = atoi(token);
   
    /*Second Part is the name*/
    token = strtok(NULL, "\0");
    assert(token != NULL);
    
    /*Allocating space in memort for name*/
    value.X = (char*)malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(value.X, token);
    
    //Insert the values in to tree
    BSTInsert(tree, value.X, value);
  }
  
  fclose(file);
  return tree;
}  
 