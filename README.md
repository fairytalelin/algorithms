# 算法与数据结构

****
* 基本排序
  * [heap sort 堆排序](#heap_sort) 
  * [qucik sort 快速排序](#qucik_sort) 
  * [insert sort 插入排序](#insert_sort) 
  * [merge sort 合并排序](#merge_sort) 
  * [radix sort 基数排序](#radix_sort) 
  * [count sort 计数排序](#count_sort) 


## <a name="heap_sort">堆排序</a> [&#8593;](#heap_sort)
**描述:** 堆排序是基于比较的排序算法。堆排序可以看作是改良的选择排序,它采用堆数据结构,每次从待排序的序列中选出最大或者最小的元素。

(二叉)堆数据结构本质上是建立在一个数组对象上的,可以把它看作是完全二叉树,如下图所示。树上的每一个节点对应于数组上的一个元素。该数组A有2个属性,数组长度A.length和堆长度A.heap-size,其中A.length>=A.heap_size。堆的第一个元素存储在数组下标为1的位置上A[1],堆的存储下标范围是1...heap-size。

堆树的根节点是A[1],给出一个节点下标很容易得出其左右孩子节点和父节点:

```
parent(i)
  return i/2;
  
left(i)
  return 2*i;

right(i)
  return 2*i + 1;
```

堆分为大堆和小堆,在大堆中每个节点i满足A[parent(i)] > A[i],根节点A[1]为最大值；小堆则相反,每个节点i满足A[parent(i)] < A[i],根节点A[1]为最小值。

堆排序分为两步:建堆和取最大值。首先把待排序的序列建堆(大堆),然后取最大值A[1],把其与堆中最后一个元素交换,把堆的长度减1,这时破坏了堆,于是重新建堆,如此循环直至堆大小为1,此时数组A就排好了序。下面是堆排序代码和演示图(图源来自wiki):

![alt text](http://upload.wikimedia.org/wikipedia/commons/4/4d/Heapsort-example.gif "堆排序演示图")

```
//时间复杂度为T(n) = n * T(maxHeapify) = n * log(n)
void buildHeapSort(int a[],int length) 
{
  int tmp,i; 
  for(i=1;i<length - 1;i++)
  {
    tmp = a[1];//a[1]是最大的一个数
    a[1] = a[length - i];//把a[1]最大的树和最后一个交换，再调用maxHeapify进行堆树调整，到循环结束即达到排序的序列
    a[length - i] = tmp;
    maxHeapify(a,1,length - i);
  }
}
//时间复杂度为树的高度T(n) = log(n)
void maxHeapify(int a[],int index,int length)
{
  int tmp,l,r;
  l = 2*index;
  r = 2*index + 1;
  printf("l=%d,r=%d,i=%d\n",l,r,index);
  if(r<length&&l<length)
  {
    if((a[l]>a[r]) && a[index] < a[l])
    {
      tmp = a[index];
      a[index] = a[l];
      a[l] = tmp;
      maxHeapify(a,l,length);
    }
    if((a[l]<a[r]) && a[index] < a[r])
    {
      tmp = a[index];
      a[index] = a[r];
      a[r] = tmp;
      maxHeapify(a,r,length);
    }
  }
  else if(r>=length&&l<length)
    if(a[index] < a[l])
    {
      tmp = a[index];
      a[index] = a[l];
      a[l] = tmp;
      maxHeapify(a,l,length);
    }
}
//用val更新替换index处的元素
void updateIndexValues(int a[],int index,int val,int heap_size)
{
  if(a[index] > val)//如果插入的元素小于原index处的元素,则调用maxHeapify找插入位置
  {
    a[index] = val;//替换后可能破坏堆的熟悉,调用maxHeapify重新堆化
    maxHeapify(a,index,heap_size);
  }
  else
  {
    a[index] = val;
    parent = index/2;
    while(parent > 1 && a[parent] < val)//如果val大于parent处的节点,则向上查找合适的节点,类是于插入排序
    {
      a[index] = a[parent];
      index = parent;
      parent = index/2;
    }
    a[index] = val;
  }
}
//删除index处的元素
void delete_heap(int a[],int index,int *heap_size)
{
  int val = a[*heap_size];//删除堆元素的操作是把要删除的元素替换为堆最后的一个元素,同时堆的大小heap_size-1
  *heap_size--;
  updateIndexValues(a,index,val,heap_size);
}
//创建最大堆树
void buildMaxHeap(int a[],int length)
{
  int mid = (length)/2;
  int i;
  for(i = mid; i >= 1; i--)
  {
    maxHeapify(a,i,length);
  }
}
```

**时间复杂度:**从上面分析可知T(buildHeapSort(n)) = n * T(maxHeapify) = n * log(n)。

**应用:**堆排序可应用于优先级队列,在linux中其进程调度使用的调度数据结构是位图bit array,查找的时间复杂度为O(1)。

## <a name="qucik_sort">快速排序</a> [&#8593;](#qucik_sort)

**描述:**quick sort快速排序和合并排序一样,采用分而治之的方法。对数组A[p,r]进行排序通常分为三部分:

-  divide:函数partition(A[p,r])把A[p,r]拆分为两部分A[p,x-1]和A[x+1,r],其中满足A[p,x-1]的所有数据小于A[x],A[x+1,r]的所有数据大于A[x]
-  conquer:递归调用quick sort方法处理A[p,x-1]和A[x+1,r]
-  combine:由于每次的各个子数组A[p,x-1]和A[x+1,r]都是有序的,因为A[p,x-1] < A[x+1,r],所以当递归处理完后已经是有序队列le,所以不用再处理合并操作

**算法代码实现和过程展示图**
```
int partition(int a[],int p,int r)
{
  int i = p - 1,j;
  int x = a[r];

  for(j = p; j < r; j++)
  {
    if(a[j] < x)
    {
      i++;
      exchange(a[i],a[j]);
    }
  }
  exchange(a[i+1],a[r])
  return (i + 1)
}

****
void quick_sort(int a[],int p,int r)
{
  if(p < r)
  {
    int x = partition(a,p,r);
    quick_sort(a,p,x-1);
    quick_sort(a,x+1,r);
  }
}
```

![快排演示图](http://upload.wikimedia.org/wikipedia/commons/thumb/8/84/Partition_example.svg/200px-Partition_example.svg.png)

**算法时间复杂度:**
- 最优复杂度:n*logn
- 最差复杂度:当序列是有序的时,和插入排序一样为n*n
- 平均复杂度:n*logn

## <a name="insert_sort">插入排序</a> [&#8593;](#insert_sort)
**描述:**插入排序是基于比较的排序算法,在有序的队列中插入元素依次比较找到插入位置。有2种实现方案,这里给出递归和非递归:
```
void insert_sort(int *a,int l, int r)
{
  for(i = l + 1; i < r; i++)
  {
    tmp = a[i];
    for(j = i - 1; j >= i; j--)
    {
      if(tmp > a[j])
        a[j+1] = a[j]
    }
    a[j+1] = tmp;
  }
}

void insert_sort_incrusive(int *a,int l, int r)
{
  if(l < r)
  {
    insert_sort_incrusive(a, l, r - 1);
  }
  tmp = a[r];
  for(j = r - 1; j >= l; j--)
  {
    if(tmp > a[j])
      a[j+1] = a[j];
  }
  a[j+1] = tmp;
}
```
![插入排序演示图](http://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif)

**时间复杂度:**
- 最优复杂度:当序列是有序的,其时间复杂度为最优,为O(n)
- 最差复杂度:当序列是逆序的,其时间复杂度为O(n*n)
- 平均复杂度:平均复杂度为O(n*n)

## <a name="merge_sort">合并排序</a> [&#8593;](#merge_sort)
## <a name="radix_sort">基数排序</a> [&#8593;](#radix_sort)
## <a name="count_sort">计数排序</a> [&#8593;](#count_sort)
