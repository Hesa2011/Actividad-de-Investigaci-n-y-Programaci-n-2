#include <iostream>
#include <vector>
#include <tbb/tbb.h>

int main() {
    const int N = 100;
    std::vector<int> datos(N);

    tbb::parallel_for(0, N, [&](int i) {
        datos[i] = i * i; ¡
    });

    int suma = tbb::parallel_reduce(
        tbb::blocked_range<int>(0, N), 
        0,                            
        [&](const tbb::blocked_range<int>& r, int parcial) {
            for (int i = r.begin(); i < r.end(); ++i)
                parcial += datos[i];
            return parcial;
        },
        std::plus<int>() 
    );

    std::cout << "Suma total: " << suma << std::endl;
    return 0;
}
