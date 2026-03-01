#ifndef REPORTES_H
#define REPORTES_H

#include "Estructuras.h"

void reporteEstadisticasPorCurso(const Curso cursos[], int totalCursos, const Nota notas[], int totalNotas);
void reporteRendimientoPorEstudiante(const Estudiante estudiantes[], int totalEstudiantes, const Curso cursos[], int totalCursos, const Nota notas[], int totalNotas);
void reporteTop10Estudiantes(const Estudiante estudiantes[], int totalEstudiantes, const Nota notas[], int totalNotas);
void reporteCursosMayorReprobacion(const Curso cursos[], int totalCursos, const Nota notas[], int totalNotas);
void reporteAnalisisPorCarrera(const Estudiante estudiantes[], int totalEstudiantes, const Curso cursos[], int totalCursos, const Nota notas[], int totalNotas);

#endif 