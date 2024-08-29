#include <iostream>
#include <string>

using namespace std ;
// Estructura para una lista
struct Paciente {
    string nombre;
    int edad;
    double altura;
    double peso;
    Paciente* next;
};

// Funcion para añadir un nuevo paciente a la lista

void AñadirPaciente(Paciente*& head, const string& nombre, int edad, double peso,double altura) {
    Paciente* NuevoPaciente = new Paciente();
    NuevoPaciente->nombre = nombre;
    NuevoPaciente->edad = edad;
    NuevoPaciente->altura = altura;
    NuevoPaciente->peso = peso;
    NuevoPaciente->next = head;
    head = NuevoPaciente;
}

//Funcion para eliminar una persona de la lista por el nombre
void EliminarPaciente(Paciente*& head, const string& nombre) {
    Paciente* actual = head;
    Paciente* anterior = nullptr;

    while (actual != nullptr && actual->nombre !=nombre) {
        anterior = actual;
        actual = actual->next;
    }

    if (actual != nullptr) {
        if (anterior == nullptr) {
            head = actual->next;
        } else {
            anterior->next = anterior->next; 
        }
        delete actual;
    }
}

// Funcion para imprimir toda la gente de la lista
void ImprimirPaciente(const Paciente* head) {
    const Paciente* actual = head;
    int contador = 1; //para ir numerando a los pacientes y se vea mas ordenado

    while (actual != nullptr) {
        cout << "Nombre: " << actual -> nombre << "\n";
        cout << "Edad: " << actual -> edad << "\n";
        cout << "Peso: " << actual -> peso << "kg\n";
        cout << "altura: "<< actual -> altura << "cm\n";
        cout <<"n"; 
    


        actual = actual->next;
        contador++;    
    }
}



void PromedioPeso(Paciente*& head){

    int contador;
    int peso_total;
    const Paciente* actual = head;

    while (actual != nullptr){

        contador = contador + 1;
        peso_total= peso_total + actual -> edad;
        actual = actual -> next;
    }
    
    cout << "El promedio de los pesos de los pacientes es de " << peso_total/contador << "kg.\n";
}

void PromedioEdad(Paciente*& head){

    int contador;
    int edad_total;
    const Paciente* actual = head;

    while (actual != nullptr){

        contador = contador + 1;
        edad_total= edad_total + actual -> edad;
        actual = actual -> next;
    }
    
    cout << "El promedio de edad de los pacientes es de " << edad_total/contador << "kg.\n";
}

        



int main() {
    Paciente* head= nullptr;
    //orden: nombre, edad, peso, altura
AñadirPaciente(head, "Cristopher Reyes", 21, 100, 1.83);
AñadirPaciente(head, "Nicolas Morales", 19,70, 1.72);
AñadirPaciente(head, "Eustaquio Tamarindo", 94, 70, 2.01);

ImprimirPaciente(head);
EliminarPaciente(head, "a");// no me dejaba poner sin el "a" porque no se llamaban todos los parametros de la funcion
return 0;
}