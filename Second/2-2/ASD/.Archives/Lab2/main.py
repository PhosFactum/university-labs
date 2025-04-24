import random
import time
import csv

# Наивный поиск
def naive_search(text, pattern):
    n, m = len(text), len(pattern)
    for i in range(n - m + 1):
        if text[i:i + m] == pattern:
            return i
    return -1

# Алгоритм Кнута-Морриса-Пратта (KMP)
def kmp_search(text, pattern):
    def compute_lps(pattern):
        lps = [0] * len(pattern)
        length = 0
        for i in range(1, len(pattern)):
            while length > 0 and pattern[i] != pattern[length]:
                length = lps[length - 1]
            if pattern[i] == pattern[length]:
                length += 1
                lps[i] = length
        return lps

    lps = compute_lps(pattern)
    i, j = 0, 0
    while i < len(text):
        if text[i] == pattern[j]:
            i += 1
            j += 1
            if j == len(pattern):
                return i - j
        else:
            if j > 0:
                j = lps[j - 1]
            else:
                i += 1
    return -1

# Алгоритм Рабина-Карпа
def rabin_karp_search(text, pattern):
    d = 256  # Размер алфавита
    q = 101  # Простое число для хеширования
    n, m = len(text), len(pattern)
    h = pow(d, m - 1, q)
    p_hash, t_hash = 0, 0

    for i in range(m):
        p_hash = (d * p_hash + ord(pattern[i])) % q
        t_hash = (d * t_hash + ord(text[i])) % q

    for i in range(n - m + 1):
        if p_hash == t_hash:
            if text[i:i + m] == pattern:
                return i
        if i < n - m:
            t_hash = (d * (t_hash - ord(text[i]) * h) + ord(text[i + m])) % q
            if t_hash < 0:
                t_hash += q
    return -1

# Генерация строки и подстроки
def generate_string_and_pattern(n, m):
    text = ''.join(random.choices('ACGT', k=n))  # Генерация строки из символов A, C, G, T
    pattern = ''.join(random.choices('ACGT', k=m))  # Генерация подстроки
    return text, pattern

# Функция для измерения времени выполнения
def measure_time(search_func, text, pattern, iterations=10_000):
    total_time = 0
    for _ in range(iterations):
        start_time = time.time()
        search_func(text, pattern)
        end_time = time.time()
        total_time += (end_time - start_time)
    return int((total_time / iterations) * 1_000_000)  # Среднее время в микросекундах

# Сохранение результатов в CSV
def save_to_csv(data, filename="search_results.csv"):
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["Length", "Naive Search", "KMP Search", "Rabin-Karp Search"])
        for row in data:
            writer.writerow(row)

# Основная функция
def main():
    results = []
    for n in range(1000, 3001, 100):  # Длина строки от 1000 до 3000 с шагом 100
        m = 20  # Длина подстроки
        text, pattern = generate_string_and_pattern(n, m)

        # Измерение времени для каждого алгоритма
        naive_time = measure_time(naive_search, text, pattern)
        kmp_time = measure_time(kmp_search, text, pattern)
        rk_time = measure_time(rabin_karp_search, text, pattern)

        # Сохранение результатов
        results.append([n, naive_time, kmp_time, rk_time])
        print(f"Length: {n}, Naive: {naive_time}, KMP: {kmp_time}, Rabin-Karp: {rk_time}")

    # Сохранение в CSV
    save_to_csv(results)

if __name__ == "__main__":
    main()
