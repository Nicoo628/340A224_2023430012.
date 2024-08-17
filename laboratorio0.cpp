#include <iostream> 
#include <string>
bool numero_par_impar(int n) {
    return n % 2 == 0;  // si es divisible por 2 es par (devuelve true)
}
int longitud_string(std::string str) {// parametros de la funcion de longitud string
    return str.length();// se usa el length que devuelve un valor en este caso representado la cantidad de string

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


//////////////////////////////////////////////////
// string del usuario
std::string string_usuario;
std::cout << "Ingrese un string:" ;
std::cin >> string_usuario;
std::cout << "longitud del String ingresado es de: "<< longitud_string(string_usuario) << std::endl;

//ejemplo directo
std::string ejemplo = "Paralelepido";
std::cout << "La longitud del string Paralelepipedo es de:" << longitud_string(ejemplo) << std::endl;


}

