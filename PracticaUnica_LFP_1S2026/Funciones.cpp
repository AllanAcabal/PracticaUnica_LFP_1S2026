    #include "Funciones.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int cargarEstudiantes(Estudiante estudiantes[], int max) {
    ifstream archivo("estudiantes.lfp");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir estudiantes.lfp" << endl;
        return 0;
    }

    int count = 0;
    string linea;
    while (getline(archivo, linea) && count < max) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string campo;
        Estudiante e;

        getline(ss, campo, ',');
        e.carnet = stoi(campo);
        getline(ss, campo, ',');
        e.nombre = campo;
        getline(ss, campo, ',');
        e.apellido = campo;
        getline(ss, campo, ',');
        e.carrera = campo;
        getline(ss, campo, ',');
        e.semestre = stoi(campo);

        estudiantes[count++] = e;
    }
    archivo.close();
    return count;
}

int cargarCursos(Curso cursos[], int max) {
    ifstream archivo("cursos.lfp");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir cursos.lfp" << endl;
        return 0;
    }

    int count = 0;
    string linea;
    while (getline(archivo, linea) && count < max) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string campo;
        Curso c;

        getline(ss, campo, ',');
        c.codigo = stoi(campo);
        getline(ss, campo, ',');
        c.nombre = campo;
        getline(ss, campo, ',');
        c.creditos = stoi(campo);
        getline(ss, campo, ',');
        c.semestre = stoi(campo);
        getline(ss, campo, ',');
        c.carrera = campo;

        cursos[count++] = c;
    }
    archivo.close();
    return count;
}

int cargarNotas(Nota notas[], int max) {
    ifstream archivo("notas.lfp");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir notas.lfp" << endl;
        return 0;
    }

    int count = 0;
    string linea;
    while (getline(archivo, linea) && count < max) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string campo;
        Nota n;

        getline(ss, campo, ',');
        n.carnet = stoi(campo);
        getline(ss, campo, ',');
        n.codigo_curso = stoi(campo);
        getline(ss, campo, ',');
        n.nota = stod(campo);
        getline(ss, campo, ',');
        n.ciclo = campo;
        getline(ss, campo, ',');
        n.anio = stoi(campo);

        notas[count++] = n;
    }
    archivo.close();
    return count;
}


int notasDeEstudiante(int carnet, const Nota notas[], int totalNotas, Nota resultado[], int maxResultado) {
    int count = 0;
    for (int i = 0; i < totalNotas && count < maxResultado; i++) {
        if (notas[i].carnet == carnet) {
            resultado[count++] = notas[i];
        }
    }
    return count;
}

int notasDeCurso(int codigo, const Nota notas[], int totalNotas, Nota resultado[], int maxResultado) {
    int count = 0;
    for (int i = 0; i < totalNotas && count < maxResultado; i++) {
        if (notas[i].codigo_curso == codigo) {
            resultado[count++] = notas[i];
        }
    }
    return count;
}

int buscarIndiceEstudiante(int carnet, const Estudiante estudiantes[], int total) {
    for (int i = 0; i < total; i++) {
        if (estudiantes[i].carnet == carnet)
            return i;
    }
    return -1;
}

int buscarIndiceCurso(int codigo, const Curso cursos[], int total) {
    for (int i = 0; i < total; i++) {
        if (cursos[i].codigo == codigo)
            return i;
    }
    return -1;
}

string nombreCurso(int codigo, const Curso cursos[], int totalCursos) {
    int idx = buscarIndiceCurso(codigo, cursos, totalCursos);
    if (idx != -1)
        return cursos[idx].nombre;
    else
        return "Desconocido";
}


double media(const double valores[], int n) {
    if (n == 0) return 0;
    double suma = 0;
    for (int i = 0; i < n; i++) suma += valores[i];
    return suma / n;
}

double mediana(double valores[], int n) {
    if (n == 0) return 0;
    
    sort(valores, valores + n);
    if (n % 2 == 0)
        return (valores[n / 2 - 1] + valores[n / 2]) / 2.0;
    else
        return valores[n / 2];
}

double desviacionEstandar(const double valores[], int n, bool poblacional) {
    if (n < 2) return 0;
    double mu = media(valores, n);
    double suma = 0;
    for (int i = 0; i < n; i++) suma += (valores[i] - mu) * (valores[i] - mu);
    double div = poblacional ? n : n - 1;
    return sqrt(suma / div);
}

double percentil(double valores[], int n, double p) {
    if (n == 0) return 0;
    sort(valores, valores + n);
    double pos = p * (n - 1) / 100.0;
    int i = static_cast<int>(pos);
    double fraccion = pos - i;
    if (i >= n - 1) return valores[n - 1];
    return valores[i] + fraccion * (valores[i + 1] - valores[i]);
}

int extraerValoresNotas(const Nota notas[], int totalNotas, double resultado[], int max) {
    int count = 0;
    for (int i = 0; i < totalNotas && count < max; i++) {
        resultado[count++] = notas[i].nota;
    }
    return count;
}