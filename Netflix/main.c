#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Lista.h"
#include "Stiva.h"
#include "Coada.h"

typedef struct serial
{
    int id;
    char* nume;
    float rating;
    int nr_sez;
    int time;
    Lista sezoane;
}Serial;

typedef struct sezon
{
    int nr_ep;
    Lista ep_length;
}Sezon;

typedef struct episod
{
    int length;
}Episod;

void delete_episode(void* a)
{
    Episod* sters = (Episod*)a;
    free(sters);

}

void delete_season(void* a)
{
    Sezon* sters = (Sezon*)a;
    distruge(sters -> ep_length);
    free(sters);
}

void delete_serial(void* a)
{
    Serial* sters = (Serial*)a;
    free(sters -> nume);
    distruge(sters -> sezoane);
    free(sters);
}

void print_serial(void* a, FILE* f)
{
    Serial* print = (Serial*)a;
    fprintf(f, "(%s, %.1f)",print -> nume, print -> rating);
}

int cmp_serial(void* a, void* b)
{
    Serial* aux1 = (Serial*)a;
    Serial* aux2 = (Serial*)b;
    if(aux1 -> rating == aux2 -> rating)
    {
        return strcmp(aux1 -> nume, aux2 -> nume);
    }
    else if(aux1 -> rating > aux2 -> rating)
        return -1;
    else return 1;
}

int cmp_nume(void* a, void* b)
{
    Serial* aux1 = (Serial*)a;
    Serial* aux2 = (Serial*)b;
    return strcmp(aux1 -> nume, aux2 -> nume);
}
void top10(Lista l)
{
    int pos=1;
    Celula* c = l -> prim;
    while(pos != 10 && c != NULL)
    {
        c = c -> urm;
        pos++;
    }

    if(c != NULL)
    {
        Celula* next = c -> urm;
        c -> urm = NULL;
        c = next;
        while(c != NULL)
        {
            next = c->urm;
            l->elib(c->info);
            free(c);
            c = next;
        }
    }

}

