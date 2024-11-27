#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

long long numSwaps = 0;
long long numComparisons = 0;

// Funções de ordenação
void bubbleSort(int arr[], int n);
void improvedBubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);
void mergeSort(int arr[], int n);
void quickSort(int arr[], int n);
void heapSort(int arr[], int n);
void radixSort(int arr[], int n);

// Funções para gerar os casos de teste
void generateBestCase(int arr[], int n);
void generateAverageCase(int arr[], int n);
void generateWorstCase(int arr[], int n);
void resetCounters();

// Declaração dos algoritmos e seus nomes
void (*algorithms[])(int[], int) = {bubbleSort, improvedBubbleSort, insertionSort, selectionSort, mergeSort, quickSort, heapSort, radixSort};
const char *names[] = {"Bubble Sort", "Improved Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort", "Heap Sort", "Radix Sort"};

// Função para resetar o contador de comparações e trocas
void resetCounters() {
    numSwaps = 0;
    numComparisons = 0;
}

// Funções para gerar os casos de teste
void generateBestCase(int arr[], int n) {
	int i;
    for (i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

void generateAverageCase(int arr[], int n) {
	int i;
    for (i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

void generateWorstCase(int arr[], int n) {
	int i;
    for (i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

// Funções de ordenação
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            numComparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                numSwaps++;
            }
        }
    }
}

void improvedBubbleSort(int arr[], int n) {
    int i, j, swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            numComparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                numSwaps++;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

void insertionSort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            numComparisons++;
            arr[j + 1] = arr[j];
            j--;
            numSwaps++;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    int i, j, minIndex;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            numComparisons++;
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        if (minIndex != i) {
            int temp = arr[minIndex];
            arr[minIndex] = arr[i];
            arr[i] = temp;
            numSwaps++;
        }
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    int i, j, k;
    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        numComparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int n) {
    mergeSortHelper(arr, 0, n - 1);
}

void mergeSortHelper(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;

    // Ordena low, mid e high
    if (arr[low] > arr[mid]) {
        int temp = arr[low];
        arr[low] = arr[mid];
        arr[mid] = temp;
    }
    if (arr[low] > arr[high]) {
        int temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
    }
    if (arr[mid] > arr[high]) {
        int temp = arr[mid];
        arr[mid] = arr[high];
        arr[high] = temp;
    }

    // Retorna o índice do pivô (mediana)
    return mid;
}

int partition(int arr[], int low, int high) {
    int pivotIndex = medianOfThree(arr, low, high);
    int pivot = arr[pivotIndex];
    int i = low - 1;
    int j, temp;

    // Move o pivô para o final
    temp = arr[pivotIndex];
    arr[pivotIndex] = arr[high];
    arr[high] = temp;
    numSwaps++;

    for (j = low; j < high; j++) {
        numComparisons++;
        if (arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            numSwaps++;
        }
    }

    // Move o pivô para sua posição correta
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    numSwaps++;
    return i + 1;
}

void quickSortHelper(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int n) {
    quickSortHelper(arr, 0, n - 1);
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
        numComparisons++;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
        numComparisons++;
    }
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        numSwaps++;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    int i, temp;
    for (i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (i = n - 1; i > 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        numSwaps++;
        heapify(arr, i, 0);
    }
}

int getMax(int arr[], int n) {
    int max = arr[0];
    int i;
    for (i = 1; i < n; i++) {
        numComparisons++;
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

void countingSortForRadix(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};
    int i;
    for (i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++) count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++) arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    int exp;
    for (exp = 1; m / exp > 0; exp *= 10) {
        countingSortForRadix(arr, n, exp);
    }
}

// Função para medir o tempo de execução e imprimir os resultados
void printResults(int arr[], int n, void (*algorithm)(int[], int), const char* name) {
    clock_t start, end;
    resetCounters();
    start = clock();
    algorithm(arr, n);
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("Algoritmo: %s\n", name);
    printf("Tempo de execucao: %.5f milisegundos\n", time_taken);
    printf("Trocas: %lld\n", numSwaps);
    printf("Comparacoes: %lld\n", numComparisons);
}

int main() {
    int size1 = 1000, size2 = 10000, size3 = 100000;

    int arr1[size1], arr2[size2], arr3[size3];
    void (*algorithms[])(int[], int) = {
    	bubbleSort, improvedBubbleSort, insertionSort, selectionSort, heapSort, radixSort, mergeSort, quickSort  
    };
    const char *names[] = {
        "Bubble Sort", "Improved Bubble Sort", "Insertion Sort", "Selection Sort", "Heap Sort", "Radix Sort", "Merge Sort", "Quick Sort"  
    };

    const char *caseNames[] = {"Best Case", "Average Case", "Worst Case"};
    void (*caseGenerators[])(int[], int) = {generateBestCase, generateAverageCase, generateWorstCase};

    int i, j, k;

	for (k = 0; k < 3; k++) { // Itera sobre os tamanhos dos arrays
	    int *arr;
	    int size;
	
	    switch (k) {
	        case 0:
	            arr = arr1;
	            size = size1;
	            break;
	        case 1:
	            arr = arr2;
	            size = size2;
	            break;
	        case 2:
	            arr = arr3;
	            size = size3;
	            break;
	    }
	
	    for (i = 0; i < 3; i++) { // Itera sobre os casos de teste
	        printf("\nAnalisando %s (%d elementos):\n", caseNames[i], size);
	        caseGenerators[i](arr, size);  // Gera o caso de teste correto
	
	        for (j = 0; j < 8; j++) { // Testa todos os algoritmos
	            resetCounters();
	            printf("Algoritmo: %s\n", names[j]);
	            int *arrCopy = malloc(size * sizeof(int));
	            memcpy(arrCopy, arr, size * sizeof(int));  // Cria uma cópia para o algoritmo não afetar os testes
	            clock_t start = clock();
	            algorithms[j](arrCopy, size);  // Ordena com o algoritmo escolhido
	            clock_t end = clock();
	            printf("Tempo de execucao: %.3f milisegundos\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);
	            printf("Trocas: %lld\n", numSwaps);
	            printf("Comparacoes: %lld\n", numComparisons);
	            free(arrCopy);
	        }
	    }
	}


    return 0;
}



