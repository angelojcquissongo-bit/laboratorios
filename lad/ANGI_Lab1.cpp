#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main(void) {
    char  categories[MAX][NAME_LEN];
    float sums[MAX];
    int   count = 0;
    int   choice;

    system("chcp 65001 > nul");

    do {
        printf("\n  +=========================================+\n");
        printf("  |   Statistique des depenses de loisirs   |\n");
        printf("  +=========================================+\n");
        printf("  | 1. Ajouter une categorie                |\n");
        printf("  | 2. Afficher les categories              |\n");
        printf("  | 3. Calculer le total et statistiques    |\n");
        printf("  | 4. Sauvegarder dans un fichier          |\n");
        printf("  | 5. Charger depuis un fichier            |\n");
        printf("  | 6. Afficher le tableau 2D               |\n");
        printf("  | 0. Quitter                              |\n");
        printf("  +=========================================+\n");
        printf("  Votre choix : ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            add_category(categories, sums, &count);
            break;
        case 2:
            show_categories(categories, sums, count);
            break;
        case 3:
            calc_total(sums, count);
            break;
        case 4:
            save_data(categories, sums, count);
            break;
        case 5:
            load_data(categories, sums, &count);
            show_categories(categories, sums, count);
            break;
        case 6: {
            if (count == 0) { printf("  Aucune donnee.\n"); break; }
            float table[MAX][COLS];
            build_matrix(sums, count, table);
            show_matrix(categories, table, count);
            break;
        }
        case 0:
            printf("\n  Au revoir!\n\n");
            break;
        default:
            printf("  Choix invalide!\n");
        }
    } while (choice != 0);

    return 0;
}