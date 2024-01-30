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

duration<double> ordenar_xmergesort(int *A, int TAM_ARREGLO)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    merge_sort_mejorado(A, 0, TAM_ARREGLO - 1);
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

double desviacionEstandar(double tiempos[], int numRepeticiones)
{
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

void experimentos(int tam, int reps, bool is, bool ss, bool bs, bool ms, bool qs, bool xs)
{

    int TAM_ARREGLO = tam;
    int RANGO_MAX = 10 * TAM_ARREGLO;
    int REPETICIONES = reps;

    // Tiempo promedio de algoritmos
    double t_prom_is = 0.0;
    double t_prom_ss = 0.0;
    double t_prom_bs = 0.0;
    double t_prom_ms = 0.0;
    double t_prom_qs = 0.0;
    double t_prom_xs = 0.0;

    cout << "#ejec,is_t,ss_t,bs_t,ms_t,qs_t,xs_t" << endl;

    srand((unsigned)time(0));
    for (int i = 0; i < REPETICIONES; i++)
    {
        int *A = new int[TAM_ARREGLO];
        duration<double> tiempo;

        // Arreglo aleatorio
        crear_arreglo(A, TAM_ARREGLO, RANGO_MAX);

        // Imprimir no de ejecucion
        cout << i + 1 << ",";

        int *aux;

        if (!is)
            cout << 0.0 << ",";
        else
        {
            aux = copiar_arreglo(A, TAM_ARREGLO);
            tiempo = ordenar_insertion_sort(aux, TAM_ARREGLO);
            t_prom_is += tiempo.count();
            delete[] aux;
            cout << tiempo.count() << ",";
        }

        if (!ss)
            cout << 0.0 << ",";
        else
        {
            aux = copiar_arreglo(A, TAM_ARREGLO);
            tiempo = ordenar_selection_sort(A, TAM_ARREGLO);
            t_prom_ss += tiempo.count();
            delete[] aux;
            cout << tiempo.count() << ",";
        }

        if (!bs)
            cout << 0.0 << ",";
        else
        {
            aux = copiar_arreglo(A, TAM_ARREGLO);
            tiempo = ordenar_bubblesort(aux, TAM_ARREGLO);
            t_prom_bs += tiempo.count();
            delete[] aux;
            cout << tiempo.count() << ",";
        }

        if (!ms)
            cout << 0.0 << ",";
        else
        {
            aux = copiar_arreglo(A, TAM_ARREGLO);
            tiempo = ordenar_merge_sort(A, TAM_ARREGLO);
            t_prom_ms += tiempo.count();
            delete[] aux;
            cout << tiempo.count() << ",";
        }

        if (!qs)
            cout << 0.0 << ",";
        else
        {
            aux = copiar_arreglo(A, TAM_ARREGLO);
            tiempo = ordenar_quicksort(A, TAM_ARREGLO);
            t_prom_qs += tiempo.count();
            delete[] aux;
            cout << tiempo.count() << ",";
        }

        if (!xs)
            cout << 0.0 << ",";
        else {
            aux = copiar_arreglo(A, TAM_ARREGLO);
            tiempo = ordenar_xmergesort(A, TAM_ARREGLO);
            t_prom_xs += tiempo.count();
            delete[] aux;
            cout << tiempo.count();
        }

        cout << endl;

        delete[] A;
    }

    // Calculo de tiempo promedio
    t_prom_is = t_prom_is / REPETICIONES;
    t_prom_ss = t_prom_ss / REPETICIONES;
    t_prom_bs = t_prom_bs / REPETICIONES;
    t_prom_ms = t_prom_ms / REPETICIONES;
    t_prom_qs = t_prom_qs / REPETICIONES;
    t_prom_xs = t_prom_xs / REPETICIONES;


    cout << "PROM," << t_prom_is << "," << t_prom_ss << "," << t_prom_bs << "," << t_prom_ms << "," << t_prom_qs << "," << t_prom_xs << endl;
}

bool incluirAlgoritmo(string listaAlgs, char alg)
{
    size_t incluir = listaAlgs.find(alg);
    return incluir != string::npos;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Sintaxis: ordenamiento_t <tamaño_arreglo> <repeticiones> <lista_algoritmos>" << endl;
        cout << "Algoritmos:" << endl;
        cout << "i: insertion sort" << endl;
        cout << "s: selection sort" << endl;
        cout << "b: bubblesort" << endl;
        cout << "m: merge sort" << endl;
        cout << "q: quicksort" << endl;
        cout << "x: merge sort mejorado" << endl;
    }
    else
    {
        cout << "Haciendo prueba con: " << endl;
        cout << "Tamano del arreglo: " << argv[1] << endl;
        bool is = incluirAlgoritmo(argv[3], 'i');
        bool ss = incluirAlgoritmo(argv[3], 's');
        bool bs = incluirAlgoritmo(argv[3], 'b');
        bool ms = incluirAlgoritmo(argv[3], 'm');
        bool qs = incluirAlgoritmo(argv[3], 'q');
        bool xs = incluirAlgoritmo(argv[3], 'x');
        experimentos(atoi(argv[1]), atoi(argv[2]), is, ss, bs, ms, qs, xs);
    }
    return EXIT_SUCCESS;
}