#include<stdio.h>
#include<stdlib.h>
#include "../utility.h"

typedef struct node
{
  int key;
  struct node *parent;
  struct node *left;
  struct node *right;
}node_t;

typedef struct tree
{
  node_t *root;
  size_t size;
}tree_t;

void inorder_tree_walk(node_t *root)
{
  if(root != NULL)
  {
    inorder_tree_walk(root->left);
    printf("%d ",root->key);
    inorder_tree_walk(root->right);
  }
}

//inorder traversal:
//keep th nodes in the path that are waiting to be visited

/* void unrecrusive_inorder_tree_walk(node_t *root)
   {
//the first node to be visited is th leftmost
node_t *node = root;
while(node != NULL)
{
//visit the top node
s->push(node);
node = node->left;
}
//find the next node
while(i <= s->length)
{
node = s->pop();
printf("%d\n",node->key);
printf("%d,");
node = node->right;
while(node != NULL)
{
s->push(node);
node = node->left;
}
}
}
*/
void preorder_tree_walk(node_t *root)
{
  if(root != NULL)
  {
    printf("%d ",root->key);
    inorder_tree_walk(root->left);
    inorder_tree_walk(root->right);
  }
}

void postorder_tree_walk(node_t *root)
{
  if(root != NULL)
  {
    inorder_tree_walk(root->left);
    inorder_tree_walk(root->right);
    printf("%d ",root->key);
  }
}

node_t *search_tree(node_t *root,int key)
{
  if(root == NULL || root->key == key)
    return root;
  if(root->key < key)
    return search_tree(root->right,key);
  else
    return search_tree(root->left,key);
}

node_t *iterative__search_tree(node_t *root,int key)
{
  while(root!=NULL && root->key != key)
  {
    if(root->key < key)
      root = root->right;
    else
      root = root->left;
  }
  return root;
}

node_t *get_tree_mininum(node_t *root)
{
  node_t *node = root;
  while(node->left != NULL)
    node = node->left;
  return node;
}

node_t *get_tree_maxnum(node_t *root)
{
  node_t *node = root;
  while(node->right != NULL)
    node = node->left;
  return node;
}

node_t *get_tree_successor(node_t * node)
{
  if(node->right != NULL)
    return get_tree_maxnum(node);
  node_t *p = node->parent;
  while(p != NULL && p->right == node)
  {
    node = p;
    p = p->parent;
  }
  return p;
}

node_t *get_tree_predecessor(node_t * node)
{
  if(node->left != NULL)
    return get_tree_maxnum(node);
  node_t *p = node->parent;
  while(p != NULL && p->left == node)
  {
    node = p;
    p = p->parent;
  }
  return p;
}

node_t *node_new(int key)
{
  node_t *node = malloc(sizeof(node_t));
  node->key = key;
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void insert_tree(tree_t *t,int key)
{
  node_t *p = NULL,*node = t->root;
  node_t *new = node_new(key);
  while(node != NULL)
  {
    p = node;
    if(node->key > key)
      node = node->left;
    else
      node = node->right;
  }
  if(p==NULL)
    t->root = new;
  else if(p->left == NULL)
  {
    new->parent = p;
    p->left = new;
  }
  else
  {
    new->parent = p;
    p->right = new;
  }
}

void transplant(tree_t *t,node_t *p,node_t *q)
{
  if(p->parent == NULL)
    t->root = q;
  else if(p->parent->left == p)
    p->parent->left = q;
  else
    p->parent->right = q;
  if(q != NULL)
    q->parent = p->parent;
}
//作图演示过程
void delete_node(tree_t *t,node_t *p)
{
  if(p->left == NULL && p->right == NULL)
  {
    transplant(t,p,NULL);
    free(p);
  }
  else if(p->right == NULL)
    transplant(t,p,p->left);
  else if(p->left != NULL && p->right != NULL)
  {
    node_t *successor = get_tree_successor(p->right);
    if(successor != p->right)
    {
      transplant(t,successor,successor->right);
      successor->right = p->right;
      successor->right->parent = successor;
    }
    transplant(t,p,successor);
    successor->left = p->left;
    successor->left->parent = successor;
  }
}
