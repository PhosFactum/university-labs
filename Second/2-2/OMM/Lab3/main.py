import numpy as np

# --- 1. Исходные данные (граф Б, вариант 8) ---

# Матрица смежности графа (0, если нет пути)
adjacency_matrix = np.array([
    [0,  5,  9,  0,  0,  0,  0, 12],  
    [5,  0,  3,  7,  0,  0,  0,  0],  
    [9,  3,  0,  4,  8,  0,  0,  0],  
    [0,  7,  4,  0,  6,  0, 10,  0],  
    [0,  0,  8,  6,  0,  5,  0, 15],  
    [0,  0,  0,  0,  5,  0,  7,  0],  
    [0,  0,  0, 10,  0,  7,  0,  9],  
    [12, 0,  0,  0, 15,  0,  9,  0]  
])

# Веса вершин (количество абонентов в каждом пункте)
weights = np.array([80, 120, 120, 90, 90, 130, 70, 90]) 

# --- 2. Поиск кратчайших путей (Флойд-Уоршелл) ---

n = adjacency_matrix.shape[0]
Dij = np.where(adjacency_matrix == 0, np.inf, adjacency_matrix)  # Заполняем "бесконечностью"
np.fill_diagonal(Dij, 0)  # Диагональ (расстояние до себя) = 0

for k in range(n):
    for i in range(n):
        for j in range(n):
            Dij[i, j] = min(Dij[i, j], Dij[i, k] + Dij[k, j])

# Открываем файл для записи результатов
with open("results_lab3.txt", "w") as file:
    
    # --- Вывод матрицы кратчайших путей ---
    file.write("Матрица кратчайших путей (Dij):\n")
    file.write("Строки и столбцы — номера населённых пунктов (x1, x2, ..., x8)\n")
    file.write(str(np.round(Dij, 2)) + "\n\n")

    # --- 3. Минимаксная задача (центр графа) ---

    max_distances = Dij.max(axis=1)  # Находим максимальное расстояние для каждой вершины
    minimax_index = np.argmin(max_distances)  # Выбираем вершину с минимальным из этих максимумов

    file.write("🔹 Минимаксная задача: поиск центра графа (узла радиосети)\n")
    file.write("Максимальные расстояния для каждой вершины:\n")
    for i, d in enumerate(max_distances):
        file.write(f"Вершина x{i+1}: max расстояние = {d}\n")
    
    file.write(f"\n✅ Оптимальный узел радиодоступа (центр графа): x{minimax_index+1}\n\n")

    # --- 4. Минисуммная задача (медиана графа) ---

    sum_distances = (Dij * weights[:, np.newaxis]).sum(axis=1)  # Умножаем на вес и суммируем
    median_index = np.argmin(sum_distances)  # Минимальная сумма

    file.write("🔹 Минисуммная задача: поиск медианы графа (оптимального узла проводного доступа)\n")
    file.write("Суммы расстояний с учётом абонентов:\n")
    for i, s in enumerate(sum_distances):
        file.write(f"Вершина x{i+1}: сумма расстояний = {s}\n")

    file.write(f"\n✅ Оптимальное расположение проводного узла: x{median_index+1}\n")

print("✅ Результаты записаны в файл results_lab3.txt")
