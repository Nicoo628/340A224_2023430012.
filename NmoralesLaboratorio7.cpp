#include <iostream>
#include <vector>
#include <climits>
// Ejemplo de algoritmo de prim apoyado de internet
using namespace std;

#define INF INT_MAX

class Grafo {
public:
    int numVertices;
    vector<vector<int>> matrizDistancias;  // Matriz de distancias del grafo

    // Constructor para inicializar el grafo con N vértices
    Grafo(int n) : numVertices(n), matrizDistancias(n, vector<int>(n, INF)) {
        // Inicializar la diagonal de la matriz a 0 (distancia de un nodo a sí mismo)
        for (int i = 0; i < n; ++i) {
            matrizDistancias[i][i] = 0;
        }
    }

    // Función para agregar una arista con un peso entre dos vértices
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
};

int main() {
    int numVertices = 5;  // Número de vértices en el grafo
    Grafo g(numVertices);

    // Agregar arcos con sus pesos
    // Los arcos estan ordenados de la siguiente manera 
    // (donde empieza,adonde llega,el coste)
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

    return 0;
}
