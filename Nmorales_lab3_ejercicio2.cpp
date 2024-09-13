#include <iostream>
#include <string>

using namespace std;

struct CONTENEDOR {
    int numero;
    string empresa;
};

struct Pila {
    CONTENEDOR contenedores [100];
    int tope = 0; 

};

bool Pila_vacia(Pila &pila) {
    return pila.tope == 0;
}

bool Pila_llena(Pila &pila, int max) {
    return pila. topa == max;

}

void Push(Pila &pila, int max, CONTENEDOR contenedor) {
    if (Pila_llena(pila, max)){
        cout << "La pila esta llena"
        } else {
            pila.tope++;
            pila.contenedores[pila.tope] = contenedor;
            cout << "agregadoo " << contenedor.numero << "/" << contenedor.empresa << " a la pila" << endl;
        }
}

CONTENEDOR Pop(Pila &pila) {
    if (Pila_vacia(pila)) {
        cout << " Vaciaa la pila" << endl;
        return CONTENEDOR{-1, ""}; 

    } else {
        CONTENEDOR contenedor = pila.contenedores[pila.tope];
        pila.tope--;
        return contenedor;
    }
}

int main() {
    int numero_max_pila, numero_pilas; //segun ej; n sera numero max pilas y m el numero de pilas
    cout << "INgrese el numero maximo de contenedores por pila:";
    cin >> numero_max_pila;
    cout << "INgrese el numero de pilas:";
    cin >> m;

    Pila pilas[200]// el array de pilas

    int opcion; 
    do {
        cout << "Opciones:\n";
        cout << "1. Agregar contenedor\n";
        cout << "2. Ver el estado de las pilas\n";
        cout << "0. Salir\n";
        cout << "Seleciione una de las opciones:  ";
        cin >> opcion;


        switch (opcion) {
            case 1: {
                int Numpila;
                cout << "Ingresa el numero de la pila donde se va a agregar (1-"<< numero_pilas <<"): ";
                cin >> Numpila
                Numpila--;

                if (Numpila < 0 || numPila >= m) {
                    cout << "Numero de pila invalido." << endl;
                    break;
                }


                CONTENEDOR ContenedorNuevo;
                cout << "INgrea el numero del contenedor: ";
                cin >> ContenedorNuevo.numero;
                cout << "Ingrese el nombre de la empresa: ";

                getline(cin, ContenedorNuevo.empresa);

                push(pilas[Numpila],numero_max_pila,ContenedorNuevo);
                break;
            }
            case 2:

