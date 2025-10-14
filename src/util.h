#ifndef UTIL_H
#define UTIL_H

#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<malloc.h>

#define NOT_FOUND -1
#define NEW_LINE "\n"
#define TRUE 1
#define FALSE 0

uint8_t loadU8(FILE *r);
uint16_t loadU16(FILE *r);
uint32_t loadU32(FILE *r);
uint64_t loadU64(FILE *r);
char *strconcat(char *original, char *sufix);

#endif