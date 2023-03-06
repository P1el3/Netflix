#ifndef STIVA_H_INCLUDED
#define STIVA_H_INCLUDED
#include "Lista.h"

typedef struct stiva
{
    Lista l;
}*Stiva;

Stiva initStiva(void (*elib)(void*), void (*print)(void*, FILE*));
void push(Stiva s, void* info);
void* pop(Stiva s);

void* extrageStiva(Stiva s, void* info, int (*cmp)(void*,void*));

void distrugeStiva(Stiva s);





#endif // STIVA_H_INCLUDED