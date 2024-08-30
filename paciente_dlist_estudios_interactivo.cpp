#include <iostream>
#include <string>
#include <fstream> // Para manejo de archivos
#include <sstream> // Para procesamiento de CSV
#include <cmath>   // Para la función pow

using namespace std;

// Estructura para una lista
struct Paciente {
    string nombre;
    int edad;
    double altura;
    double peso;
    Paciente* next;
};

// Función para añadir un nuevo paciente a la lista
void AñadirPaciente(Paciente*& head, const string& nombre, int edad, double peso, double altura) {
    Paciente* NuevoPaciente = new Paciente();
    NuevoPaciente->nombre = nombre;
    NuevoPaciente->edad = edad;
    NuevoPaciente->altura = altura;
    NuevoPaciente->peso = peso;
    NuevoPaciente->next = head;
    head = NuevoPaciente;
}

// Función para eliminar una persona de la lista por el nombre
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

// Función para imprimir toda la gente de la lista
void ImprimirPaciente(const Paciente* head) {
    const Paciente* actual = head;
    int contador = 1; // Para ir numerando a los pacientes y se vea más ordenado

    if (head == nullptr) {
        cout << "No hay pacientes en la lista.\n";
        return;
    }

    while (actual != nullptr) {
        cout << "Paciente " << contador << ":\n";
        cout << "Nombre: " << actual->nombre << "\n";
        cout << "Edad: " << actual->edad << "\n";
        cout << "Peso: " << actual->peso << " kg\n";
        cout << "Altura: " << actual->altura << " m\n";
        cout << "\n"; // Línea en blanco entre pacientes

        actual = actual->next;
        contador++;
    }
}

void PromedioPeso(Paciente*& head) {
    int contador = 0;
    double peso_total = 0; // Inicializar como 0
    const Paciente* actual = head;

    if (head == nullptr) {
        cout << "No hay pacientes en la lista para calcular el promedio de peso.\n";
        return;
    }

    while (actual != nullptr) {
        contador++;
        peso_total += actual->peso;
        actual = actual->next;
    }

    if (contador > 0) {
        cout << "El promedio de los pesos de los pacientes es de " << peso_total / contador << " kg.\n";
    }
}

void PromedioEdad(Paciente*& head) {
    int contador = 0;
    int edad_total = 0; // Inicializar como 0
    const Paciente* actual = head;

    if (head == nullptr) {
        cout << "No hay pacientes en la lista para calcular el promedio de edad.\n";
        return;
    }

    while (actual != nullptr) {
        contador++;
        edad_total += actual->edad;
        actual = actual->next;
    }

    if (contador > 0) {
        cout << "El promedio de edad de los pacientes es de " << edad_total / contador << " años.\n";
    }
}

void CalcularIMC(const Paciente* head) {
    const Paciente* actual = head;

    if (head == nullptr) {
        cout << "No hay pacientes en la lista para calcular el IMC.\n";
        return;
    }

    while (actual != nullptr) {
        // IMC = peso / (altura^2)
        double imc = actual->peso / pow(actual->altura, 2);
        cout << actual->nombre << " posee un IMC de: " << imc << "\n";
        actual = actual->next;
    }
}

// Función para cargar pacientes desde un archivo CSV
void CargarPacientesDesdeArchivo(Paciente*& head, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << "\n";
        return;
    }

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre;
        int edad;
        double peso, altura;

        getline(ss, nombre, ',');
        ss >> edad;
        ss.ignore(); // Ignora la coma
        ss >> peso;
        ss.ignore(); // Ignora la coma
        ss >> altura;

        AñadirPaciente(head, nombre, edad, peso, altura);
    }

    archivo.close();
}

// Menú interactivo
void MostrarMenu() {
    cout << "Gestión de Pacientes\n";
    cout << "1. Añadir Paciente\n";
    cout << "2. Eliminar Paciente\n";
    cout << "3. Mostrar Pacientes\n";
    cout << "4. Calcular Promedio de Edad\n";
    cout << "5. Calcular Promedio de Peso\n";
    cout << "6. Calcular IMC de Pacientes\n";
    cout << "7. Cargar Pacientes desde Archivo\n";
    cout << "8. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    Paciente* head = nullptr;

    // Añadir pacientes iniciales
    AñadirPaciente(head, "Cristopher Reyes", 22, 100, 1.83);
    AñadirPaciente(head, "Nicolas Morales", 19, 70, 1.72);
    AñadirPaciente(head, "Eustaquio Tamarindo", 94, 70, 2.01);

    int opcion;
    
    do {
        MostrarMenu();
        cin >> opcion;
        cin.ignore(); // Ignora cualquier carácter sobrante en el búfer de entrada

        switch(opcion) {
            case 1: {
                string nombre;
                int edad;
                double peso, altura;
                cout << "Nombre: ";
                getline(cin, nombre);
                cout << "Edad: ";
                cin >> edad;
                cout << "Peso (kg): ";
                cin >> peso;
                cout << "Altura (m): ";
                cin >> altura;
                AñadirPaciente(head, nombre, edad, peso, altura);
                cout << "Paciente añadido exitosamente.\n";
                break;
            }
            case 2: {
                string nombre;
                cout << "Nombre del paciente a eliminar: ";
                getline(cin, nombre);
                EliminarPaciente(head, nombre);
                cout << "Paciente eliminado exitosamente.\n";
                break;
            }
            case 3: {
                cout << "Mostrando todos los pacientes:\n";
                ImprimirPaciente(head);
                break;
            }
            case 4: {
                cout << "Calculando el promedio de edad de los pacientes:\n";
                PromedioEdad(head);
                break;
            }
            case 5: {
                cout << "Calculando el promedio de peso de los pacientes:\n";
                PromedioPeso(head);
                break;
            }
            case 6: {
                cout << "Calculando el IMC de los pacientes:\n";
                CalcularIMC(head);
                break;
            }
            case 7: {
                string nombreArchivo;
                cout << "Ingrese el nombre del archivo CSV: ";
                getline(cin, nombreArchivo);
                CargarPacientesDesdeArchivo(head, nombreArchivo);
                cout << "Pacientes cargados exitosamente desde el archivo.\n";
                break;
            }
            case 8:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
                break;
        }

        cout << "\n";

    } while (opcion != 8);

    return 0;
}
