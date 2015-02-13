#include<stdio.h>
#include "../utility.h"
void countSort(int a[],int b[],int c[],int maxValue,int length)
{
  int i;
  for(i = 0; i <= maxValue; i++)
  {
    c[i] = 0;
  }//初始化每个在a数组中出现的次数为0
  for(i = 0; i < length; i++)
  {
    c[a[i]] = c[a[i]] + 1;
  }//计算a数组中比每个元素的个数，例如c[i] = 4,这就是指a[4]=i,i是a数组中的元素，4指的是比a中元素i大的个数
  printArray(c,0,maxValue);
  for(i = 1;i <= maxValue; i++)
  {
    c[i] = c[i] + c[i-1];
  }
  printArray(c,0,maxValue);
  for(i = 0; i < length; i++)
  {
    b[c[a[i]]-1] = a[i];//此处减去1是因为我们是在数组b中是从0开始存储数组的。如在计算c数组时，也就是计算a数组每个元素出现的个数
    //如果c的数组为 2，1，5，6，7，4，2，第一个数值2 指的是在数组a中0的出现次数为2，1表示1出现的次数为1等等。
    printf("b[%d]=%d,c[a[%d]]=%d,a[%d]=%d \n",c[a[i]],a[i],i,c[a[i]],i,a[i]);
    c[a[i]] = c[a[i]] - 1;
  }
  printArray(b,0,11);
}

int main()
{// 0 0 1 2 3 4
  int a[] = {4,1,0,22,3,5,6,6,2,0,33,45};
  int b[12];
  int length = 12,maxValue = a[0];
  int i;
  for(i = 1; i < length; i++)
  {
    if(a[i] > maxValue)
      maxValue = a[i];
  }
  int c[maxValue+1];
  countSort(a,b,c,maxValue,12);
}
