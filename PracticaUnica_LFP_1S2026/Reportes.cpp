#include "Reportes.h"
#include "Funciones.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>

using namespace std;

void reporteEstadisticasPorCurso(const Curso cursos[], int totalCursos, const Nota notas[], int totalNotas) {
    string filename = "reporte_estadisticas_por_curso.html";
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo crear el archivo " << filename << endl;
        return;
    }

    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Estadísticas por Curso</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; margin: 20px; }\n";
    file << "h1 { color: #333; }\n";
    file << "table { border-collapse: collapse; width: 100%; }\n";
    file << "th, td { border: 1px solid #ddd; padding: 8px; text-align: center; }\n";
    file << "th { background-color: #4CAF50; color: white; }\n";
    file << "tr:nth-child(even) { background-color: #f2f2f2; }\n";
    file << "</style>\n";
    file << "</head>\n<body>\n";
    file << "<h1>Estadísticas Generales por Curso</h1>\n";

    file << "<table>\n";
    file << "<tr>\n";
    file << "<th>Código</th>\n";
    file << "<th>Nombre del Curso</th>\n";
    file << "<th>Estudiantes</th>\n";
    file << "<th>Promedio</th>\n";
    file << "<th>Máxima</th>\n";
    file << "<th>Mínima</th>\n";
    file << "<th>Desv. Est.</th>\n";
    file << "<th>Mediana</th>\n";
    file << "</tr>\n";

    for (int i = 0; i < totalCursos; i++) {
        const Curso& curso = cursos[i];
        Nota notasCurso[MAX_NOTAS];
        int totalNotasCurso = notasDeCurso(curso.codigo, notas, totalNotas, notasCurso, MAX_NOTAS);
        if (totalNotasCurso == 0) continue;

        double valores[MAX_NOTAS];
        int n = extraerValoresNotas(notasCurso, totalNotasCurso, valores, MAX_NOTAS);

        double prom = media(valores, n);
        double max = *max_element(valores, valores + n);
        double min = *min_element(valores, valores + n);
        double desv = desviacionEstandar(valores, n, true);
        double med = mediana(valores, n); 

        file << "<tr>\n";
        file << "<td>" << curso.codigo << "</td>\n";
        file << "<td style=\"text-align:left;\">" << curso.nombre << "</td>\n";
        file << "<td>" << totalNotasCurso << "</td>\n";
        file << "<td>" << fixed << setprecision(2) << prom << "</td>\n";
        file << "<td>" << fixed << setprecision(2) << max << "</td>\n";
        file << "<td>" << fixed << setprecision(2) << min << "</td>\n";
        file << "<td>" << fixed << setprecision(2) << desv << "</td>\n";
        file << "<td>" << fixed << setprecision(2) << med << "</td>\n";
        file << "</tr>\n";
    }

    file << "</table>\n";
    file << "<p>Nota: Solo se muestran cursos con al menos una nota registrada.</p>\n";
    file << "</body>\n</html>";
    file.close();

    cout << "Reporte generado: " << filename << endl;
}

