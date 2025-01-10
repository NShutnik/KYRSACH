/*
* Программа: Построение программы вычисления результатов соревнований по стрельбе из лука»
* Автор кода: Сунцов Никита Евгеньевич
* Группа: бОИС-242
* Вариант: 20
*/

#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h" // подключение header файла, где выводится интерфейс
#include "export.h" // подключение header файла, где выводится в файл

#define MAX_SHOOTERS 100 // максимальное кол-во стрелков
#define MAX_NAME_LEN 20 // максимальная длина имени стрелка

/*
* подсчет суммы очков стрелков
* row - массив значений выстрелов определенного стрелка
* n - текущее кол-во выстрелов
* возвращаемый тип int, возвращается сумма очков указанного стрелка
*/
int sum_points(int row[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += row[i];
    }
    return sum;
}

/*
* функция сортировки пузырьком
* arr - массив значений выстрелов стрелков
* names - массив строк с именами стрелков
* L - кол-во стрелков
* возвращает void тип, массив выстрелов и имен сортируется сразу
*/
void bubbleSort(int arr[], char names[][MAX_NAME_LEN], int L) {
    for (int i = 0; i < L - 1; i++) {
        for (int j = 0; j < L - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr, names, j, j + 1);
        }
    }
}

/*
* функция для редактирования значений выстрелов или имен стрелков
* matrix - матрица значений выстрелов стрелков
* names - массив строк имен стрелков
* scores - массив очков стрелков
* L - максимальное кол-во стрелков, для проверки границ
* n - максимальное кол-во выстрелов, для проверки границ
* возвращает void тип, значения имен или выстрелов меняются сразу используя оператор &
*/
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

/*
* нахождение среднего, максимального и минимального значения
* a - матрица значений выстрелов стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* возвращает среднее значение, float тип
*/
float findAverage(int a[MAX_SHOOTERS][MAX_SHOOTERS], int L, int n) {
    int total_sum = 0;
    for (int i = 0; i < L; i++) {
        total_sum += sum_points(a[i], n);
    }
    return total_sum / (float)L;
}

/*
* нахождение максимального значения
* a - матрица значений выстрелов стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* возвращает максимальное значение, int тип
*/
int findMax(int a[MAX_SHOOTERS][MAX_SHOOTERS], int L, int n) {
    int max = 0;
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        if (sum > max) max = sum;
    }
    return max;
}

/*
* нахождение минимального значения
* a - матрица значений выстрелов стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* возвращает минимальное значение, int тип
*/
int findMin(int a[MAX_SHOOTERS][MAX_SHOOTERS], int L, int n) {
    int min = 99999;
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        if (sum < min) min = sum;
    }
    return min;
}

/*
* функция для вывода имен стрелков и суммы очков
* a - массив значений выстрелов
* names - массив строк с именами стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* возвращает void тип, таблица выводится при вызове функции
*/
void displayScores(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int n) {
    printf("\nОчки стрелков:\n");
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        printf("%s: %d очков\n", names[i], sum);
    }
}

/*
* функция для вывода таблицы имен и значений выстрелов
* a - массив значений выстрелов
* names - массив строк с именами стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* возвращает void тип, таблица выводится при вызове функции
*/
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

/*
* функция для нахождения лучшего стрелка
* a - массив значений выстрелов
* names - массив строк с именами стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* возвращает имя лучшего стрелка
*/
char* findBestShooter(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int n) {
    int best_score = 0, best_id = 0;
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        if (sum > best_score) {
            best_score = sum;
            best_id = i;
        }
    }
    return names[best_id];
}

/*
* функция для нахождения худшего стрелка
* a - массив значений выстрелов
* names - массив строк с именами стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* возвращает массив char тип, возвращает имя худшего стрелка
*/
char* findWorstShooter(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int n) {
    int worst_score = 99999, worst_id = 0;
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        if (sum < worst_score) {
            worst_score = sum;
            worst_id = i;
        }
    }
    return names[worst_id];
}

/*
* функция для нахождения стрелков, которые набрали более, чем threshold очков
* a - массив значений выстрелов
* names - массив строк с именами стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* threshold - минимальное кол-во очков для проверки на минимальное значение
* возвращает int тип
*/
int shootersAboveThreshold(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int n, int threshold, char result[][MAX_NAME_LEN]) {
    int count = 0;
    for (int i = 0; i < L; i++) {
        int sum = sum_points(a[i], n);
        if (sum >= threshold) {
            strcpy(result[count], names[i]);
            count++;
        }
    }
    return count;
}

