#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_NAME_LENGTH 100
#define MAX_INGREDIENTS 100
#define MAX_RECIPES 100
#define MAX_LINE_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int count;
} Ingredient;

typedef struct {
    int ingredientCount;
    Ingredient ingredients[MAX_INGREDIENTS];
} Recipe;

// Funkce pro nalezení indexu ingredience podle názvu
int findIngredientIndex(Ingredient ingredients[], int ingredientCount, const char* name) {
    for (int i = 0; i < ingredientCount; i++) {
        if (strcmp(ingredients[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, ""); // Nastavení locale pro správné zobrazení znaků

    if (argc != 3) {
        printf("Usage: %s <number_of_ingredients> <number_of_recipes>\n", argv[0]);
        return 1;
    }

    int ingredientCount = atoi(argv[1]);
    int recipeCount = atoi(argv[2]);

    if (ingredientCount <= 0 || recipeCount <= 0) {
        printf("Both the number of ingredients and recipes must be positive integers.\n");
        return 1;
    }

    // Alokace paměti pro ingredience a recepty
    Ingredient* ingredients = (Ingredient*)malloc(ingredientCount * sizeof(Ingredient));
    Recipe* recipes = (Recipe*)malloc(recipeCount * sizeof(Recipe));

    if (ingredients == NULL || recipes == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Načtení ingrediencí
    printf("Zadejte ingredience ve formátu 'name,count':\n");
    for (int i = 0; i < ingredientCount; i++) {
        char line[MAX_LINE_LENGTH];
        if (!fgets(line, sizeof(line), stdin)) {
            printf("Chyba při čtení ingrediencí.\n");
            free(ingredients);
            free(recipes);
            return 1;
        }
        line[strcspn(line, "\n")] = 0; // Odstranění znaku nového řádku

        char* name = strtok(line, ",");
        char* countStr = strtok(NULL, ",");

        if (name == NULL || countStr == NULL) {
            printf("Chybný formát ingredience: %s\n", line);
            free(ingredients);
            free(recipes);
            return 1;
        }

        strcpy(ingredients[i].name, name);
        ingredients[i].count = atoi(countStr);
    }

    // Načtení receptů
    printf("Zadejte recepty ve formátu 'ingredientCount;name1,count1;name2,count2;...':\n");
    for (int i = 0; i < recipeCount; i++) {
        char line[MAX_LINE_LENGTH];
        if (!fgets(line, sizeof(line), stdin)) {
            printf("Chyba při čtení receptů.\n");
            free(ingredients);
            free(recipes);
            return 1;
        }
        line[strcspn(line, "\n")] = 0; // Odstranění znaku nového řádku

        char* token = strtok(line, ";");
        if (token == NULL) {
            printf("Chybný formát receptu %d.\n", i + 1);
            free(ingredients);
            free(recipes);
            return 1;
        }

        recipes[i].ingredientCount = atoi(token);
        if (recipes[i].ingredientCount <= 0) {
            printf("Chybný počet ingrediencí v receptu %d.\n", i + 1);
            free(ingredients);
            free(recipes);
            return 1;
        }

        for (int j = 0; j < recipes[i].ingredientCount; j++) {
            token = strtok(NULL, ";");
            if (token == NULL) {
                printf("Chybný formát receptu %d.\n", i + 1);
                free(ingredients);
                free(recipes);
                return 1;
            }

            char* name = strtok(token, ",");
            char* countStr = strtok(NULL, ",");

            if (name == NULL || countStr == NULL) {
                printf("Chybný formát ingredience v receptu %d.\n", i + 1);
                free(ingredients);
                free(recipes);
                return 1;
            }

            strcpy(recipes[i].ingredients[j].name, name);
            recipes[i].ingredients[j].count = atoi(countStr);
        }
    }

    // Určení maximálního počtu porcí pro každý recept
    for (int i = 0; i < recipeCount; i++) {
        int portions = 1000000; // Velká hodnota místo INT_MAX

        for (int j = 0; j < recipes[i].ingredientCount; j++) {
            int ingredientIndex = findIngredientIndex(ingredients, ingredientCount, recipes[i].ingredients[j].name);
            if (ingredientIndex == -1) {
                portions = 0; // Chybí-li ingredience, nelze uvařit žádnou porci
                break;
            }

            int possiblePortions = ingredients[ingredientIndex].count / recipes[i].ingredients[j].count;
            if (possiblePortions < portions) {
                portions = possiblePortions;
            }
        }

        // Výstup výsledku pro aktuální recept
        if (portions == 0) {
            printf("Recept %d nelze uvařit ani jednou.\n", i + 1);
        } else {
            printf("Recept %d lze uvařit %dx.\n", i + 1, portions);
        }
    }

    // Uvolnění alokované paměti
    free(ingredients);
    free(recipes);

    return 0;
}