void reporteRendimientoPorEstudiante(const Estudiante estudiantes[], int totalEstudiantes, const Curso cursos[], int totalCursos, const Nota notas[], int totalNotas) {
    string filename = "reporte_rendimiento_estudiante.html";
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo crear el archivo " << filename << endl;
        return;
    }

    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Rendimiento por Estudiante</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; margin: 20px; }\n";
    file << "h1 { color: #333; }\n";
    file << "table { border-collapse: collapse; width: 100%; }\n";
    file << "th, td { border: 1px solid #ddd; padding: 8px; text-align: center; }\n";
    file << "th { background-color: #2196F3; color: white; }\n";
    file << "tr:nth-child(even) { background-color: #f2f2f2; }\n";
    file << "</style>\n";
    file << "</head>\n<body>\n";
    file << "<h1>Rendimiento por Estudiante</h1>\n";

    file << "<table>\n";
    file << "<tr>\n";
    file << "<th>Carnet</th>\n";
    file << "<th>Nombre Completo</th>\n";
    file << "<th>Carrera</th>\n";
    file << "<th>Semestre</th>\n";
    file << "<th>Promedio General</th>\n";
    file << "<th>Aprobados</th>\n";
    file << "<th>Reprobados</th>\n";
    file << "<th>Créditos Acum.</th>\n";
    file << "</tr>\n";

    for (int i = 0; i < totalEstudiantes; i++) {
        const Estudiante& est = estudiantes[i];
        Nota notasEst[MAX_NOTAS];
        int totalNotasEst = notasDeEstudiante(est.carnet, notas, totalNotas, notasEst, MAX_NOTAS);
        if (totalNotasEst == 0) continue;

        double valores[MAX_NOTAS];
        int n = extraerValoresNotas(notasEst, totalNotasEst, valores, MAX_NOTAS);
        double promedio = media(valores, n);

        int aprobados = 0, reprobados = 0;
        int creditosAcum = 0;

        for (int j = 0; j < totalNotasEst; j++) {
            if (notasEst[j].nota >= 61) {
                aprobados++;
                int idx = buscarIndiceCurso(notasEst[j].codigo_curso, cursos, totalCursos);
                if (idx != -1)
                    creditosAcum += cursos[idx].creditos;
            }
            else {
                reprobados++;
            }
        }

        file << "<tr>\n";
        file << "<td>" << est.carnet << "</td>\n";
        file << "<td style=\"text-align:left;\">" << est.nombre << " " << est.apellido << "</td>\n";
        file << "<td>" << est.carrera << "</td>\n";
        file << "<td>" << est.semestre << "</td>\n";
        file << "<td>" << fixed << setprecision(2) << promedio << "</td>\n";
        file << "<td>" << aprobados << "</td>\n";
        file << "<td>" << reprobados << "</td>\n";
        file << "<td>" << creditosAcum << "</td>\n";
        file << "</tr>\n";
    }

    file << "</table>\n";
    file << "</body>\n</html>";
    file.close();

    cout << "Reporte generado: " << filename << endl;
}

void reporteTop10Estudiantes(const Estudiante estudiantes[], int totalEstudiantes, const Nota notas[], int totalNotas) {
    string filename = "reporte_top10_estudiantes.html";
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo crear el archivo " << filename << endl;
        return;
    }

    struct EstPromedio {
        const Estudiante* estudiante;
        double promedio;
    };

    EstPromedio lista[MAX_ESTUDIANTES];
    int count = 0;

    for (int i = 0; i < totalEstudiantes; i++) {
        const Estudiante& est = estudiantes[i];
        Nota notasEst[MAX_NOTAS];
        int totalNotasEst = notasDeEstudiante(est.carnet, notas, totalNotas, notasEst, MAX_NOTAS);
        if (totalNotasEst == 0) continue;

        double valores[MAX_NOTAS];
        int n = extraerValoresNotas(notasEst, totalNotasEst, valores, MAX_NOTAS);
        double prom = media(valores, n);

        lista[count].estudiante = &est;
        lista[count].promedio = prom;
        count++;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (lista[i].promedio < lista[j].promedio) {
                EstPromedio temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }

    int top = (count < 10) ? count : 10;

    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Top 10 Mejores Estudiantes</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; margin: 20px; }\n";
    file << "h1 { color: #333; }\n";
    file << "table { border-collapse: collapse; width: 100%; }\n";
    file << "th, td { border: 1px solid #ddd; padding: 8px; text-align: center; }\n";
    file << "th { background-color: #FF9800; color: white; }\n";
    file << "tr:nth-child(even) { background-color: #f2f2f2; }\n";
    file << "</style>\n";
    file << "</head>\n<body>\n";
    file << "<h1>Top 10 Mejores Estudiantes</h1>\n";

    file << "<table>\n";
    file << "<tr>\n";
    file << "<th>Posición</th>\n";
    file << "<th>Carnet</th>\n";
    file << "<th>Nombre Completo</th>\n";
    file << "<th>Carrera</th>\n";
    file << "<th>Semestre</th>\n";
    file << "<th>Promedio</th>\n";
    file << "</tr>\n";

    for (int i = 0; i < top; i++) {
        const auto& item = lista[i];
        file << "<tr>\n";
        file << "<td>" << i + 1 << "</td>\n";
        file << "<td>" << item.estudiante->carnet << "</td>\n";
        file << "<td style=\"text-align:left;\">" << item.estudiante->nombre << " " << item.estudiante->apellido << "</td>\n";
        file << "<td>" << item.estudiante->carrera << "</td>\n";
        file << "<td>" << item.estudiante->semestre << "</td>\n";
        file << "<td>" << fixed << setprecision(2) << item.promedio << "</td>\n";
        file << "</tr>\n";
    }

    file << "</table>\n";
    file << "</body>\n</html>";
    file.close();

    cout << "Reporte generado: " << filename << endl;
}

