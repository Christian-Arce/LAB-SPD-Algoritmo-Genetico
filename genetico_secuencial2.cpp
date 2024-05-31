#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <ctime>
#include <chrono>

// Función de aptitud: x^2
double get_Aptitude(const std::vector<int>& individuo) {
    int x = 0;
    for (int i = individuo.size() - 1, j = 0; i >= 0; --i, ++j) {
        x += individuo[i] * std::pow(2, j);
    }
    return std::pow(x, 2);
}

// Inicialización de la población
std::vector<std::vector<int>> crear_Poblacion(int tamPoblacion, int tamano) {
    std::vector<std::vector<int>> poblacion;
    for (int i = 0; i < tamPoblacion; ++i) {
        std::vector<int> individuo(tamano);
        for (int j = 0; j < tamano; ++j) {
            individuo[j] = rand() % 2; // Genera aleatoriamente 0 o 1
        }
        poblacion.push_back(individuo);
    }
    return poblacion;
}

// Evaluación de aptitud para toda la población
void evaluar_Poblacion(const std::vector<std::vector<int>>& poblacion, std::vector<double>& aptitudes) {
    for (size_t i = 0; i < poblacion.size(); ++i) {
        aptitudes[i] = get_Aptitude(poblacion[i]);
    }
}

// Selección de individuos (torneo)
int seleccionar_Padres(const std::vector<double>& aptitudes) {
    int tamTorneo = 3; // Tamaño del torneo
    int mejor = rand() % aptitudes.size();
    for (int i = 1; i < tamTorneo; ++i) {
        int contendor = rand() % aptitudes.size();
        if (aptitudes[contendor] > aptitudes[mejor]) {
            mejor = contendor;
        }
    }
    return mejor;
}

// Cruce de un punto
std::vector<int> cruzar(const std::vector<int>& padre1, const std::vector<int>& padre2) {
    int puntoCruce = rand() % padre1.size();
    std::vector<int> hijo(padre1.size());
    for (int i = 0; i < padre1.size(); ++i) {
        if (i < puntoCruce) {
            hijo[i] = padre1[i];
        } else {
            hijo[i] = padre2[i];
        }
    }
    return hijo;
}

// Mutación
void mutar(std::vector<int>& individuo, double tasaMutacion) {
    for (int i = 0; i < individuo.size(); ++i) {
        if ((rand() / double(RAND_MAX)) < tasaMutacion) {
            individuo[i] = !individuo[i];
        }
    }
}

// Selección de la próxima generación
std::vector<std::vector<int>> seleccionar_Nueva_Generacion(const std::vector<std::vector<int>>& poblacion, const std::vector<double>& aptitudes, double tasaMutacion) {
    std::vector<std::vector<int>> nueva_generacion;
    for (size_t i = 0; i < poblacion.size() / 2; ++i) {
        int padre1 = seleccionar_Padres(aptitudes);
        int padre2 = seleccionar_Padres(aptitudes);

        // Cruzar
        std::vector<int> hijo1 = cruzar(poblacion[padre1], poblacion[padre2]);
        std::vector<int> hijo2 = cruzar(poblacion[padre2], poblacion[padre1]);

        // Mutar
        mutar(hijo1, tasaMutacion);
        mutar(hijo2, tasaMutacion);

        // Agregar hijos a la nueva generación
        nueva_generacion.push_back(hijo1);
        nueva_generacion.push_back(hijo2);
    }
    return nueva_generacion;
}

int main() {
    srand(time(0));

    // Parámetros del algoritmo genético
    const int tamPoblacion = 8000;
    const int tamanoIndividuo = 18;
    const int numGeneraciones = 12000;
    const double tasaMutacion = 0.01;

    // Inicialización de población
    std::vector<std::vector<int>> poblacion = crear_Poblacion(tamPoblacion, tamanoIndividuo);
    std::vector<double> aptitudes(tamPoblacion);

    // Medición de tiempo de ejecución
    auto start_time = std::chrono::steady_clock::now();

    // Bucle principal del algoritmo genético
    for (int generacion = 0; generacion < numGeneraciones; ++generacion) {
        // Evaluación de aptitud
        evaluar_Poblacion(poblacion, aptitudes);

        // Selección de la próxima generación
        poblacion = seleccionar_Nueva_Generacion(poblacion, aptitudes, tasaMutacion);
    }

    // Medición de tiempo de ejecución
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // Evaluación final de la aptitud
    evaluar_Poblacion(poblacion, aptitudes);

    // Encontrar el individuo con mayor aptitud
    double mejor_aptitud = aptitudes[0];
    int mejor_individuo = 0;
    for (size_t i = 1; i < aptitudes.size(); ++i) {
        if (aptitudes[i] > mejor_aptitud) {
            mejor_aptitud = aptitudes[i];
            mejor_individuo = i;
        }
    }

    // Imprimir resultados
    std::cout << "Mejor individuo: ";
    for (int bit : poblacion[mejor_individuo]) {
        std::cout << bit;
    }
    std::cout << " con aptitud: " << mejor_aptitud << std::endl;

    // Imprimir tiempo de ejecución
    std::cout << "Tiempo de ejecución: " << elapsed_time << " milisegundos" << std::endl;

    return 0;
}
