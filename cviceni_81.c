#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

    char jmeno[50];
    int vek;
    float prumer;
} Student;

void pridat_studenta(Student *studenti, int *pocet) {

    printf("Zadej jmeno studenta: \n");
    scanf("%s", &studenti[*pocet].jmeno);
    printf("Zadej vek studenta: \n");
    scanf("%d", &studenti[*pocet].vek);
    printf("Zadej prumer studenta: \n");
    scanf("%.2f", &studenti[*pocet].prumer);
    (*pocet)++;

}

void vypis_studentu(Student *studenti, int pocet) {

    if(pocet == 0) {

        printf("Vypis studentu je prazdny!");

    }
    else {

        printf("\n --- Aktualni studenti ---\n");
        for(int i = 0; i < pocet; i++) {

            printf("Student %d: \n", i + 1);
            printf("Jmeno: %s\n", studenti[i].jmeno);
            printf("Vek: %d\n", studenti[i].vek);
            printf("Prumer: %.2f\n", studenti[i].prumer);

        }

    }
}

int main() {

    Student studenti[5];
    int pocet = 0;
    int volba = 0;

    while(1) {
        printf("1 - Pridej studenta\n");
        printf("2 - Vypis studentu\n");
        printf("3 - Konec programu\n");
        printf("Zadej volbu: \n");
        scanf("%d", &volba);
        switch(volba) {
            case 1:
                pridat_studenta(studenti,&pocet);
                break;

            case 2:
                vypis_studentu(studenti, pocet);
                break;
            case 3:
                printf("Konec programu!");
                return 0;
            default:
                printf("Neplatny vstup!");
        }

    }

    return 0;
}