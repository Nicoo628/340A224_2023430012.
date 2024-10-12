#include <iostream>
#include <cstdlib> 
using namespace std;

// inicializar matriz. recibe puntero a la matriz.
void inicializar_matriz_enteros(int **matriz, int n) {
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
        // Se inicializa con el -1 para indicar que no hay conexion
            matriz[fila][col] = -1; 
        }
    }
}

// imprime matriz nxn
void imprimir_matriz(int **matriz, int n) {
    cout << endl;
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            cout << matriz[fila][col] << " ";
        }
        cout << endl;
    }
}


int main(int argc, char **argv) {
    // Valida cantidad de parametros minimos
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <número de vértices>" << endl;
        return 1;
    }

    // Convertir string a entero
    int n = atoi(argv[1]);

    // Crear matriz nxn de enteros
    int **matriz;
    matriz = new int*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new int[n];
    }

    
    inicializar_matriz_enteros(matriz, n);
    imprimir_matriz(matriz, n);

    // para liberar memoria
    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}
