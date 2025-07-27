#include<init.h>

int pc = -1;
MaHashMap *ma_hashmap;

int initJVM(char* path){
    initHeap();
    ma_hashmap = malloc(sizeof(MaHashMap));

    FILE *r = fopen(path, "rb");
    int ma = loadClass(r, -1);

    initFirstFrame(ma);
    
    return ma;
}