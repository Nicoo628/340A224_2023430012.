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
    if (nodo->FE == 2) {
        if (nodo->derecho->FE == -1)
            RotaDerechaIzquierda(a, nodo);
        else
            RotaDerechaDerecha(a, nodo);
    }
}

void Reestructura_der(Arbol* a, pNodo nodo) {
    nodo->FE -= 1;
    if (nodo->FE == -2) {
        if (nodo->izquierdo->FE == 1)
            RotaIzquierdaDerecha(a, nodo);
        else
            RotaIzquierdaIzquierda(a, nodo);
    }
}

void RotaDerechaDerecha(Arbol* a, pNodo nodo) {
    pNodo hijo = nodo->derecho;
    nodo->derecho = hijo->izquierdo;

    if (hijo->izquierdo) hijo->izquierdo->padre = nodo;
    hijo->padre = nodo->padre;

    if (!nodo->padre) {
        *a = hijo;
    } else if (nodo->padre->izquierdo == nodo) {
        nodo->padre->izquierdo = hijo;
    } else {
        nodo->padre->derecho = hijo;
    }

    hijo->izquierdo = nodo;
    nodo->padre = hijo;
    nodo->FE = nodo->FE - 1 - std::max(0, hijo->FE);
    hijo->FE = hijo->FE - 1 + std::min(0, nodo->FE);
}

void RotaIzquierdaIzquierda(Arbol* a, pNodo nodo) {
    pNodo hijo = nodo->izquierdo;
    nodo->izquierdo = hijo->derecho;

    if (hijo->derecho) hijo->derecho->padre = nodo;
    hijo->padre = nodo->padre;

    if (!nodo->padre) {
        *a = hijo;
    } else if (nodo->padre->izquierdo == nodo) {
        nodo->padre->izquierdo = hijo;
    } else {
        nodo->padre->derecho = hijo;
    }

    hijo->derecho = nodo;
    nodo->padre = hijo;
    nodo->FE = nodo->FE + 1 - std::min(0, hijo->FE);
    hijo->FE = hijo->FE + 1 + std::max(0, nodo->FE);
}

void RotaDerechaIzquierda(Arbol* a, pNodo nodo) {
    RotaDerechaDerecha(a, nodo->derecho);
    RotaIzquierdaIzquierda(a, nodo);
}

void RotaIzquierdaDerecha(Arbol* a, pNodo nodo) {
    RotaIzquierdaIzquierda(a, nodo->izquierdo);
    RotaDerechaDerecha(a, nodo);
}

void PreOrden(Arbol a, std::ofstream &fp) {
    if (a) {
        fp << a->dato << ";\n";
        if (a->izquierdo) {
            fp << a->dato << "->" << a->izquierdo->dato << ";\n";
            PreOrden(a->izquierdo, fp);
        }
        if (a->derecho) {
            fp << a->dato << "->" << a->derecho->dato << ";\n";
            PreOrden(a->derecho, fp);
        }
    }
}

// Función de búsqueda de número
int BuscarNumero(Arbol a, int dat) {
    while (a) {
        if (dat == a->dato) {
            return TRUE;  // Encontrado
        } else if (dat < a->dato) {
            a = a->izquierdo;
        } else {
            a = a->derecho;
        }
    }
    return FALSE;  // No encontrado
}

// Comprobar si es un nodo hoja
int EsHoja(pNodo r) {
    return (r && r->izquierdo == NULL && r->derecho == NULL);
}

// Contar número de nodos
int NumeroNodos(Arbol a, int* c) {
    if (a) {
        (*c)++;
        NumeroNodos(a->izquierdo, c);
        NumeroNodos(a->derecho, c);
    }
    return *c;
}

// Calcular la altura de un árbol
int AlturaArbol(Arbol a, int* altura) {
    if (a) {
        AlturaArbol(a->izquierdo, altura);
        AlturaArbol(a->derecho, altura);
        (*altura)++;
    }
    return *altura;
}

// Calcular altura de un dato
int Altura(Arbol a, int dat) {
    if (a) {
        if (dat == a->dato) {
            return 0;
        } else if (dat < a->dato) {
            return 1 + Altura(a->izquierdo, dat);
        } else {
            return 1 + Altura(a->derecho, dat);
        }
    }
    return -1; // Si el dato no se encuentra
}
