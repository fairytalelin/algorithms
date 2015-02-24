#include<stdio.h>
#include<stdlib.h>
#include "../utility.h"
#define MAXSIZE 4
//下面是实现一个在a[MAXSIZE]中可以容纳MAXSIZE-1个元素的队列，注意只可以容纳MAXSIZE-1个元素，当队列满时，tail处的位置没有元素
typedef struct queue
{
  int head;
  int tail;
  int a[MAXSIZE];
}que;

int deque(que*);
int enque(que*,int);
int isFull(que*);
int isEmpty(que*);
que* initQue();

int main()
{
  que* q = initQue();
  enque(q,1);
  enque(q,2);
  enque(q,3);
  int result = enque(q,213);
  //int result = enque(q,5);
  //int result = deque(q);
  printArray(q->a,q->head,q->tail-1);//队列的元素在head和tail-1之间，tail表示下一个元素的位置
  printf("the result = %d",result);
}

int deque(que* q)
{
  if(isEmpty(q))
    return -1;
  int el = q->a[q->head];
  q->head = (q->head+1)%MAXSIZE;
  return el;
}

int enque(que* q,int value)
{
  if(isFull(q))
    return -1;
  q->a[q->tail] = value;
  q->tail = (q->tail+1)%MAXSIZE;
  return q->tail;
}

int isEmpty(que* q)
{
  if(q->head == q->tail)
    return 1;
  return 0;
}

int isFull(que* q)
{
  if(q->head == (q->tail+1)%(MAXSIZE))
    return 1;
  return 0;
}

que* initQue()
{
  que *q = (que*)malloc(sizeof(que));
  q->head = q->tail = 0;
  return q;
}
