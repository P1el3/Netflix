#ifndef COADA_H_INCLUDED
#define COADA_H_INCLUDED
#include "Lista.h"


typedef struct coada
{
    Lista l;
}*Coada;

Coada initCoada(void (*elib)(void*), void (*print)(void*, FILE*));
int nq(Coada s, void* info);
void* dq(Coada s);

void* extrageCoada(Coada s, void* info, int (*cmp)(void*,void*));

void distrugeCoada(Coada s);




#endif // COADA_H_INCLUDED