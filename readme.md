Proyecto de Alineamiento de Secuencias de ADN

En esteproyecto implementa un programa en C++ para realizar el alineamiento de dos secuencias biológicas utilizando una matriz de puntajes y el algoritmo Needleman-Wunsch. Además, el programa genera una visualización en formato Graphviz para representar el alineamiento resultante.

Características principales:
Lectura de una matriz de emparejamiento (matriz U) desde un archivo CSV.
Rellenado de la matriz de alineamiento según el algoritmo de alineamiento global.
Cálculo y visualización de las secuencias alineadas.
Generación de un archivo de alineamiento en formato texto.
Creación de un archivo Graphviz para representar el alineamiento en un grafo visual.


Archivos incluidos

main.cpp: Contiene el código fuente principal con las funciones para leer, procesar y generar alineamientos.

alineamiento.txt: Archivo de salida que almacena las secuencias alineadas.

alineamiento.dot: Archivo de salida en formato Graphviz para la visualización del alineamiento.

matrizU.csv: Archivo de entrada con la matriz de emparejamiento.

cad1.tex y cad2.tex: que tienen las secuencias
Instrucciones de uso ( compila con el siguiente comando): ./a.out cad1.tex cad2.tex Matriz_U.csv