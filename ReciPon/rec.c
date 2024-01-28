#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Rec{
    char rec[20];
    int brPojavljivanja;
    float frekvencija;
    struct Rec *next;
}Rec;

int ispisiMeni()
{
    char op[10];
    int opcija = 0;
    printf("MENI: \n");
    printf("1. Ucitaj datoteku (sortirano alfabetski)\n");
    printf("2. Ispisi sve reci, njihov broj pojavljivanja i frekvenciju\n");
    printf("3. Ispisi reci po broju pojavljivanja (opadajuce)\n");
    printf("4. Izadji iz programa\n");
    while(opcija < 1 || opcija > 4){
        printf("Izaberite opciju: ");
        fgets(op, 10, stdin);
        op[strlen(op) - 1] = 0;
        opcija = atoi(op);
    }
    return opcija;
}

Rec *dodajSortirano(Rec *lista, Rec* noviElement)
{
    if(!lista){
        return noviElement;
    }
    if(strcmp(lista->rec, noviElement->rec) > 0){
        noviElement->next = lista;
        return noviElement;
    }
    lista->next = dodajSortirano(lista->next, noviElement);
    return lista;
}

Rec *ucitajListu()
{
    Rec *lista = NULL;
    char naziv[100], string[30];
    int n = 0;
    FILE *f;
    printf("Unesite ime datoteke: ");
    fgets(naziv, 100, stdin);
    naziv[strlen(naziv) - 1] = 0;
    if(f = fopen(naziv, "r")){
        while(!feof(f)){
            int flag = 0;
            fscanf(f, "%s", string);
            n += 1;
            Rec *pocetak = lista;
            while(pocetak){
                if(strcmp(pocetak->rec, string) == 0){
                    flag = 1;
                    pocetak->brPojavljivanja += 1;
                }
                pocetak = pocetak->next;
            }
            if(!flag){
                Rec *noviElement = (Rec*) malloc(sizeof(Rec));
                strcpy(noviElement->rec, string);
                noviElement->brPojavljivanja = 1;
                noviElement->next = NULL;
                lista = dodajSortirano(lista, noviElement);
            }
        }
        Rec *p = lista;
        while(p){
            p->frekvencija = (1.0 * p->brPojavljivanja / n);
            p = p->next;
        }
        fclose(f);
        printf("Datoteka je uspesno ucitana\n");
    }else{
        printf("Datoteka ne postoji ili je nije moguce citati\n");
    }
    return lista;
}

void ispisiListu(Rec *lista)
{
    if(!lista){
        return;
    }
    printf("%15s %5d %f\n", lista->rec, lista->brPojavljivanja, lista->frekvencija);
    ispisiListu(lista->next);
}

typedef struct Pom{
    char rec[20];
    int brPojavljivanja;
    struct Pom *next;
}Pom;

Pom *dodaj(Pom *lista, Pom *noviElement)
{
    if(!lista){
        return noviElement;
    }
    if(lista->brPojavljivanja < noviElement->brPojavljivanja){
        noviElement->next = lista;
        return noviElement;
    }
    lista->next = dodaj(lista->next, noviElement);
    return lista;
}

void ispisiSortirano(Rec *lista)
{
    Pom *pocetak = NULL;
    while(lista){
        Pom *noviElement = (Pom*) malloc(sizeof(Pom));
        strcpy(noviElement->rec, lista->rec);
        noviElement->brPojavljivanja = lista->brPojavljivanja;
        noviElement->next = NULL;
        pocetak = dodaj(pocetak, noviElement);
        lista = lista->next;
    }
    while(pocetak){
        printf("%15s %5d\n", pocetak->rec, pocetak->brPojavljivanja);
        Pom *t = pocetak;
        pocetak = pocetak->next;
        free(t);
    }
}

Rec *brisiListu(Rec *lista)
{
    if(!lista){
        return NULL;
    }
    Rec *t = lista->next;
    free(lista);
    brisiListu(t);
}

int main()
{
    Rec *reci = NULL;
    int opcija;
    while(1){
        opcija = ispisiMeni();
        switch(opcija){
            case 1:{
                reci = brisiListu(reci);
                reci = ucitajListu();
                break;
            }
            case 2:{
                ispisiListu(reci);
                break;
            }
            case 3:{
                ispisiSortirano(reci);
                break;
            }
            case 4:{
                reci = brisiListu(reci);
                return 0;
            }
        }
    }
}
