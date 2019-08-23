struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

// Algoritmos simples (menor desempenho)
void bubbleSort(int *V, int N);
void insertionSort(int *V, int N);
void selectionSort(int *V, int N);

// ALgoritmos sofisticados
void mergeSort(int *V, int inicio, int fim);
void quickSort(int *V, int inicio, int fim);
void heapSort(int *V, int N);
