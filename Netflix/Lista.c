#include "Lista.h"

Lista initLista(void (*elib)(void*), void (*print)(void*, FILE*))
{
    Lista l = (Lista)malloc(sizeof(struct l));
    l->print =  print;
    l->elib = elib;
    l->prim = NULL;
    return l;
}

Celula* alocareCelula(void *info, Celula *urm)
{
    Celula *new_c = (Celula*)malloc(sizeof(Celula));
    new_c->info = info;
    new_c->urm = urm;
    return new_c;
}

void inserare(Lista l, void *info, int *pos)
{
    *pos = 1;
    if( l->prim == NULL )
        l->prim = alocareCelula(info, NULL);
    else
    {
        *pos = 2;
        Celula *c = l->prim;
        while( c->urm != NULL )
            c = c->urm, (*pos)++;
        c->urm = alocareCelula(info, NULL);
    }
}

void inserareOrdonata(Lista l, void *info, int *pos, int (*cmp)(void*,void*))
{
    *pos = 1;
    if( l->prim == NULL )
        l->prim = alocareCelula(info, NULL);
    else
    {
        if( cmp(info, l->prim->info) < 0 )
        {
            l->prim = alocareCelula(info, l->prim);
            return;
        }

        *pos = 2;
        Celula *c = l->prim;
        while( c->urm != NULL && cmp(info, c->urm->info) > 0 )
            c = c->urm, (*pos)++;
        c->urm = alocareCelula(info, c->urm);
    }
}

void inserarePrimul(Lista l, void *info)
{
    l->prim = alocareCelula(info, l->prim);
}
void inserarePePozitie(Lista l, void *info, int pos)
{
    if( pos == 1)
        l -> prim = alocareCelula(info, l -> prim);
    else
    {
        Celula *c = l->prim;
        while( pos != 2 && c -> urm != NULL)
        {
            c = c -> urm;
            pos--;
        }
        c -> urm = alocareCelula(info, c -> urm);
    }
}

void* cautare(Lista l, void *info, int (*cmp)(void*, void*))
{
    Celula *c = l -> prim;
    while(c != NULL)
    {
        if(cmp(c -> info, info) == 0)
            return c -> info;
        c = c -> urm;
    }
    return NULL;
}

void* extragere(Lista l, void *info, int (*cmp)(void*, void*))
{
    if(l -> prim == NULL)
    {
        return NULL;
    }

    if(cmp(l -> prim -> info, info) == 0)
    {
        Celula *aux = l -> prim;
        void *res = aux -> info;
        l -> prim = l -> prim -> urm;
        free (aux);
        return res;
    }
    Celula *c = l -> prim;
    while(c -> urm != NULL)
    {
        if(cmp(c -> urm -> info, info) == 0)
        {
            Celula *aux = c -> urm;
            void *res = aux -> info;
            c -> urm = c -> urm -> urm;
            free (aux);
            return res;
        }

        c = c -> urm;
    }
    return NULL;
}

void* extragerePrimul(Lista l)
{
    if(l -> prim == NULL)
    {
        return NULL;
    }
    Celula *aux = l -> prim;
    void *res = aux -> info;
    l -> prim = l -> prim -> urm;
    free (aux);
    return res;
}

void stergePrimul(Lista l)
{
    if( l->prim == NULL )
        return;

    Celula *c = l->prim;
    l->prim = l->prim->urm;
    l->elib(c->info);
    free(c);
}

void sterge(Lista l, void *info, int (*cmp)(void*,void*))
{
    if( cmp(l->prim->info, info) == 0 )
        stergePrimul(l);
    else
    {
        Celula *c = l->prim;
        while( c->urm != NULL && cmp(info, c->urm->info) != 0 )
            c = c->urm;

        if( c->urm != NULL )
        {
            Celula *aux = c->urm;
            c->urm = aux->urm;
            l->elib(aux->info);
            free(aux);
        }
    }
}

void distruge(Lista l)
{
    Celula *crt = l->prim;
    Celula *urm;

    while( crt != NULL )
    {
        urm = crt->urm;
        l->elib(crt->info);
        free(crt);
        crt = urm;
    }
    free(l);
}

void afisare(Lista l, FILE* f)
{
    fprintf(f, "[");

    Celula *c = l->prim;
    while( c != NULL )
    {
        l->print(c->info, f);
        if(c -> urm != NULL)
            fprintf(f, ", ");
        c = c->urm;
    }

    fprintf(f, "]");
}
