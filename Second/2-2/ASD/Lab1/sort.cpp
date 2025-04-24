#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Функции сортировки
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Генерация случайного массива с нормальным распределением
vector<int> generateRandomNumbers(int count, int minVal, int maxVal) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(minVal, maxVal);
    vector<int> numbers(count);
    for (int& num : numbers) {
        num = dist(gen);
    }
    return numbers;
}

// Функция замера времени выполнения
long long measureSortTime(void (*sortFunc)(vector<int>&), vector<int> arr) {
    auto start = steady_clock::now();
    sortFunc(arr);
    auto stop = steady_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

// Многопоточное вычисление среднего времени сортировки
long long averageSortTime(void (*sortFunc)(vector<int>&), const vector<int>& arr, int tests) {
    long long totalTime = 0;
    #pragma omp parallel for reduction(+:totalTime)
    for (int i = 0; i < tests; ++i) {
        vector<int> arrCopy = arr;
        totalTime += measureSortTime(sortFunc, arrCopy);
    }
    return totalTime / tests;
}

int main() {
    vector<int> sizes;
    for (int i = 150; i <= 2100; i += 150) {
        sizes.push_back(i);
    }

    ofstream results("sorting_results.xlsx");
    results << "Elements,Insertion Sort (µs),Selection Sort (µs),Bubble Sort (µs)\n";

    const int numTests = 1000;  // Уменьшено для ускорения

    for (int n : sizes) {
        cout << "Тест для " << n << " элементов..." << endl;
        vector<int> numbers = generateRandomNumbers(n, -10000, 10000);

        long long insertionTime = averageSortTime(insertionSort, numbers, numTests);
        long long selectionTime = averageSortTime(selectionSort, numbers, numTests);
        long long bubbleTime = averageSortTime(bubbleSort, numbers, numTests);

        results << n << "," << insertionTime << "," << selectionTime << "," << bubbleTime << "\n";

        cout << "Вставками: " << insertionTime << " µs | "
             << "Выбором: " << selectionTime << " µs | "
             << "Пузырьком: " << bubbleTime << " µs" << endl;
    }

    results.close();
    cout << "Результаты сохранены в sorting_results.xlsx" << endl;
    return 0;
}

