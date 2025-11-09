#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Структура для представления матрицы стоимости
struct CostMatrix {
    int rows;
    int cols;
    int supply[MAX_SIZE];
    int demand[MAX_SIZE];
    int allocation[MAX_SIZE][MAX_SIZE];
};

// Функция для чтения матрицы стоимости из файла
void readCostMatrix(struct CostMatrix *matrix, FILE *file) {        // input.txt
    fscanf(file, "%d %d", &matrix->rows, &matrix->cols);            // first line - num rows and num cols
    for (int i = 0; i < matrix->rows; i++) {
        fscanf(file, "%d", &matrix->supply[i]);                     // read second line with rows (supplies)
    }
    for (int j = 0; j < matrix->cols; j++) {                        
        fscanf(file, "%d", &matrix->demand[j]);                     // read third line woth cols (demands)
    }
}

// Функция для вывода результата
void printAllocation(struct CostMatrix *costMatrix, bool isFinal) {
    if (isFinal)
        printf("\n\nОптимальное распределение:\n");
    for (int i = 0; i < costMatrix->rows; i++) {
        for (int j = 0; j < costMatrix->cols; j++) {
            printf("%d\t", costMatrix->allocation[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Функция для решения транспортной задачи методом северо-западного угла
void solveTransportationProblem(struct CostMatrix *costMatrix) {
    int i = 0, j = 0;
    while (i < costMatrix->rows && j < costMatrix->cols) {
        if (costMatrix->supply[i] < costMatrix->demand[j]) {
            costMatrix->allocation[i][j] = costMatrix->supply[i];
            costMatrix->demand[j] -= costMatrix->supply[i];
            costMatrix->supply[i] = 0;
            i++;
        } else {
            costMatrix->allocation[i][j] = costMatrix->demand[j];
            costMatrix->supply[i] -= costMatrix->demand[j];
            costMatrix->demand[j] = 0;
            j++;
        }
        printAllocation(costMatrix, false);
    }
}


int main() {
    struct CostMatrix costMatrix;

    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    readCostMatrix(&costMatrix, file);
    fclose(file);

    solveTransportationProblem(&costMatrix);
    printAllocation(&costMatrix, true);

    return 0;
}
