// Archivos binarios.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ALUMNOS = 100;
const int TAM_NOMBRE = 50;


struct Alumno {
    char nombre[TAM_NOMBRE];
    int matricula;
    float calificacion;
};


bool guardarBinario(const Alumno alumnos[], int n, const string& ruta) {
    ofstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << ruta << endl;
        return false;
    }

   
    archivo.write(reinterpret_cast<const char*>(alumnos), n * sizeof(Alumno));
    archivo.close();
    return true;
}


int leerBinario(Alumno alumnos[], int maximo, const string& ruta) {
    ifstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << ruta << endl;
        return -1;
    }

    int n = 0;
    while (n < maximo &&
        archivo.read(reinterpret_cast<char*>(&alumnos[n]), sizeof(Alumno))) {
        n++;
    }
    archivo.close();
    return n;
}


long tamanoArchivo(const string& ruta) {
    ifstream archivo(ruta, ios::binary | ios::ate);  
    if (!archivo.is_open()) return -1;
    return static_cast<long>(archivo.tellg());
}

void mostrarAlumnos(const Alumno alumnos[], int n) {
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << alumnos[i].nombre
            << " | Matricula: " << alumnos[i].matricula
            << " | Calificacion: " << alumnos[i].calificacion << endl;
    }
}

int main() {
    string ruta = "alumnos.bin";

    Alumno originales[] = {
        {"alejandro sanz",    1001, 9.5f},
        {"Luis miguel",   1002, 8.0f},
        {"jose jose", 1003, 7.5f},
        {"karely ruiz",  1004, 9.0f}
    };
    int nOriginales = sizeof(originales) / sizeof(originales[0]);

    
    if (!guardarBinario(originales, nOriginales, ruta)) return 1;
    cout << "Se guardaron " << nOriginales << " alumnos en " << ruta << endl;

    
    Alumno leidos[MAX_ALUMNOS];
    int nLeidos = leerBinario(leidos, MAX_ALUMNOS, ruta);
    if (nLeidos < 0) return 1;

    cout << "\nAlumnos leidos del binario (" << nLeidos << "):\n";
    mostrarAlumnos(leidos, nLeidos);

    
    cout << "\nTamano del archivo: " << tamanoArchivo(ruta) << " bytes\n";
    cout << "sizeof(Alumno) = " << sizeof(Alumno) << " bytes x "
        << nLeidos << " alumnos = " << sizeof(Alumno) * nLeidos << " bytes" << endl;
    return 0;
}