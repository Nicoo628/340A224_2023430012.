#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define TRUE 1
#define FALSE 0

enum { IZQUIERDO, DERECHO };

struct Nodo {
    int dato;
    int FE;
    Nodo* derecho;
    Nodo* izquierdo;
    Nodo* padre;
};

typedef Nodo* pNodo;
typedef Nodo* Arbol;

/* Insertar en arbol ordenado: */
void Insertar(Arbol* a, int dat);
/* Borrar un elemento: */
void Borrar(Arbol* a, int dat);
/* Funcion de busqueda: */
int Buscar(Arbol a, int dat);
/* Comprobar si es un nodo hoja: */
int EsHoja(pNodo r);
/* Contar numero de nodos: */
int NumeroNodos(Arbol a, int* c);
/* Calcular la altura de un arbol: */
int AlturaArbol(Arbol a, int* altura);
/* Calcular altura de un dato: */
int Altura(Arbol a, int dat);
/* Generar salida para Graphiz */
void PreOrden(Arbol, std::ofstream &fp);

// Funciones de equilibrado:
void Equilibrar(Arbol* raiz, pNodo nodo, int, int);
void RotaDerechaDerecha(Arbol* raiz, pNodo nodo);
void RotaIzquierdaIzquierda(Arbol* raiz, pNodo nodo);
void RotaDerechaIzquierda(Arbol* raiz, pNodo nodo);
void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo);

/* Funciones auxiliares: */
void Podar(Arbol* a);
void auxContador(Arbol a, int*);
void auxAltura(Arbol a, int, int*);

void MenuPrincipal();
void GenerarGrafo(Arbol);
void Elimina_balanceado(Arbol* a, int dat); // Función de eliminación balanceada
void Reestructura_izq(Arbol* a, pNodo nodo);
void Reestructura_der(Arbol* a, pNodo nodo);

// Nueva función de búsqueda
int BuscarNumero(Arbol a, int dat);
// Nueva función de modificar elemento
void ModificarElemento(Arbol* a, int dat, int nuevoDato);

int main() {
    Arbol ArbolInt = NULL;
    int opcion = 0;
    int valor;

    while (opcion != 6) {
        MenuPrincipal();
        std::cout << "Ingrese su opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Ingrese su numero: ";
                std::cin >> valor;
                Insertar(&ArbolInt, valor);
                break;
            case 2: // Opción de búsqueda
                std::cout << "Ingrese el número a buscar: ";
                std::cin >> valor;
                if (BuscarNumero(ArbolInt, valor)) {
                    std::cout << "El número " << valor << " se encontró en el árbol." << std::endl;
                } else {
                    std::cout << "El número " << valor << " no se encontró en el árbol." << std::endl;
                }
                break;
            case 3:
                std::cout << "Ingrese el número a eliminar: ";
                std::cin >> valor;
                Elimina_balanceado(&ArbolInt, valor);
                break;
            case 4: // Opción de modificar elemento
                {
                    int nuevoValor;
                    std::cout << "Ingrese el número a modificar: ";
                    std::cin >> valor;
                    std::cout << "Ingrese el nuevo valor: ";
                    std::cin >> nuevoValor;
                    ModificarElemento(&ArbolInt, valor, nuevoValor);
                }
                break;
            case 5:
                GenerarGrafo(ArbolInt);
                break;
        }
    }

    /* Liberar memoria asociada al arbol. */
    Podar(&ArbolInt);
    return 0;
}

void GenerarGrafo(Arbol ArbolInt) {
    std::ofstream fp("grafo.txt");

    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=yellow];\n";

    fp << "nullraiz [shape=point];\n";
    fp << "nullraiz->" << ArbolInt->dato << " [label=" << ArbolInt->FE << "];\n";
    PreOrden(ArbolInt, fp);

    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

