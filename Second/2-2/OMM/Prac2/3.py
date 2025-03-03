import numpy as np

A = np.array([
    [27, 14, 2, 26, -8, -6, 14, 0, 0, 0],
    [19, 19, -7, 20, -5, 29, 20, 0, 0, 0],
    [3, -28, 5, -3, -29, -16, -14, -1, 0, 0],
    [-14, -17, -6, -4, -22, -27, -8, 0, -1, 0],
    [21, 28, -6, 19, -3, 16, 4, 0, 0, -1]
])

selected_cols = (0, 1, 2, 5, 6)
A_sub = A[:, list(selected_cols)]

try:
    A_inv = np.linalg.inv(A_sub)

    # Создаем матрицу S из оставшихся столбцов
    remaining_cols = [i for i in range(A.shape[1]) if i not in selected_cols]
    S = A[:, remaining_cols]

    # Вычисляем произведение
    result = np.dot(A_inv, S)
    print("Результат произведения A⁻¹ * S:\n", result)

except np.linalg.LinAlgError:
    print("Обратной матрицы не существует (матрица вырожденная).")


'''
10 14 13 29 -3
-7 2  18 12 25
23 21 18 8  1
'''
