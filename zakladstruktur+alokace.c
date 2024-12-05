#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int den;
    char nazev[100];
    float zacatekdne;
    float konecdne;
    int pocetobchodu;

}zaznamdne;

void radekakcie(zaznamdne *akcie, int radky) {
    char buffer[100];
    for (int i = 0; i < radky; i++) {
        printf("Zadej radek cislo %d (ve formatu: den,nazevAkcie,zacatek,konec,pocet):\n", i + 1);
        if (fgets(buffer, sizeof(buffer), stdin)) {

            char *token = strtok(buffer, ",");
            if (token) akcie[i].den = atoi(token);

            token = strtok(NULL, ",");
            if (token) strncpy(akcie[i].nazev, token, sizeof(akcie[i].nazev) - 1);

            token = strtok(NULL, ",");
            if (token) akcie[i].zacatekdne = atof(token);

            token = strtok(NULL, ",");
            if (token) akcie[i].konecdne = atof(token);

            token = strtok(NULL, ",");
            if (token) akcie[i].pocetobchodu = atoi(token);
        } else {
            printf("Chyba pri nacitani radku.\n");
            break;
        }
    }
}

int main(int argc, char** argv) {

    if(argc < 3) {
        printf("Chyba pri zadani pozadovane akcie!");
    }

    char *hledanaakcie = argv[1];
    int pocetradku = atoi(argv[2]);

    if(hledanaakcie == NULL) {
        printf("Chyba pri zadavani nazvu hledane akcie!");
    }

    if(pocetradku == 0) {
        printf("Chyba pri zadavani poctu akcii!");
    }

    zaznamdne *akcie = (zaznamdne *)malloc(pocetradku * sizeof(zaznamdne));

    radekakcie(akcie, pocetradku);

    for(int i = 0; i < pocetradku; i++) {
        printf("\nDen: %d", akcie[i].den);
        printf("\nNazev akcie: %s", akcie[i].nazev);
        printf("\nHodnota na zacatku dne: %2.f", akcie[i].zacatekdne);
        printf("\nHodnota na konci dne: %2.f", akcie[i].konecdne);
        printf("\nPocet obchodu: %d", akcie[i].pocetobchodu);

    }


    printf("\nHledana akcie: %s", hledanaakcie);

    return 0;
}