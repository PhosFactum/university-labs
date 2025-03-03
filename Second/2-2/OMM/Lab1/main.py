import numpy as np
import matplotlib.pyplot as plt

# Исходные данные
Aish = np.array([[3, 4, 3, 8, 9],
                 [5, 2, 1, 4, 3],
                 [4, 9, 4, 6, 7],
                 [3, 4, 11, 5, 4],
                 [8, 9, 8, 7, 1]])

Bish = np.array([[61], [43], [79], [87], [58]])

n = 8  # Вариант 8

A = Aish + (2 * n - 1)
B = Bish + (9 * n - 4)

# Транспонированные матрицы
At = A.T
Bt = B.T

# Обратная матрица A
Aobr = np.linalg.inv(A)
provA = np.dot(A, Aobr)

# Проверка ортогональности (матрица A ортогональна)
A_ortho = np.dot(A, Aobr)

# Матрица нормированных коэффициентов с проверкой на нулевое деление
C = (Bt - np.min(Bt)) / (np.ptp(Bt) if np.ptp(Bt) != 0 else 1)

# Умножение матриц
Fcb = np.dot(C, B)
Fbc = np.dot(B, C)

# Определитель матриц A и Fbc
det_A = np.linalg.det(A)
det_Fbc = np.linalg.det(Fbc)

# Главные миноры (по 1, 2, 3, ... столбцам и строкам)
main_minors = []
minor_sums = []
for i in range(A.shape[0]):  # Нужно пройтись по всем строкам и столбцам
    minor = np.delete(np.delete(A, i, axis=0), i, axis=1)  # Убираем i-ю строку и i-й столбец
    det_minor = np.linalg.det(minor)
    main_minors.append(round(det_minor, 3))
    minor_sums.append(round(det_minor, 3))  # Суммируем только определители миноров

# Проверка на определитель Fbc
# Убраны предупреждения
# Если нужно, можно сделать вывод в файл, но без вывода на экран:
# if det_Fbc == 0:
#     f.write(f"Определитель матрицы Fbc равен 0.\n")

# Сумма миноров
total_minor_sum = sum(minor_sums)

# Решение СЛАУ методом Гаусса
XGs = np.linalg.solve(A, B)
EpsGs = np.dot(A, XGs) - B

# Решение СЛАУ методом обратной матрицы
Xom = np.dot(Aobr, B)
Epsom = np.dot(A, Xom) - B

# Запись результатов в файл
with open('result8.txt', 'w') as f:
    f.write(f'Исходные данные варианта: {n}\n\n')
    f.write(f'Матрица A:\n{np.round(A, 3)}\n\n')
    f.write(f'Сумма матрицы A: {round(np.sum(A), 3)}\n\n')
    f.write(f'Матрица B:\n{np.round(B, 3)}\n\n')
    f.write(f'Сумма матрицы B: {round(np.sum(B), 3)}\n\n')
    f.write(f'Транспонированная матрица A:\n{np.round(At, 3)}\n\n')
    f.write(f'Сумма транспонированной матрицы A: {round(np.sum(At), 3)}\n\n')
    f.write(f'Транспонированная матрица B:\n{np.round(Bt, 3)}\n\n')
    f.write(f'Сумма транспонированной матрицы B: {round(np.sum(Bt), 3)}\n\n')
    f.write(f'Определитель матрицы A: {round(det_A, 3)}\n\n')
    f.write(f'Обратная матрица A:\n{np.round(Aobr, 3)}\n\n')
    f.write(f'Сумма обратной матрицы A: {round(np.sum(Aobr), 3)}\n\n')
    f.write(f'Проверка обратной матрицы A:\n{np.round(provA, 3)}\n\n')
    f.write(f'Матрица A ортогональна:\n{np.round(A_ortho, 3)}\n\n')
    f.write(f'Проверка матрицы A на ортогональность:\n{np.round(A_ortho, 3)}\n\n')
    f.write(f'Сумма матрицы A ортогональной: {round(np.sum(A_ortho), 3)}\n\n')
    f.write(f'Матрица нормированных коэффициентов C:\n{np.round(C, 3)}\n\n')
    f.write(f'Результат умножения Fcb = C * B:\n{np.round(Fcb, 3)}\n\n')
    f.write(f'Определитель матрицы Fbc: {round(det_Fbc, 3)}\n\n')
    
    # Главные миноры и их сумма
    f.write(f'Главные миноры матрицы A (с учётом удаления строки и столбца):\n')
    for i, minor in enumerate(main_minors):
        f.write(f'Минор {i+1} (без {i+1}-й строки и {i+1}-го столбца): {minor}, сумма: {minor_sums[i]}\n')
    f.write(f'Сумма всех миноров: {round(np.sum(minor_sums), 3)}\n')
    
    f.write(f'Решение СЛАУ Ax = B методом Гаусса:\n{np.round(XGs, 3)}\n\n')
    f.write(f'Решение СЛАУ Ax = B методом обратной матрицы:\n{np.round(Xom, 3)}\n\n')

