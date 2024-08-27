#include <iostream>
#include <string>

using namespace std ;
//STRUCT
struct Persona {
    string nombre;
    int edad;
    double altura;
    double peso;
};

int main() { 
    //Creacion del arreglo para 3 objetos
    Persona paciente[4];



    // creacion de instancias
    paciente[0].nombre = "Javier";
    paciente[0].edad = 20;
    paciente[0].altura = 1.85;
    paciente[0].peso = 100;

    paciente[1].nombre = "Cristopher";
    paciente[1].edad = 20;
    paciente[1].altura = 1.80;
    paciente[1].peso = 70;

    paciente[2].nombre = "Diego";
    paciente[2].edad = 20;
    paciente[2].altura = 1.63;
    paciente[2].peso = 89;
// Imprimir la informacion desde el arreglo
    for (int i = 0; i < 3; ++i) {
        cout << "Nombre: " << paciente[i].nombre <<"\n";
        cout << "Edad: " << paciente[i].edad <<"\n";
        cout << "Altura: " << paciente[i].altura <<"cm\n";
        cout << "Peso: " << paciente[i].peso <<"kg\n";
        cout << endl;
    }

    return 0;
}
