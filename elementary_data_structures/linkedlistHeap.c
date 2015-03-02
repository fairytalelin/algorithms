#include<stdio.h>
#include<stdlib.h>

typedef struct linkednode
{
  int value;
  struct linkednode* left;
  struct linkednode* right;
  struct linkednode* parent;
}lnode;
