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

void CalculoPrioridadA1C(const Paciente* head) {
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
 
//Funcion para cargar desde el archivo csv (REUTILIZADO DE EJEMPLO GUARDIANES)
void CargarPacientesCSV (Paciente*& head, const string& paciente_lista){
    ifstream archivo(paciente_lista);
    string linea;

    if (!archivo.is_open()) {
    cout << "Nose pudo abrir el archivo. \n";
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

// Funciones para buscar al paciente ya sea por su imc o a1c
void BuscarPacienteIMC(const Paciente* head, double imcBuscado) {// se compara con poco margen de error
    const Paciente* actual = head;
    bool encontrado = false;

    while (actual != nullptr) {
        if (fabs(actual->imc - imcBuscado) < 0.01) {
            cout << " Paciente con IMC de " <<imcBuscado << " encontrado:\n";
            cout << "Nombre: " << actual -> nombre << "\n";
            cout << "Edad: " << actual -> edad << "\n";
            cout << "Peso: " << actual -> peso << "kg\n";
            cout << "Altura: " << actual -> altura <<"m\n";
            cout << "IMC: " << actual -> imc << "\n";
            encontrado = true;

    }
    actual = actual ->next;
 }

 if (!encontrado) {
    cout << " Ningun paciente tiene un IMC de " << imcBuscado << ".\n";
    }
}
// reclicle literalmente lo mismo 
void BuscarPacienteA1C(const Paciente* head, double a1cBuscado) {// se compara con poco margen de error
    const Paciente* actual = head;
    bool encontrado = false;

    while (actual != nullptr) {
        if (fabs(actual->a1c - a1cBuscado) < 0.01) {
            cout << " Paciente con A1C de " <<a1cBuscado << " encontrado:\n";
            cout << "Nombre: " << actual -> nombre << "\n";
            cout << "Edad: " << actual -> edad << "\n";
            cout << "Peso: " << actual -> peso << "kg\n";
            cout << "Altura: " << actual -> altura <<"m\n";
            cout << "A1C: " << actual -> imc << "\n";
            encontrado = true;

    }
    actual = actual ->next;
 }

 if (!encontrado) {
    cout << "Ningun paciente tiene un A1C de " << a1cBuscado << ".\n";
    }
}
// La manera que voy a calcular la prioridad todal va a ser la siguiente(Tome parte de su idea que explico en clases)
// voy a darles valores numericos a cada "fase" entre la imc y a1c, desde 1 hasta el 3 cada una
//El riesgo mas bajo del 1 hasta el mas alto 3, y la suma entre ellas seria la prioridad del paciente
// Los valores totales de la prioridad final seria de 2-6
void PrioridadAtencion(const Paciente* head) {
    const Paciente* actual = head;

while  (actual != nullptr){
    int riesgoIMC = 0;
    int riesgoA1C = 0;

    // Riesgo del IMC
    if (actual ->imc >= 18.5 && actual -> imc <= 24.9) {
        riesgoIMC = 1;
    } else if (actual ->imc >= 25 && actual ->imc <= 29.9) {
        riesgoIMC = 2;
    } else if (actual ->imc >= 30) {
        riesgoIMC = 3;
    }


    // Riesgo del A1C 
    if (actual ->a1c < 5.7) {
        riesgoA1C = 1;
    } else if (actual ->a1c >= 5.7 && actual ->a1c <= 6.4 ) {
        riesgoA1C = 2;
    } else if (actual -> a1c >= 6.5) {
        riesgoA1C = 3;
    }

    // calcular el indice de prioridad total

    int IndicePrioridad = riesgoIMC + riesgoA1C;

    cout << "Paciente: " << actual->nombre << "\n";
        cout << "IMC: " << actual->imc << "\n";
        cout << "A1C: " << actual->a1c << "\n";
        cout << "Índice de Prioridad: " << IndicePrioridad << " (entre 2 y 6, donde 6 es la mayor prioridad)\n";
        cout << "------------------------------------------\n";

        // Avanzar al siguiente paciente
        actual = actual->next;
    }
}




int main() {;
    Paciente* head = nullptr;
    CargarPacientesCSV(head, "paciente_lista.csv");

    // Orden: nombre, edad, peso, altura, a1c
    
    ImprimirPaciente(head);
    PromedioEdad(head);
    PromedioPeso(head);
    CalcularIMC(head);
    CalculoPrioridadA1C(head);

    EliminarPaciente(head, "a"); // no me dejaba poner sin el "a" porque no se llamaban todos los parámetros de la función
    
    //buscar directamente a los pacientes con ejemplos
    BuscarPacienteIMC(head, 22.921);
    BuscarPacienteA1C(head, 5.7);
    PrioridadAtencion(head);
    return 0;
}

   
//fabs compara numero de punto flotante con pequeño margen de error, para llevar mejor los decimales