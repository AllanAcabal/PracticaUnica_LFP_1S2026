#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include "Estructuras.h"

int cargarEstudiantes(Estudiante estudiantes[], int max);
int cargarCursos(Curso cursos[], int max);
int cargarNotas(Nota notas[], int max);

int notasDeEstudiante(int carnet, const Nota notas[], int totalNotas, Nota resultado[], int maxResultado);
int notasDeCurso(int codigo, const Nota notas[], int totalNotas, Nota resultado[], int maxResultado);
int buscarIndiceEstudiante(int carnet, const Estudiante estudiantes[], int total);
int buscarIndiceCurso(int codigo, const Curso cursos[], int total);
std::string nombreCurso(int codigo, const Curso cursos[], int totalCursos);

double media(const double valores[], int n);
double mediana(double valores[], int n);  
double desviacionEstandar(const double valores[], int n, bool poblacional = true);
double percentil(double valores[], int n, double p); 

int extraerValoresNotas(const Nota notas[], int totalNotas, double resultado[], int max);

#endif 