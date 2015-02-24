#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "../utility.h"

typedef struct linklist
{
  int value;
  struct linklist *next;
}LinkedList;
void radixSort(int a[],int length,int bit)
{
  LinkedList *b[10];
  int i,remainder,j;
  LinkedList *tmp,*last;
  for(i = 0; i < length; i++)
  {
    remainder = a[i]%((int)pow(10,bit));
    //printf("0\n");
    //printf("remainder = %d\n",remainder);
    printf("0");
    if(b[remainder]==NULL)
    {
      printf("1");
      b[remainder] = (LinkedList *)malloc(sizeof(LinkedList));
      b[remainder]->next = NULL;
    }
    else
    {
      printf("1111");
      last = tmp;
      tmp = b[remainder]->next;
      while(tmp != NULL)
      {
        last = tmp;
        tmp = tmp->next;
      }
      printf("2");
      tmp = (LinkedList *)malloc(sizeof(LinkedList));
      tmp->value = a[i];
      tmp->next = NULL;
      last->next = tmp;
    }
    printf("tmp->value=%d\n",a[i]);
  }
  for(i = 0,j = 0; i <= 9 && j < 8; i++)
  {
    while(b[i]!=NULL)
    {
      a[j++] = b[i++]->value;
    }
  }
  printArray(a,0,7);
}
void getMaxtmpt(int a[],int length,int* d)
{
  int i,tmp=1;
  for(i = 0; i < length; i++)
  {
    while(a[i]/tmp)
    {
      tmp = tmp * 10;
      *d = *d + 1;
    }
  }
}
int main()
{
  int a[] = {170,45,75,90,802,2,24,66};
  int d = 0,i;
  getMaxtmpt(a,8,&d);
  for(i = 1; i <= d; i++)
  {
    radixSort(a,8,i);
  }
}
