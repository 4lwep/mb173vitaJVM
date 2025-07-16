#ifndef METHOD_AREA_H
#define METHOD_AREA_H

#include<loader.h>

typedef struct{
    int *cp;
    int *field_data;
    int *method_data;
    int *code;
} MethodArea;

#endif