#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// divide el arreglo y encuentra la posicion del pivote
int reducir(int arreglo[], int inicio, int fin) {
    int pivote = arreglo[inicio];
    int izquierda = inicio + 1;
    int derecha = fin;

    // particion
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

// Quicksort
void quicksort(int arreglo[], int tamanio) {
    const int MAX = 100;
    int pilaMenor[MAX], pilaMayor[MAX];
    int tope = 0;

    // Inicia las pilas
    pilaMenor[tope] = 0;
    pilaMayor[tope] = tamanio - 1;
    tope++;


    while (tope > 0) {
        tope--;
        int inicio = pilaMenor[tope];
        int fin = pilaMayor[tope];
        int posicion;
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

// metodo seleccion
void seleccion(int arreglo[], int tamanio) {
    int posicionMinima;
    int valorTemporal;
    int indiceActual, indiceBusqueda;

    // viaja por el arreglo
    for (indiceActual = 0; indiceActual < tamanio - 1; indiceActual++) {
        posicionMinima = indiceActual;
        valorTemporal = arreglo[indiceActual];

    // busca el menor elemento
        for (indiceBusqueda = indiceActual + 1; indiceBusqueda < tamanio; indiceBusqueda++) {
            if (arreglo[indiceBusqueda] < valorTemporal) {
                valorTemporal = arreglo[indiceBusqueda];
                posicionMinima = indiceBusqueda;
            }
        }

        // se intercambian si encontro uno menor
        arreglo[posicionMinima] = arreglo[indiceActual];
        arreglo[indiceActual] = valorTemporal;
    }
}

int main() {
    int N;
    char mostrarContenido;

    cout << "Ingrese el numero de elementos: ";
    cin >> N;

    if (N <= 0) {
        cerr << "El numero tiene que ser positivo (no arruine el programa)." << endl;
        return 1;
    }

    cout << "Quiere mostrar el contenido de los vectores? (s/n): ";
    cin >> mostrarContenido;

    if (mostrarContenido != 's' && mostrarContenido != 'n') {
        cerr << "Entrada no valida. Use 's' para si o 'n' para no." << endl;
        return 1;
    }

    // Valores aleatorios
    int* datos = new int[N];
    srand(time(0));
    for (int i = 0; i < N; ++i) {
        datos[i] = rand() % 10000; // Valores aleatorios entre 0 y 9999
    }

    // Mostrar el contenido inicial del vector si corresponde
    if (mostrarContenido == 's') {
        cout << "Contenido inicial del vector: ";
        for (int i = 0; i < N; ++i) {
            cout << datos[i] << " ";
        }
        cout << endl;
    }

    //se usa para ambos metodos 
    int* datosSeleccion = new int[N];
    int* datosQuicksort = new int[N];
    copy(datos, datos + N, datosSeleccion);
    copy(datos, datos + N, datosQuicksort);

    // Quise medir el tiempo en microsegundos porque en milisegundos me estaba dando problemas 
    auto inicioSeleccion = high_resolution_clock::now();
    seleccion(datosSeleccion, N);
    auto finSeleccion = high_resolution_clock::now();
    auto duracionSeleccion = duration_cast<microseconds>(finSeleccion - inicioSeleccion).count();

    auto inicioQuicksort = high_resolution_clock::now();
    quicksort(datosQuicksort, N);
    auto finQuicksort = high_resolution_clock::now();
    auto duracionQuicksort = duration_cast<microseconds>(finQuicksort - inicioQuicksort).count();

    // Mostrar el resultado del tiempo (con el ejemplo dado en la guia)
    cout << "-----------------------------------------" << endl;
    cout << "Metodo          | Tiempo (microsegundos)" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Seleccion       | " << duracionSeleccion << " us" << endl;
    cout << "Quicksort       | " << duracionQuicksort << " us" << endl;
    cout << "-----------------------------------------" << endl;

    // Mostrar el contenido ordenado 
    if (mostrarContenido == 's') {
        cout << "Seleccion ordenado: ";
        for (int i = 0; i < N; ++i) {
            cout << datosSeleccion[i] << " ";
        }
        cout << endl;

        cout << "Quicksort ordenado: ";
        for (int i = 0; i < N; ++i) {
            cout << datosQuicksort[i] << " ";
        }
        cout << endl;
    }

    // Liberar memoria
    delete[] datos;
    delete[] datosSeleccion;
    delete[] datosQuicksort;

    return 0;
}
