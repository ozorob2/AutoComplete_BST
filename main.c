/*main.cpp*/
 
//
// Auto-complete using a binary search tree.
//
// Name: Omar Zorob
// NetID: ozorob2
// U. of Illinois, Chicago
// CS251, Spring 2017
// Project 03
//
 
// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
#include "bst.h"
//
// skipRestOfInput:
//
// Inputs and discards the remainder of the current line for the 
// given input stream, including the EOL character(s).
//
void skipRestOfInput(FILE *stream)
{
  char restOfLine[256];
  int rolLength = sizeof(restOfLine) / sizeof(restOfLine[0]);
 
  fgets(restOfLine, rolLength, stream);
}
 
//
// getFileName: inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is exited.
//
char *getFileName()
{
  char filename[512];
  int  fnsize = sizeof(filename) / sizeof(filename[0]);
 
  // input filename from the keyboard:
  fgets(filename, fnsize, stdin);
  filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):
 
  // make sure filename exists and can be opened:
  FILE *infile = fopen(filename, "r");
  if (infile == NULL)
  {
    printf("**Error: unable to open '%s'\n\n", filename);
    exit(-1);
  }
 
  fclose(infile);
 
  // duplicate and return filename:
  char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));
  strcpy(s, filename);
 
  return s;
}
 

 
int main()
{
  char *filename = getFileName();
  char  cmd[64];
  char  text[512];
 
  printf("** Starting Autocomplete **\n");
  
  /*Places item from txt file into Tree*/ 
  BST* tree = TxtToTree(filename);

  printf("** Ready **\n");
  scanf("%s", cmd);
 
  while (strcmp(cmd, "exit") != 0)
  {
   
   /*If user inputs stats Print out Number of Nodes in Tree and height of tree*/ 
    if (strcmp(cmd, "stats") == 0)
    {
        printf("**Tree count:  %d\n", tree->Count);
        printf("**Tree Height: %d\n", BSTHeight(tree));
    }
    else if (strcmp(cmd, "add") == 0)
    {
      /*Getting rest of input*/
      long long weight;
      char      part2[512];
      int       part2size = sizeof(part2) / sizeof(part2[0]);
 
      BSTValue value;
      scanf("%lld %s", &weight, text);
      fgets(part2, part2size, stdin);
      part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
      strcat(text, part2);
      
      /*allocate space for char array where key will be stored*/
      value.X = (char*)malloc((strlen(text) + 1));
      strcpy(value.X, text);
      
      //Store user inputed weight 
      value.Y = weight;
      
      //Insert User input to tree
      int x = BSTInsert(tree, value.X, value);//returns 0 if not inserted and 1 if inserted
      
      //If x = 0 the insert was not succesful as value was already in tree
      if(x == 0)
      printf("**Not added...\n");
      
      else
      printf("**Added\n");
    }
    else if (strcmp(cmd, "find") == 0)
    {
      /*Getting rest of input*/
      char part2[512];
      int  part2size = sizeof(part2) / sizeof(part2[0]);
      
      scanf("%s", text);
      fgets(part2, part2size, stdin);
      part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
      strcat(text, part2);
 
      BSTNode *found = BSTSearch(tree, text);
      
      /*If no node was found print not found*/
      if (found == NULL)
      {
         printf("**Not found...\n");
      }
      
      /*If found print the key of value and the weight of value*/
      else
         printf("%s: %lld\n", found->Key, found->Value.Y);  
   }
      
    else if (strcmp(cmd, "suggest") == 0)
    {
      
      /*Getting rest of input*/ 
      int  k;
      char part2[512];
      int  part2size = sizeof(part2) / sizeof(part2[0]);
 
      scanf("%d %s", &k, text);
      fgets(part2, part2size, stdin);
      part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
      strcat(text, part2);
      
      /*Find the root of our subtree essentially first node that matches prefix*/ 
      BSTNode *subTreeRoot = SuggestRoot(tree, text);
      
      int b = 0;
      
      /*If subTreeRoot is null no nodes matched the prefix*/ 
      if (subTreeRoot != NULL)
      { 
         
         /*Nothing in the bst search matched the prefix*/ 
         BST* subTree = BSTCreate();
      
         /*Insert root node for subTree*/ 
         BSTInsert(subTree, subTreeRoot->Key, subTreeRoot->Value);
      
         /*Creates subTree of everything below and including subTreeRoot*/ 
         subTree = CreateSubTree(subTree, subTreeRoot);
      
         /*Gets the number of nodes that are similar to the prefix*/ 
         int numMatch = NumSimilar(subTree->Root, text);
      
         /*Creates an array of values for those that match the prefix and sorts them*/ 
         BSTValue* subTreeValues = BSTSort(subTree, numMatch, text);
       
         printf("** [Sub-tree root:  (%s,%lld)]\n", subTree->Root->Key, subTree->Root->Value.Y);
         printf("** [Sub-tree count: %d]\n", subTree->Count);
         printf("** [Num matches:    %d]\n", numMatch);
      
         /*While b < number of suggestions the user wants and the number of matches for the prefix print them*/ 
         while(b < k && b < numMatch)
         {
            printf("%s: %lld\n", subTreeValues[b].X, subTreeValues[b].Y);
            b++;
         }

         free(subTreeValues);//deallocates space for subTreeValues
         free(subTree);      //deallocates space for subTree
      
         }
      else
      {
         /*Nothing in the bst search matched the prefix*/ 
         printf("**No suggestions...\n");
      }
    }
    else
    {
      /*User Input was not recognized*/ 
      printf("**unknown cmd, try again...\n");
    }
 
   /*Get Users Next Input*/ 
   scanf("%s", cmd);
  }
  
  printf("** Done **\n");
  free(tree);
  return 0;
}