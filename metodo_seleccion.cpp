#include <iostream>
#include <chrono>  // Para medir el tiempo
using namespace std;

// Aplica el metodo de seleccion en el array
void seleccion(int arreglo[], int tamanio) {
    int posicionMinima;
    int valorTemporal;
    int indiceActual, indiceBusqueda;

    // itera a traves del arreglo
    for (indiceActual = 0; indiceActual < tamanio - 1; indiceActual++) {
        posicionMinima = indiceActual;
        valorTemporal = arreglo[indiceActual];

        // Busca el menor elemento en el arreglo
        for (indiceBusqueda = indiceActual + 1; indiceBusqueda < tamanio; indiceBusqueda++) {
            if (arreglo[indiceBusqueda] < valorTemporal) {
                valorTemporal = arreglo[indiceBusqueda];
                posicionMinima = indiceBusqueda;
            }
        }

        // Intercambia los puestos si encontro uno menor
        arreglo[posicionMinima] = arreglo[indiceActual];
        arreglo[indiceActual] = valorTemporal;
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

    // Inicio de la medición del tiempo
    auto start = std::chrono::high_resolution_clock::now();

    // Ordenar utilizando el método de selección
    seleccion(datos, tamanio);

    // Fin de la medición del tiempo
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = (end - start);

    cout << "Arreglo Metodo Seleccion: ";
    for (int i = 0; i < tamanio; i++) {
        cout << datos[i] << " ";
    }
    cout << endl;

    // Mostrar el tiempo de ejecución
    cout << "\nTiempo de ejecucion del metodo de seleccion: " << duration.count() << " segundos" << endl;

    return 0;
}