# Построение графика пересечений
AAx = np.arange(1, 26)
muAAx = (AAx - 1) / (AAx * (n + 39) / (n + 31))
AAx1 = [0, 0.99]
muAAx1 = [0, 0]

plt.figure(figsize=(6, 3))
plt.plot(AAx, muAAx, 'b', linewidth=4)
plt.plot(AAx1, muAAx1, 'b', linewidth=4)
plt.grid(True)
plt.xlabel('AA', fontsize=20)
plt.ylabel('μ(AA)', fontsize=20)
plt.xticks([0, 5, 10, 15, 20, 25])
plt.yticks([0, 0.25, 0.5, 0.75, 1])
plt.savefig('intersections.pdf')
plt.show()

# Нахождение значений целевой функции
k = round(((32 - n) / (41 - n)) * n)
w = round((n - k + 6) / (n + 1))

t = np.arange(-4 * np.pi, 3 * np.pi, 0.1)
V1 = k * np.cos(w * t) + (n / (n + 3)) * np.cos(3 * w * t)
V2 = k / 2 + w * t - 1
F = np.maximum(V1, V2)

# Находим разницу между V1 и V2 для обнаружения точек пересечения
diff = V1 - V2

# Находим индексы, где разница меняет знак (пересечение)
intersection_indices = np.where(np.diff(np.sign(diff)))[0]

# Если есть пересечение, выводим координаты точек
intersection_t = t[intersection_indices]
intersection_V1 = V1[intersection_indices]  # Значение V1 в точке пересечения (они равны V2)

# Ищем максимальное пересечение
max_intersection_idx = np.argmax(intersection_V1)
max_intersection_t = intersection_t[max_intersection_idx]
max_intersection_value = intersection_V1[max_intersection_idx]

# Строим графики
plt.figure(figsize=(6, 3))
plt.plot(t, V1, 'b', linewidth=4, label='V1')
plt.plot(t, V2, 'g', linewidth=4, label='V2')

# Отображаем точку максимального пересечения на графике
plt.plot(max_intersection_t, max_intersection_value, 'ro', markersize=8, label='Максимальное пересечение')

plt.legend()
plt.grid(True)
plt.xlabel('t', fontsize=14)
plt.ylabel('Значение функции', fontsize=14)

# Сохранение графика
plt.savefig('intersections_target_function.pdf')
plt.show()

# Запись результатов в файл
with open('result8.txt', 'a') as f:
    f.write(f'\nk = {k}\n')
    f.write(f'w = {w}\n')
    if len(intersection_indices) > 0:
        f.write(f'Максимальная точка пересечения: t = {round(max_intersection_t, 3)}, значение = {round(max_intersection_value, 3)}\n')

    f.write(f'Максимум целевой функции: {round(np.max(F), 3)} при t = {round(t[np.argmax(F)], 3)}\n')