/*
* сортирует массив суммы очков в возрастающем порядке
* a - массив значений выстрелов
* names - массив строк с именами стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* возвращает void тип
* сортирует, используя функцию bubbleSort (сортировка пузырьком)
*/
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

/*
* добавляет нового стрелка
* a - массив значений выстрелов
* names - массив строк с именами стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* возвращает void тип
* используем указатель L для сохранения в матрице и генерации выстрелов для нового стрелка
*/
void addNewShooter(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int *L, int n) {
    printf("\nВведите имя нового участника: ");
    scanf("%s", names[*L]);
    for (int i = 0; i < n; i++) {
        a[*L][i] = rand() % 10 + 1;
    }
    (*L)++;
    printf("Новый стрелок добавлен!\n");
}

/*
* добавляет новые значения выстрелов для всех стрелков
* a - массив значений выстрелов
* names - массив строк с именами стрелков
* L - максимальное кол-во стрелков
* n - максимальное кол-во выстрелов
* возвращает void тип
* используем указатель N для сохранения в матрице и генерации выстрелов для всех стрелка
*/
void addNewShotResults(int a[MAX_SHOOTERS][MAX_SHOOTERS], char names[MAX_SHOOTERS][MAX_NAME_LEN], int L, int *n) {
    printf("\nВведите новые результаты для каждого стрелка:\n");
    for (int i = 0; i < L; i++) {
        printf("Результат для %s: ", names[i]);
        scanf("%d", &a[i][*n]);
    }
    (*n)++;
    printf("Новые результаты добавлены!\n");
}

int main() {
    setlocale(LC_ALL, "RUS"); // поддержка русского языка
    srand(time(NULL));
    int L, n; // L - кол-во стрелков, n - кол-во выстрелов
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
            a[i][j] = rand() % 10 + 1; // генерация значений выстрелов в диапазоне от 1 до 10
        }
    }

    while (1) {
        int choice; // переменная, где хранится выбор пользователя
        interface(); // вызов функции из header файла interface.h
        scanf("%d", &choice);

        switch (choice) {
            // если выбор равен 1, то вызывается функция вывода таблицы
            case 1: 
                displayTable(a, names, L, n); 
                break;
            // если выбор равен 2, то вызывается функция вывода суммы очков стрелков
            case 2: 
                displayScores(a, names, L, n); 
                break;
            // если выбор равен 3, то вызывается функция для нахождения лучшего стрелка
            case 3: 
                printf("Лучший стрелок: %s\n", findBestShooter(a, names, L, n));
                break;
            // если выбор равен 4, то вызывается функция для нахождения худшего стрелка
            case 4:  
                printf("Худший стрелок: %s\n", findWorstShooter(a, names, L, n));
                break;
            // если выбор равен 5, то нужно ввести кол-во очков и вызывается функция для нахождения игроков более чем threshold очков
            case 5: {
                int threshold;
                printf("Введите пороговое значение: ");
                scanf("%d", &threshold);

                char result[MAX_SHOOTERS][MAX_NAME_LEN];
                int count = shootersAboveThreshold(a, names, L, n, threshold, result);

                printf("Стрелки с результатами выше %d:\n", threshold);
                for (int i = 0; i < count; i++) {
                    printf("%s\n", result[i]);
                }
                break;
            }
            // если выбор равен 6, то вызывается функция сортировки
            case 6: 
                sortByScores(a, names, L, n); 
                break;
            // если выбор равен 7, то вызывается функция для добавления нового стрелка
            case 7: 
                addNewShooter(a, names, &L, n); 
                break; // &L - для обновления значения нового стрелка и его имя в матрицу, работа с памятью
            // если выбор равен 8, то вызывается функция для добавления новый значений выстрелов
            case 8: 
                addNewShotResults(a, names, L, &n); 
                break; // &n - для обновления значений в новом столбце
            // если выбор равен 9, то вызывается функция для статистических вычислений
            case 9: {
                printf("Средний результат: %.2f\n", findAverage(a, L, n));
                printf("Максимальный результат: %d\n", findMax(a, L, n));
                printf("Минимальный результат: %d\n", findMin(a, L, n));
                break;
            }
            // если выбор равен 10, то вызывается функция из header файла export.h
            case 10: 
                exportDataToFile(a, names, L, n); 
                break;
            // если выбор равен 11, то вызывается функция для редактирования значения имени или выстрелов
            case 11: 
                edit(a, names, scores, L, n); 
                break;
            // если выбор 0, то программа завершается
            case 0: 
                return 0;
            // в остальных случаях, выводится текст: "Некорректный выбор"
            default: 
                printf("Некорректный выбор\n"); 
                break;
        }
    }

    return 0;
}
