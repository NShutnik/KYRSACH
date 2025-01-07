#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SHOOTERS 100
#define MAX_NAME_LEN 20

void swap(int* arr, char names[][MAX_NAME_LEN], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    
    char temp_name[MAX_NAME_LEN];
    strcpy(temp_name, names[i]);
    strcpy(names[i], names[j]);
    strcpy(names[j], temp_name);
}

void bubbleSort(int arr[], char names[][MAX_NAME_LEN], int L) {
    for (int i = 0; i < L - 1; i++) {
        for (int j = 0; j < L - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr, names, j, j + 1);
        }
    }
}

int sum_points(int row[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += row[i];
    }
    return sum;
}

void edit(int matrix[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int scores[MAX_SHOOTERS], int L, int n) {
    int choice;
    printf("\nВыберите, что редактировать:\n");
    printf("1. Имя стрелка\n");
    printf("2. Значение выстрела\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int index;
        printf("Введите номер стрелка (1-%d): ", L);
        scanf("%d", &index);
        if (index < 1 || index > L) {
            printf("Неверный номер стрелка!\n");
            return;
        }
        index--;

        printf("Текущее имя: %s\n", names[index]);
        printf("Введите новое имя: ");
        scanf("%s", names[index]);
        printf("Имя успешно обновлено!\n");
    } else if (choice == 2) {
        int row, col;
        printf("Введите номер стрелка (1-%d): ", L);
        scanf("%d", &row);
        printf("Введите номер выстрела (1-%d): ", n);
        scanf("%d", &col);

        if (row < 1 || row > L || col < 1 || col > n) {
            printf("Неверные координаты!\n");
            return;
        }
        row--;
        col--;

        printf("Текущее значение: %d\n", matrix[row][col]);
        printf("Введите новое значение (1-10): ");
        scanf("%d", &matrix[row][col]);

        if (matrix[row][col] < 1 || matrix[row][col] > 10) {
            printf("Неверное значение!\n");
            return;
        }

        scores[row] = sum_points(matrix[row], n);
        printf("Значение успешно обновлено!\n");
    } else {
        printf("Неверный выбор!\n");
    }
}

void analyzeResults(int a[MAX_SHOOTERS][MAX_SHOOTERS], int L, int n, float *average, int *max, int *min) {
    int total_sum = 0;
    *max = 0;
    *min = 99999;

    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        total_sum += sum;
        if (sum > *max) *max = sum;
        if (sum < *min) *min = sum;
    }

    *average = total_sum / (float)L;
}

void displayTable(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int n) {
    printf("\nТаблица результатов:\n");
    for (int i = 0; i < L; i++) {
        printf("%s: ", names[i]);
        for (int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void displayScores(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int n) {
    printf("\nОчки стрелков:\n");
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        printf("%s: %d очков\n", names[i], sum);
    }
}

void findBestShooter(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int n) {
    int best_score = 0, best_id = 0;
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        if (sum > best_score) {
            best_score = sum;
            best_id = i;
        }
    }
    printf("\nЛучший стрелок: %s с результатом %d очков\n", names[best_id], best_score);
}

void findWorstShooter(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int n) {
    int worst_score = 99999, worst_id = 0;
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        if (sum < worst_score) {
            worst_score = sum;
            worst_id = i;
        }
    }
    printf("\nХудший стрелок: %s с результатом %d очков\n", names[worst_id], worst_score);
}

void shootersAboveThreshold(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int n, int threshold) {
    printf("\nСтрелки набравшие более %d очков:\n", threshold);
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        if (sum >= threshold) {
            printf("%s с результатом %d очков\n", names[i], sum);
        }
    }
}

void sortByScores(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int n) {
    int sum_all[MAX_SHOOTERS];
    for (int i = 0; i < L; i++) {
        sum_all[i] = sum_points(a[i], n);
    }
    bubbleSort(sum_all, names, L);
    printf("\nОтсортированные очки по возрастанию:\n");
    for (int i = 0; i < L; i++) {
        printf("%s: %d очков\n", names[i], sum_all[i]);
    }
}

void addNewShooter(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int *L, int n) {
    printf("\nВведите имя нового участника: ");
    scanf("%s", names[*L]);
    for (int i = 0; i < n; i++) {
        a[*L][i] = rand() % 10 + 1;
    }
    (*L)++;
    printf("Новый стрелок добавлен!\n");
}

void addNewShotResults(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int *n) {
    printf("\nВведите новые результаты для каждого стрелка:\n");
    for (int i = 0; i < L; i++) {
        printf("Результат для %s: ", names[i]);
        scanf("%d", &a[i][*n]);
    }
    (*n)++;
    printf("Новые результаты добавлены!\n");
}

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

    float average;
    int max_result, min_result;
    analyzeResults(a, L, n, &average, &max_result, &min_result);

    fprintf(file, "\nАнализ результатов:\n");
    fprintf(file, "Средний результат: %.2f\n", average);
    fprintf(file, "Максимальный результат: %d\n", max_result);
    fprintf(file, "Минимальный результат: %d\n", min_result);

    fprintf(file, "\nОчки каждого стрелка:\n");
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        fprintf(file, "%s: %d очков\n", names[i], sum);
    }

    fclose(file);
    printf("Данные успешно экспортированы в файл 'results.txt'\n");
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    int L, n;
    printf("Введите кол-во стрелков: ");
    scanf("%d", &L);
    printf("Введите кол-во выстрелов: ");
    scanf("%d", &n);

    int scores[MAX_SHOOTERS];
    char names[MAX_SHOOTERS][MAX_NAME_LEN];
    int a[MAX_SHOOTERS][MAX_SHOOTERS];

    for (int i = 0; i < L; i++) {
        printf("Имя %d стрелка: ", i + 1);
        scanf("%s", names[i]);
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % 10 + 1;
        }
    }

    while (1) {
        int choice;
        printf("\n1 - Вывести таблицу\n");
        printf("2 - Очки стрелков\n");
        printf("3 - Лучший стрелок\n");
        printf("4 - Худший стрелок\n");
        printf("5 - Стрелки набравшие более N очков\n");
        printf("6 - Сортировка по очкам\n");
        printf("7 - Добавить нового стрелка\n");
        printf("8 - Добавить новые результаты выстрела\n");
        printf("9 - Анализ таблицы\n");
        printf("10 - Экспортировать данные в файл\n");
        printf("11 - Редактировать данные\n");
        printf("0 - Выйти\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayTable(a, names, L, n); break;
            case 2: displayScores(a, names, L, n); break;
            case 3: findBestShooter(a, names, L, n); break;
            case 4: findWorstShooter(a, names, L, n); break;
            case 5: {
                int threshold;
                printf("Введите минимальное количество очков: ");
                scanf("%d", &threshold);
                shootersAboveThreshold(a, names, L, n, threshold);
                break;
            }
            case 6: sortByScores(a, names, L, n); break;
            case 7: addNewShooter(a, names, &L, n); break;
            case 8: addNewShotResults(a, names, L, &n); break;
            case 9: {
                float average;
                int max_result, min_result;
                analyzeResults(a, L, n, &average, &max_result, &min_result);
                printf("Средний результат: %.2f\n", average);
                printf("Максимальный результат: %d\n", max_result);
                printf("Минимальный результат: %d\n", min_result);
                break;
            }
            case 10: exportDataToFile(a, names, L, n); break;
            case 11: edit(a, names, scores, L, n); break;
            case 0: return 0;
            default: printf("Некорректный выбор\n"); break;
        }
    }

    return 0;
}
