Proyecto de Alineamiento de Secuencias de ADN

Este proyecto implementa un algoritmo de alineamiento de secuencias de ADN utilizando el algoritmo de Needleman-Wunsch para encontrar el alineamiento óptimo entre dos secuencias de ADN. Utiliza una matriz de puntuación personalizada, representada por un archivo CSV, y genera una visualización gráfica del alineamiento utilizando Graphviz.

se realiza 
lectura de secuencias de ADN y se genera matriz de puntuacion
Se uso el algoritmo de Needleman-wunsh como fue sugerido en la pauta
La vizualizacion de alineamiento es generada en formato png usando GRapvhiz
Los colores de los nucleotidos son Adenina(VERDE), timina(rojo), citocina(azul), guanina(amarillo)

Instrucciones
Compilación y Ejecución

    Compilar el código: Abre una terminal y navega hasta el directorio donde está tu archivo algoritmo.cpp, luego ejecuta:

g++ algoritmo.cpp -o alineamiento

Ejecutar el programa: Una vez compilado, ejecuta el programa con los siguientes parámetros:

./alineamiento cad1.txt cad2.txt matriz_U.csv

Donde:

    cad1.txt: El archivo que contiene la primera secuencia de ADN.
    cad2.txt: El archivo que contiene la segunda secuencia de ADN.
    matriz_U.csv: El archivo CSV con la matriz de puntuación.

    Este proyecto fue hecho por NIcolas Morales