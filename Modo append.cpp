// Modo append.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  
    ofstream archivo("alumnos.txt", ios::app);

    
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    string nombre, matricula;
    float promedio;

   
    cout << "Ingrese el nombre completo del alumno: ";
    getline(cin, nombre);

    cout << "Ingrese la matricula: ";
    getline(cin, matricula);

    cout << "Ingrese el promedio: ";
    cin >> promedio;

   
    archivo << nombre << " | " << matricula << " | " << promedio << "\n";

    
    archivo.close();

    cout << "Alumno agregado exitosamente sin perder los datos anteriores." << endl;

    return 0;
}