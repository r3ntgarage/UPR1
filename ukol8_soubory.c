#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void prevod_na_male(char *str) {
    if (str == NULL) {
        return;
    }
    for (; *str; str++) {
        *str = tolower((unsigned char)*str);
    }
}

char *hledaniretezce(char *vstupniradek, char *hledanyretezec, int ignorovani) {
    if (vstupniradek == NULL || hledanyretezec == NULL) {
        return NULL;
    }

    if(ignorovani == 1) {
        char vstupniradek_kopie[100];
        char hledanyretezec_kopie[100];

        strncpy(vstupniradek_kopie, vstupniradek, sizeof(vstupniradek_kopie) - 1);
        strncpy(hledanyretezec_kopie, hledanyretezec, sizeof(hledanyretezec_kopie) - 1);
        

        prevod_na_male(vstupniradek_kopie);
        prevod_na_male(hledanyretezec_kopie);

        return strstr(vstupniradek_kopie, hledanyretezec_kopie);
    }

    return strstr(vstupniradek, hledanyretezec);
}

    int main(int argc, char** argv[])
{
    
	char *vstup = NULL;
    char *vystup = NULL;
    char *hledane = NULL;
    int ignorovanivelikosti = 0;

    for(int i = 1; i < argc; i++) {
        if(strcmp(*argv[i], "-i") == 0) {
            ignorovanivelikosti = 1;
        }

        else if(strcmp(*argv[i], "-o") == 0) {
            if(i + 1 < argc) {
                *vystup = **argv[i + 1];
            }
            else {
                fprintf(stderr, "Chyba v zadani vystupu!\n");
                return 1;
            }
        }

        else if (vstup == NULL) {
            vstup = *argv[i];
        } 
        else if (hledane == NULL) {
            hledane = *argv[i];
        }
    }

    if(hledane == NULL) {
        fprintf(stderr, "Chyba v zadani hledaneho slova!\n");
        return 1;
    }

    FILE *vstupni_soubor = fopen(vstup, "r");

    FILE *vystupni_soubor = fopen(vystup, "w");

    char radek[100];

    fgets(radek, sizeof(radek), vstupni_soubor);
    radek[strcspn(radek, "\n")] = '0';

    hledaniretezce(radek, hledane, ignorovanivelikosti);

    if(vystupni_soubor != NULL) {
        fprintf(vystupni_soubor, "%s", radek);
    }

    if(vystupni_soubor == NULL) {
        printf("%s", radek);
    }




    fclose(vstupni_soubor);
    fclose(vystupni_soubor);

    return 0;
}