import numpy as np

def compute_alpha(D, S):
    try:
        D_inv = np.linalg.inv(D)  # Находим обратную матрицу D^-1
        alpha = np.dot(D_inv, S)  # Умножаем D^-1 на S
        return alpha
    except np.linalg.LinAlgError:
        print("Матрица D вырожденная, нельзя найти обратную.")
        return None

# Пример
D = np.array([
    [10, 14, 16, 13, 29],
    [-7, 2, 8, 18, 12],
    [23, 21, 21, 18, 8],
    [2, 16, 6, 24, 3],
    [13, 4, 11, 1, -7]
])

S = np.array([
    [-3, -3, 0, 0, 0],
    [25, 13, 0, 0, 0],
    [1, 11, -1, 0, 0],
    [16, 25, 0, -1, 0],
    [8, -9, 0, 0, 1]
])

alpha = compute_alpha(D, S)
if alpha is not None:
    print("Матрица α (D^-1 * S):\n", np.round(alpha, 3))

