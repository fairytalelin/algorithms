#include<stdio.h>
#include<stdlib.h>
#include "../utility.h"

typedef struct linklist
{
  int value;
  struct linklist *next;
}LinkList;
void radixSort(int a[],int length,int bit)
{
  LinkList b[9];
  int i,remainder;
  for(i = 0; i < length; i++)
  {
    remainder = a[i]%10^bit;
    b[remainder] = (LinkList)malloc(sizeof(LinkList));
  }
}
void getMaxBit(int a[],int length,int* d)
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
  getMaxBit(a,8,&d);
  for(i = 1; i <= d; i++)
  {
    radixSort(a,8,i);
  }
}
