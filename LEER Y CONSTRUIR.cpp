// LEER Y CONSTRUIR.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Alumno {
    int matricula;
    string nombre;
    float promedio;
};

void guardarArchivo(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo.\n";
        return;
    }

    
    archivo << "101,Juan Perez,9.5\n";
    archivo << "102,Maria Gomez,8.8\n";
    archivo << "103,Carlos Lopez,9.2\n";

    archivo.close();
    cout << "=> Archivo '" << nombreArchivo << "' generado con datos de prueba.\n";
}


void leerYReconstruir(const string& nombreArchivo, vector<Alumno>& alumnos) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo. Asegurate de crearlo primero (Opcion 1).\n";
        return;
    }

    alumnos.clear(); 
    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string tempMatricula, tempPromedio;
        Alumno a;

        
        getline(ss, tempMatricula, ',');
        getline(ss, a.nombre, ',');
        getline(ss, tempPromedio, ',');

        
        a.matricula = stoi(tempMatricula);
        a.promedio = stof(tempPromedio);

        alumnos.push_back(a);
    }
    archivo.close();
    cout << "=> ¡Arreglo reconstruido con exito desde el archivo! (" << alumnos.size() << " registros cargados).\n";
}


void mostrarAlumnos(const vector<Alumno>& alumnos) {
    if (alumnos.empty()) {
        cout << "El arreglo en memoria esta vacio. Primero lee el archivo (Opcion 2).\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "     ALUMNOS RECONSTRUIDOS EN MEMORIA    \n";
    cout << "========================================\n";
    for (size_t i = 0; i < alumnos.size(); i++) {
        cout << "[" << i + 1 << "] Matricula: " << alumnos[i].matricula
            << " | Nombre: " << alumnos[i].nombre
            << " | Promedio: " << alumnos[i].promedio << endl;
    }
    cout << "========================================\n";
}

int main() {
    vector<Alumno> alumnosEnMemoria;
    string archivoDatos = "alumnos.txt";
    int opcion;

    do {
        cout << "\n================ MENU ================\n";
        cout << "1. Generar archivo de prueba (Opcional)\n";
        cout << "2. Leer archivo y reconstruir arreglo\n";
        cout << "3. Mostrar datos leidos en memoria\n";
        cout << "4. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            guardarArchivo(archivoDatos);
            break;
        case 2:
            leerYReconstruir(archivoDatos, alumnosEnMemoria);
            break;
        case 3:
            mostrarAlumnos(alumnosEnMemoria);
            break;
        case 4:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion invalida. Intenta de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}