void MenuPrincipal() {
    std::cout << "\n";
    std::cout << "<1> Ingresar numero\n";
    std::cout << "<2> Busqueda numero\n";
    std::cout << "<3> Eliminar numero\n";
    std::cout << "<4> Modificar elemento ingresado\n";
    std::cout << "<5> Generar Grafo\n";
    std::cout << "<6> Salir\n";
    std::cout << "\n";
}

void Podar(Arbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        free(*a);
        *a = NULL;
    }
}

void Insertar(Arbol* a, int dat) {
    pNodo padre = NULL;
    pNodo actual = *a;

    while (actual != NULL && dat != actual->dato) {
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
    }

    if (actual != NULL)
        return;

    if (padre == NULL) {
        *a = new Nodo{dat, 0, NULL, NULL, NULL};
    } else if (dat < padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->izquierdo = actual;
        Equilibrar(a, padre, IZQUIERDO, TRUE);
    } else if (dat > padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->derecho = actual;
        Equilibrar(a, padre, DERECHO, TRUE);
    }
}

void Equilibrar(Arbol* a, pNodo nodo, int rama, int nuevo) {
    int salir = FALSE;

    while (nodo && !salir) {
        if (nuevo){
            if (rama == IZQUIERDO){
                nodo->FE -= 1;
            } else {
                nodo->FE += 1;
            }
        }
        else{
            if (rama == IZQUIERDO){
                nodo->FE += 1;
            } 
            else {
                nodo->FE -= 1;
            }
        }

        if (nodo->FE == 0)
            salir = TRUE;
        else if (nodo->FE == -2) {
            if (nodo->izquierdo->FE == 1)
                RotaIzquierdaDerecha(a, nodo);
            else
                RotaIzquierdaIzquierda(a, nodo);
            salir = TRUE;
        } else if (nodo->FE == 2) {
            if (nodo->derecho->FE == -1)
                RotaDerechaIzquierda(a, nodo);
            else
                RotaDerechaDerecha(a, nodo);
            salir = TRUE;
        }

        if (nodo->padre) {
            if (nodo->padre->derecho == nodo) {
                rama = DERECHO;
            } else {
                rama = IZQUIERDO;
            }
        }
        nodo = nodo->padre;
    }
}

void Elimina_balanceado(Arbol* a, int dat) {
    pNodo actual = *a;
    pNodo padre = NULL;
    int lado = 0;

    while (actual && actual->dato != dat) {
        padre = actual;
        if (dat < actual->dato) {
            actual = actual->izquierdo;
            lado = IZQUIERDO;
        } else {
            actual = actual->derecho;
            lado = DERECHO;
        }
    }

    if (!actual) return;  // El elemento no existe

    if (actual->izquierdo && actual->derecho) {
        pNodo sucesor = actual->derecho;
        while (sucesor->izquierdo) sucesor = sucesor->izquierdo;
        actual->dato = sucesor->dato;
        Elimina_balanceado(&(actual->derecho), sucesor->dato);
    } else {
        pNodo hijo = actual->izquierdo ? actual->izquierdo : actual->derecho;

        if (!padre) {
            *a = hijo;
        } else if (lado == IZQUIERDO) {
            padre->izquierdo = hijo;
            Reestructura_izq(a, padre);
        } else {
            padre->derecho = hijo;
            Reestructura_der(a, padre);
        }

        if (hijo) hijo->padre = padre;
        delete actual;
    }
}

void Reestructura_izq(Arbol* a, pNodo nodo) {
    nodo->FE += 1;
    if (nodo->FE == 1) return;
    if (nodo->FE == 2) {
        if (nodo->izquierdo->FE == 1) {
            RotaIzquierdaIzquierda(a, nodo);
        } else {
            RotaIzquierdaDerecha(a, nodo);
        }
    }
}

