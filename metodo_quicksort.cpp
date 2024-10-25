#include <iostream>
#include <chrono>  // Para medir el tiempo
#include <cstdlib> // Para generar números aleatorios
using namespace std;

// Función que divide el arreglo y encuentra la posicion del pivote
int reducir(int arreglo[], int inicio, int fin) {
    int pivote = arreglo[inicio];
    int izquierda = inicio + 1;
    int derecha = fin;

    // Algoritmo de particion
    while (izquierda <= derecha) {
        while (izquierda <= fin && arreglo[izquierda] <= pivote) {
            izquierda++;
        }
        while (derecha >= inicio && arreglo[derecha] > pivote) {
            derecha--;
        }
        if (izquierda < derecha) {
            swap(arreglo[izquierda], arreglo[derecha]);
        }
    }
    swap(arreglo[inicio], arreglo[derecha]);
    return derecha;
}

void quicksort(int arreglo[], int tamanio) {
    const int MAX = 10000; // tamaño maximo de las pilas
    int pilaMenor[MAX], pilaMayor[MAX];
    int tope = 0;

    // Inicializar las pilas
    pilaMenor[tope] = 0;
    pilaMayor[tope] = tamanio - 1;
    tope++;

    // Algoritmo iterativo de Quicksort
    while (tope > 0) {
        tope--;
        int inicio = pilaMenor[tope];
        int fin = pilaMayor[tope];
        int posicion;

        // Reduce la lista para obtener la posicion del pivote
        posicion = reducir(arreglo, inicio, fin);

        // Procesa las sublistas que resultan
        if (inicio < posicion - 1) {
            pilaMenor[tope] = inicio;
            pilaMayor[tope] = posicion - 1;
            tope++;
        }
        if (fin > posicion + 1) {
            pilaMenor[tope] = posicion + 1;
            pilaMayor[tope] = fin;
            tope++;
        }
    }
}

int main() {
    const int tamanio = 10000;
    int datos[tamanio];

    // Generar un arreglo aleatorio grande
    srand(time(0));
    for (int i = 0; i < tamanio; i++) {
        datos[i] = rand() % 10000; // Números aleatorios entre 0 y 9999
    }

    // Inicio de la medición del tiempo
    auto start = std::chrono::high_resolution_clock::now();

    // Ordenar utilizando el método Quicksort
    quicksort(datos, tamanio);

    // Fin de la medición del tiempo
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Mostrar el tiempo de ejecución en milisegundos
    cout << "\nTiempo de ejecucion del Quicksort para un arreglo de 10,000 elementos: " << duration.count() << " milisegundos" << endl;

    return 0;
}
