#include <iostream>
#include <string>

using namespace std ;
//STRUCT
struct Paciente {
    string nombre;
    int edad;
    double altura;
    double peso;
};

int main() {
    Paciente paciente1;
    Paciente paciente2;
    Paciente paciente3;
    // creacion de instancias
    paciente3.nombre = "Antonio";
    paciente3.edad = 20;
    paciente3.altura = 1.85;
    paciente3.peso = 100;

    paciente2.nombre = "Cristopher";
    paciente2.edad = 20;
    paciente2.altura = 1.80;
    paciente2.peso = 70;

    paciente1.nombre = "Diego";
    paciente1.edad = 20;
    paciente1.altura = 1.63;
    paciente1.peso = 89;
//Paciente 3 ATRIBUTOS
    cout << "Nombre Paciente 3: " << paciente3.nombre << "\n";
    cout << "Edad Paciente 3: " << paciente3.edad << "\n";
    cout << "Altura Paciente 3: " << paciente3.altura << "cm\n";
    cout << "Peso Paciente 3:" << paciente3.peso << "kg\n";
//Paciente 2
    cout << "Nombre Paciente 2: " << paciente2.nombre << "\n";
    cout << "Edad Paciente 2: " << paciente2.edad << "\n";
    cout << "Altura Paciente 2: " << paciente2.altura << "cm\n";
    cout << "Peso Paciente 1:" << paciente3.peso << "kg\n";
//Paciente 1
    cout << "Nombre Paciente 1: " << paciente1.nombre << "\n";
    cout << "Edad Paciente 1: " << paciente1.edad << "\n";
    cout << "Altura Paciente 1: " << paciente1.altura << "cm\n";
    cout << "Peso Paciente 1:" << paciente3.peso << "kg\n";
}