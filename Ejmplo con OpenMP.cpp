#include <iostream>
#include <omp.h>

#define N 100

int main() {
    int suma = 0;
    int arreglo[N];

    for (int i = 0; i < N; i++) {
        arreglo[i] = i + 1;
    }

    // Paralelizar el bucle
    #pragma omp parallel for reduction(+:suma)
    for (int i = 0; i < N; i++) {
        suma += arreglo[i];

        std::cout << "Hilo "
                  << omp_get_thread_num()
                  << " procesa i="
                  << i << std::endl;
    }

    std::cout << "\nSuma total = "
              << suma << std::endl;

    return 0;
}