#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

#define ROWS 7
#define COLS 7

int main() {
    int A[ROWS][COLS] = {
        { 3, -1,  4,  1,  5,  9,  2},
        { 6,  5,  3,  5,  8,  9,  7},
        { 9, -2,  6,  4,  3,  3, -8},
        { 2,  7,  1,  8,  2,  8,  4},
        { 1,  6,  1,  8,  0, -3,  9},
        { 8,  9,  4, 10,  4,  5,  2},
        { 3,  0, -8,  8,  7,  9,  3}
    };

    // ── Affichage de la matrice ──────────────────────────────
    printf("\n  Matrice A (%dx%d) :\n\n", ROWS, COLS);

    // En-tête colonnes
    printf("       ");
    for (int j = 0; j < COLS; j++)
        printf("  j=%-2d", j);
    printf("\n");

    // Séparateur haut
    printf("       ");
    for (int j = 0; j < COLS; j++)
        printf("------");
    printf("\n");

    // Lignes
    for (int i = 0; i < ROWS; i++) {
        printf("  i=%-2d |", i);
        for (int j = 0; j < COLS; j++)
            printf(" %4d ", A[i][j]);
        printf("|\n");
    }

    // Séparateur bas
    printf("       ");
    for (int j = 0; j < COLS; j++)
        printf("------");
    printf("\n");

    // ── Affichage du tableau résultat ───────────────────────
    printf("\n  Résultats (N°12) : somme ligne+colonne du max dans la zone\n\n");

    // En-tête
    printf("  +--------+-------+-------+------------------------------------+\n");
    printf("  |  N°    |   i   |   j   |             Résultat               |\n");
    printf("  +--------+-------+-------+------------------------------------+\n");

    int num = 1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            int max_val = A[i][j];
            int max_r = i, max_c = j;

            // 1. Ligne i, de j jusqu'à la fin (droite)
            for (int c = j; c < COLS; c++) {
                if (A[i][c] > max_val) {
                    max_val = A[i][c];
                    max_r = i;
                    max_c = c;
                }
            }

            // 2. Colonne j, de i jusqu'en bas
            for (int r = i; r < ROWS; r++) {
                if (A[r][j] > max_val) {
                    max_val = A[r][j];
                    max_r = r;
                    max_c = j;
                }
            }

            // 3. Dernière ligne, de colonne 0 jusqu'à j (exclu)
            for (int c = 0; c < j; c++) {
                if (A[ROWS - 1][c] > max_val) {
                    max_val = A[ROWS - 1][c];
                    max_r = ROWS - 1;
                    max_c = c;
                }
            }

            int result = max_r + max_c;
            printf("  |  %-5d |  %-4d |  %-4d |  max=A(%d,%d)=%-4d  =>  %d+%d = %-4d      |\n",
                num++, i, j, max_r, max_c, max_val, max_r, max_c, result);
        }

        // Séparateur entre les lignes de la matrice
        if (i < ROWS - 1)
            printf("  +--------+-------+-------+------------------------------------+\n");
    }

    printf("  +--------+-------+-------+------------------------------------+\n");

    return 0;
}