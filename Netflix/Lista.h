#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

typedef struct cel
{
    void *info;
    struct cel *urm;
}Celula;

typedef struct l
{
    Celula *prim;

    void (*elib)(void*);
    void  (*print)(void*, FILE*);
}*Lista;

Lista initLista(void (*elib)(void*), void (*print)(void*, FILE*));

void inserare(Lista l, void *info, int *pos);
void inserareOrdonata(Lista l, void *info, int *pos, int (*cmp)(void*,void*));
void inserarePrimul(Lista l, void *info);
void inserarePePozitie(Lista l, void *info, int pos);

void* cautare(Lista l, void *info, int (*cmp)(void*, void*));
void* extragere(Lista l, void *info, int (*cmp)(void*, void*));
void* extragerePrimul(Lista l);

void distruge(Lista l);
void sterge(Lista l, void *info, int (*cmp)(void*, void*));
void stergePrimul(Lista l);

void afisare(Lista l, FILE *f);
#endif // LISTA_H_INCLUDED
