#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 

using namespace std;



void generarGraphviz(const string& alineamientoSecuencia1, const string& alineamientoSecuencia2, const string& nombreArchivo);

string leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se puede abrir el archivo : " << nombreArchivo << endl;
        exit(1);
    }
    string contenido;
    getline(archivo, contenido);
    archivo.close();
    return contenido;
}

// LEER LA MATRIZ U------------------------------
vector<vector<int>> leerMatrizU(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se pudo abrir la matriz U: " << nombreArchivo << endl;
        exit(1);
    }

    vector<vector<int>> matrizU;
    string linea;

    while (getline(archivo, linea)) {
        vector<int> fila;
        stringstream ss(linea);
        string valor;

        while (getline(ss, valor, ',')) {
            fila.push_back(stoi(valor)); 
        }

        matrizU.push_back(fila);
    }

    archivo.close();
    return matrizU;
}

// Nucleotido a indice
int indiceDeLetra(char nucleotido) {
    if (nucleotido == 'A') return 0;
    if (nucleotido == 'C') return 1;
    if (nucleotido == 'G') return 2;
    if (nucleotido == 'T') return 3;
    return -1;  
}



//LLENADO DE LA MATRIZ Y ALINEAMIENTO DE LAS SECUENCIAS----------------------------------------
void RellenarMatriz(const string& secuencia1, const string& secuencia2, const vector<vector<int>>& matrizU, int gap) {
    int longitudSecuencia1 = secuencia1.size();  // Longitudes de las secuencias
    int longitudSecuencia2 = secuencia2.size(); 

    int matriz[1000][1000] = {0};  // Tamaño de la matriz (modificable segun se requiera)

    // Rellenar la matriz
    for (int fila = 0; fila <= longitudSecuencia1; fila++) {
        for (int columna = 0; columna <= longitudSecuencia2; columna++) {
            if (fila == 0 && columna == 0) {
                matriz[fila][columna] = 0;
            } else if (fila > 0 && columna == 0) {
                matriz[fila][columna] = matriz[fila - 1][columna] + gap;  // gap en la primera secuencia
            } else if (fila == 0 && columna > 0) {
                matriz[fila][columna] = matriz[fila][columna - 1] + gap;  // gap en la segunda secuencia
            } else {
                // el puntaje diagonal
                int indice1 = indiceDeLetra(secuencia1[fila - 1]);
                int indice2 = indiceDeLetra(secuencia2[columna - 1]);
                int puntajeDiagonal = matriz[fila - 1][columna - 1] + matrizU[indice1][indice2];

                // gaps ( arriba o derecha)
                int puntajeArriba = matriz[fila - 1][columna] + gap;  // Gap en la segunda secuencia
                int puntajeIzquierda = matriz[fila][columna - 1] + gap;  // Gap en la primera secuencia

            
                matriz[fila][columna] = max(puntajeDiagonal, max(puntajeArriba, puntajeIzquierda));
            }
        }
    }

    // Imprimir la matriz de puntajes resultante
    cout << "Matriz de puntajes:\n";
    for (int fila = 0; fila <= longitudSecuencia1; fila++) {
        for (int columna = 0; columna <= longitudSecuencia2; columna++) {
            cout << matriz[fila][columna] << "\t";
        }
        cout << endl;
    }

    //-----Alineamiento
    int fila = longitudSecuencia1;
    int columna = longitudSecuencia2;
    string alineamientoSecuencia1 = "";
    string alineamientoSecuencia2 = "";

    while (fila > 0 || columna > 0) {
        if (fila > 0 && columna > 0) {
            // Puntaje diagonal con la matriz U
            int indice1 = indiceDeLetra(secuencia1[fila - 1]);
            int indice2 = indiceDeLetra(secuencia2[columna - 1]);
            int puntajeDiagonal = matriz[fila - 1][columna - 1] + matrizU[indice1][indice2];

            if (matriz[fila][columna] == puntajeDiagonal) {
                alineamientoSecuencia1 = secuencia1[fila - 1] + alineamientoSecuencia1;
                alineamientoSecuencia2 = secuencia2[columna - 1] + alineamientoSecuencia2;
                fila--;
                columna--;
            } else if (matriz[fila][columna] == matriz[fila - 1][columna] + gap) {
                alineamientoSecuencia1 = secuencia1[fila - 1] + alineamientoSecuencia1;
                alineamientoSecuencia2 = "-" + alineamientoSecuencia2;
                fila--;
            } else {
                alineamientoSecuencia1 = "-" + alineamientoSecuencia1;
                alineamientoSecuencia2 = secuencia2[columna - 1] + alineamientoSecuencia2;
                columna--;
            }
        } else if (fila > 0) {
            alineamientoSecuencia1 = secuencia1[fila - 1] + alineamientoSecuencia1;
            alineamientoSecuencia2 = "-" + alineamientoSecuencia2;
            fila--;
        } else {
            alineamientoSecuencia1 = "-" + alineamientoSecuencia1;
            alineamientoSecuencia2 = secuencia2[columna - 1] + alineamientoSecuencia2;
            columna--;
        }
    }

    // imprimir los alineamientos 
    cout << "Alineamiento de la primera secuencia: " << alineamientoSecuencia1 << endl;
    cout << "Alineamiento de la segunda secuencia: " << alineamientoSecuencia2 << endl;

    // Guardar el alineamiento en un archivo de texto (opcional) por creatividad
    ofstream outputFile("alineamiento.txt");
    if (outputFile.is_open()) {
        outputFile << "Alineamiento de la primera secuencia: " << alineamientoSecuencia1 << endl;
        outputFile << "Alineamiento de la segunda secuencia: " << alineamientoSecuencia2 << endl;
        outputFile.close();
        cout << "Alineamiento guardado en 'alineamiento.txt'.\n";
    } else {
        cerr << "Error al guardar el alineamiento.\n";
    }

    
    generarGraphviz(alineamientoSecuencia1, alineamientoSecuencia2, "alineamiento.dot");
}

