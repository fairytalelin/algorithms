#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct linkednode
{
  int value;
  struct linkednode* left;
  struct linkednode* right;
  struct linkednode* parent;
}lnode;

typedef struct linkedlist
{
  int count;
  lnode* head;
  lnode* tail;
}linkedlist;

void maxHeapify(linkedlist* l,lnode*);
void buildMaxHeap(linkedlist*);
void exchange(linkedlist*,lnode*,lnode*);
void exchangeValue(lnode*,lnode*);
lnode* getPrev(linkedlist*,lnode*);
void insert(linkedlist*,int);
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
  /* add n numbers between 0 and 50 to linkedlist */
  for(i=0;i<=n;i++)
    insert(l,rand()%50);
  iterate(l);
  buildMaxHeap(l);
  iterate(l);
}

void maxHeapify(linkedlist* l,lnode* node)
{
  lnode* left = 2*node;
  lnode* right = 2*node + 1;
  int tmp;
  if(left!=NULL)
  {
    if(right==NULL)
    {
      if(node->value < left->value)
      {
        printf("11\n");
        exchangeValue(left,node);
        //exchange(l,left,node);
        //tmp = left->value;
        //left->value = node->value;
        //node->value = tmp;
        maxHeapify(l,left);
      }
    }
    else
    {
      if(left->value > node->value && left->value > right->value)
      {
        printf("22\n");
        tmp = left->value;
        exchangeValue(left,node);
        //exchange(l,left,node);
        //left->value = node->value;
        //node->value = tmp;
        maxHeapify(l,left);
      }
      if(right->value > node->value && left->value < right->value)
      {
        printf("33\n");
        exchangeValue(right,node);
        //exchange(l,right,node);
        //tmp = right->value;
        //right->value = node->value;
        //node->value = tmp;
        maxHeapify(l,right);
      }
    }
  }
}

void exchangeValue(lnode* s,lnode* d)
{
  int tmp;
  tmp = s->value;
  s->value = d->value;
  d->value = tmp;
}

void buildMaxHeap(linkedlist* l)
{
  int n = l->count/2;
  int i;
  lnode* node = l->head;
  for(i = 1; i <= n; i++)
  {
    maxHeapify(l,node);
    node = node->next;
  }
}

lnode* getPrev(linkedlist* l,lnode* node)
{
  if(node == l->head)
    return NULL;
  lnode* prev = l->head;
  printf("prev=%d\n",prev->value);
  while(prev->next != node)
    prev = prev->next;
  return prev;
}

void exchange(linkedlist* l,lnode* s,lnode* d)
{
  lnode* snext = s->next;
  lnode* dnext = d->next;
  lnode* sprev = getPrev(l,s);
  printf("s=%d,sprev=%d\n",s->value,sprev->value);
  lnode* dprev = getPrev(l,d);
  sprev->next = d;
  dprev->next = s;
  d->next = snext;
  s->next = dnext;
}

void insert(linkedlist* l,int value)
{
  lnode* node = (lnode*)malloc(sizeof(lnode));
  node->value = value;
  node->next = l->head;
  if(l->head == NULL)
    l->tail = node;
  l->head = node;
  l->count++;
}

linkedlist* init()
{
  linkedlist* l = (linkedlist*)malloc(sizeof(linkedlist));
  l->count = 0;
  l->head = l->tail = NULL;
  return l;
}

void iterate(linkedlist* l)
{
  lnode* node = l->head;
  while(node!=NULL)
  {
    printf("%d,",node->value);
    node = node->next;
  }
  putchar('\n');
}
