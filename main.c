#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int comparacoes;
    int trocas;
} Metrica;

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

int loadData(const char *filename, int array[], int max_size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return -1;
    }

    int size = 0;
    while (fscanf(file, "%d", &array[size]) != EOF && size < max_size) {
        size++;
    }

    fclose(file);
    return size;
}

int main() {
    int array[1001]; 
    int size;

    size = loadData("dados.txt", array, 100);
    if (size == -1) {
        return 1;  
    }

    int backupArray[1001];
    for (int i = 0; i < size; i++) {
        backupArray[i] = array[i];
    }

    Metrica metricaBubble = {0, 0};
    Metrica metricaQuick = {0, 0};

    printf("\nComparando os dois algoritmos:\n");

    for (int i = 0; i < size; i++) {
        array[i] = backupArray[i];
    }

    bubbleSort(array, size, &metricaBubble);
    quickSort(array, 0, size - 1, &metricaQuick);

    printf("Metricas do Bubble Sort: %d comparacoes, %d trocas\n", metricaBubble.comparacoes, metricaBubble.trocas);
    printf("Metricas do Quick Sort: %d comparacoes, %d trocas\n", metricaQuick.comparacoes, metricaQuick.trocas);

    if (metricaBubble.comparacoes < metricaQuick.comparacoes) {
        printf("Bubble Sort foi mais eficiente em termos de comparações.\n");
    } else if(metricaBubble.comparacoes > metricaQuick.comparacoes) {
        printf("Quick Sort foi mais eficiente em termos de comparações.\n");
    } else {
        printf("As comparacoes foram iguais\n");
    }

    if (metricaBubble.trocas < metricaQuick.trocas) {
        printf("Bubble Sort foi mais eficiente em termos de trocas.\n");
    } else if(metricaBubble.trocas > metricaQuick.trocas) {
        printf("Quick Sort foi mais eficiente em termos de trocas.\n");
    } else {
        printf("As trocas foram iguais\n");
    }

    return 0;
}
