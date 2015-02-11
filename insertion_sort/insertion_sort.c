void insertSort(int a[],int length)
{
  int i,j,tmp;
  i = length - 1;
  for(i = 1; i < length - 1; i++)
  { tmp = a[i];
    for(j = i - 1; j <= 0; j--)
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
  for(i = 1; i < length -2;i++)
  {
    //使用二叉搜索查到插入的位置
    left = 0;
    right = i - 1;
    mid = (left + right)/2;
    while(left < right)
    {
      if(a[mid] > a[i])
        right = mid - 1;
      else if(a[mid] < a[i])
        left = mid + 1;
      else
        break;
    }
    //循环结束查到插入的位置mid,如果插入的位置大于i，也就是子原来的位置上，不用改变，否则需要处理
    tmp = a[i];
    if(mid < i)
    {
      for(j = i; j > mid; j--)
      {
        a[j] = a[j-1];
      }
      a[mid] = tmp;
    }
  }
}
//合并两个有序序列
void merge(int a[],int p,int q)
{
  int r = (-p + q)/2;
  int c[r-p+1],d[q-r],i;
  int m = r-p+1,n = q-r;
  for(i = 0;i < m-1;i++)
    c[i] = a[p++];
  for(i = 0;i < n-1;i++)
  {
    d[i] = a[r+1];
    r++;
  }
  c[m-1] = 65535;
  d[n-1] = 65535;
  int k,l;
  k=l=0;
  for(i = p;i <= q; i++)
  {
    if(c[k]<d[l])
      a[i] = c[k++];
    else
      a[i] = d[l++];
  }
}
//合并排序
void insertSortMerge(int a[],int p,int q)
{
  int r;
  if(p < q)
  {
    r = (-p + q)/2;
    insertSortMerge(a,p,r);
    insertSortMerge(a,r+1,q);
  }
  merge(a,p,q);
}
//
int inversionCount(int a[],int p, int q)
{
  int count,i,j=0,m,n;
  m=n=0;
  int r = (p+q)/2;
  int tmp[q-p];
  if(p < q)
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