void RotaIzquierdaIzquierda(Arbol* a, pNodo nodo) {
    pNodo izq = nodo->izquierdo;
    nodo->izquierdo = izq->derecho;
    if (izq->derecho) izq->derecho->padre = nodo;

    izq->padre = nodo->padre;
    if (!nodo->padre) {
        *a = izq;
    } else if (nodo == nodo->padre->izquierdo) {
        nodo->padre->izquierdo = izq;
    } else {
        nodo->padre->derecho = izq;
    }
    izq->derecho = nodo;
    nodo->padre = izq;

    nodo->FE = 0;
    izq->FE = 0;
}

void RotaIzquierdaDerecha(Arbol* a, pNodo nodo) {
    pNodo izq = nodo->izquierdo;
    pNodo der = izq->derecho;
    izq->derecho = der->izquierdo;
    if (der->izquierdo) der->izquierdo->padre = izq;

    der->padre = nodo->padre;
    if (!nodo->padre) {
        *a = der;
    } else if (nodo == nodo->padre->izquierdo) {
        nodo->padre->izquierdo = der;
    } else {
        nodo->padre->derecho = der;
    }
    der->izquierdo = izq;
    izq->padre = der;
    nodo->izquierdo = der->derecho;
    if (der->derecho) der->derecho->padre = nodo;
    der->derecho = nodo;
    nodo->padre = der;

    if (der->FE == 1) {
        nodo->FE = -1;
        izq->FE = 0;
    } else if (der->FE == 0) {
        nodo->FE = 0;
        izq->FE = 0;
    } else {
        nodo->FE = 0;
        izq->FE = 1;
    }
    der->FE = 0;
}

void RotaDerechaDerecha(Arbol* a, pNodo nodo) {
    pNodo der = nodo->derecho;
    nodo->derecho = der->izquierdo;
    if (der->izquierdo) der->izquierdo->padre = nodo;

    der->padre = nodo->padre;
    if (!nodo->padre) {
        *a = der;
    } else if (nodo == nodo->padre->izquierdo) {
        nodo->padre->izquierdo = der;
    } else {
        nodo->padre->derecho = der;
    }
    der->izquierdo = nodo;
    nodo->padre = der;

    nodo->FE = 0;
    der->FE = 0;
}

void RotaDerechaIzquierda(Arbol* a, pNodo nodo) {
    pNodo der = nodo->derecho;
    pNodo izq = der->izquierdo;
    der->izquierdo = izq->derecho;
    if (izq->derecho) izq->derecho->padre = der;

    izq->padre = nodo->padre;
    if (!nodo->padre) {
        *a = izq;
    } else if (nodo == nodo->padre->izquierdo) {
        nodo->padre->izquierdo = izq;
    } else {
        nodo->padre->derecho = izq;
    }
    izq->derecho = der;
    der->padre = izq;

    nodo->derecho = izq->izquierdo;
    if (izq->izquierdo) izq->izquierdo->padre = nodo;
    izq->izquierdo = nodo;
    nodo->padre = izq;

    if (izq->FE == -1) {
        nodo->FE = 1;
        der->FE = 0;
    } else if (izq->FE == 0) {
        nodo->FE = 0;
        der->FE = 0;
    } else {
        nodo->FE = 0;
        der->FE = -1;
    }
    izq->FE = 0;
}

int BuscarNumero(Arbol a, int dat) {
    while (a) {
        if (dat == a->dato) return TRUE;
        else if (dat < a->dato) a = a->izquierdo;
        else a = a->derecho;
    }
    return FALSE;
}

void ModificarElemento(Arbol* a, int dat, int nuevoDato) {
    pNodo nodo = *a;

    while (nodo) {
        if (dat == nodo->dato) {
            if (BuscarNumero(*a, nuevoDato)) {
                std::cout << "El valor " << nuevoDato << " ya existe en el árbol." << std::endl;
                return;
            }
            nodo->dato = nuevoDato;
            return;
        } else if (dat < nodo->dato) {
            nodo = nodo->izquierdo;
        } else {
            nodo = nodo->derecho;
        }
    }
    std::cout << "El valor " << dat << " no se encontró en el árbol." << std::endl;
}