int main(int argc, char** argv)
{
    Lista Tendinte = initLista(delete_serial, print_serial);
    Lista Documentare = initLista(delete_serial, print_serial);
    Lista Tutoriale_C = initLista(delete_serial, print_serial);
    Lista Top10_Ro = initLista(delete_serial, print_serial);
    Stiva Watching = initStiva(delete_serial, print_serial);
    Coada Watch_Later = initCoada(delete_serial, print_serial);
    Stiva History = initStiva(delete_serial, print_serial);
    Lista vector[4] = {Tendinte, Documentare, Tutoriale_C, Top10_Ro};

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    int pos;
    char v[69];
    while(fscanf(input, "%s", v) == 1)
    {
        if(strcmp(v,"add") == 0)
        {
            Serial* add = (Serial*)malloc(sizeof(Serial));
            add -> sezoane = initLista(delete_season, NULL); //NULL deoarece nu trb sa printez un sez

            add -> nume = (char*)malloc(33*sizeof(char));
            fscanf(input, "%d %s %f %d", &add -> id, add -> nume, &add -> rating, &add -> nr_sez);
            int i;
            for(i = 0; i < add -> nr_sez; i++)
            {
               Sezon* sez = (Sezon*)malloc(sizeof(Sezon));
               sez -> ep_length = initLista(delete_episode, NULL); //NULL deoarece nu trb sa printez un ep
               fscanf(input, "%d", &sez -> nr_ep);
               int j;
               for(j = 0; j < sez -> nr_ep; j++)
               {
                    Episod* ep = (Episod*)malloc(sizeof(Episod));
                    fscanf(input, "%d", &ep -> length);
                    add -> time += ep ->length;

                    inserare(sez -> ep_length, (void*)ep, &pos);
               }
             inserare(add ->sezoane, (void*)sez, &pos);
            }
            if(add -> id == 1)
                inserareOrdonata(Tendinte, (void*)add, &pos, cmp_serial);
            else if(add -> id == 2)
                inserareOrdonata(Documentare, (void*)add, &pos, cmp_serial);
            else if(add -> id == 3)
                inserareOrdonata(Tutoriale_C, (void*)add, &pos, cmp_serial);

            fprintf(output, "Serialul %s a fost adaugat la pozitia %d.\n", add -> nume, pos);
        }

        else if(strcmp(v, "show") == 0)
        {
            char X[11];
            fscanf(input, "%s", X);
            if(strcmp(X, "1") == 0)
            {
                fprintf(output, "Categoria 1: ");
                afisare(Tendinte, output);
                fprintf(output, ".\n");
            }
            else if(strcmp(X, "2") == 0)
            {
                fprintf(output, "Categoria 2: ");
                afisare(Documentare, output);
                fprintf(output, ".\n");
            }
            else if(strcmp(X, "3") == 0)
            {
                fprintf(output, "Categoria 3: ");
                afisare(Tutoriale_C, output);
                fprintf(output, ".\n");
            }
             else if(strcmp(X, "top10") == 0)
            {
                fprintf(output, "Categoria top10: ");
                afisare(Top10_Ro, output);
                fprintf(output, ".\n");
            }
            else if(strcmp(X, "later") == 0)
            {
                fprintf(output, "Categoria later: ");
                afisare(Watch_Later -> l, output);
                fprintf(output, ".\n");
            }
            else if(strcmp(X, "watching") == 0)
            {
                fprintf(output, "Categoria watching: ");
                afisare(Watching -> l, output);
                fprintf(output, ".\n");
            }
            else if(strcmp(X, "history") == 0)
            {
                fprintf(output, "Categoria history: ");
                afisare(History -> l, output);
                fprintf(output, ".\n");
            }
        }

        else if(strcmp(v, "later") == 0)
        {
            Serial* caut = (Serial*)malloc(sizeof(Serial));
            caut -> nume = (char*)malloc(33*sizeof(char));
            fscanf(input, "%s", caut -> nume);
            void* hold = NULL;
            int i;
            for(i = 0; i < 4 && hold == NULL; i++)
                hold = extragere(vector[i], (void*)caut, cmp_nume);
            if(hold == NULL)
                hold = extrageCoada(Watch_Later, (void*) caut, cmp_nume);
            if(hold == NULL)
                hold = extrageStiva(Watching, (void*) caut, cmp_nume);
            if(hold == NULL)
                hold = extrageStiva(History, (void*) caut, cmp_nume);

            int res = nq(Watch_Later, hold);

            fprintf(output, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n", caut -> nume, res);
            free(caut->nume);
            free(caut);
        }

        else if(strcmp(v, "watch") == 0)
        {
            Serial* caut = (Serial*)malloc(sizeof(Serial));
            caut -> nume = (char*)malloc(33*sizeof(char));
            fscanf(input, "%s", caut -> nume);
            int  durata;
            fscanf(input, "%d", &durata);
            void* hold = NULL;
            int i;
            for(i = 0; i < 4 && hold == NULL; i++)
                hold = extragere(vector[i], (void*)caut, cmp_nume);
            if(hold == NULL)
                hold = extrageCoada(Watch_Later, (void*) caut, cmp_nume);
            if(hold == NULL)
                hold = extrageStiva(Watching, (void*) caut, cmp_nume);
            if(hold == NULL)
                hold = extrageStiva(History, (void*) caut, cmp_nume);

            Serial* sr = (Serial*)hold;
            if(sr -> time > durata)
            {
                push(Watching, (void*)sr);
                sr -> time -= durata;
            }
            else
            {
                push(History, (void*)sr);
                fprintf(output, "Serialul %s a fost vizionat integral.\n",caut -> nume);
            }
        }

        else if(strcmp(v, "add_top") == 0)
        {
            Serial* add = (Serial*)malloc(sizeof(Serial));
            add -> sezoane = initLista(delete_season, NULL); //NULL deoarece nu trb sa printez un sez

            add -> nume = (char*)malloc(33*sizeof(char));
            int position;
            fscanf(input, "%d", &position);
            fscanf(input, "%s %f %d", add -> nume, &add -> rating, &add -> nr_sez);
            int i;
            for(i = 0; i < add -> nr_sez; i++)
            {
               Sezon* sez = (Sezon*)malloc(sizeof(Sezon));
               sez -> ep_length = initLista(delete_episode, NULL); //NULL deoarece nu trb sa printez un ep
               fscanf(input, "%d", &sez -> nr_ep);
               int j;
               for(j = 0; j < sez -> nr_ep; j++)
               {
                    Episod* ep = (Episod*)malloc(sizeof(Episod));
                    fscanf(input, "%d", &ep -> length);
                    add -> time += ep ->length;
                    inserare(sez -> ep_length, (void*)ep, &pos);
               }
             inserare(add ->sezoane, (void*)sez, &pos);
            }
            inserarePePozitie(Top10_Ro, (void*)add, position);
            top10(Top10_Ro);
            fprintf(output, "Categoria top10: ");
            afisare(Top10_Ro, output);
            fprintf(output, ".\n");
        }
        else if( strcmp(v,"add_sez") == 0 )
        {
            Serial *caut = (Serial*)malloc(sizeof(Serial));
            caut->nume = (char*)malloc(33*sizeof(char));
            fscanf(input, "%s", caut->nume);
            int sez_time = 0;

            Sezon *nou = (Sezon*)malloc(sizeof(Sezon));
            nou->ep_length = initLista(delete_episode, NULL);
            fscanf(input, "%d", &nou->nr_ep);
            int i;
            for(i = 0; i < nou->nr_ep; i++ )
            {
                Episod *ep = (Episod*)malloc(sizeof(Episod));
                fscanf(input, "%d", &ep->length);
                sez_time += ep->length;
                inserare(nou->ep_length, (void*)ep, &pos);
            }
            void *hold = NULL;
            for(i = 0; i < 4 && hold == NULL; i++ )
                hold = cautare(vector[i], (void*)caut, cmp_nume);
            if( hold == NULL )
                hold = cautare(Watch_Later->l, (void*)caut, cmp_nume);
            if( hold == NULL )
                hold = cautare(Watching->l, (void*)caut, cmp_nume);
            if( hold == NULL )
                hold = cautare(History->l, (void*)caut, cmp_nume);

            Serial *sr = (Serial*)hold;
            inserare(sr->sezoane, (void*)nou, &pos);
            sr->time += sez_time;
            free(caut->nume);
            free(caut);
            fprintf(output, "Serialul %s are un sezon nou.\n", sr->nume);
        }
    }
    fclose(input);
    fclose(output);
    distruge(Tendinte);
    distruge(Documentare);
    distruge(Tutoriale_C);
    distruge(Top10_Ro);
    distrugeStiva(Watching);
    distrugeCoada(Watch_Later);
    distrugeStiva(History);

    return 0;
}