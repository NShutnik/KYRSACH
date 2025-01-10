#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SHOOTERS 100
#define MAX_NAME_LEN 20

float findAverage(int(*)[100], int, int);
int findMax(int(*)[100], int, int);
int findMin(int(*)[100], int, int);
int sum_points(int(*), int);

/*
* функция для создания и обновления значений в файл results.txt
* a - матрица значений выстрелов
* names - массив строк имен стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* возвращается тип void
* в файл сохраняется текущая таблица: имена и значения выстрелов
* также, статистические значения
*/
void exportDataToFile(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int n) {
    FILE *file = fopen("results.txt", "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла!\n");
        return;
    }

    fprintf(file, "Таблица результатов:\n");
    for (int i = 0; i < L; i++) {
        fprintf(file, "%s: ", names[i]);
        for (int j = 0; j < n; j++) {
            fprintf(file, "%d ", a[i][j]);
        }
        fprintf(file, "\n");
    }


    fprintf(file, "\nАнализ результатов:\n");
    fprintf(file, "Средний результат: %.2f\n", findAverage(a, L, n));
    fprintf(file, "Максимальный результат: %d\n", findMax(a, L, n));
    fprintf(file, "Минимальный результат: %d\n", findMin(a, L, n));

    fprintf(file, "\nОчки каждого стрелка:\n");
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        fprintf(file, "%s: %d очков\n", names[i], sum);
    }

    fclose(file);
    printf("Данные успешно экспортированы в файл 'results.txt'\n");
}

/*
* функция для того, чтобы поменять значения местами
* arr - передается массив очков
* names - массив строк имен стрелков
* i, j - временные переменные для индексации (смены местами значений выстрелов и имен)
* возвращается тип void
* strcpy - сохраняет значение второго аргумента в первый аргумент
*/
void swap(int* arr, char names[][MAX_NAME_LEN], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    
    char temp_name[MAX_NAME_LEN];
    strcpy(temp_name, names[i]);
    strcpy(names[i], names[j]);
    strcpy(names[j], temp_name);
}
