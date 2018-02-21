#include<stdio.h>
#include<limits.h>
#include "../utility.h"

void maxHeapInsert(int a[], int value, int *length);

void maxHeapify(int a[], int index, int length) {
    int tmp, l, r;
    l = 2 * index;
    r = 2 * index + 1;
    printf("l=%d,r=%d,i=%d\n", l, r, index);
    if (r < length && l < length) {
        if ((a[l] > a[r]) && a[index] < a[l]) {
            tmp = a[index];
            a[index] = a[l];
            a[l] = tmp;
            maxHeapify(a, l, length);
        }
        if ((a[l] < a[r]) && a[index] < a[r]) {
            tmp = a[index];
            a[index] = a[r];
            a[r] = tmp;
            maxHeapify(a, r, length);
        }
    } else if (r >= length && l < length)
        if (a[index] < a[l]) {
            tmp = a[index];
            a[index] = a[l];
            a[l] = tmp;
            maxHeapify(a, l, length);
        }
}

//创建最大堆树
void buildMaxHeap(int a[], int length) {
    int mid = (length) / 2;
    int i;
    for (i = mid; i >= 1; i--) {
        maxHeapify(a, i, length);
    }
}

void buildHeapByInsert(int a[], int length) {
    int i, heapSize = 1;
    for (i = 2; i < length; i++) {
        maxHeapInsert(a, a[i], &heapSize);
    }
}

//在已经建好的堆树中进行排序，得出的序列是从小到大排序的
void buildHeapSort(int a[], int length) {
    int tmp, i;
    for (i = 1; i < length - 1; i++) {
        tmp = a[1];//a[1]是最大的一个数
        a[1] = a[length - i];//把a[1]最大的树和最后一个交换，再调用maxHeapify进行堆树调整，到循环结束即达到排序的序列
        a[length - i] = tmp;
        maxHeapify(a, 1, length - i);
    }
}

//用value替换索引index处的数值，如果该数值大于index处的数字，则向上与其父节点比较，找到合适的位置
//查找合适的位置的过程和insert sort 插入排序很想
//如果value小于index处的数值，则向下查找调用
void heapIncreaseValue(int a[], int index, int value) {
    if (value < a[index])
        return;
    int parent = index / 2;
    printf("a[%d] = %d\n", index, a[index]);
    while (parent >= 1 && value > a[parent]) {
        a[index] = a[parent];
        index = parent;
        parent = index / 2;
    }
    a[index] = value;
}

//想建好的堆树中插入一个新数值
//首先把堆的长度增加1，并把该处的只设置为int 类型的最小值，然后调用heapIncreaseValue出入新的数值
void maxHeapInsert(int a[], int value, int *length) {
    (*length)++;
    a[*length] = INT_MIN;
    heapIncreaseValue(a, *length, value);
}

void mergeBy(int a[], int b[], int length, int length1) {
    int i, j;
    for (i = 0; i < length1; i++) {
        a[length++] = INT_MIN;
        heapIncreaseValue(a, length - 1, b[i]);
    }
}

int getlChild(int i, int length) {
    int lChild = 2 * i;
    if (lChild > length)
        return 0;
    return lChild;
}

int getrChild(int i, int length) {
    int rChild = 2 * i + 1;
    if (rChild > length)
        return 0;
    return rChild;
}

int getParent(int i) {
    return i / 2;
}

/****************************** delete a node in index i in array a   *************************************/
//删除索引i处的元素，先把该元素和a[length-1]处的数值替换，然后length-1,如果i处的新数值大于原来的，则调用
//heapIncreaseValue,否则调用maxHeapify，重新调整一棵新的堆树
void heapDelete(int a[], int *length, int i) {
    int last = a[*length - 1];
    (*length)--;
    if (a[i] > last) {
        a[i] = last;
        maxHeapify(a, i, *length);
    } else
        heapIncreaseValue(a, i, last);
    return;
}

//注意要进行堆排序的序列，其下标应该从1开始，否则出错
int main() {
    int a[11] = {6, 65535, 4, 0, -1, 33, 5, 13, 67, 20, 10};
    int c[11] = {6, 65535, 4, 0, -1, 33, 5, 13, 67, 20, 10};
    int b[5] = {3, 6, 7, 8, 9};
    int length = 11;
    buildMaxHeap(a, 11);
    //buildHeapSort(a,11);
    printArray(a, 0, length - 1);////
    buildHeapByInsert(c, 11);
    //heapDelete(a,&length,2);
    printArray(c, 0, length - 1);////
    //mergeBy(a, b, 11,5);
    //buildHeapSort(a,16);
    //printArray(a,16);////
    //heapIncreaseValue(a,3,100);
    //heapDelete(a,11,4);
    //printArray(a,11);
}
