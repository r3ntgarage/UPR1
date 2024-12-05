#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int den;
    char inicialyakcie[50];
    float hodnotazacatekdne;
    float hodnotakonecdne;
    int pocetobchodu;
} zaznamdne;

void radekakcie(zaznamdne *akcie, int radky) {
    char buffer[100];
    for (int i = 0; i < radky; i++) {
        printf("Zadej radek cislo %d (ve formatu: den,nazevAkcie,zacatek,konec,pocet):\n", i + 1);
        if (fgets(buffer, sizeof(buffer), stdin)) {

            char *token = strtok(buffer, ",");
            if (token) akcie[i].den = atoi(token);

            token = strtok(NULL, ",");
            if (token) strncpy(akcie[i].inicialyakcie, token, sizeof(akcie[i].inicialyakcie) - 1);

            token = strtok(NULL, ",");
            if (token) akcie[i].hodnotazacatekdne = atof(token);

            token = strtok(NULL, ",");
            if (token) akcie[i].hodnotakonecdne = atof(token);

            token = strtok(NULL, ",");
            if (token) akcie[i].pocetobchodu = atoi(token);
        } else {
            printf("Chyba pri nacitani radku.\n");
            break;
        }
    }
}


int main() {
    char nazevakcie[50];
    int pocetradku;

    printf("Zadej nazev akcie a pocet radku: ");
    scanf("%s %d", nazevakcie, &pocetradku);
    getchar();

    if(pocetradku <= 0) {
        printf("Chyba ve vstupu!");
        return 1;
    }

    zaznamdne *akcie = (zaznamdne *)malloc(pocetradku * sizeof(zaznamdne));

    radekakcie(akcie, pocetradku);

    int nejviceprodeje = 0;
    int indexnejviceprodeje;

    for (int i = 0; i < pocetradku; i++) {

        if(strcmp(nazevakcie, akcie[i].inicialyakcie) == 0 && akcie[i].pocetobchodu > nejviceprodeje){

            nejviceprodeje = akcie[i].pocetobchodu;

            indexnejviceprodeje = i;

        }

    }

    if (nejviceprodeje > 0){
        printf("<html>\n<body>\n<div>\n");
        printf("<h1>%s: highest volume</h1>\n", nazevakcie);
        printf("<div>Day: %d</div>\n<div>Start price: %.2f</div>\n",akcie[indexnejviceprodeje].den,akcie[indexnejviceprodeje].hodnotazacatekdne);
        printf("<div>End price: %.2f</div>\n<div>Volume: %d</div>\n",akcie[indexnejviceprodeje].hodnotakonecdne, akcie[indexnejviceprodeje].pocetobchodu);
        printf("</div>\n<table>\n<thead>\n");
        printf("<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n");
        printf("</thead>\n<tbody>\n");

    }

    else{
        printf("<html>\n<body>\n<div>\n");
        printf("Ticker %s was not found\n", nazevakcie);
        printf("</div>\n<table>\n<thead>\n");
        printf("<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n");
        printf("</thead>\n<tbody>\n");

    }

    for(int i = pocetradku - 1; i >= 0; i--){

        if(strcmp(nazevakcie, akcie[i].inicialyakcie) == 0){

            printf("<tr>\n    <td><b>%d</b></td>\n", akcie[i].den);
            printf("    <td><b>%s</b></td>\n", akcie[i].inicialyakcie);
            printf("    <td><b>%.2f</b></td>\n", akcie[i].hodnotazacatekdne);
            printf("    <td><b>%.2f</b></td>\n", akcie[i].hodnotakonecdne);
            printf("    <td><b>%.2f</b></td>\n", akcie[i].hodnotakonecdne-akcie[i].hodnotazacatekdne);
            printf("    <td><b>%d</b></td>\n", akcie[i].pocetobchodu);
            printf("</tr>\n");   
            printf("</tbody>\n</table>\n</body>\n</html>");

        }

        if(strcmp(nazevakcie, akcie[i].inicialyakcie) != 0){

            printf("<tr>\n    <td>%d</td>\n", akcie[i].den);
            printf("    <td>%s</td>\n", akcie[i].inicialyakcie);
            printf("    <td>%.2f</td>\n", akcie[i].hodnotazacatekdne);
            printf("    <td>%.2f</td>\n", akcie[i].hodnotakonecdne);
            printf("    <td>%.2f</td>\n", akcie[i].hodnotakonecdne-akcie[i].hodnotazacatekdne);
            printf("    <td>%d</td>\n", akcie[i].pocetobchodu);
            printf("</tr>\n");
            printf("</tbody>\n</table>\n</body>\n</html>");

        }

    }

    free(akcie);

    return 0;
}