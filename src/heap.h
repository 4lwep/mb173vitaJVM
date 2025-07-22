#ifndef HEAP_H
#define HEAP_H

#include<stdint.h>

#define HEAPSIZE (50 * 1024 * 1024)  //50 MB
#define MARK 0;
#define MAX_HEAP_ENTRY_SIZE 0x7FFF
#define ENTRY_MARK_MASK 0x8000

typedef struct {
    uint16_t length; //Tamaño real de 15 bits, el primer bit se usa para los flags definidos arriba
} HeapEntry;

extern uint8_t heap[HEAPSIZE];

void initHeap();
int searchFreeSpaceIndex(int bytes);
uint16_t heapAlloc(int bytes);
//int heap_garbage_collect();

#endif