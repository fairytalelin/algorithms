#include<limits.h>
#include<stdio.h>
#include "../utility.h"
void insertSort(int a[],int length)
{
  int i,j,tmp;
  for(i = 1; i <= length - 1; i++)
  { tmp = a[i];
    for(j = i - 1; j >= 0; j--)
      if(tmp < a[j])
        a[j+1] = a[j];
      else
        break;
    a[j+1] = tmp;
  }
}

void insertSortRecursive(int a[],int length)
{
  int tmp,val,i;
  val = a[length - 1];
  if(length == 1)
    return;
  insertSortRecursive(a,length - 1);
  for(i = length - 2; i >= 0; i++)
  {
    if(a[i] > val)
      a[i+1] = a[i];
    else
      break;
  }
  a[i+1] = val;
}
//T(n)=T(n-1)+(n-1)=T(n-2)+(n-2)+n-1=T(n-3)+(n-3)+(n-2)+(n-1)=T(n-k)+k*n-(1+k)*k/2
//当k=n-1,T(n)=T(1)+(n-1)*n-n*(n-1)/2=T(1)+(n-1)*(n-1/2)
void binaryInsertSort(int a[],int length)
{
  int i,j,tmp,mid,left,right;
  for(i = 1; i < length;i++)
  {
    //使用二叉搜索查到插入的位置
    left = 0;
    right = i - 1;
    mid = (left + right)/2;
    while(left <= right)
    {
      if(a[mid] > a[i])
        right = mid - 1;
      else if(a[mid] < a[i])
        left = mid + 1;
      else
        break;
      mid = (left + right)/2;
    }
    //循环结束查到插入的位置mid,如果插入的位置大于i，也就是子原来的位置上，不用改变，否则需要处理
    printf("mid = %d,a[%d]=%d,left=%d\n",mid,mid,a[mid],left);
    tmp = a[i];//当left>right时，说明插入的位置在right和left之间，这时要把a[i]插到right之后，left之前,也就是插到left位置上
    if(left < i)
    {
      for(j = i; j > left; j--)
      {
        a[j] = a[j-1];
      }
      a[left] = tmp;
    }
    printArray(a,0,i);
  }
}
int inversionCount(int a[],int p, int q)
{
  int count,i,j=0,m,n;
  m=n=0;
  int r = (p+q)/2;
  int tmp[q-p];
  if(p <= q)
  {
    count = inversionCount(a,p,r);
    count += inversionCount(a,r+1,q);
  }
  int b[r-p],c[q-r-1];
  if(a[r]<a[r+1])
    return count;
  for(i=0;i<=q-p;i++)
  {
    if(b[m]<c[n])
      a[i]=b[m++];
    else
      a[i]=c[n++];
    count += r + 1 - i;
  }
  for(i=p;i<=q;i++)
    a[p]=tmp[j++];

  return count;
}

int main()
{
  int a[] = {4,3,1,0,54,12,2,5,33,66};
  //insertSort(a,10);
  binaryInsertSort(a,10);
  printArray(a,0,9);
}
