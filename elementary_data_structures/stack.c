#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 12
typedef struct Stacks {
    int top;
    int a[MAXSIZE];
    int length;
} stack;

int isFull(stack *s);

int isEmpty(stack *s);

int push(stack *s, int value) {
    if (isFull(s))
        return -1;
    (s->top)++;
    s->a[s->top] = value;
    return s->top;
}

int pop(stack *s) {
    if (isEmpty(s))
        return -1;
    int item = s->a[s->top];
    (s->top)--;
    return item;
}

int isEmpty(stack *s) {
    if (s->top == 0)
        return 1;
    return 0;
}

int isFull(stack *s) {
    if (s->top + 1 >= s->length)
        return 1;
    return 0;
}

int main() {
    stack *s = (stack *) malloc(sizeof(stack));
    s->top = 0;
    s->length = MAXSIZE;
    int result = push(s, 1);
    if (result != -1)
        printf("result = %d\n", result);
}
