#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "../utility.h"

typedef struct linkednode
{
  int value;
  struct linkednode* prev;
  struct linkednode* next;
}lnode;
typedef struct linkedlist
{
  lnode* head;
}linkedlist;

lnode* search(linkedlist*,int);
void insert(linkedlist*,int);
int delete(linkedlist*,int);
linkedlist* init();
void iterate(linkedlist*);

int main()
{
  linkedlist* l = init();
  time_t t;
  int i,n;
  n=10;
  /* initializes random number generator */
  srand((unsigned)time(&t));
  insert(l,50);
  /* add n numbers between 0 and 50 to linkedlist */
  for(i=0;i<=n;i++)
    insert(l,rand()%50);
  lnode* node = l->head;
  iterate(l);
  delete(l,50);
  putchar('\n');
  iterate(l);
}

lnode* search(linkedlist* list,int value)
{
  lnode* node = list->head;
  while(node!=NULL&&node->value!=value)
    node = node->next;
  return node;
}
//从linkedlist头部插入新元素
void insert(linkedlist* l,int value)
{
  lnode* node = (lnode*)malloc(sizeof(lnode));
  node->value=value;
  node->next=l->head;
  if(l->head!=NULL)
    l->head->prev=node;
  node->prev=NULL;
  l->head=node;
}

int delete(linkedlist* l,int value)
{
  lnode* node = search(l,value);
  if(node == NULL)
    return 0;
  if(node->next!=NULL)
    node->next->prev=node->prev;
  if(node->prev!=NULL)
    node->prev->next=node->next;
  else//否则是删除头部，需要更新linkedlist的head字段属性
    l->head=node->next;
  free(node);
  return 1;
}

linkedlist* init()
{
  linkedlist* l = (linkedlist*)malloc(sizeof(linkedlist));
  l->head = NULL;
  return l;
}
void iterate(linkedlist* l)
{
  lnode* node = l->head;
  while(node!=NULL)
  {
    printf("%d\n",node->value);
    node=node->next;
  }
}
