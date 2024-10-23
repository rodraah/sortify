#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char FILENAME[] = "dados.txt";

// Novo tipo que vai armazenar as métricas
// dos métodos de ordenação.
typedef struct {
    char nome[20];
    int comparacoes;
    int trocas;
} Metrica;

void insertionSort(int array[], int size, Metrica *metrica) {
    int currentIndex, key, position;
    for (currentIndex = 1; currentIndex < size; currentIndex++) {
        metrica->comparacoes++;
        key = array[currentIndex]; 
        position = currentIndex - 1;

        while (position >= 0 && array[position] > key) {
            metrica->comparacoes++;
            array[position + 1] = array[position];
            metrica->trocas++;
            position--;
        }
        array[position + 1] = key; 
        metrica->trocas++;
    }
}

void bubbleSort(int array[], int size, Metrica *metrica) {
    for (int step = 0; step < size - 1; ++step) {
        for (int i = 0; i < size - step - 1; ++i) {
            metrica->comparacoes++;
            if (array[i] > array[i + 1]) {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                metrica->trocas++;
            }
        }
    }
}

void quickSort(int array[], int low, int high, Metrica *metrica) {
    if (low < high) {
        int pivot = array[high];
        int i = (low - 1);
        
        for (int j = low; j < high; j++) {
            metrica->comparacoes++;
            if (array[j] <= pivot) {
                i++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                metrica->trocas++;
            }
        }
        
        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;
        metrica->trocas++;
        
        int pi = i + 1;
        
        quickSort(array, low, pi - 1, metrica);
        quickSort(array, pi + 1, high, metrica);
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int loadData(const char *filename, int **array) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return -1;
    }

    int size = 0;
    int capacity = 10;
    *array = malloc(capacity * sizeof(int));

    while (fscanf(file, "%d", &(*array)[size]) == 1) {
        size++;
        if (size >= capacity) {
            capacity *= 2;
            *array = realloc(*array, capacity * sizeof(int));
        }
    }

    fclose(file);
    return size;
}

int main() {
    int *originalArray = NULL; 
    int size = -1;

    size = loadData(FILENAME, &originalArray);
    if (size == -1) {
        return 1;
    }

    int *array = malloc(sizeof(int) * size);

    Metrica metricaInsert = {"Insertion Sort", 0,0};
    Metrica metricaBubble = {"Bubble Sort", 0, 0};
    Metrica metricaQuick = {"Quick Sort", 0, 0};

    printf("\nComparando os três algoritmos:\n");

    memcpy(array, originalArray, sizeof(int) * size);
    insertionSort(array, size, &metricaInsert);

    memcpy(array, originalArray, sizeof(int) * size);
    bubbleSort(array, size, &metricaBubble);

    memcpy(array, originalArray, sizeof(int) * size);
    quickSort(array, 0, size - 1, &metricaQuick);

    printf("Métricas do Insertion Sort: %d comparacoes, %d trocas\n", metricaInsert.comparacoes, metricaInsert.trocas);
    printf("Metricas do Bubble Sort: %d comparacoes, %d trocas\n", metricaBubble.comparacoes, metricaBubble.trocas);
    printf("Metricas do Quick Sort: %d comparacoes, %d trocas\n", metricaQuick.comparacoes, metricaQuick.trocas);

    // Printar o método mais eficiente em comparações e trocas
    Metrica metricas[] = {metricaInsert, metricaBubble, metricaQuick};

    Metrica *menosComparacoes;
    Metrica *menosTrocas;

    for (int i=0;i<3;i++) {
        if (i==0) {
            menosComparacoes = &metricas[i];
            menosTrocas = &metricas[i];
            continue;
        }

        if (metricas[i].comparacoes < menosComparacoes->comparacoes) {
            menosComparacoes = &metricas[i];
        }
        if (metricas[i].trocas < menosTrocas->trocas) {
            menosTrocas = &metricas[i];
        }
    }

    printf("\n");
    printf("%s foi mais eficiente em comparações\n", menosComparacoes->nome);
    printf("%s foi mais eficiente em trocas\n", menosTrocas->nome);

    return 0;
}