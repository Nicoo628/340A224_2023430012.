#include <iostream>
#include <string>

using namespace std;

struct CONTENEDOR {
    int numero;
    string empresa;
};

struct Pila {
    CONTENEDOR contenedores[100];
    int tope = 0; // indice del ultimo contenedor en la pila
};



bool Pila_vacia(Pila &pila) {
    return pila.tope == 0;
}



bool Pila_llena(Pila &pila, int max) {
    return pila.tope == max;
}


void Push(Pila &pila, int max, CONTENEDOR contenedor) {
    if (Pila_llena(pila, max)) {
        cout << "La pila esta llena" << endl;
    } else {
        pila.tope++;
        pila.contenedores[pila.tope] = contenedor;
        cout << "agregado " << contenedor.numero << "/" << contenedor.empresa << " a la pila" << endl;
    }
}



CONTENEDOR Pop(Pila &pila) {
    if (Pila_vacia(pila)) {
        cout << "pila vacia" << endl;
        return CONTENEDOR{-1, ""}; // valor para indicar que la pila estaba vacia
    } else {
        CONTENEDOR contenedor = pila.contenedores[pila.tope];
        pila.tope--;
        return contenedor;
    }
}



void Ver_pilas(Pila pilas[], int m) {
    for (int i = 0; i < m; i++) {
        cout << "pila " << i + 1 << ":" << endl;
        if (Pila_vacia(pilas[i])) {
            cout << "vacia" << endl;
        } else {
            for (int j = pilas[i].tope; j > 0; j--) {
                cout << "|" << pilas[i].contenedores[j].numero << "/" << pilas[i].contenedores[j].empresa << "|" << endl;
            }
        }
    }
}



int main() {
    int numero_max_pila, numero_pilas;
    cout << "ingrese el numero maximo de contenedores por pila: ";
    cin >> numero_max_pila;
    cout << "ingrese el numero de pilas: ";
    cin >> numero_pilas;

    Pila pilas[200]; // array de pilas

    int opcion; 
    do {
        cout << "opciones:\n";
        cout << "1. agregar contenedor\n";
        cout << "2. ver el estado de las pilas\n";
        cout << "0. salir\n";
        cout << "seleccione una de las opciones: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int Numpila;
                cout << "ingresa el numero de la pila donde se va a agregar (1-" << numero_pilas << "): ";
                cin >> Numpila;
                Numpila--;

                if (Numpila < 0 || Numpila >= numero_pilas) {
                    cout << "numero de pila invalido." << endl;
                    break;
                }

                CONTENEDOR ContenedorNuevo;
                cout << "ingrese el numero del contenedor: ";
                cin >> ContenedorNuevo.numero;
                cout << "ingrese el nombre de la empresa: ";
                cin.ignore();
                getline(cin, ContenedorNuevo.empresa);

                Push(pilas[Numpila], numero_max_pila, ContenedorNuevo);
                break;
            }
            case 2:
                Ver_pilas(pilas, numero_pilas);
                break;
            case 0:
                cout << "saliendo del programa..." << endl;
                break;
            default:
                cout << "opcion invalida." << endl;
        }
    } while (opcion != 0);

    return 0;
}
