// escritura de texto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Definición de la estructura
struct Alumno {
    string matricula;
    string nombre;
    float calificacionSegundoParcial;
};

// Prototipos de funciones
void agregarAlumno(Alumno alumnos[], int& contador, int maxAlumnos);
void mostrarAlumnos(const Alumno alumnos[], int contador);
void guardarEnArchivo(const Alumno alumnos[], int contador);

int main() {
    const int MAX_ALUMNOS = 50; // Capacidad máxima del arreglo
    Alumno alumnos[MAX_ALUMNOS];
    int contador = 0; // Lleva la cuenta de cuántos alumnos hay registrados
    int opcion;

    do {
        cout << "\n--- MENU SEGUNDO PARCIAL ---" << endl;
        cout << "1. Registrar alumno" << endl;
        cout << "2. Mostrar alumnos en memoria" << endl;
        cout << "3. Guardar en archivo de texto" << endl;
        cout << "4. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            agregarAlumno(alumnos, contador, MAX_ALUMNOS);
            break;
        case 2:
            mostrarAlumnos(alumnos, contador);
            break;
        case 3:
            guardarEnArchivo(alumnos, contador);
            break;
        case 4:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion no valida. Intenta de nuevo." << endl;
        }
    } while (opcion != 4);

    return 0;
}

// Función para capturar un nuevo alumno en el arreglo
void agregarAlumno(Alumno alumnos[], int& contador, int maxAlumnos) {
    if (contador >= maxAlumnos) {
        cout << "El arreglo esta lleno. No se pueden agregar mas alumnos." << endl;
        return;
    }

    cout << "\nMatricula: ";
    cin >> alumnos[contador].matricula;

    // Limpiamos el buffer antes de usar getline para leer nombres con espacios
    cin.ignore();
    cout << "Nombre completo: ";
    getline(cin, alumnos[contador].nombre);

    cout << "Calificacion Segundo Parcial: ";
    cin >> alumnos[contador].calificacionSegundoParcial;

    contador++;
    cout << "Alumno agregado correctamente." << endl;
}

// Función para visualizar los datos antes de guardarlos
void mostrarAlumnos(const Alumno alumnos[], int contador) {
    if (contador == 0) {
        cout << "\nNo hay alumnos registrados aun." << endl;
        return;
    }

    cout << "\n--- LISTA DE ALUMNOS ---" << endl;
    for (int i = 0; i < contador; ++i) {
        cout << i + 1 << ". " << alumnos[i].matricula << " | "
            << alumnos[i].nombre << " | "
            << alumnos[i].calificacionSegundoParcial << endl;
    }
}

// Función para escribir el arreglo en el archivo de texto
void guardarEnArchivo(const Alumno alumnos[], int contador) {
    if (contador == 0) {
        cout << "\nNo hay datos para guardar." << endl;
        return;
    }

    ofstream archivo("alumnos_segundo_parcial.txt");

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear o abrir el archivo." << endl;
        return;
    }

    // Escribe un alumno por línea
    for (int i = 0; i < contador; ++i) {
        archivo << alumnos[i].matricula << ","
            << alumnos[i].nombre << ","
            << alumnos[i].calificacionSegundoParcial << "\n";
    }

    archivo.close();
    cout << "\nSe guardaron " << contador << " alumnos en 'alumnos_segundo_parcial.txt'." << endl;
}