void reporteCursosMayorReprobacion(const Curso cursos[], int totalCursos, const Nota notas[], int totalNotas) {
    string filename = "reporte_cursos_reprobacion.html";
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo crear el archivo " << filename << endl;
        return;
    }

    struct CursoRep {
        int codigo;
        string nombre;
        int total;
        int aprobados;
        int reprobados;
        double porcentaje;
    };

    CursoRep lista[MAX_CURSOS];
    int count = 0;

    for (int i = 0; i < totalCursos; i++) {
        const Curso& curso = cursos[i];
        Nota notasCurso[MAX_NOTAS];
        int totalNotasCurso = notasDeCurso(curso.codigo, notas, totalNotas, notasCurso, MAX_NOTAS);
        if (totalNotasCurso == 0) continue;

        int total = totalNotasCurso;
        int aprob = 0, reprob = 0;
        for (int j = 0; j < totalNotasCurso; j++) {
            if (notasCurso[j].nota >= 61)
                aprob++;
            else
                reprob++;
        }
        double porcentaje = (total > 0) ? (reprob * 100.0 / total) : 0.0;
        lista[count].codigo = curso.codigo;
        lista[count].nombre = curso.nombre;
        lista[count].total = total;
        lista[count].aprobados = aprob;
        lista[count].reprobados = reprob;
        lista[count].porcentaje = porcentaje;
        count++;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (lista[i].porcentaje < lista[j].porcentaje) {
                CursoRep temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }

    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Cursos con Mayor Reprobación</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; margin: 20px; }\n";
    file << "h1 { color: #333; }\n";
    file << "table { border-collapse: collapse; width: 100%; }\n";
    file << "th, td { border: 1px solid #ddd; padding: 8px; text-align: center; }\n";
    file << "th { background-color: #f44336; color: white; }\n";
    file << "tr:nth-child(even) { background-color: #f2f2f2; }\n";
    file << "</style>\n";
    file << "</head>\n<body>\n";
    file << "<h1>Cursos con Mayor Índice de Reprobación</h1>\n";

    file << "<table>\n";
    file << "<tr>\n";
    file << "<th>Código</th>\n";
    file << "<th>Nombre del Curso</th>\n";
    file << "<th>Total Estudiantes</th>\n";
    file << "<th>Aprobados</th>\n";
    file << "<th>Reprobados</th>\n";
    file << "<th>% Reprobación</th>\n";
    file << "</tr>\n";

    for (int i = 0; i < count; i++) {
        const auto& item = lista[i];
        file << "<tr>\n";
        file << "<td>" << item.codigo << "</td>\n";
        file << "<td style=\"text-align:left;\">" << item.nombre << "</td>\n";
        file << "<td>" << item.total << "</td>\n";
        file << "<td>" << item.aprobados << "</td>\n";
        file << "<td>" << item.reprobados << "</td>\n";
        file << "<td>" << fixed << setprecision(2) << item.porcentaje << "%</td>\n";
        file << "</tr>\n";
    }

    file << "</table>\n";
    file << "</body>\n</html>";
    file.close();

    cout << "Reporte generado: " << filename << endl;
}

