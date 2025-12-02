#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

double* full_elements(double* ptr_array, int size); // заполнение массива значениями
int put_elements(double* ptr_array, int size); // печать элементов массива
double* calc_elements(double* ptr_array, int size); // обработка элементов массива
double sum_elements(double* ptr_array, int begin, int end); // вычисление суммы элементов массива от индекса begin до индекса end включительно
int find_element(double* ptr_array, int n, double element); // поиск элемента а
int function(double* ptr_array, int n, double element); // Вычисление индекса минимального положительного элемента, большего заданного значения А
int lr11(int num);
void print_result(int sum, int min, int max);

double* fill_random(double* ptr_array, int size);
int delete_k(double* ptr_arr, int size, double element);
int find_last_negative(double* ptr_arr, int size);
double* insert(double* ptr_arr, int* size, int index, double num);

int main() {
	setlocale(LC_ALL, "");
    srand(time(NULL)); // Генератор чисел

	double* ptr_array;
    int size, begin = 6, end = 8, n = -1;
    double element;

    printf("Введите размер массива: ");
    scanf("%d", &size);

	ptr_array = (double*)malloc(size * sizeof(double));

	if (ptr_array == NULL) {

		puts("error");

		return -1;
	}

	full_elements(ptr_array, size);

    printf("Начальный массив: ");
    put_elements(ptr_array, size);

    calc_elements(ptr_array, size);

    printf("\nМассив после изменения: ");
    put_elements(ptr_array, size);

    printf("\n\nСумма элементов массива с индексом от %d до %d = %.1lf\n\n", begin, end, sum_elements(ptr_array,begin,end));

    printf("Введите элемент А: ");
    scanf("%lf", &element);

    printf("\nИндекс найденного элемента = %d\n\n", find_element(ptr_array, size, element));

    printf("\nИндекс минимального положительного элемента, большего чем А = %d\n\n", function(ptr_array, size, element));

    free(ptr_array);


    // 11 лаба
    printf("\n\nДомашнее задание к лр 11\n");

    int num;
    printf("Введите размер массива (1-100): ");
    scanf("%d", &num);

    printf("Сумма за исключением min и max: %d\n", lr11(num));


    // 16 лаба

    printf("\n\nЛР 16: часть 2\n");

    int size2;
    printf("Введите размер массива для задания 2: ");
    scanf("%d", &size2);

    double* arr2 = (double*)malloc(size2 * sizeof(double));
    if (arr2 == NULL) {

        puts("error");

        return -1;
    }

    // 2. Заполнение случайными числами от -1 до 1
    fill_random(arr2, size2);
    printf("\nМассив со случайными числами от -1 до 1:\n");
    put_elements(arr2, size2);

    // 2.1 Удаление элементов, значение которых превышает A
    printf("\n\n2.1 Удаление элементов > A \n");
    printf("Введите значение A: ");
    scanf("%lf", &element);

    int new_size = delete_k(arr2, size2, element);
    printf("Массив после удаления элементов:\n");
    put_elements(arr2, new_size);

    // 2.2 Вставка -999 после последнего отрицательного
    printf("\n\n2.2 Вставка -999 после последнего отрицательного\n");
    
    int last_negative_index = find_last_negative(arr2, new_size);

    if (last_negative_index != -1) {
        arr2 = insert(arr2, &new_size, last_negative_index + 1, -999.0);
        printf("Массив после вставки -999:\n");
        put_elements(arr2, new_size);
    }
    else {
        printf("Отрицательных элементов не найдено.\n");
    }

    free(arr2);

    return 0;
}

double* full_elements(double* ptr_array, int size) {
    double start = 1.3, end = 3.4, step = 0.1;
    for (int i = 0; i < size; i++) {
        double x = 1.3 + i * 0.1; 
        ptr_array[i] = 5 * pow(x, 3) + 2 * pow(x, 2) - 15 * x - 6;
    }
    return ptr_array;    
}

int put_elements(double* ptr_array, int size) {
    printf("\na[%d] =", size);

    for (int i = 0; i < size; i++)
    {
        printf(" %.2f", ptr_array[i]);
    }
}

double* calc_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++)
    {
        ptr_array[i] = ceilf(ptr_array[i]);
    }
    return ptr_array;
}

double sum_elements(double* ptr_array, int begin, int end) {
    double sum = 0;
    for (int i = begin; i <= end; i++)
    {
        sum += ptr_array[i];
    }
    return sum;
}

int find_element(double* ptr_array, int n, double element) {
    for (int i = 0; i < n; i++)
    {
        if (fabs(ptr_array[i] - element) < 0.1) return i;
    }
    return -1;
}

int function(double* ptr_array, int n, double element) {
    int result = -1;

    for (int i = 0; i < n; i++) {
        if (ptr_array[i] > 0 && ptr_array[i] > element) {
            if (result == -1 || ptr_array[i] < ptr_array[result]) {
                result = i;
            }
        }
    }

    return result;
}
// ДЗ к ЛР 11
int lr11(int num) {

    int arr[100], sum = 0, min, max;

    printf("Введите %d чисел: ", num);
    for (int i = 0; i < num; i++) {
        scanf("%d", &arr[i]);
        if (i == 0) {
            min = max = arr[0];
        }
        else {
            if (arr[i] < min) min = arr[i];
            if (arr[i] > max) max = arr[i];
        }
        sum += arr[i];
    }
    print_result(sum, min, max);

    return sum - min - max;
}

void print_result(int sum, int min, int max) {
    printf("Общая сумма: %d\n", sum);
    printf("Минимальный элемент: %d\n", min);
    printf("Максимальный элемент: %d\n", max);
}
 // ЛР 16. Задание 2 - заполнение случайными числами
double* fill_random(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        ptr_array[i] = (rand() % 201 - 100) / 100.0;
    }
    return ptr_array;
}

// ЛР 16. Задание 2.1 - Удаление элементов значение которых превышает A
int delete_k(double* ptr_arr, int size, double element) {
    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (ptr_arr[i] <= element) {
            ptr_arr[new_size] = ptr_arr[i];
            new_size++;
        }
    }

    printf("Удалено элементов: %d\n", size - new_size);
    return new_size;
}

// ЛР 16. Задание 2.2 - Вставка -999 после последнего отрицательного
// Поиск индекса последнего отрицательного элемента
int find_last_negative(double* ptr_arr, int size) {
    int last_index = -1;
    for (int i = 0; i < size; i++) {
        if (ptr_arr[i] < 0) {
            last_index = i;
        }
    }
    return last_index;
}

// Функция вставки элемента в массив
double* insert(double* ptr_arr, int* size, int index, double num) {
    int size_n = (*size) + 1;

    if (ptr_arr == NULL) return NULL;

    double* ptr_arr_n = (double*)realloc(ptr_arr, size_n * sizeof(double));
    if (ptr_arr_n == NULL) return ptr_arr;

    ptr_arr = ptr_arr_n;

    for (int i = size_n - 1; i > index; i--) {
        ptr_arr[i] = ptr_arr[i - 1];
    }

    ptr_arr[index] = num;
    *size = size_n;

    return ptr_arr;
}