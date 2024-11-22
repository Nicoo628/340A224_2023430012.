#include <iostream>
#include <algorithm> // Para std::max
using namespace std;

// rellenar matriz
void RellenarMatriz(const string& secuencia1, const string& secuencia2, int coincidencia, int diferencia, int gap) {
    int longitudSecuencia1 = secuencia1.size(); // Longitudes de las secuencias
    int longitudSecuencia2 = secuencia2.size(); 


    int matriz[100][100] = {0}; //tamaño matriz

    // Rellenar la matriz
    for (int fila = 0; fila <= longitudSecuencia1; fila++) { // los ++ son para controlar mejor los bucles
        for (int columna = 0; columna <= longitudSecuencia2; columna++) {
            if (fila == 0 && columna == 0) {
                matriz[fila][columna] = 0; 

            } else if (fila > 0 && columna == 0) {
                matriz[fila][columna] = matriz[fila - 1][columna] + gap; // gap en la primera sec
            } else if (fila == 0 && columna > 0) {
                matriz[fila][columna] = matriz[fila][columna - 1] + gap; // gap en la segunda sec
            } else {
                // Calculamos el puntaje diagonal (si los caracteres coinciden o no)
                int puntajeDiagonal;
                if (secuencia1[fila - 1] == secuencia2[columna - 1]) {
                    puntajeDiagonal = matriz[fila - 1][columna - 1] + coincidencia; // Coincidencia
                } else {
                    puntajeDiagonal = matriz[fila - 1][columna - 1] + diferencia; // No coincidencia
                }

                int puntajeArriba = matriz[fila - 1][columna] + gap;   // Gap en la segunda secuencia
                int puntajeIzquierda = matriz[fila][columna - 1] + gap; // Gap en la primera secuencia

                // Calcular el máximo de las tres opciones
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



    //-----ALINEAMIENTO
    int fila = longitudSecuencia1;
    int columna = longitudSecuencia2;
    string alineamientoSecuencia1 = "";
    string alineamientoSecuencia2 = "";


    while (fila > 0 || columna > 0) {// para ir recorriendo la matris inversamente
        if (fila > 0 && columna > 0) {//(Esquina inferior izquierda hacia arriba)
            // en diagoal
            int puntajeDiagonal;
            if (secuencia1[fila - 1] == secuencia2[columna - 1]) {
                puntajeDiagonal = matriz[fila - 1][columna - 1] + coincidencia; // Coincidencia
            } else {
                puntajeDiagonal = matriz[fila - 1][columna - 1] + diferencia; // Diferencia
            }

            if (matriz[fila][columna] == puntajeDiagonal) {
                alineamientoSecuencia1 = secuencia1[fila - 1] + alineamientoSecuencia1;
                alineamientoSecuencia2 = secuencia2[columna - 1] + alineamientoSecuencia2;
                fila--; 
                columna--; 
            } else if (matriz[fila][columna] == matriz[fila - 1][columna] + gap) {
                // se mueve hacia arriba (gap en la segunda secuencia (T))
                alineamientoSecuencia1 = secuencia1[fila - 1] + alineamientoSecuencia1;
                alineamientoSecuencia2 = "-" + alineamientoSecuencia2;
                fila--;
            } else {
                // se mueve hacia la izquierda (gap en la primera secuencia (S))
                alineamientoSecuencia1 = "-" + alineamientoSecuencia1;
                alineamientoSecuencia2 = secuencia2[columna - 1] + alineamientoSecuencia2;
                columna--;
            }

        } else if (fila > 0) {
            // Movimiento hacia arriba (solo fila restante)
            alineamientoSecuencia1 = secuencia1[fila - 1] + alineamientoSecuencia1;
            alineamientoSecuencia2 = "-" + alineamientoSecuencia2;
            fila--;

        } else {
            // Movimiento hacia la izquierda (solo columna restante)
            alineamientoSecuencia1 = "-" + alineamientoSecuencia1;
            alineamientoSecuencia2 = secuencia2[columna - 1] + alineamientoSecuencia2;
            columna--;
        }
    }

    // Imprimir el alineamiento 
    cout << "Alineamiento de la primera secuencia: " << alineamientoSecuencia1 << endl;
    cout << "Alineamiento de la segunda secuencia: " << alineamientoSecuencia2 << endl;
}

int main() {
    // secuencias
    string primeraSecuencia = "CAGCTAGCG"; // eje y
    string segundaSecuencia = "CCATACGA"; // eje x

    // reglas
    int coincidencia = 1;
    int diferencia = -1;
    int gap = -1;

    // mostrar
    RellenarMatriz(primeraSecuencia, segundaSecuencia, coincidencia, diferencia, gap);

    return 0;
}
