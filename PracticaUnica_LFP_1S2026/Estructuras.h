#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>

// Constantes para tamaños máximos
const int MAX_ESTUDIANTES = 100;
const int MAX_CURSOS = 50;
const int MAX_NOTAS = 500;

struct Estudiante {
    int carnet;
    std::string nombre;
    std::string apellido;
    std::string carrera;
    int semestre;
};

struct Curso {
    int codigo;
    std::string nombre;
    int creditos;
    int semestre;
    std::string carrera;
};

struct Nota {
    int carnet;
    int codigo_curso;
    double nota;
    std::string ciclo; // "1S" o "2S"
    int anio;
};

#endif // ESTRUCTURAS_H