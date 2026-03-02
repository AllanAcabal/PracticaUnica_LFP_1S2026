#include <iostream>
#include <limits> 
#include "Estructuras.h"
#include "Funciones.h"
#include "Reportes.h"

using namespace std;

int main() {
    Estudiante estudiantes[MAX_ESTUDIANTES];
    Curso cursos[MAX_CURSOS];
    Nota notas[MAX_NOTAS];

    int totalEstudiantes = 0;
    int totalCursos = 0;
    int totalNotas = 0;

    int opcion;
    do {
        cout << "\n==========================================\n";
        cout << " SISTEMA DE ANALISIS ACADEMICO\n";
        cout << "==========================================\n";
        cout << "1. Cargar archivo de estudiantes\n";
        cout << "2. Cargar archivo de cursos\n";
        cout << "3. Cargar archivo de notas\n";
        cout << "4. Generar Reporte: Estadisticas por Curso\n";
        cout << "5. Generar Reporte: Rendimiento por Estudiante\n";
        cout << "6. Generar Reporte: Top 10 Mejores Estudiantes\n";
        cout << "7. Generar Reporte: Cursos con Mayor Reprobacion\n";
        cout << "8. Generar Reporte: Analisis por Carrera\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opcion: ";

        while (!(cin >> opcion)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Entrada invalida. Por favor ingrese un numero: ";
        }

        if (opcion < 1 || opcion > 9) {
            cout << "Opcion fuera de rango. Intente de nuevo.\n";
            continue; 
        }

        switch (opcion) {
        case 1:
            totalEstudiantes = cargarEstudiantes(estudiantes, MAX_ESTUDIANTES);
            cout << "Estudiantes cargados: " << totalEstudiantes << endl;
            break;
        case 2:
            totalCursos = cargarCursos(cursos, MAX_CURSOS);
            cout << "Cursos cargados: " << totalCursos << endl;
            break;
        case 3:
            totalNotas = cargarNotas(notas, MAX_NOTAS);
            cout << "Notas cargadas: " << totalNotas << endl;
            break;
        case 4:
            if (totalCursos == 0 || totalNotas == 0)
                cout << "Primero debe cargar cursos y notas.\n";
            else
                reporteEstadisticasPorCurso(cursos, totalCursos, notas, totalNotas);
            break;
        case 5:
            if (totalEstudiantes == 0 || totalNotas == 0)
                cout << "Primero debe cargar estudiantes y notas.\n";
            else
                reporteRendimientoPorEstudiante(estudiantes, totalEstudiantes, cursos, totalCursos, notas, totalNotas);
            break;
        case 6:
            if (totalEstudiantes == 0 || totalNotas == 0)
                cout << "Primero debe cargar estudiantes y notas.\n";
            else
                reporteTop10Estudiantes(estudiantes, totalEstudiantes, notas, totalNotas);
            break;
        case 7:
            if (totalCursos == 0 || totalNotas == 0)
                cout << "Primero debe cargar cursos y notas.\n";
            else
                reporteCursosMayorReprobacion(cursos, totalCursos, notas, totalNotas);
            break;
        case 8:
            if (totalEstudiantes == 0 || totalCursos == 0 || totalNotas == 0)
                cout << "Primero debe cargar estudiantes, cursos y notas.\n";
            else
                reporteAnalisisPorCarrera(estudiantes, totalEstudiantes, cursos, totalCursos, notas, totalNotas);
            break;
        case 9:
            cout << "Saliendo del sistema, ten feliz dia\n";
            break;
        }
    } while (opcion != 9);

    return 0;
}