// el graphvizz
void generarGraphviz(const string& alineamientoSecuencia1, const string& alineamientoSecuencia2, const string& nombreArchivo) {
    // comienza en 0 y se va ajustando segun el largo de la seq
    size_t start = 0;
    size_t end = min(alineamientoSecuencia1.length(), static_cast<size_t>(100)); // (modificable)


    ofstream dotFile(nombreArchivo);
    if (!dotFile.is_open()) {
        cerr << "No se genera el graphviz." << endl;
        return;
    }

    dotFile << "digraph G {\n";
    dotFile << "  rankdir=TB;\n";  // hace que el grafico este en horizontal
    dotFile << "  node [shape=ellipse, style=filled];\n"; // nodos con colorsito



    // CAJITA----------------------------------COLORES------------------------------------------
    dotFile << "   subgraph cluster_info {\n";
    dotFile << "       label=\"Colores\";\n";
    dotFile << "       style=dotted;\n";
    dotFile << "       node [style=filled, width=0.1, fontsize=3];\n";  // TAMAÑO NODOS---
    dotFile << "       ranksep=0.05;\n";  
// cada nucleotido
    dotFile << "       A_legend [label=\"Adenina (A)\", shape=ellipse, fillcolor=green];\n";
    dotFile << "       T_legend [label=\"Timina (T)\", shape=ellipse, fillcolor=red];\n";
    dotFile << "       C_legend [label=\"Citosina (C)\", shape=ellipse, fillcolor=blue];\n";
    dotFile << "       G_legend [label=\"Guanina (G)\", shape=ellipse, fillcolor=yellow];\n";
    dotFile << "       Match [label=\"Match\", shape=plaintext, color=green];\n";
    dotFile << "       Gap [label=\"Gap\", shape=plaintext, color=red];\n";
    dotFile << "   }\n";
    auto obtenerColor = [](char nucleotido) {
        switch (nucleotido) {
            case 'A': return "green";   // Adenina
            case 'T': return "red";     // Timina
            case 'C': return "blue";    // Citosina
            case 'G': return "yellow";  // Guanina
            default: return "gray";     // para que los gaps
        }
    };

    // ciclo for que itera por el rango que tenga la secuencia de nucleotidos
    for (size_t k = start; k < end; k++) {
        char nucleoA = alineamientoSecuencia1[k];
        char nucleoB = alineamientoSecuencia2[k];


        // se le asigna el color a cada nucleotido
        dotFile << "   A" << k << " [label=\"" << nucleoA << "\", fillcolor=" << obtenerColor(nucleoA) << "];\n";
        dotFile << "   B" << k << " [label=\"" << nucleoB << "\", fillcolor=" << obtenerColor(nucleoB) << "];\n";

        // conexiones (MATCH,GAP)
        if (nucleoA != '-' && nucleoB != '-') {
            dotFile << "   A" << k << " -> B" << k << " [label=\"Match\" color=green];\n";
        } else if (nucleoA == '-' || nucleoB == '-') {
            dotFile << "   A" << k << " -> B" << k << " [label=\"Gap\" color=red];\n";
        }
    }

    dotFile << "}\n";
    dotFile.close();

    cout << "Alineamiento Grapvhiz guardado como '" << nombreArchivo << "'." << endl;
    system("dot -Tpng alineamiento.dot -o alineamiento.png");
    system("eog alineamiento.png&");
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Ejecucion incorrecta. Es:\n";
        cerr << "./a.out cad1.tex cad2.tex Matriz_U.csv";
        return 1;
    }

//prueba con cadenas mas largas: AGCTTAGGCTAAGCTTAGGCTTAGCTAAGCT
//TCGATCGATCGATCGATCGTC



    string secuencia1 = leerArchivo(argv[1]);
    string secuencia2 = leerArchivo(argv[2]);

    vector<vector<int>> matrizU = leerMatrizU(argv[3]);

    int gap = -1;  // Puntaje para gaps

    RellenarMatriz(secuencia1, secuencia2, matrizU, gap);

    return 0;
}
