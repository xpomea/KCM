#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

int main() {
    srand(42);
    const int n = 100; // количество итераций
    const int m = 100000; // размер массива

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, m);

    double total_iter_time = 0.0;

    for (int i = 0; i < n; ++i) {
        std::vector<int> arr(m);
        for (int j = 0; j < m; ++j) {
            arr[j] = dist(rng);
        }

        auto start = std::chrono::high_resolution_clock::now();
        std::sort(arr.begin(), arr.end());
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> iter_time = end - start;
        total_iter_time += iter_time.count();
        std::cout << "Iteration " << i + 1 << ": " << iter_time.count() << " ms\n";
    }

    double mean_time = total_iter_time / n;
    std::cout << "Mean time per iteration: " << mean_time << " ms\n";

    return 0;
}
