#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct listCDT* listADT;

listADT newList();
listNodeT * createNode(void * element, size_t size);
void freeList(listADT list);
int queue(listADT list, void * element, size_t size);
void * dequeue(listADT list);
int push(listADT list, void * element, size_t size);
int pop(listADT list);
int isEmpty(listADT list);

typedef struct listNodeT{
    void * value;
    size_t size;
    struct listNodeT * next;
} listNodeT;

typedef struct listCDT{
    listNodeT * first;
    listNodeT * last;
} listCDT;

#endif