#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void swap(int* arr, char names[][20], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    
    char temp_name[20];
    strcpy(temp_name, names[i]);
    strcpy(names[i], names[j]);
    strcpy(names[j], temp_name);
}

void bubbleSort(int arr[], char names[][20], int L) {
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

void edit(int matrix[100][100], char names[100][20], int scores[100], int L, int n) {
    int choice;
    printf("Выберите, что редактировать:\n");
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

void analyzeResults(int a[100][100], int L, int n, float *average, int *max, int *min) {
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

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    int L, n;
    int max = 10;
    int min = 1;
    printf("Введите кол-во стрелков: ");
    scanf("%d", &L);
    printf("Введите кол-во выстрелов: ");
    scanf("%d", &n);
    int sum_all[100];
    char name[100][20];
    int a[100][100];

    for (int i = 0; i < L; i++) {
        printf("Имя %d стрелка: ", i + 1);
        scanf("%s", name[i]);
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % (max - min + 1) + min;
        }
    }

    while (1) {
        int ch;
        printf("1 - Вывести таблицу\n");
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
        scanf("%d", &ch);

        if (ch == 1) {
            for (int i = 0; i < L; i++) {
                printf("%s: ", name[i]);
                for (int j = 0; j < n; j++) {
                    printf("%d ", a[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        } else if (ch == 2) {
            for (int i = 0; i < L; i++) {
                int sum = sum_points(a[i], n);
                printf("%s: %d очков\n", name[i], sum);
            }
            printf("\n");
        } else if (ch == 3) {
            int best_score = 0, best_id = 0;
            for (int i = 0; i < L; i++) {
                int sum = sum_points(a[i], n);
                if (sum > best_score) {
                    best_score = sum;
                    best_id = i;
                }
            }
            printf("Лучший стрелок: %s с результатом %d очков\n", name[best_id], best_score);
        } else if (ch == 4) {
            int worst_score = 99999, worst_id = 0;
            for (int i = 0; i < L; i++) {
                int sum = sum_points(a[i], n);
                if (sum < worst_score) {
                    worst_score = sum;
                    worst_id = i;
                }
            }
            printf("Худший стрелок: %s с результатом %d очков\n", name[worst_id], worst_score);
        } else if (ch == 5) {
            int N;
            printf("Введите минимальное количество очков: ");
            scanf("%d", &N);
            for (int i = 0; i < L; i++) {
                int sum = sum_points(a[i], n);
                if (sum >= N) {
                    printf("Участник: %s с результатом %d очков\n", name[i], sum);
                }
            }
        } else if (ch == 6) {
            for (int i = 0; i < L; i++) {
                sum_all[i] = sum_points(a[i], n);
            }
            bubbleSort(sum_all, name, L);
            printf("Отсортированные очки по возрастанию: \n");
            for (int i = 0; i < L; i++) {
                printf("%d ", sum_all[i]);
            }
            printf("\n");
        } else if (ch == 7) {
            printf("Введите имя нового участника: ");
            scanf("%s", name[L]);
            for (int i = 0; i < n; i++) {
                a[L][i] = rand() % (max - min + 1) + min;
            }
            L++;
        } else if (ch == 8) {
            printf("Введите новые результаты для каждого стрелка: \n");
            for (int i = 0; i < L; i++) {
                printf("Результат для %s: ", name[i]);
                scanf("%d", &a[i][n]);
            }
            n++;
        } else if (ch == 9) {
            float average;
            int max_result, min_result;
            analyzeResults(a, L, n, &average, &max_result, &min_result);
            printf("Средний результат: %.2f\n", average);
            printf("Максимальный результат: %d\n", max_result);
            printf("Минимальный результат: %d\n", min_result);
        } else if (ch == 10) {
            FILE *file = fopen("results.txt", "w");
            if (file == NULL) {
                printf("Ошибка при открытии файла!\n");
                continue;
            }

            fprintf(file, "Таблица результатов:\n");
            for (int i = 0; i < L; i++) {
                fprintf(file, "%s: ", name[i]);
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
                fprintf(file, "%s: %d очков\n", name[i], sum);
            }

            fclose(file);
            printf("Данные успешно экспортированы в файл 'results.txt'\n");
        } else if (ch == 11) {
            edit(a, name, sum_all, L, n);
        } 
        
        else if (ch == 0) {
            break;
        } else {
            printf("Некорректный выбор\n");
        }
    }

    return 0;
}
