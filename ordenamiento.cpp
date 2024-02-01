#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <cmath>

#include "ordenamiento_t.h"
#include "ordenamiento_rec_t.h"

using namespace std;
using namespace std::chrono;

duration<double> crear_arreglo(int *A, int TAM_ARREGLO, int RANGO_MAX)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    for (int i = 0; i < TAM_ARREGLO; i++)
    {
        int x = rand() % RANGO_MAX;
        A[i] = x;
    }
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

duration<double> ordenar_insertion_sort(int *A, int TAM_ARREGLO)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    insertion_sort(A, TAM_ARREGLO);
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

duration<double> ordenar_selection_sort(int *A, int TAM_ARREGLO)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    selection_sort(A, TAM_ARREGLO);
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

duration<double> ordenar_bubblesort(int *A, int TAM_ARREGLO)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    bubblesort(A, TAM_ARREGLO);
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

duration<double> ordenar_merge_sort(int *A, int TAM_ARREGLO)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    merge_sort(A, 0, TAM_ARREGLO - 1);
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

duration<double> ordenar_quicksort(int *A, int TAM_ARREGLO)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    quicksort(A, 0, TAM_ARREGLO - 1);
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

int *copiar_arreglo(int A[], int n)
{
    int *aux = new int[n];
    for (int i = 0; i < n; i++)
    {
        aux[i] = A[i];
    }
    return aux;
}

void imprimirTabla(int repeticion, double t_is, double t_ss, double t_bs, double t_ms, double t_qs)
{
    // Si es la primera repetición, imprime los encabezados de la tabla
    if (repeticion == 1) {
        std::cout << std::setw(6) << "#ejec" << std::setw(12) << "is_t" << std::setw(12) << "ss_t" << std::setw(12) << "bs_t" << std::setw(12) << "ms_t" << std::setw(12) << "qs_t" << std::endl;
    }

    // Función para imprimir en notación científica si el número es menor a cierto umbral
    auto imprimirTiempo = [](double tiempo) {
        if (tiempo < 0.00009) {
            std::cout << std::setw(12) << std::scientific << std::setprecision(5) << tiempo;
        } else {
            std::cout << std::setw(12) << std::fixed << std::setprecision(5) << tiempo;
        }
    };

    // Imprime los resultados de la repetición actual
    std::cout << std::setw(6) << repeticion << "\t";
    imprimirTiempo(t_is);
    imprimirTiempo(t_ss);
    imprimirTiempo(t_bs);
    imprimirTiempo(t_ms);
    imprimirTiempo(t_qs);
    std::cout << std::endl;
}

double calcularDesviacionEstandar(double tiempos[], int numRepeticiones) {
    double sumatoria = 0.0;
    double t_promedio = 0.0;

    // Calcular la suma de los tiempos
    for (int i = 0; i < numRepeticiones; ++i)
    {
        sumatoria += tiempos[i];
    }

    // Calcular el tiempo promedio
    t_promedio = sumatoria / numRepeticiones;

    // Calcular la suma de las diferencias cuadráticas
    double sumatoriaDifCuadratica = 0.0;
    for (int i = 0; i < numRepeticiones; ++i)
    {
        double dif = tiempos[i] - t_promedio;
        sumatoriaDifCuadratica += dif * dif;
    }

    // Calcular la varianza y la desviación estándar
    double varianza = sumatoriaDifCuadratica / numRepeticiones;
    double desviacionEstandar = sqrt(varianza);

    return desviacionEstandar;
}

