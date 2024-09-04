#include <iostream>
#include <string>
#include <cmath> // Para la función pow

using namespace std;

// Estructura para una lista
struct Paciente {
    string nombre;
    int edad;
    double altura; 
    double peso; 
    double imc;
    double a1c;
    Paciente* next;
};

// Funcion para añadir un nuevo paciente a la lista
void AñadirPaciente(Paciente*& head, const string& nombre, int edad, double peso, double altura, double a1c) {
    Paciente* NuevoPaciente = new Paciente();
    NuevoPaciente->nombre = nombre;
    NuevoPaciente->edad = edad;
    NuevoPaciente->altura = altura;
    NuevoPaciente->peso = peso;
    NuevoPaciente->a1c =a1c;
    NuevoPaciente->imc = peso / pow(altura, 2);// se calcula y almacena el imc acaa
    NuevoPaciente->next = head;
    head = NuevoPaciente;
}

// Funcion para eliminar una persona de la lista por el nombre
void EliminarPaciente(Paciente*& head, const string& nombre) {
    Paciente* actual = head;
    Paciente* anterior = nullptr;

    while (actual != nullptr && actual->nombre != nombre) {
        anterior = actual;
        actual = actual->next;
    }

    if (actual != nullptr) {
        if (anterior == nullptr) {
            head = actual->next;
        } else {
            anterior->next = actual->next;
        }
        delete actual;
    }
}

// Funcion para imprimir toda la gente de la lista
void ImprimirPaciente(const Paciente* head) {
    const Paciente* actual = head;
    int contador = 1; // Para ir numerando a los pacientes y se vea más ordenado

    while (actual != nullptr) {
        cout << "Nombre: " << actual->nombre << "\n";
        cout << "Edad: " << actual->edad << "\n";
        cout << "Peso: " << actual->peso << "kg\n";
        cout << "Altura: " << actual->altura << "m\n"; // Altura en metros
        cout << "\n"; // Línea en blanco entre pacientes

        actual = actual->next;
        contador++;
    }
}

void PromedioPeso(Paciente*& head) {
    int contador = 0;
    double peso_total = 0; // Inicializar como 0
    const Paciente* actual = head;

    while (actual != nullptr) {
        contador++;
        peso_total += actual->peso;
        actual = actual->next;
    }

    if (contador > 0) {
        cout << "El promedio de los pesos de los pacientes es de " << peso_total / contador << " kg.\n";
    } else {
        cout << "No hay pacientes en la lista para calcular el promedio de peso.\n";
    }
}

void PromedioEdad(Paciente*& head) {
    int contador = 0;
    int edad_total = 0; // Inicializar como 0
    const Paciente* actual = head;

    while (actual != nullptr) {
        contador++;
        edad_total += actual->edad;
        actual = actual->next;
    }

    if (contador > 0) {
        cout << "El promedio de edad de los pacientes es de " << edad_total / contador << " años.\n";
    } else {
        cout << "No hay pacientes en la lista para calcular el promedio de edad.\n";
    }
}

void CalcularIMC(const Paciente* head) {
    const Paciente* actual = head;

    while (actual != nullptr) {
        // IMC = peso / (altura^2)
        double imc = actual->peso / pow(actual->altura, 2);

        cout << actual->nombre << " posee un IMC de: " << imc << "\n";

        actual = actual->next;
    }
} 

void CalculoPrioridad(const Paciente* head) {
    const Paciente* actual = head;

while (actual !=nullptr) {// para que recorra todos los pacientes
    if (actual->a1c > 6.5) {
        cout << actual->nombre << "Tiene el nivel de A1C elevado (Diabetes).\n";
    } else if (actual->a1c >= 5.7) {
        cout << actual->nombre << "Tiene el nivel de A1C en Prediabetes.\n ";
    } else {
        cout << actual->nombre << " Tiene un nivel de A1C estandar. \n";
    }
    actual = actual->next;
}

}
 

int main() {;
    Paciente* head = nullptr;
    // Orden: nombre, edad, peso, altura, a1c
    AñadirPaciente(head, "Cristopher Reyes ", 22, 100, 1.83, 5.2);
    AñadirPaciente(head, "Nicolas Morales ", 19, 64, 1.71, 6.1);
    AñadirPaciente(head, "Eustaquio Tamarindo ", 94, 70, 2.01, 7.0);
    
    ImprimirPaciente(head);
    PromedioEdad(head);
    PromedioPeso(head);
    CalcularIMC(head);
    CalculoPrioridad(head);

    EliminarPaciente(head, "a"); // no me dejaba poner sin el "a" porque no se llamaban todos los parámetros de la función
    return 0;
}