void reporteAnalisisPorCarrera(const Estudiante estudiantes[], int totalEstudiantes, const Curso cursos[], int totalCursos, const Nota notas[], int totalNotas) {
    string filename = "reporte_analisis_carrera.html";
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo crear el archivo " << filename << endl;
        return;
    }

    string carreras[MAX_ESTUDIANTES];
    int totalCarreras = 0;
    for (int i = 0; i < totalEstudiantes; i++) {
        const string& carrera = estudiantes[i].carrera;
        bool encontrada = false;
        for (int j = 0; j < totalCarreras; j++) {
            if (carreras[j] == carrera) {
                encontrada = true;
                break;
            }
        }
        if (!encontrada) {
            carreras[totalCarreras++] = carrera;
        }
    }

    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Análisis por Carrera</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; margin: 20px; }\n";
    file << "h1 { color: #333; }\n";
    file << "h2 { color: #555; }\n";
    file << "table { border-collapse: collapse; width: 100%; margin-bottom: 20px; }\n";
    file << "th, td { border: 1px solid #ddd; padding: 8px; text-align: center; }\n";
    file << "th { background-color: #9C27B0; color: white; }\n";
    file << ".semestre-table { width: auto; margin-top: 10px; }\n";
    file << "</style>\n";
    file << "</head>\n<body>\n";
    file << "<h1>Análisis por Carrera</h1>\n";

    for (int c = 0; c < totalCarreras; c++) {
        const string& carrera = carreras[c];

        const Estudiante* estudiantesCarrera[MAX_ESTUDIANTES];
        int totalEstCarrera = 0;
        for (int i = 0; i < totalEstudiantes; i++) {
            if (estudiantes[i].carrera == carrera) {
                estudiantesCarrera[totalEstCarrera++] = &estudiantes[i];
            }
        }
        if (totalEstCarrera == 0) continue;

        double todasNotas[MAX_NOTAS];
        int totalNotasCarrera = 0;
        for (int i = 0; i < totalEstCarrera; i++) {
            Nota notasEst[MAX_NOTAS];
            int n = notasDeEstudiante(estudiantesCarrera[i]->carnet, notas, totalNotas, notasEst, MAX_NOTAS);
            for (int j = 0; j < n; j++) {
                todasNotas[totalNotasCarrera++] = notasEst[j].nota;
            }
        }
        double promedioCarrera = media(todasNotas, totalNotasCarrera);

        int cursosCarrera = 0;
        for (int i = 0; i < totalCursos; i++) {
            if (cursos[i].carrera == carrera)
                cursosCarrera++;
        }

        map<int, int> distSemestre;
        for (int i = 0; i < totalEstCarrera; i++) {
            distSemestre[estudiantesCarrera[i]->semestre]++;
        }

        file << "<h2>Carrera: " << carrera << "</h2>\n";
        file << "<table>\n";
        file << "<tr><th>Total Estudiantes</th><td>" << totalEstCarrera << "</td></tr>\n";
        file << "<tr><th>Promedio General</th><td>" << fixed << setprecision(2) << promedioCarrera << "</td></tr>\n";
        file << "<tr><th>Cursos Disponibles</th><td>" << cursosCarrera << "</td></tr>\n";
        file << "</table>\n";

        file << "<h3>Distribución por Semestre</h3>\n";
        file << "<table class=\"semestre-table\">\n";
        file << "<tr><th>Semestre</th><th>Cantidad Estudiantes</th></tr>\n";
        for (const auto& par : distSemestre) {
            file << "<tr><td>" << par.first << "</td><td>" << par.second << "</td></tr>\n";
        }
        file << "</table>\n";
        file << "<hr>\n";
    }

    file << "</body>\n</html>";
    file.close();

    cout << "Reporte generado: " << filename << endl;
}