void experimentos(int tam) {

    int TAM_ARREGLO = tam;
    int RANGO_MAX = 10 * TAM_ARREGLO;
    int REPETICIONES = 30;

    // Tiempo promedio de algoritmos
    double t_prom_is = 0.0;
    double t_prom_ss = 0.0;
    double t_prom_bs = 0.0;
    double t_prom_ms = 0.0;
    double t_prom_qs = 0.0;

    // Almacena los tiempos de ejecución en arrays
    double tiempos_is[REPETICIONES];
    double tiempos_ss[REPETICIONES];
    double tiempos_bs[REPETICIONES];
    double tiempos_ms[REPETICIONES];
    double tiempos_qs[REPETICIONES];

    srand((unsigned) time(0));
    for (int i = 0; i < REPETICIONES; i++) {

        // Variables de tiempo de ejecucion
        double t_is = 0.0;
        double t_ss = 0.0;
        double t_bs = 0.0;
        double t_ms = 0.0;
        double t_qs = 0.0;

        int *A = new int[TAM_ARREGLO];
        duration<double> tiempo;

        // Arreglo aleatorio
        crear_arreglo(A, TAM_ARREGLO, RANGO_MAX);

        int *aux;

        aux = copiar_arreglo(A, TAM_ARREGLO);
        tiempo = ordenar_insertion_sort(aux, TAM_ARREGLO);
        t_prom_is += tiempo.count();
        t_is = tiempo.count();
        tiempos_is[i] = tiempo.count();
        delete[] aux;

        aux = copiar_arreglo(A, TAM_ARREGLO);
        tiempo = ordenar_selection_sort(A, TAM_ARREGLO);
        t_prom_ss += tiempo.count();
        t_ss = tiempo.count();
        tiempos_ss[i] = tiempo.count();
        delete[] aux;

        aux = copiar_arreglo(A, TAM_ARREGLO);
        tiempo = ordenar_bubblesort(aux, TAM_ARREGLO);
        t_prom_bs += tiempo.count();
        t_bs = tiempo.count();
        tiempos_bs[i] = tiempo.count();
        delete[] aux;

        aux = copiar_arreglo(A, TAM_ARREGLO);
        tiempo = ordenar_merge_sort(A, TAM_ARREGLO);
        t_prom_ms += tiempo.count();
        t_ms = tiempo.count();
        tiempos_ms[i] = tiempo.count();
        delete[] aux;

        aux = copiar_arreglo(A, TAM_ARREGLO);
        tiempo = ordenar_quicksort(A, TAM_ARREGLO);
        t_prom_qs += tiempo.count();
        t_qs = tiempo.count();
        tiempos_qs[i] = tiempo.count();
        delete[] aux;

        imprimirTabla(i+1, t_is, t_ss, t_bs, t_ms, t_qs);

        delete [] A;
    }
    
    // Calculo de tiempo promedio 
    t_prom_is = t_prom_is / REPETICIONES;
    t_prom_ss = t_prom_ss / REPETICIONES;
    t_prom_bs = t_prom_bs / REPETICIONES;
    t_prom_ms = t_prom_ms / REPETICIONES;
    t_prom_qs = t_prom_qs / REPETICIONES;

    // Desplegar resultados
    cout << "*** TIEMPO PROMEDIO ***" << endl;
    cout << "Insertion sort:\t" << t_prom_is << endl;
    cout << "Selection sort:\t" << t_prom_ss << endl;
    cout << "Bubble sort:\t" << t_prom_bs << endl;
    cout << "Merge sort:\t" << t_prom_ms << endl;
    cout << "Quicksort:\t" << t_prom_qs << endl;
    cout << "*** DESVIACION ESTANDAR ***" << endl;
    cout << "Insertion sort:\t" << calcularDesviacionEstandar(tiempos_is, REPETICIONES) << endl;
    cout << "Selection sort:\t" << calcularDesviacionEstandar(tiempos_ss, REPETICIONES) << endl;
    cout << "Bubble sort:\t" << calcularDesviacionEstandar(tiempos_bs, REPETICIONES) << endl;
    cout << "Merge sort:\t" << calcularDesviacionEstandar(tiempos_ms, REPETICIONES) << endl;
    cout << "Quick sort:\t" << calcularDesviacionEstandar(tiempos_qs, REPETICIONES) << endl;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Sintaxis: ordenamiento <tamano arreglo>" << endl;
    } else {
        cout << "Haciendo prueba con: " << endl;
        cout << "Tamano del arreglo: " << argv[1] << endl;
        experimentos(atoi(argv[1]));
    }
    return EXIT_SUCCESS;
}