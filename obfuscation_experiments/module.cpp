#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <random>

int bubble() {
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


int matrix() {
    int n = 1000;  // Size of the matrix
    std::random_device rd;
    std::mt19937 rng(rd());  // Mersenne Twister RNG
    std::uniform_int_distribution<int> dist(1, 10);  // Random numbers between 1 and 10

    // Create two n x n matrices and a result matrix
    std::vector<std::vector<int>> A(n, std::vector<int>(n));
    std::vector<std::vector<int>> B(n, std::vector<int>(n));
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));  // Result matrix, initialized to 0

    // Fill matrices A and B with random values
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = dist(rng);
            B[i][j] = dist(rng);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Matrix multiplication: C = A * B
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Matrix multiplication took " << duration.count() << " seconds." << std::endl;

    return 0;
}


int sort_std() {
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
