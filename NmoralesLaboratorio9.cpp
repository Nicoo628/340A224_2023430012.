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

int main() {
    int tabla[TAMANIO_TABLA] = {VACIO}; // Inicialización de la tabla hash
    imprimirTabla(tabla);

    return 0;
}
