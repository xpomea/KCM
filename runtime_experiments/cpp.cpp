#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

int main() {
    const int n = 10; // количество итераций
    const int m = 100000; // размер массива

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, m);

    double sum_time = 0.0;

    for (int i = 0; i < n; ++i) {
        std::vector<int> arr(m);
        for (int j = 0; j < m; ++j) {
            arr[j] = dist(rng);
        }

        auto start = std::chrono::high_resolution_clock::now();
        std::sort(arr.begin(), arr.end());
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> iter_time = end - start;
        sum_time += iter_time.count();

        std::cout << "Iteration " << i + 1 << ": " << iter_time.count() << " ms\n";
    }

    std::cout << "Mean iteration time: " << (sum_time / n) << " ms\n";

    return 0;
}


// #include <iostream>
// #include <vector>
// #include <random>
// #include <chrono>

// int main() {
//     int n = 1000;  // Size of the matrix
//     std::random_device rd;
//     std::mt19937 rng(rd());  // Mersenne Twister RNG
//     std::uniform_int_distribution<int> dist(1, 10);  // Random numbers between 1 and 10

//     // Create two n x n matrices and a result matrix
//     std::vector<std::vector<int>> A(n, std::vector<int>(n));
//     std::vector<std::vector<int>> B(n, std::vector<int>(n));
//     std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));  // Result matrix, initialized to 0

//     // Fill matrices A and B with random values
//     for (int i = 0; i < n; ++i) {
//         for (int j = 0; j < n; ++j) {
//             A[i][j] = dist(rng);
//             B[i][j] = dist(rng);
//         }
//     }

//     auto start = std::chrono::high_resolution_clock::now();

//     // Matrix multiplication: C = A * B
//     for (int i = 0; i < n; ++i) {
//         for (int j = 0; j < n; ++j) {
//             for (int k = 0; k < n; ++k) {
//                 C[i][j] += A[i][k] * B[k][j];
//             }
//         }
//     }

//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;

//     std::cout << "Matrix multiplication took " << duration.count() << " seconds." << std::endl;

//     return 0;
// }
