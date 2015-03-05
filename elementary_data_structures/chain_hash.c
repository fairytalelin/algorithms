/*
 * chaining hash is a way to solve the collision with the same hashcode with the linked list
 * */
#include<stdio.h>
#include<stdlib.h>
#include "../utility.h"
#include<string.h>

#define MAXSIZE 12
#define length(x) (( sizeof(x) / sizeof*(x)))

typedef struct node
{
  void *key;
  void *item;
  struct node* prev;
  struct node* next;
}node_t;
typedef struct linkedhead
{
  node_t *head;
  size_t size;
}head_t;
node_t* new_node(void *key,void *item);
head_t *new_head();

/*定义函数指针，必须用括号括起来*/
typedef unsigned (*hash_f)(const void *key);
typedef int (*compare_f)(const void *a,const void *b);
typedef void (*del_item_f)();
typedef void (*del_key_f)();
void new_chain(node_t *head, node_t *node);

typedef struct hashtable
{
  head_t **table;
  size_t size;
  size_t capacity;
  size_t curindex;
  hash_f hash;
  compare_f compare;
  del_item_f delitem;
  del_key_f delkey;
}hash_t;

node_t *search_node(hash_t *htab,void *key);

int main()
{
  int a[] = {1,2,3,4,5,6,7};
  int *p = a, *q = a + 5;
  //char *str = calloc(10,sizeof(char));
  char *str = malloc(10*sizeof(char));
  if(str == NULL)
    return 0;
  putchar(*str);
  //printf("sizeof str is %lu\n",sizeof(str)/sizeof(*str));
  return 0;
}

hash_t *init_htab(size_t size,hash_f hash,compare_f compare,del_item_f delitem,del_key_f delkey)
{
  hash_t *htab = malloc(sizeof(hash_t));
  size_t i;
  if(htab == NULL)
    return NULL;
  htab->table = malloc(size * sizeof(head_t));
  if(htab->table == NULL)
  {
    free(htab);
    return NULL;
  }
  for(i = 0; i < size; i++)
    htab->table[i] = NULL;
  htab->hash = hash;
  htab->compare = compare;
  htab->delitem = delitem;
  htab->delkey = delkey;
  htab->curindex = 0;
  htab->size = 0;
  htab->capacity = size;
  return htab;
}

int insert_htab(hash_t *htab,void *key,void *item)
{
  node_t *node = search_node(htab,key);
  if(node != NULL)
    return 0;
  node = new_node(key,item);
  if(node == NULL)
    return 0;
  unsigned hashcode = htab->hash(key);
  head_t *head = htab->table[hashcode];
  if(head == NULL)
  {
    head = new_head();
    if(head == NULL)
      return 0;
    head->head = node;
  }
  else
    new_chain(head->head,node);
  head->size++;
  htab->size++;
  return 1;
}

int del_node(hash_t *htab,void *key)
{
  node_t *node = search_node(htab,key),*prev,*next;
  unsigned hashcode = htab->hash(key);
  if(node == NULL)
    return 0;
  prev = node->prev;
  next = node->next;
  if(prev == NULL)
  {
    if(next!=NULL)
      next->prev = NULL;
    htab->table[hashcode]->head = next;
    if(next == NULL)
    {
      free(htab->table[hashcode]);
      htab->table[hashcode] = NULL;
    }
  }
  else
  {
    prev->next = next;
    if(next != NULL)
      next->prev = prev;
  }
  htab->table[hashcode]->size--;
  htab->size--;
  node->next = NULL;
  htab->delitem(node->item);
  htab->delkey(node->key);
  free(node);
  return 1;
}

node_t *search_node(hash_t *htab,void *key)
{
  unsigned hashcode = htab->hash(key);
  head_t *head = htab->table[hashcode];
  if(head == NULL)
    return NULL;
  node_t *node = head->head;
  while(node != NULL)
  {
    if(htab->compare(node->key,key) == 0)
      return node;
    node = node->next;
  }
  return node;
}

void del_htab(hash_t *htab)
{
  size_t i;
  for(i = 0; i < htab->capacity; i++)
  {
    node_t *node,*save;
    if(htab->table[i] == NULL)
      continue;
    node = htab->table[i]->head;
    while( node != NULL )
    {
      save = node->next;
      htab->delitem(node->item);
      htab->delkey(node->key);
      free(node);
      node = save;
    }
    free(htab->table[i]);//只要是通过动态分配的内存在释放时都要用free手动释放
  }
  free(htab->table);
  free(htab);
}

void new_chain(node_t *head, node_t *node)
{
  node->next = head->next;
  if(head->next != NULL)
    head->next->prev = node;
  node->prev = head;
  head->next = node;
}

head_t *new_head()
{
  head_t *head = malloc(sizeof(head_t));
  if(head == NULL)
    return NULL;
  head->size = 0;
  return head;
}

unsigned hash(const void *key)
{
  const int *k = key;
  return *k%MAXSIZE;
}

node_t* new_node(void *key,void *item)
{
  node_t *node = malloc(sizeof(node_t));
  if(node == NULL)
    return NULL;
  node->key = key;
  node->item = item;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

//const void *a 和 void const *a 都是指指针a指向的值为不可变，void * const a指的是指针a不可变,
int compare(const void *a, const void *b)
{
  const int *ia = a;
  const int *ib = b;

  if (*ia > *ib)
    return 1;
  else if (*ia < *ib)
    return -1;
  else
    return 0;
}
