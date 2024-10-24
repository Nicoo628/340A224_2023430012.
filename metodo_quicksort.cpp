#include <iostream>
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
    const int MAX = 100; // tamaño maximo de las pilas
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
    int datos[] = {29, 10, 14, 37, 13, 5, 22, 40, 2, 17};
    int tamanio = sizeof(datos) / sizeof(datos[0]);

    cout << "Arreglo original: ";
    for (int i = 0; i < tamanio; i++) {
        cout << datos[i] << " ";
    }
    cout << endl;

    // Ordenar utilizando el método Quicksort
    quicksort(datos, tamanio);

    cout << "Arreglo Metodo Quicksort: ";
    for (int i = 0; i < tamanio; i++) {
        cout << datos[i] << " ";
    }
    cout << endl;

    return 0;
}
