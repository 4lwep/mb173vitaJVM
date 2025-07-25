#include<init.h>

int initJVM(char* path){
    initHeap();

    FILE *r = fopen(path, "rb");
    int ma = loadClass(r, -1);
    
    return ma;
}