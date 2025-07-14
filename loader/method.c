#include<method.h>

unsigned int methodCount;

void parseMethods(FILE *r){
    methodCount = loadU16(r);
}