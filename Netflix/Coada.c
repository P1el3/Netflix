#include "Coada.h"

Coada initCoada(void (*elib)(void*), void (*print)(void*, FILE*))
{
    Coada s = malloc(sizeof(Coada));
    s -> l = initLista(elib, print);
    return s;
}

void distrugeCoada(Coada s)
{
    distruge(s -> l);
    free(s);
}

int nq(Coada s, void* info)
{
    int pos;
    inserare(s -> l, info, &pos);

    return pos;
}

void* dq(Coada s)
{
    return extragerePrimul(s -> l);
}

void* extrageCoada(Coada s, void* info, int (*cmp)(void*,void*))
{
    Coada aux = initCoada(s -> l ->elib, NULL);

    while(s -> l -> prim != NULL && cmp(s -> l -> prim -> info, info) != 0)
    {
        void* a = dq(s);
        nq(aux, a);
    }
    void* res = dq(s);
    while(s -> l -> prim != NULL)
    {
    void* a = dq(s);
    nq(aux, a);
    }

    while(aux -> l -> prim != NULL)
    {
        void *b = dq(aux);
        nq(s, b);
    }
    distrugeCoada(aux);
    return res;
}


