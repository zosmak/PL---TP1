#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _abbrev {
    char *abr; // abreviatura
    char *exp; // expansao
    struct _abbrev *next;
} Abbrev;

Abbrev* InsertAbbrev(Abbrev* lst, char* ab, char* ex) {
    Abbrev *cell = (Abbrev*) malloc(sizeof(Abbrev));
    cell->abr = strdup(ab);
    cell->exp = strdup(ex);
    cell->next = lst;
    return cell;
}

void ListAbbrev(Abbrev* lst) {
    if (lst != NULL) {
        printf("%s => %s\n", lst->abr, lst->exp);
        ListAbbrev(lst->next);
    }
}

char* SearchAbbrev(Abbrev* lst, char* ab) {
    if (lst == NULL) return NULL;
    if (strcmp(lst->abr, ab) == 0) {
        return lst->exp;
    } else {
        return SearchAbbrev(lst->next, ab);
    }
}

/*
int main() {
    Abbrev *l = NULL;
    l = InsertAbbrev(l, "ipca", "Instituto P. C. A.");
    l = InsertAbbrev(l, "fcf", "Fut. Clube Fam.");
    l = InsertAbbrev(l, "tub", "Trans. Urb. Braga");
    if (SearchAbbrev(l, "ipca")) printf("IPCA EXISTE!\n");
    if (SearchAbbrev(l, "slb")) printf("SLB EXISTE!\n");
    ListAbbrev(l);
    return 0;
}
*/
