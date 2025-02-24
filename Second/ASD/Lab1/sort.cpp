#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Функция сортировки вставками
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

// Функция сортировки выбором
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

// Функция сортировки пузырьком
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

// Генерация случайного массива
vector<int> generateRandomNumbers(int count, int minVal, int maxVal) {
    vector<int> numbers(count);
    srand(time(0));
    for (int i = 0; i < count; i++) {
        numbers[i] = rand() % (maxVal - minVal + 1) + minVal;
    }
    return numbers;
}

// Функция замера времени выполнения
long long measureSortTime(void (*sortFunc)(vector<int>&), vector<int> arr) {
    auto start = steady_clock::now();
    sortFunc(arr);
    auto stop = steady_clock::now();
    return duration_cast<milliseconds>(stop - start).count();
}

// Функция записи отсортированных данных в файл
void writeSortedNumbersToFile(const vector<int>& arr, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка при открытии файла " << filename << endl;
        return;
    }
    for (int num : arr) {
        outFile << num << "\n";
    }
    outFile.close();
}

int main() {
    vector<int> sizes = {1000, 2000, 5000, 10000, 15000, 20000, 50000, 100000};
    ofstream results("sorting_results.csv");
    results << "Elements,Insertion Sort (ms),Selection Sort (ms),Bubble Sort (ms)\n";

    for (int n : sizes) {
        cout << "Тест для " << n << " элементов..." << endl;
        vector<int> numbers = generateRandomNumbers(n, -10000, 10000);

        // Копии массива для каждого метода сортировки
        vector<int> insertionArr = numbers;
        vector<int> selectionArr = numbers;
        vector<int> bubbleArr = numbers;

        // Измерение времени сортировки
        long long insertionTime = measureSortTime(insertionSort, insertionArr);
        long long selectionTime = measureSortTime(selectionSort, selectionArr);
        long long bubbleTime = measureSortTime(bubbleSort, bubbleArr);

        // Запись времени выполнения в CSV
        results << n << "," << insertionTime << "," << selectionTime << "," << bubbleTime << "\n";

        // Запись отсортированных массивов в файлы
        writeSortedNumbersToFile(insertionArr, "insertion_sorted_" + to_string(n) + ".txt");
        writeSortedNumbersToFile(selectionArr, "selection_sorted_" + to_string(n) + ".txt");
        writeSortedNumbersToFile(bubbleArr, "bubble_sorted_" + to_string(n) + ".txt");

        cout << "Вставками: " << insertionTime << " мс | "
             << "Выбором: " << selectionTime << " мс | "
             << "Пузырьком: " << bubbleTime << " мс" << endl;
    }

    results.close();
    cout << "Результаты сохранены в sorting_results.csv" << endl;
    cout << "Отсортированные данные записаны в .txt файлы" << endl;
    return 0;
}


