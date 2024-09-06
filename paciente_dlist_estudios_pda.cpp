#include <iostream>
#include <string>
#include <cmath> // Para la función pow
#include <fstream>
#include <sstream>
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

// Función para calcular el índice de prioridad (IMC + A1C)
int CalcularIndicePrioridad(const Paciente* paciente) {
    int riesgoIMC = 0;
    int riesgoA1C = 0;

    // Riesgo del IMC
    if (paciente->imc >= 18.5 && paciente->imc <= 24.9) {
        riesgoIMC = 1;
    } else if (paciente->imc >= 25 && paciente->imc <= 29.9) {
        riesgoIMC = 2;
    } else if (paciente->imc >= 30) {
        riesgoIMC = 3;
    }

    // Riesgo del A1C
    if (paciente->a1c < 5.7) {
        riesgoA1C = 1;
    } else if (paciente->a1c >= 5.7 && paciente->a1c <= 6.4) {
        riesgoA1C = 2;
    } else if (paciente->a1c >= 6.5) {
        riesgoA1C = 3;
    }

    return riesgoIMC + riesgoA1C;
}

// Función para añadir un nuevo paciente a la lista, manteniendo el orden por prioridad
void AñadirPaciente(Paciente*& head, const string& nombre, int edad, double peso, double altura, double a1c) {
    Paciente* NuevoPaciente = new Paciente();
    NuevoPaciente->nombre = nombre;
    NuevoPaciente->edad = edad;
    NuevoPaciente->altura = altura;
    NuevoPaciente->peso = peso;
    NuevoPaciente->a1c = a1c;
    NuevoPaciente->imc = peso / pow(altura, 2); // Se calcula y almacena el IMC aquí

    int prioridadNuevo = CalcularIndicePrioridad(NuevoPaciente);

    if (head == nullptr || CalcularIndicePrioridad(head) < prioridadNuevo) {
        NuevoPaciente->next = head;
        head = NuevoPaciente;
    } else {
        Paciente* actual = head;
        while (actual->next != nullptr && CalcularIndicePrioridad(actual->next) >= prioridadNuevo) {
            actual = actual->next;
        }
        NuevoPaciente->next = actual->next;
        actual->next = NuevoPaciente;
    }
}

// Función para eliminar un paciente de la lista por el nombre
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

// Función para imprimir toda la lista de pacientes
void ImprimirPaciente(const Paciente* head) {
    const Paciente* actual = head;
    int contador = 1; // Para numerar a los pacientes

    while (actual != nullptr) {
        cout << "Paciente " << contador << ":\n";
        cout << "Nombre: " << actual->nombre << "\n";
        cout << "Edad: " << actual->edad << "\n";
        cout << "Peso: " << actual->peso << " kg\n";
        cout << "Altura: " << actual->altura << " m\n";
        cout << "IMC: " << actual->imc << "\n";
        cout << "A1C: " << actual->a1c << "\n\n";
        actual = actual->next;
        contador++;
    }
}

