#include <iostream>
#include <cstdlib> 
#include <fstream>
#include <climits>

using namespace std;

// inicializar matriz. recibe puntero a la matriz.
void inicializar_matriz_enteros(int **matriz, int n) {
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
        // Se inicializa con el -1 para indicar que no hay conexion
            matriz[fila][col] = -1; 
        }
    }
}

// imprime matriz nxn
void imprimir_matriz(int **matriz, int n) {
    cout << endl;
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            cout << matriz[fila][col] << " ";
        }
        cout << endl;
    }
}

// leer matriz desde terminal
void leer_matriz(int **matriz, int n) {
    cout << " Ingrese los valore de la matriz:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Distancia de nodo" << i << " a nodo " << j << " :0 " ;
            cin >> matriz[i][j];
        }
    }
}

void imprimir_grafo(int **matriz, string *V, int n) {
    std::ofstream fp("grafo.txt");

    fp << "digraph G {\n";
    fp << "graph [rankdir=LR]\n";
    fp << "node [style=filled fillcolor=yellow];\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matriz[i][j] > 0) {
                fp << V[i] << "->" << V[j] << " [label=" << matriz[i][j] << "];\n";
            }
        }
    }

    fp << "}\n";
    fp.close();

    // Para generar el grafo usando Grapvhiz
    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}
void dijkstra(int **matriz, int n, int origen, int *dist, bool *visitado) {
    // Inicializamos las distancias
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX; // Distancia infinita
        visitado[i] = false; // Ningún nodo ha sido visitado aún
    }

    dist[origen] = 0; // La distancia del nodo origen es 0

    for (int i = 0; i < n; i++) {
        // Encontrar el nodo no visitado con la menor distancia
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INT_MAX) break; // Si la menor distancia es infinita, no hay más nodos alcanzables

        visitado[u] = true;

        // Actualizar distancias de los nodos adyacentes
        for (int v = 0; v < n; v++) {
            if (matriz[u][v] != -1 && !visitado[v]) {
                int nuevaDist = dist[u] + matriz[u][v];
                if (nuevaDist < dist[v]) {
                    dist[v] = nuevaDist;
                }
            }
        }
    }
}


int main(int argc, char **argv) {
// numero de elementos
int n;
    // Valida la cantidad de parametros minimos
    if (argc < 2) {
        cout << "Uso: \n./matriz n" << endl;
        return -1;
    }

    // Convertir string a entero
    int n = atoi(argv[1]);

    // Crear matriz nxn de enteros
    int **matriz;
    matriz = new int*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new int[n];
    }

    
    inicializar_matriz_enteros(matriz, n);
    imprimir_matriz(matriz, n);

    // para liberar memoria
    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}
