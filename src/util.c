#include "util.h"

uint8_t loadU8(FILE *r){
    unsigned char bytes[1];
    
    while(!fread(bytes, 1, 1, r));
    
    return (uint8_t)bytes[0];
}

uint16_t loadU16(FILE *r){
    unsigned char bytes[2];
    
    while(!fread(bytes, 2, 1, r));
    
    return (uint16_t)bytes[0] << 8 | (uint16_t)bytes[1];
}

uint32_t loadU32(FILE *r){
    unsigned char bytes[4];
    
    while(!fread(bytes, 1, 4, r));
    
    return ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) | ((uint32_t)bytes[2] << 8)  |  (uint32_t)bytes[3];
}

uint64_t loadU64(FILE *r){
    unsigned char bytes[8];
    
    while(!fread(bytes, 8, 1, r));
    
    return ((uint64_t)bytes[0] << 56) | ((uint64_t)bytes[1] << 48) |
           ((uint64_t)bytes[2] << 40) | ((uint64_t)bytes[3] << 32) |
           ((uint64_t)bytes[4] << 24) | ((uint64_t)bytes[5] << 16) |
           ((uint64_t)bytes[6] << 8)  |  (uint64_t)bytes[7];
}

char *strconcat(char *original, char *sufix){
    int size = strlen(original) + strlen(sufix) + 1;
    char *copy = malloc(size);
    strcpy(copy, original);

    strcat(copy, sufix);

    return copy;
}