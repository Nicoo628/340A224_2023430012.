#include <iostream>
#include <cstdlib> 
#include <fstream>
#include <climits>
#include <limits>
#include <vector>
#include <string>

using namespace std;

void inicializar_matriz_enteros(int **matriz, int n);
void imprimir_matriz(int **matriz, int n);
void leer_matriz(int **matriz, int n);
void imprimir_grafo(int **matriz, string *V, int n);
void dijkstra(int **matriz, int n, int origen, int *dist, bool *visitado);
void mostrar_distancias(int *dist, int n);
void mostrar_menu();

// Inicializar la matriz de enteros
void inicializar_matriz_enteros(int **matriz, int n) {
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            // Se inicializa con el -1 para indicar que no hay conexión
            matriz[fila][col] = -1; 
        }
    }
}

// Imprimir la matriz nxn
void imprimir_matriz(int **matriz, int n) {
    cout << endl << "Matriz de distancias: " << endl;
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            if (matriz[fila][col] == -1) {
                cout << "INF ";
            } else {
                cout << matriz[fila][col] << " ";
            }
        }
        cout << endl;
    }
}

// Leer matriz desde la terminal
void leer_matriz(int **matriz, int n) {
    cout << "Ingrese los valores de la matriz:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Distancia de nodo " << i << " a nodo " << j << ": ";
            cin >> matriz[i][j];
            if (matriz[i][j] < 0 && i != j) {
                cout << "Error: la distancia entre nodos no puede ser negativa." << endl;
                cout << "Por favor, ingrese nuevamente la distancia." << endl;
                --j; // Decrementar para reingresar el valor en la misma posición
            }
        }
    }
}

// Imprimir el grafo en formato dot para Graphviz
void imprimir_grafo(int **matriz, string *V, int n) {
    ofstream fp("grafo.txt");
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
    
    // Para generar el grafo usando Graphviz
    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

// Implementación del Algoritmo de Dijkstra
void dijkstra(int **matriz, int n, int origen, int *dist, bool *visitado) {
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

// Mostrar las distancias calculadas por Dijkstra
void mostrar_distancias(int *dist, int n) {
    cout << "Distancias mínimas desde el nodo origen:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Distancia al nodo " << i << ": ";
        if (dist[i] == INT_MAX) {
            cout << "Inalcanzable" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }
}

void mostrar_menu() {
    cout << "\n--- Menú ---" << endl;
    cout << "1. Ingresar matriz de distancias" << endl;
    cout << "2. Ejecutar algoritmo de Dijkstra" << endl;
    cout << "3. Imprimir grafo" << endl;
    cout << "4. Imprimir matriz de distancias" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opción: ";
}

int main(int argc, char **argv) {
    int n;
    // Validar la cantidad de parámetros mínimos
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <número de vértices>" << endl;
        return 1;
    }

    // Convertir string a entero
    n = atoi(argv[1]);

    // Validar el valor de n
    if (n < 2) {
        cout << "El número de vértices debe ser mayor que 1." << endl;
        return 1;
    }

    // Crear matriz nxn de enteros
    int **matriz;
    matriz = new int*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new int[n];
    }

    string *nombres_nodos = new string[n];
    for (int i = 0; i < n; i++) {
        nombres_nodos[i] = "Nodo" + to_string(i);
    }

    int *dist = new int[n];
    bool *visitado = new bool[n];

    // Inicializar la matriz
    inicializar_matriz_enteros(matriz, n);

    // Menú interactivo
    bool salir = false;
    while (!salir) {
        mostrar_menu();
        int opcion;
        cin >> opcion;

        switch (opcion) {
            case 1:
                leer_matriz(matriz, n);
                break;

            case 2:
                int origen;
                cout << "Ingrese el nodo de origen: ";
                cin >> origen;
                if (origen < 0 || origen >= n) {
                    cout << "Nodo de origen no válido." << endl;
                    break;
                }
                dijkstra(matriz, n, origen, dist, visitado);
                mostrar_distancias(dist, n);
                break;

            case 3:
                imprimir_grafo(matriz, nombres_nodos, n);
                cout << "Grafo generado con éxito. Revisa el archivo 'grafo.png'." << endl;
                break;

            case 4:
                imprimir_matriz(matriz, n);
                break;

            case 5:
                salir = true;
                break;

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
    delete[] dist;
    delete[] visitado;
    delete[] nombres_nodos;

    return 0;
}
