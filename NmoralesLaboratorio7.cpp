#include <iostream>
#include <vector>
#include <climits>
#include <queue>
// Ejemplo de algoritmo de prim apoyado de internet
using namespace std;

#define INF INT_MAX   // INF representa que no hay conexion entre dos nodos

class Grafo {
public:
    int numVertices;
    vector<vector<int>> matrizDistancias;  // Matriz de distancias del grafo

    // Constructor para inicializar el grafo con N vertices
    Grafo(int n) : numVertices(n), matrizDistancias(n, vector<int>(n, INF)) {
        // Inicializar la diagonal de la matriz a 0 (distancia de un nodo a si mismo)
        for (int i = 0; i < n; ++i) {
            matrizDistancias[i][i] = 0;
        }
    }

    // Funcion para agregar una arista con un peso entre dos vertices
    void agregarArco(int u, int v, int peso) {
        matrizDistancias[u][v] = peso;
        matrizDistancias[v][u] = peso;  // Para grafos no dirigidos
    }

    // Mostrar la matriz de distancias (opcional, para verificar)
    void mostrarMatriz() {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                if (matrizDistancias[i][j] == INF) {
                    cout << "INF ";
                } else {
                    cout << matrizDistancias[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    // Funcion del algoritmo de prim
    void prim() {// ARBOL DE COSTO MINIMO
        vector<int> clave(numVertices, INF);  // Clave para cada vertice 
        vector<int> padre(numVertices, -1);   // Almacena el padre de cada vertice 
        vector<bool> enMST(numVertices, false);  // Marca si el vertice ya esta incluido

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> colaPrioridad;

        // Inicializar el primer vertice (indice 0)
        int origen = 0;
        clave[origen] = 0;
        colaPrioridad.push(make_pair(0, origen));

        // Algoritmo de Prim
        while (!colaPrioridad.empty()) {
            int u = colaPrioridad.top().second;
            colaPrioridad.pop();

            // Si el nodo ya tiene el costo minimo se ignora
            if (enMST[u]) continue;

            // Marcar el nodo como incluido en el arbol de costo minimo
            enMST[u] = true;

            // Explorar los vecinos de u
            for (int v = 0; v < numVertices; ++v) {
                int peso = matrizDistancias[u][v];

                // Si v no esta incluido en el arbol de costo minimo y el peso de la arista es menor que el valor minimo de la conexion actual de v
                if (!enMST[v] && peso != INF && peso < clave[v]) {
                    clave[v] = peso;
                    padre[v] = u;
                    colaPrioridad.push(make_pair(clave[v], v));
                }
            }
        }

        // Mostrar el arbol de costo minimo
        cout << "Arcos en el Arbol de Expansion Minima:\n";
        for (int i = 1; i < numVertices; ++i) {
            if (padre[i] != -1) {
                cout << "Arco: " << padre[i] << " - " << i << " Peso: " << clave[i] << "\n";
            }
        }
    }
};

int main() {
    int numVertices = 5;  // Numero de vertices en el grafo
    Grafo g(numVertices);

    // Agregar arcos con sus pesos
    // Los arcos estan ordenados de la siguiente manera 
    // (donde empieza, adonde llega, el coste)
    g.agregarArco(0, 1, 2); // Empieza del 0, llega al 1, y cuesta 2
    g.agregarArco(0, 2, 4);
    g.agregarArco(1, 2, 1);
    g.agregarArco(1, 3, 7);
    g.agregarArco(2, 3, 3);
    g.agregarArco(2, 4, 5);
    g.agregarArco(3, 4, 1);

    // Mostrar la matriz de distancias
    cout << "Matriz de distancias:" << endl;
    g.mostrarMatriz();

    // Ejecutar el algoritmo de Prim
    cout << "\nEjecutando el algoritmo de Prim...\n";
    g.prim();

    return 0;
}
