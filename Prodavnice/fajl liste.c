#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define naziv "prodavnice.txt"

typedef struct Prodavnica
{
    char ime[15];
    char proizvod[15];
    int cena;
    int kolicina;
    struct Prodavnica *next;
}Prodavnica;



int ispisiMeni(){
    char op[15];
    int opcija = 0;
    printf("1. Ucitaj podatke\n");
    printf("2. Ispisi podatke\n");
    printf("5. Izlaz iz programa i brisanje liste\n");
    while(opcija < 1 || opcija > 5)
    {
        printf("Unesite opciju: ");
        fgets(op, 15, stdin);
        op[strlen(op)-1] = 0;
        opcija = atoi(op);
    }
    return opcija;
}

Prodavnica *sortirajElemente(Prodavnica *head, Prodavnica *new)
{
    if (!head)
        return new;

    // Usporedba po nazivu
    int rezultatUsporedbe = strcmp(head->ime, new->ime);

    // Ako su nazivi jednaki, usporedi po količini
    if (rezultatUsporedbe == 0) {
        if (head->kolicina > new->kolicina) {
            new->next = head;
            return new;
        }
    }
    // Ako je naziv "veći" (u smislu leksikografskog redoslijeda), ubaci novi element ispred
    else if (rezultatUsporedbe > 0) {
        new->next = head;
        return new;
    }

    // Ako nije pronađeno mjesto za ubacivanje, rekurzivno sortiraj ostatak liste
    head->next = sortirajElemente(head->next, new);

    return head;
}

Prodavnica *ucitajPodatke()
{
    char string[100], *token;
    Prodavnica *head = NULL;
    FILE *f;
    if(f = fopen(naziv, "r"))
    {
        while(fgets(string, 100, f) == string)
        {
            Prodavnica *new = malloc(sizeof(Prodavnica));
            token = strtok(string, ",");
            strcpy(new->ime, token);
            token = strtok(NULL, ",");
            strcpy(new->proizvod, token);
            token = strtok(NULL, ",");
            new->cena = atoi(token);
            token = strtok(NULL, " \n");
            new->kolicina = atoi(token);
            new->next = NULL;
            head = sortirajElemente(head, new);

        }
        fclose(f);
        printf("Datoteka je uspesno ucitana!\n");
    }
    else
    {
        printf("Datoteka NIJE uspesno ucitana!\n");
    }
    return head;
}

void ispisi(Prodavnica *head)
{
    if(!head)
        return;
    printf("%s %s %i %i\n", head->ime, head->proizvod, head->cena, head->kolicina);
    ispisi(head->next);
}

void izbrisi(Prodavnica *head)
{
    if(!head)
        return;
    izbrisi(head->next);
    free(head);
}



int main()
{
    Prodavnica *head = NULL;
    int opcija;
    while(1)
    {
        opcija = ispisiMeni();
        switch(opcija)
        {
            case 1:{
                head = ucitajPodatke();
                break;
            }
            case 2:{
                ispisi(head);
                break;
            }
            case 3:{
            }
            case 5:{
                izbrisi(head);
                return 0;
                break;
            }
        }
    }

}



