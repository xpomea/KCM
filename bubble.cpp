#include <iostream>
#include <vector>
#include <cstdlib>   // Для srand, rand
#include <chrono>    // Для замеров времени

int main() {
    // Размер массива
    const int N = 100000;

    // Фиксируем seed, чтобы результаты были воспроизводимы
    srand(43);

    // Генерируем вектор случайных чисел
    std::vector<int> arr(N);
    for(int i = 0; i < N; ++i) {
        arr[i] = rand();
    }

    // Замеряем время начала
    auto start = std::chrono::high_resolution_clock::now();

    // Алгоритм пузырьковой сортировки
    for(int i = 0; i < N - 1; ++i)
        for(int j = 0; j < N - i - 1; ++j)
            if(arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j+1]);

    // Замеряем время окончания
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Bubble sort time: " << duration.count() << " s" << std::endl;

    // При желании можно вывести несколько первых/последних элементов для проверки
    // std::cout << "First elements: ";
    // for(int i = 0; i < 10; i++) {
    //     std::cout << arr[i] << " ";
    // }
    // std::cout << std::endl;

    return 0;
}
