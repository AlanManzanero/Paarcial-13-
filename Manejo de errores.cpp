
// Manejo de errores.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string nombreArchivo = "alumnos_inexistente.dat";

   
    ifstream archivo(nombreArchivo, ios::in | ios::binary);

  
    if (!archivo.is_open()) {
      
        cout << "[AVISO] No se pudo encontrar o abrir el archivo: " << nombreArchivo << endl;
        cout << "Verifica que el archivo exista en la ruta correcta." << endl;

      
        return 1;
    }

    
    cout << "¡Archivo abierto exitosamente!" << endl;

    
    archivo.close();

    return 0;
}