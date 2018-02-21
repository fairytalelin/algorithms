/**
 *实现direct-address table的算法
 *direct-address表中，数组下标直接是元素的key,所以称为直接地址，T[el->key]=el。且设定所有元素中的key不可以重复
*/
#include<stdio.h>
#include<stdlib.h>
#include "../utility.h"

#define MAXSIZE 12

typedef struct element {
    int key;
    int value;
} el;

el directAddressSearch(el *, int);

int directAddressInsert(el *, el *);

int directAddressDelete(el **, el *);

el *initEl();

int main() {
    el T[MAXSIZE];
    el *e1 = initEl();
    e1->value = 121;
    e1->key = 3;
    directAddressInsert(T, e1);
    printf("T[%d]=%d\n", e1->key, T[e1->key].value);
    el e2 = directAddressSearch(T, 3);
    printf("T[%d]=%d\n", e2.key, T[e2.key].value);
}

el *initEl() {
    el *e = malloc(sizeof(*e));
    return e;
}

el directAddressSearch(el *T, int key) {
    return T[key];
}

int directAddressInsert(el T[], el *el) {
    T[el->key] = *el;
    return el->key;
}

int directAddressDelete(el **T, el *el) {
    T[el->key] = NULL;
    int key = el->key;
    free(el);
    return key;
}
