// Procesamiento de datos persistidos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;

const int MAX_ALUMNOS = 100;
const int TAM_NOMBRE = 50;

struct Alumno {
    char nombre[TAM_NOMBRE];
    int matricula;
    float calificacion;
};


long tamanoArchivo(const string& ruta) {
    ifstream archivo(ruta, ios::binary | ios::ate);
    if (!archivo.is_open()) return -1;
    return static_cast<long>(archivo.tellg());
}

bool guardarBinario(const Alumno alumnos[], int n, const string& ruta) {
    ofstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo crear o abrir '" << ruta
            << "' para escribir. Revisa que la carpeta exista y que tengas permisos." << endl;
        return false;
    }

    archivo.write(reinterpret_cast<const char*>(alumnos), n * sizeof(Alumno));

    if (!archivo.good()) {
        cerr << "Error: ocurrio un problema al escribir en '" << ruta << "'." << endl;
        return false;
    }
    archivo.close();
    return true;
}


int leerBinario(Alumno alumnos[], int maximo, const string& ruta) {
    ifstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: no se encontro el archivo '" << ruta
            << "'. Verifica el nombre o la ruta, o guarda los alumnos primero." << endl;
        return -1;
    }

    long tam = tamanoArchivo(ruta);
    if (tam % sizeof(Alumno) != 0) {
        cerr << "Error: '" << ruta << "' esta danado o no tiene el formato esperado ("
            << tam << " bytes no es multiplo de " << sizeof(Alumno) << ")." << endl;
        return -1;
    }

    int n = 0;
    while (n < maximo &&
        archivo.read(reinterpret_cast<char*>(&alumnos[n]), sizeof(Alumno))) {
        n++;
    }
    archivo.close();

    if (n == 0) {
        cerr << "Aviso: el archivo '" << ruta << "' esta vacio." << endl;
    }
    return n;
}


bool generarReporte(const Alumno alumnos[], int n, const string& rutaReporte) {
    if (n <= 0) {
        cerr << "Error: no hay alumnos para generar el reporte." << endl;
        return false;
    }

    Alumno copia[MAX_ALUMNOS];
    for (int i = 0; i < n; i++) copia[i] = alumnos[i];

    stable_sort(copia, copia + n, [](const Alumno& a, const Alumno& b) {
        return a.calificacion > b.calificacion;      
        });

    ofstream reporte(rutaReporte);                   
    if (!reporte.is_open()) {
        cerr << "Error: no se pudo crear el reporte '" << rutaReporte << "'." << endl;
        return false;
    }

    float suma = 0;
    for (int i = 0; i < n; i++) suma += copia[i].calificacion;

    reporte << "REPORTE DE ALUMNOS (ordenados por promedio, de mayor a menor)\n";
    reporte << left << setw(7) << "Lugar"
        << setw(22) << "Nombre"
        << setw(12) << "Matricula"
        << "Promedio\n";
  

    reporte << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        reporte << left << setw(7) << i + 1
            << setw(22) << copia[i].nombre
            << setw(12) << copia[i].matricula
            << copia[i].calificacion << "\n";
    }

    reporte << "Total de alumnos:  " << n << "\n";
    reporte << "Promedio general:  " << suma / n << "\n";
    reporte << "Mejor promedio:    " << copia[0].nombre << " (" << copia[0].calificacion << ")\n";
    reporte << "Menor promedio:    " << copia[n - 1].nombre << " (" << copia[n - 1].calificacion << ")\n";

    reporte.close();
    return true;
}

void mostrarTexto(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir '" << ruta << "'." << endl;
        return;
    }
    string linea;
    while (getline(archivo, linea)) cout << linea << endl;
}

int main() {
    string rutaBin = "alumnos.bin";
    string rutaReporte = "reporte.txt";

    
    Alumno originales[] = {
        {"pepez",    1001, 6.0f},
        {"Luis z",   1002, 8.0f},
        {"Marias", 1003, 7.5f},
        {"karel ",  1004, 9.0f}
    };
    int nOriginales = sizeof(originales) / sizeof(originales[0]);

    if (!guardarBinario(originales, nOriginales, rutaBin)) return 1;
    cout << "Se guardaron " << nOriginales << " alumnos en " << rutaBin << endl;

    
    Alumno leidos[MAX_ALUMNOS];
    int n = leerBinario(leidos, MAX_ALUMNOS, rutaBin);
    if (n < 0) return 1;

    if (!generarReporte(leidos, n, rutaReporte)) return 1;
    cout << "Reporte generado en " << rutaReporte << "\n\n";

    mostrarTexto(rutaReporte);
    return 0;
}