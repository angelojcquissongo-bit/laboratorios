#pragma once
#pragma once
#define NAME_LEN 50
#define COLS 3  // 0 — somme, 1 — % du total, 2 — rang
#define MAX 100

__declspec(dllimport) void add_category(char categories[][NAME_LEN], float sums[], int* count);
__declspec(dllimport) void show_categories(char categories[][NAME_LEN], float sums[], int count);
__declspec(dllimport) void calc_total(float sums[], int count);
__declspec(dllimport) void save_data(char categories[][NAME_LEN], float sums[], int count);
__declspec(dllimport) void load_data(char categories[][NAME_LEN], float sums[], int* count);
__declspec(dllimport) void build_matrix(float sums[], int count, float table[][COLS]);
__declspec(dllimport) void show_matrix(char categories[][NAME_LEN], float table[][COLS], int count);