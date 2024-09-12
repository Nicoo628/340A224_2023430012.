#include <iostream>
#include <string>  

using namespace std;

// indico el tamaño maximo que va a tener la pila
const int MAX = 100;  

// Para ver si la fila esta vacia o no
void Pila_vacia(int tope, bool &band) {
    if (tope == 0) {
        band = true;  // esta vacia
    } else {
        band = false; // no está vacia
    }
}

// Comprueba si la fila esta llena
void Pila_llena(int tope, int max, bool &band) {
    if (tope == max) {
        band = true;  // esta llena
    } else {
        band = false; // no esta llena
    }
}



// para insertar numero/elemento en la pila (EL PUSH) // SEGUI LOS EJEMPLOS DE LA GUIA
void Push(int pila[], int &tope, int max, int dato) {
    bool band;
    Pila_llena(tope, max, band);
    if (band) {
        cout << "Desbordamiento, la pila esta llena" << endl;
    } else {
        tope++;
        pila[tope] = dato;

    }
}

// Eliminar elemento de la pila (POP)
void Pop(int pila[], int &tope) {
    bool band;
    Pila_vacia(tope, band);
    if (band) {
        cout << "Subdesbordamiento la pila esta vacia" << endl;
    } else {
        cout << "Elemento eliminado: " << pila[tope] << endl;
        tope--;
    }
}

// Función para mostrar la pila
void Ver_pila(int pila[], int tope) {
    if (tope == 0) {
        cout << "La pila está vacía" << endl;
    } else {
        for (int i = tope; i > 0; i--) {
            cout << "|" << pila[i] << "|" << endl;
        }
    }
}

int main() { 
    
    int pila[MAX];
    int tope = 0;  //Se inicia con la pila vacia
    int maxSize, opcion, valor;
    string entrada;

    cout << "Ingrese tamaño máximo de la Pila: ";
    cin >> entrada;
    maxSize = stoi(entrada); // Convierte de string a int 

    do {
        cout << "Agregar/push [1]\n";
        cout << "Remover/pop [2]\n";
        cout << "Ver pila [3]\n";
        cout << "Salir [0]\n";
        cout << "----------------\n";
        cout << "Opción: ";
        cin >> entrada;
        opcion = stoi(entrada); // Convertir string a int

        switch (opcion) {
        case 1:
            cout << "Ingrese valor: ";
            cin >> entrada;
            valor = stoi(entrada); // Convertir string a int
            Push(pila, tope, maxSize, valor);
            break;
        case 2:
            Pop(pila, tope);
            break;
        case 3:
            Ver_pila(pila, tope);
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opción invalida" << endl;
        }
    } while (opcion != 0);

    return 0;
}
