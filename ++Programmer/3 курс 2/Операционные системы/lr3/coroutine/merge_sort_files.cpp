#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define MAX_FILES 3
#define MAX_NUMBERS 1000
#define OUTPUT_FILE_NAME "output.txt"

const std::vector<std::string> inputFiles = { "file1.txt", "file2.txt", "file3.txt" };

// Функция для слияния двух отсортированных массивов в один отсортированный массив
void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L(n1), R(n2);

    // Копируем данные во временные массивы L[] и R[]
    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    // Слияние временных массивов обратно в arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // Копируем оставшиеся элементы L[]
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // Копируем оставшиеся элементы R[]
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// Функция для рекурсивной сортировки массива слиянием
void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        // Находим среднюю точку
        int m = l + (r - l) / 2;

        // Рекурсивно сортируем первую и вторую половины
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Сливаем отсортированные половины
        merge(arr, l, m, r);
    }
}

int main() {
    std::vector<int> allNumbers;
    
    // Чтение чисел из файлов и сортировка
    for (const auto& inputFile : inputFiles) {
        std::ifstream file(inputFile);
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла: " << inputFile << std::endl;
            return EXIT_FAILURE;
        }

        int number;
        while (file >> number)
            allNumbers.push_back(number);
	printf("%d", allNumbers.size());
        file.close();
    }

    // Сортировка всех чисел в массиве allNumbers
    mergeSort(allNumbers, 0, allNumbers.size() - 1);

    // Запись отсортированных чисел в файл
    std::ofstream fileOut(OUTPUT_FILE_NAME);
    if (!fileOut.is_open()) {
        std::cerr << "Ошибка открытия файла: " << OUTPUT_FILE_NAME << std::endl;
        return EXIT_FAILURE;
    }

    for (const auto& num : allNumbers)
        fileOut << num << std::endl;

    fileOut.close();

    std::cout << "Сортировка завершена. Результат записан в файл " << OUTPUT_FILE_NAME << std::endl;
    
    return EXIT_SUCCESS;
}

