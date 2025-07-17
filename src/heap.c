#include<heap.h>

uint8_t heap[HEAPSIZE];

//Viene de nanoVM/src/heap.c línea 387 --- https://github.com/harbaum/NanoVM/blob/master/vm/src/heap.c
void initHeap(){
  HeapEntry *h;
  HeapEntry *h2;

  // just one big free block
  h = (HeapEntry*)&heap[0];

  h->length = MAX_HEAP_ENTRY_SIZE;

  h2 = (HeapEntry*)&heap[MAX_HEAP_ENTRY_SIZE + sizeof(HeapEntry)];

  h2->length = MAX_HEAP_ENTRY_SIZE;
}

int searchFreeSpaceIndex(int bytes){
  int curr = 0;
  HeapEntry *l;

  do {
    l = (HeapEntry*)&heap[curr];

    if (((l->length & MAX_HEAP_ENTRY_SIZE) > bytes) && (l->length & ENTRY_MARK_MASK)){
      printf("trueewe\n");
      return curr;
    }
    curr += l->length;
  }while(curr < l->length);
}