#include<init.h>

int pc = -1;

int initJVM(char* path){
    initHeap();

    FILE *r = fopen(path, "rb");
    int ma = loadClass(r, -1);
    
    return ma;
}