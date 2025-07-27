#include<heap.h>

uint8_t heap[HEAPSIZE];

//Viene de nanoVM/src/heap.c línea 387 --- https://github.com/harbaum/NanoVM/blob/master/vm/src/heap.c
void initHeap(){
  HeapEntry *h;

  // just one big free block
  h = (HeapEntry*)&heap[0];

  h->length = MAX_HEAP_ENTRY_SIZE | ENTRY_MARK_MASK;
}

int searchFreeSpaceIndex(int bytes){
  int curr = 0;
  HeapEntry *l;

  do {
    l = (HeapEntry*)&heap[curr];

    if (!l->length){ //Si la entrada no existe se crea una con la longitud adecuada
      for (int i = curr; i<curr + MAX_HEAP_ENTRY_SIZE; i++){
        HeapEntry *s = (HeapEntry*)&heap[i];
        if(s->length){
          l->length = (i - curr) | ENTRY_MARK_MASK;
          if ((l->length & MAX_HEAP_ENTRY_SIZE) > bytes) return curr;
        }
        if(i == (curr + MAX_HEAP_ENTRY_SIZE) - 1){
          l->length = MAX_HEAP_ENTRY_SIZE | ENTRY_MARK_MASK;
        }
      }
    }

    if (((l->length & MAX_HEAP_ENTRY_SIZE) > bytes) && (l->length & ENTRY_MARK_MASK)) return curr;

    curr += (l->length & MAX_HEAP_ENTRY_SIZE) + sizeof(HeapEntry);
  }while(curr < sizeof(heap));

  return -1;
}

int heapAlloc(int bytes){
  if (bytes > MAX_HEAP_ENTRY_SIZE) return -1;

  HeapEntry *newEntry;
  HeapEntry *newEmptyEntry;
  int index = searchFreeSpaceIndex(bytes);

  if(index == -1) return index;

  newEntry = (HeapEntry*)&heap[index];

  newEmptyEntry = (HeapEntry*)&heap[index + bytes + sizeof(HeapEntry)];
  newEmptyEntry->length = ((newEntry->length - bytes) & MAX_HEAP_ENTRY_SIZE) | ENTRY_MARK_MASK;

  newEntry->length = bytes;

  return index + sizeof(HeapEntry);
}