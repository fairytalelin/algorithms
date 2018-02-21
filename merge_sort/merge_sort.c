#include<limits.h>
#include <printf.h>
#include "../utility.h"

void merge(int a[], int p, int q) {
    int r = (p + q) / 2;
    int m, n;
    m = r - p + 2;
    n = q - r + 1;
    if (n == 0)
        n = 2;
    if (m == 0)
        m = 2;
    int c[m], d[n], i;
    for (i = 0; i < m - 1; i++)
        c[i] = a[p + i];
    for (i = 0; i < n - 1; i++) {
        d[i] = a[r + i + 1];
    }
    c[m - 1] = INT_MAX;
    d[n - 1] = INT_MAX;
    int k, l;
    k = l = 0;
    for (i = p; i <= q; i++) {
        if (c[k] < d[l])
            a[i] = c[k++];
        else
            a[i] = d[l++];
    }
    printf("合并后:");
    printf("p=%d,q=%d,m=%d,n=%d\n", p, q, m, n);
    printArray(a, p, q);
}

void insertSortMerge(int a[], int p, int q) {
    int r;
    if (p < q) {
        r = (q + p) / 2;
        insertSortMerge(a, p, r);
        insertSortMerge(a, r + 1, q);
    }
    merge(a, p, q);
}
