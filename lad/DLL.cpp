#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX      100
#define NAME_LEN 50
#define COLS     3
#define FILENAME "loisirs.txt"

// ── Utilitaire interne ───────────────────────────────────────
static void print_separator(int width) {
    printf("  +");
    for (int i = 0; i < width; i++) printf("-");
    printf("+\n");
}

// ────────────────────────────────────────────────────────────
__declspec(dllexport)
void add_category(char categories[][NAME_LEN], float sums[], int* count) {
    if (*count >= MAX) {
        printf("  Impossible d'ajouter plus de categories!\n");
        return;
    }
    printf("  Nom de la categorie : ");
    fgets(categories[*count], NAME_LEN, stdin);
    categories[*count][strcspn(categories[*count], "\n")] = '\0';

    printf("  Depense (euros)     : ");
    scanf("%f", &sums[*count]);
    getchar();

    (*count)++;
    printf("  Categorie ajoutee!\n");
}

// ────────────────────────────────────────────────────────────
__declspec(dllexport)
void show_categories(char categories[][NAME_LEN], float sums[], int count) {
    if (count == 0) { printf("  Aucune donnee.\n"); return; }

    printf("\n");
    print_separator(46);
    printf("  | %-4s | %-24s | %-10s |\n", "N.", "Categorie", "Depense");
    print_separator(46);
    for (int i = 0; i < count; i++)
        printf("  | %-4d | %-24s | %8.2f   |\n", i + 1, categories[i], sums[i]);
    print_separator(46);
}

// ────────────────────────────────────────────────────────────
__declspec(dllexport)
void calc_total(float sums[], int count) {
    if (count == 0) { printf("  Aucune donnee.\n"); return; }

    float total = 0.0f;
    int   max_i = 0, min_i = 0;

    for (int i = 0; i < count; i++) {
        total += sums[i];
        if (sums[i] > sums[max_i]) max_i = i;
        if (sums[i] < sums[min_i]) min_i = i;
    }

    printf("\n");
    print_separator(46);
    printf("  | %-44s |\n", "  Statistiques");
    print_separator(46);
    printf("  | Total des depenses    : %18.2f eur |\n", total);
    printf("  | Categorie max (N.%2d)  : %18.2f eur |\n", max_i + 1, sums[max_i]);
    printf("  | Categorie min (N.%2d)  : %18.2f eur |\n", min_i + 1, sums[min_i]);
    printf("  | Moyenne par categorie : %18.2f eur |\n", total / count);
    print_separator(46);
}

// ────────────────────────────────────────────────────────────
__declspec(dllexport)
void save_data(char categories[][NAME_LEN], float sums[], int count) {
    if (count == 0) { printf("  Aucune donnee a sauvegarder.\n"); return; }

    FILE* f = fopen(FILENAME, "w");
    if (!f) { printf("  Erreur ouverture fichier!\n"); return; }

    fprintf(f, "%d\n", count);
    for (int i = 0; i < count; i++)
        fprintf(f, "%s\n%.2f\n", categories[i], sums[i]);

    fclose(f);
    printf("  Donnees sauvegardees dans '%s'.\n", FILENAME);
}

// ────────────────────────────────────────────────────────────
__declspec(dllexport)
void load_data(char categories[][NAME_LEN], float sums[], int* count) {
    FILE* f = fopen(FILENAME, "r");
    if (!f) { printf("  Fichier '%s' introuvable.\n", FILENAME); return; }

    fscanf(f, "%d\n", count);
    for (int i = 0; i < *count; i++) {
        fgets(categories[i], NAME_LEN, f);
        categories[i][strcspn(categories[i], "\n")] = '\0';
        fscanf(f, "%f\n", &sums[i]);
    }
    fclose(f);
    printf("  Donnees chargees depuis '%s'.\n", FILENAME);
}

// ────────────────────────────────────────────────────────────
// table[i][0] = depense
// table[i][1] = % du total
// table[i][2] = rang (1 = plus eleve)
__declspec(dllexport)
void build_matrix(float sums[], int count, float table[][COLS]) {
    float total = 0.0f;
    for (int i = 0; i < count; i++) total += sums[i];

    for (int i = 0; i < count; i++) {
        table[i][0] = sums[i];
        table[i][1] = (total > 0) ? (sums[i] / total * 100.0f) : 0.0f;

        // Rang : nombre d'elements >= sums[i]
        int rang = 1;
        for (int j = 0; j < count; j++)
            if (sums[j] > sums[i]) rang++;
        table[i][2] = (float)rang;
    }
}

// ────────────────────────────────────────────────────────────
__declspec(dllexport)
void show_matrix(char categories[][NAME_LEN], float table[][COLS], int count) {
    if (count == 0) { printf("  Aucune donnee.\n"); return; }

    printf("\n");
    print_separator(58);
    printf("  | %-4s | %-20s | %-10s | %-7s | %-4s |\n",
        "N.", "Categorie", "Depense", "   %  ", "Rang");
    print_separator(58);
    for (int i = 0; i < count; i++) {
        printf("  | %-4d | %-20s | %8.2f eur | %6.2f%% | %4.0f |\n",
            i + 1, categories[i], table[i][0], table[i][1], table[i][2]);
    }
    print_separator(58);
}