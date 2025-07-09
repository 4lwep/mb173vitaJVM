#include<stdio.h>
#include<malloc.h>

unsigned int loadU8(FILE *r){
    unsigned char bytes[1];
    
    while(!fread(bytes, 1, 1, r));
    
    return bytes[0];
}

unsigned int loadU16(FILE *r){
    unsigned char bytes[2];
    
    while(!fread(bytes, 2, 1, r));
    
    return bytes[0] << 8 | bytes[1];
}

unsigned int loadU32(FILE *r){
    unsigned char bytes[4];
    
    while(!fread(bytes, 1, 4, r));
    
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8)  |  bytes[3];
}

unsigned int loadU64(FILE *r){
    unsigned char bytes[8];
    
    while(!fread(bytes, 8, 1, r));
    
    return (bytes[0] << 56) | (bytes[1] << 48) |
           (bytes[2] << 40) | (bytes[3] << 32) |
           (bytes[4] << 24) | (bytes[5] << 16) |
           (bytes[6] << 8)  |  bytes[7];
}