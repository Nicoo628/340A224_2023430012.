#include <iostream> 

bool numero_par_impar(int n) {
    return n % 2 == 0;  // si es divisible por 2 es par (devuelve true)


}
int main() {
    int numero; 
    std::cout << "Ingrese un numero ";
    std::cin >> numero;// para almacenar

    if (numero_par_impar(numero)) {
        std::cout << "El número " << numero << " es par." << std::endl;
    } else {
        std::cout << "El número " << numero << " es impar." << std::endl;
    }
//NUMERO DEL 1 AL 10
    for (int i = 1; i <= 10; i++) { 
        if (numero_par_impar(i)) {
            std::cout << "El número " << i << " es par." << std::endl;
        } else {
            std::cout << "El número " << i << " es impar." << std::endl;
        }
    }




}







//INDICACIONES
// Leer un numero y almacenarlo en una variable
//crear funcion que identifique si el numero es par ono
// crear una funcion que determine la longitud de un string
