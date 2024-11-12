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

// Doble Direccion Hash
void dobleDireccionHash(int tabla[], int clave) {
    int indice = funcionHash(clave);
    int tamanoPaso = funcionHashSecundaria(clave);
    int desplazamiento = 0;

    while (tabla[indice] != VACIO) {
        indice = (indice + tamanoPaso) % TAMANIO_TABLA;
        desplazamiento++;
    }
    tabla[indice] = clave;
    cout << "Clave " << clave << " insertada en posicion " << indice 
         << " con desplazamiento de " << desplazamiento << " utilizando doble hash." << endl;
}

// Encadenamiento
void encadenamiento(list<int> tabla[], int clave) {
    int indice = funcionHash(clave);
    tabla[indice].push_back(clave);
    cout << "Clave " << clave << " insertada en la lista de la posicion " << indice << "." << endl;
}

// buscar para cada metodo
void buscarPruebaLineal(const int tabla[], int clave) {
    int indice = funcionHash(clave);
    int indiceInicial = indice;
    int desplazamiento = 0;

    while (tabla[indice] != clave) {
        if (tabla[indice] == VACIO) {
            cout << "La clave " << clave << " no se encuentra en la tabla." << endl;
            return;
        }
        indice = (indice + 1) % TAMANIO_TABLA;
        desplazamiento++;
    }
    cout << "Clave " << clave << " encontrada en posicion " << indice 
         << " despues de un desplazamiento de " << desplazamiento 
         << " desde la posicion inicial " << indiceInicial << "." << endl;
}

void buscarPruebaCuadratica(const int tabla[], int clave) {
    int indice = funcionHash(clave);
    int i = 1;
    int desplazamiento = 0;

    while (tabla[indice] != clave) {
        if (tabla[indice] == VACIO) {
            cout << "La clave " << clave << " no se encuentra en la tabla." << endl;
            return;
        }
        indice = (funcionHash(clave) + i * i) % TAMANIO_TABLA;
        desplazamiento++;
        i++;
    }
    cout << "Clave " << clave << " encontrada en posicion " << indice 
         << " despues de un desplazamiento cuadratico de " << desplazamiento << "." << endl;
}

void buscarDobleDireccionHash(const int tabla[], int clave) {
    int indice = funcionHash(clave);
    int tamanoPaso = funcionHashSecundaria(clave);
    int desplazamiento = 0;

    while (tabla[indice] != clave) {
        if (tabla[indice] == VACIO) {
            cout << "La clave " << clave << " no se encuentra en la tabla." << endl;
            return;
        }
        indice = (indice + tamanoPaso) % TAMANIO_TABLA;
        desplazamiento++;
    }
    cout << "Clave " << clave << " encontrada en posicion " << indice 
         << " despues de un desplazamiento de " << desplazamiento << " usando doble hash." << endl;
}

void buscarEncadenamiento(const list<int> tabla[], int clave) {
    int indice = funcionHash(clave);
    for (const int& valor : tabla[indice]) {
        if (valor == clave) {
            cout << "Clave " << clave << " encontrada en la lista de la posicion " << indice << "." << endl;
            return;
        }
    }
    cout << "La clave " << clave << " no se encuentra en la tabla." << endl;
}

// El codigo se imprime seleccionando L C D E desde la terminal a la hora de ejecutar/ ej: ./a.out D, doble direccion hash
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: ./hash {L|C|D|E}" << endl;
        cerr << "Seleccione el metodo de resolucion de colisiones usando una de las opciones:" << endl;
        cerr << "L: Prueba Lineal" << endl;
        cerr << "C: Prueba Cuadratica" << endl;
        cerr << "D: Doble Direccion Hash" << endl;
        cerr << "E: Encadenamiento" << endl;
        return 1;
    }

    char metodo = argv[1][0];
    int tablaHash[TAMANIO_TABLA];
    list<int> tablaEncadenamiento[TAMANIO_TABLA];
    
    // se inicializa la tabla hash con -1 para indicar posiciones vacias
    for (int i = 0; i < TAMANIO_TABLA; i++) {
        tablaHash[i] = VACIO;
    }

    int claves[] = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};
    int nClaves = sizeof(claves) / sizeof(claves[0]);

    cout << "Metodo seleccionado: ";
    switch (metodo) {
        case 'L': cout << "Prueba Lineal" << endl; break;
        case 'C': cout << "Prueba Cuadratica" << endl; break;
        case 'D': cout << "Doble Direccion Hash" << endl; break;
        case 'E': cout << "Encadenamiento" << endl; break;
        default: cerr << "Metodo no valido" << endl; return 1;
    }

    // se inserta la tabla hash segun el metodo que se escogio
    for (int i = 0; i < nClaves; i++) {
        int clave = claves[i];
        cout << "Insertando clave: " << clave << endl;
        switch (metodo) {
            case 'L':
                pruebaLineal(tablaHash, clave);
                break;
            case 'C':
                pruebaCuadratica(tablaHash, clave);
                break;
            case 'D':
                dobleDireccionHash(tablaHash, clave);
                break;
            case 'E':
                encadenamiento(tablaEncadenamiento, clave);
                break;
        }
        // Imprimir tabla segun el metodo
        if (metodo == 'E') {
            imprimirTablaEncadenamiento(tablaEncadenamiento);
        } else {
            imprimirTabla(tablaHash);
        }
    }

    // Busqueda de elementos
    int claveBuscar;
    cout << "Ingrese una clave para buscar en la tabla: ";
    cin >> claveBuscar;

    switch (metodo) {
        case 'L':
            buscarPruebaLineal(tablaHash, claveBuscar);
            break;
        case 'C':
            buscarPruebaCuadratica(tablaHash, claveBuscar);
            break;
        case 'D':
            buscarDobleDireccionHash(tablaHash, claveBuscar);
            break;
        case 'E':
            buscarEncadenamiento(tablaEncadenamiento, claveBuscar);
            break;
    }

    return 0;
}