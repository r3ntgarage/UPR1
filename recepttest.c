#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nazev[100];
    int pocet;

}Ingredience;

typedef struct {
    char nazev[100];
    int pocet;

}Ingrediencereceptu;

typedef struct {
    int pocetingrediencireceptu;
    Ingrediencereceptu *ingrediencereceptu;
    

}Recepty;

void spracujingredience(Ingredience *ingredience, int pocetingre) {
    for(int i = 0; i < pocetingre; i++) {
        char radek[100];
        printf("Zadej %d ingredienci a jeji mnozstvi (napr.: 50,Paprika): \n", i + 1);
        if(fgets(radek, sizeof(radek), stdin)) {

            radek[strcspn(radek, "\n")] = '\0';

            char *token = strtok(radek, ",");

            if (token) ingredience[i].pocet = atoi(token);

            token = strtok(NULL, ",");
            if(token) strcpy(ingredience[i].nazev, token);

        }

        else {
            printf("Chyba pri nacitani radku!");
        }
        

    }
}

void spracujrecept() {

}

int main(int argc, char** argv) {

    int pocetingredienci = atoi(argv[1]);
    int pocetreceptu = atoi(argv[2]);

    if(pocetingredienci < 0) {
        printf("Pocet ingredienci nebyl zadan spravne!");
    }

    if(pocetreceptu < 0) {
        printf("Pocet receptu nebyl zadan spravne!");
    }

    Ingredience *ingredience = (Ingredience *)malloc(pocetingredienci * sizeof(Ingredience));

    spracujingredience(ingredience, pocetingredienci);

    Recepty *recepty = (Recepty *)malloc(pocetreceptu * sizeof(Recepty));

    for(int i = 0; i < pocetreceptu; i++) {
        char radek[100];
        printf("Zadej %d recept (napr.: <pocet ingredienci n>; <nazev n-te ingredience>, <mnozstvi n-te ingredience>): ", i + 1);
        if(fgets(radek, sizeof(radek), stdin)) {

            radek[strcspn(radek, "\n")] = '\0';

            char *token = strtok(radek, ",;");

            if(token) recepty[i].pocetingrediencireceptu = atoi(token);

            Ingrediencereceptu * ingrediencereceptu = (Ingrediencereceptu *)malloc(recepty[i].pocetingrediencireceptu * sizeof(Ingrediencereceptu));

            for(int j = 0; j < recepty[i].pocetingrediencireceptu; j++) {
                token = strtok(NULL, ",;");
            if (token) strcpy(ingrediencereceptu[i].nazev, token);

            token = strtok(NULL, ",;");
            if (token) ingrediencereceptu[i].pocet = atoi(token);
            }

            for(int k = 0; k < recepty[i].pocetingrediencireceptu; k++) {
                printf("Ingredience c.%d: \n", k + 1);
                printf("Nazev ingredience: %s\n", ingrediencereceptu[k].nazev);
                printf("Mnozstvi ingredience: %d\n", ingrediencereceptu[k].pocet);
    }

            free(ingrediencereceptu);
        }
    }


    for(int i = 0; i < pocetingredienci; i++) {
        printf("Ingredience c.%d: \n", i + 1);
        printf("Nazev ingredience: %s\n", ingredience[i].nazev);
        printf("Mnozstvi ingredience: %d\n", ingredience[i].pocet);
    }
    

   free(ingredience);
   free(recepty);

    return 0;
}