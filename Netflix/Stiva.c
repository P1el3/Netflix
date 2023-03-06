#include "Stiva.h"


Stiva initStiva(void (*elib)(void*), void (*print)(void*, FILE*))
{
    Stiva s = malloc(sizeof(Stiva));
    s -> l = initLista(elib, print);
    return s;
}

void distrugeStiva(Stiva s)
{
    distruge(s -> l);
    free(s);
}

void push(Stiva s, void* info)
{
    inserarePrimul(s -> l, info);
}

void* pop(Stiva s)
{
    return extragerePrimul(s -> l);
}

void* extrageStiva(Stiva s, void* info, int (*cmp)(void*,void*))
{
    Stiva aux = initStiva(s -> l ->elib, NULL);
    
    
    while(s -> l -> prim != NULL && cmp(s -> l -> prim -> info, info) != 0)
    {
        void* a = pop(s);
        push(aux, a);
    }
    void* res = pop(s);
    while(aux -> l -> prim != NULL)
    {
        void *b = pop(aux);
        push(s, b);
    }
    distrugeStiva(aux);
    return res;
}