#include <iostream>
#include <vector>
#include <tbb/tbb.h>

int main() {
    const int N = 100;
    std::vector<int> datos(N);

    // Llenamos el vector en paralelo
    tbb::parallel_for(0, N, [&](int i) {
        datos[i] = i * i; // cada elemento = su índice al cuadrado
    });

    // Suma paralela con parallel_reduce
    int suma = tbb::parallel_reduce(
        tbb::blocked_range<int>(0, N), // rango a procesar
        0,                             // valor inicial
        [&](const tbb::blocked_range<int>& r, int parcial) {
            for (int i = r.begin(); i < r.end(); ++i)
                parcial += datos[i];
            return parcial;
        },
        std::plus<int>() // cómo combinar los resultados parciales
    );

    std::cout << "Suma total: " << suma << std::endl;
    return 0;
}
