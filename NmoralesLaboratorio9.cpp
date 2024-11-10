#include <iostream>
#include <list>
#include <string>
using namespace std;

const int TAMANIO_TABLA = 20;
const int VACIO = -1;

// Hash
int funcionHash(int clave) {
    return clave % TAMANIO_TABLA;
}

// Hash doble direccion
int funcionHashSecundaria(int clave) {
    return (clave / TAMANIO_TABLA) % TAMANIO_TABLA;
}

// Tabla hash no encadenamiento
void imprimirTabla(const int tabla[]) {
    cout << "Estado actual de la tabla hash:" << endl;
    for (int i = 0; i < TAMANIO_TABLA; i++) {
        if (tabla[i] == VACIO) {
            cout << i << ": Vacio" << endl;
        } else {
            cout << i << ": " << tabla[i] << endl;
        }
    }
    cout << endl;
}
// Tabla hash con encadenamiento
void imprimirTablaEncadenamiento(const list<int> tabla[]) {
    cout << "Estado actual de la tabla hash con encadenamiento:" << endl;
    for (int i = 0; i < TAMANIO_TABLA; i++) {
        cout << i << ": ";
        for (int valor : tabla[i]) {
            cout << valor << " -> ";
        }
        cout << "NULL" << endl;
    }
    cout << endl;
}

// Prueba Lineal
void pruebaLineal(int tabla[], int clave) {
    int indice = funcionHash(clave);
    int indiceInicial = indice;
    int desplazamiento = 0;

    while (tabla[indice] != VACIO) {
        indice = (indice + 1) % TAMANIO_TABLA;
        desplazamiento++;
    }
    tabla[indice] = clave;
    cout << "Clave " << clave << " insertada en posicion " << indice 
         << " con desplazamiento de " << desplazamiento 
         << " desde la posicion inicial " << indiceInicial << "." << endl;
}

// Prueba Cuadratica
void pruebaCuadratica(int tabla[], int clave) {
    int indice = funcionHash(clave);
    int desplazamiento = 0;
    int i = 1;

    while (tabla[indice] != VACIO) {
        indice = (funcionHash(clave) + i * i) % TAMANIO_TABLA;
        desplazamiento++;
        i++;
    }
    tabla[indice] = clave;
    cout << "Clave " << clave << " insertada en posicion " << indice 
         << " con desplazamiento cuadratico de " << desplazamiento << "." << endl;
}

int main() {
    int tabla[TAMANIO_TABLA] = {VACIO}; // Inicialización de la tabla hash
    pruebaLineal(tabla, 25);
    imprimirTabla(tabla);

    pruebaCuadratica(tabla, 15);
    imprimirTabla(tabla);

    return 0;
}