// Función para calcular el promedio del peso
void PromedioPeso(Paciente*& head) {
    int contador = 0;
    double peso_total = 0;
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

// Función para calcular el promedio de la edad
void PromedioEdad(Paciente*& head) {
    int contador = 0;
    int edad_total = 0;
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

// Función para calcular y mostrar el IMC de los pacientes
void CalcularIMC(const Paciente* head) {
    const Paciente* actual = head;

    while (actual != nullptr) {
        double imc = actual->peso / pow(actual->altura, 2);
        cout << actual->nombre << " posee un IMC de: " << imc << "\n";
        actual = actual->next;
    }
}

// Función para calcular la prioridad del A1C de los pacientes
void CalculoPrioridadA1C(const Paciente* head) {
    const Paciente* actual = head;

    while (actual != nullptr) {
        if (actual->a1c > 6.5) {
            cout << actual->nombre << " tiene un nivel de A1C elevado (Diabetes).\n";
        } else if (actual->a1c >= 5.7) {
            cout << actual->nombre << " tiene un nivel de A1C en Prediabetes.\n";
        } else {
            cout << actual->nombre << " tiene un nivel de A1C estándar.\n";
        }
        actual = actual->next;
    }
}

// Función para cargar los pacientes desde un archivo CSV
void CargarPacientesCSV(Paciente*& head, const string& paciente_lista) {
    ifstream archivo(paciente_lista);
    string linea;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    getline(archivo, linea); // Descarta el encabezado

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre;
        int edad;
        double altura;
        double peso;
        double a1c;
        string valor;

        getline(ss, nombre, ',');
        getline(ss, valor, ',');
        edad = stoi(valor);
        getline(ss, valor, ',');
        altura = stod(valor);
        getline(ss, valor, ',');
        peso = stod(valor);
        getline(ss, valor, ',');
        a1c = stod(valor);

        AñadirPaciente(head, nombre, edad, peso, altura, a1c);
    }

    archivo.close();
}

// Función para buscar un paciente por su IMC
void BuscarPacienteIMC(const Paciente* head, double imcBuscado) {
    const Paciente* actual = head;
    bool encontrado = false;

    while (actual != nullptr) {
        if (fabs(actual->imc - imcBuscado) < 0.01) {
            cout << "Paciente con IMC de " << imcBuscado << " encontrado:\n";
            cout << "Nombre: " << actual->nombre << "\n";
            cout << "Edad: " << actual->edad << "\n";
            cout << "Peso: " << actual->peso << "kg\n";
            cout << "Altura: " << actual->altura << "m\n";
            cout << "IMC: " << actual->imc << "\n";
            encontrado = true;
        }
        actual = actual->next;
    }

    if (!encontrado) {
        cout << "Ningún paciente tiene un IMC de " << imcBuscado << ".\n";
    }
}

// Función para buscar un paciente por su A1C
void BuscarPacienteA1C(const Paciente* head, double a1cBuscado) {
    const Paciente* actual = head;
    bool encontrado = false;

    while (actual != nullptr) {
        if (fabs(actual->a1c - a1cBuscado) < 0.01) {
            cout << "Paciente con A1C de " << a1cBuscado << " encontrado:\n";
            cout << "Nombre: " << actual->nombre << "\n";
            cout << "Edad: " << actual->edad << "\n";
            cout << "Peso: " << actual->peso << "kg\n";
            cout << "Altura: " << actual->altura << "m\n";
            cout << "A1C: " << actual->a1c << "\n";
            encontrado = true;
        }
        actual = actual->next;
    }

    if (!encontrado) {
        cout << "Ningún paciente tiene un A1C de " << a1cBuscado << ".\n";
    }
}

// Función para mostrar la prioridad de atención de los pacientes
void PrioridadAtencion(const Paciente* head) {
    const Paciente* actual = head;

    while (actual != nullptr) {
        int IndicePrioridad = CalcularIndicePrioridad(actual);

        cout << "Paciente: " << actual->nombre << "\n";
        cout << "IMC: " << actual->imc << "\n";
        cout << "A1C: " << actual->a1c << "\n";
        cout << "Índice de Prioridad: " << IndicePrioridad << " (entre 2 y 6, donde 6 es la mayor prioridad)\n";
        cout << "------------------------------------------\n";

        actual = actual->next;
    }
}

int main() {
    Paciente* head = nullptr;
    CargarPacientesCSV(head, "paciente_lista.csv");

    ImprimirPaciente(head);
    PromedioEdad(head);
    PromedioPeso(head);
    CalcularIMC(head);
    CalculoPrioridadA1C(head);

    EliminarPaciente(head, "a"); // Solo un ejemplo para probar la función de eliminación

    // Buscar pacientes por IMC y A1C con ejemplos
    BuscarPacienteIMC(head, 22.921);
    BuscarPacienteA1C(head, 5.7);

    PrioridadAtencion(head);

    return 0;
}
