#include <iostream>
#include <vector>
#include <cstdlib>   // Для srand, rand
#include <chrono>    // Для замеров времени

int main() {
    const int N = 100000;     // Размер массива
    const int experiments = 25; // Количество экспериментов

    srand(42); // Фиксируем seed

    double total_time = 0.0;

    for (int exp = 0; exp < experiments; ++exp) {
        // Генерируем вектор случайных чисел
        std::vector<int> arr(N);
        for(int i = 0; i < N; ++i) {
            arr[i] = rand();
        }

        // Замеряем время начала
        auto start = std::chrono::high_resolution_clock::now();

        // Алгоритм пузырьковой сортировки
        for(int i = 0; i < N - 1; ++i) {
            for(int j = 0; j < N - i - 1; ++j) {
                if(arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }

        // Замеряем время окончания
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << "Experiment " << exp + 1 << ": " << duration.count() << " s\n";
        total_time += duration.count();
    }

    double mean_time = total_time / experiments;
    std::cout << "Mean bubble sort time over " << experiments << " runs: " 
              << mean_time << " s" << std::endl;

    return 0;
}
