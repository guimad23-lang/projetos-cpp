#include <iostream>

using namespace std;

// Função auxiliar para imprimir o vetor
void imprimirVetor(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Função que implementa o Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Encontra o índice do menor elemento no restante do vetor
        int indice_minimo = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[indice_minimo]) {
                indice_minimo = j;
            }
        }
        
        // Troca o menor elemento encontrado com o primeiro elemento da parte não ordenada
        if (indice_minimo != i) {
            int temp = arr[indice_minimo];
            arr[indice_minimo] = arr[i];
            arr[i] = temp;
        }
    }
}

int main() {
    // Vetor de entrada
    int v[] = {49, 38, 58, 87, 34, 93, 26, 13};
    
    // Calcula a quantidade de elementos no vetor
    int n = sizeof(v) / sizeof(v[0]);

    cout << "Vetor antes da ordenacao:" << endl;
    imprimirVetor(v, n);

    // Chama a função de ordenação
    selectionSort(v, n);

    cout << "\nVetor depois da ordenacao:" << endl;
    imprimirVetor(v, n);

    return 0;
}
