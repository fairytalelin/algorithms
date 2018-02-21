#include<stdio.h>
#include "../utility.h"

int partition(int a[], int p, int r) {
    int i = p - 1, j, tmp;
    int x = a[r];
    for (j = p; j <= r - 1; j++) {
        if (a[j] < x) {
            i++;
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }
    a[r] = a[i + 1];
    a[i + 1] = x;
    return (i + 1);
}

void quickSort(int a[], int p, int r) {
    int q;
    if (p < r) {
        q = partition(a, p, r);
        quickSort(a, p, q - 1);
        quickSort(a, q + 1, r);
    }
}

int main() {
    int a[] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
    quickSort(a, 0, 11);
    printArray(a, 0, 11);
}
