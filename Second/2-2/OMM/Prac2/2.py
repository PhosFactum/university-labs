import numpy as np
from itertools import combinations

A = np.array([
    [10, 14, 16, 13, 29, -3, -3, 0, 0, 0],
    [-7, 2, 8, 18, 12, 25, 13, 0, 0, 0],
    [23, 21, 21, 18, 8, 1, 11, -1, 0, 0],
    [2, 16, 6, 24, 3, 16, 25, 0, -1, 0],
    [13, 4, 11, 1, -7, 8, -9, 0, 0, 1]
])

B = np.array([81, 75, 98, 85, 29])

# Все возможные комбинации индексов столбцов (5 из 10)
column_combinations = combinations(range(A.shape[1]), 5)

valid_combinations = []

for cols in column_combinations:
    A_sub = A[:, list(cols)]
    try:
        A_inv = np.linalg.inv(A_sub)
        result = np.dot(A_inv, B)
        if np.all(result >= 0):
            valid_combinations.append((cols, result))
    except np.linalg.LinAlgError:
        pass # Игнорируем вырожденные матрицы


if valid_combinations:
    print("Найдены комбинации столбцов, дающие неотрицательный результат:")
    for cols, result in valid_combinations:
        print(f"Столбцы: {cols}, Результат: {result}")
else:
    print("Нет комбинаций столбцов, дающих только неотрицательный результат.")
