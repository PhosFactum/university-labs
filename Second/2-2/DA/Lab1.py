import math
import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
import numpy as np  # для построения гладкой кривой
from scipy.stats import chi2, norm

def main():
    # Ваша исходная выборка
    data = [
        5.3, 5.6, -1.4, 2.7, 10.7, -3.9, 12.6, 18.1, -0.7, 6.1,
        2.1, 2.8, -1.7, 12.5, 11.6, 19.2, -1.1, 6.6, 11.4, 9.6,
        8.6, 4.4, 13.0, 10.2, 10.8, 16.7, 6.2, -0.2, 3.2, 4.0,
        19.9, 7.4, -3.7, 14.0, 10.5, 7.0, 12.6, 1.7, 4.1, 8.8,
        6.9, -0.2, 1.0, 14.7, 14.7, 3.9, 2.8, 22.9, 7.9, 5.2
    ]
    # 1) Вариационный ряд (отсортированные данные)
    sorted_data = sorted(data)

    # 2) Минимальный и максимальный элементы
    min_val = min(sorted_data)
    max_val = max(sorted_data)

    # 3) Объём выборки
    n = len(data)

    # 4) Размах выборки
    data_range = max_val - min_val

    # 5) Количество интервалов l
    l_raw = 1 + 3.32 * math.log10(n)
    l = math.floor(l_raw)
    l = max(5, min(25, l))

    # 6) Длина интервала
    h = data_range / l

    # 7) Границы интервалов
    boundaries = [min_val + i * h for i in range(l)]
    boundaries.append(max_val)

    # 8) Интервалы
    intervals = [f"[{boundaries[i]:.3f}; {boundaries[i+1]:.3f})" for i in range(l-1)]
    intervals.append(f"[{boundaries[-2]:.3f}; {boundaries[-1]:.3f}]")

    # 9) Абсолютные частоты
    freq = [0] * l
    for value in sorted_data:
        for j in range(l):
            left, right = boundaries[j], boundaries[j+1]
            if j < l - 1:
                if left <= value < right:
                    freq[j] += 1
                    break
            else:
                if left <= value <= right:
                    freq[j] += 1
                    break

    # 10) Объединение интервалов, если в интервале меньше 5 значений
    if freq[5] < 5:
        freq[4] += freq[5]  # Прибавляем значения из 6 интервала в 5
        freq.pop(5)  # Удаляем 6 интервал
        boundaries.pop(5)  # Удаляем границу 6 интервала
        l -= 1  # Уменьшаем число интервалов

    # Проверка всех остальных интервалов на количество выборочных значений
    i = 1
    while i < l:
        if freq[i] < 5:
            freq[i-1] += freq[i]  # Прибавляем значения из текущего интервала в предыдущий
            freq.pop(i)  # Удаляем текущий интервал
            l -= 1  # Уменьшаем число интервалов
            boundaries.pop(i)  # Удаляем границу текущего интервала
        else:
            i += 1

    # Если количество интервалов стало меньше 5, добавляем еще один интервал вручную
    if l < 5:
        boundaries.append(max_val + h)
        freq.append(0)  # Допустим, в этом интервале пока нет значений
        l += 1  # Увеличиваем число интервалов

    # Пересчитываем новые середины интервалов
    midpoints = [(boundaries[i] + boundaries[i+1]) / 2 for i in range(l)]

    # 11) Относительные частоты
    rel_freq = [f / n for f in freq]

    # 12) Накопленные частоты
    cum_freq = [sum(rel_freq[:i+1]) for i in range(l)]

    # --- Вывод всех рассчитанных значений ---
    print("\nГраницы интервалов (a_i):")
    for i, b in enumerate(boundaries):
        print(f"a{i} = {b:.3f}")

    print("\nИнтервалы:")
    for i, iv in enumerate(intervals, 1):
        print(f"I{i} = {iv}")

    print("\nЧисло выборочных значений в каждом интервале:")
    for i, val in enumerate(freq, 1):
        print(f"n{i} = {val}")
    print(f"Контроль: сумма n_i = {sum(freq)}")

    print("\nЧастоты интервального ряда (p_i*):")
    for i, val in enumerate(rel_freq, 1):
        print(f"p{i}* = {val:.3f}")
    print(f"Контроль: сумма p_i* = {sum(rel_freq):.3f}")

    print("\nНакопленные частоты z_i:")
    for i, val in enumerate(cum_freq, 1):
        print(f"z{i} = {val:.3f}")

    print("\nСередины интервалов x_i*: ")
    for i, mp in enumerate(midpoints, 1):
        print(f"x{i}* = {mp:.3f}")


    # --- Расчет теоретических частот для нормального распределения ---
    def normal_pdf(x, mu, sigma):
        """Вычисление плотности нормального распределения"""
        return (1.0 / (sigma * math.sqrt(2 * math.pi))) * math.exp(-((x - mu) ** 2) / (2 * sigma ** 2))


    # Вычислим параметры для нормального распределения (выборочное среднее и стандартное отклонение)
    sample_mean = sum(midpoints[i] * rel_freq[i] for i in range(l))
    sample_var = sum(((midpoints[i] - sample_mean) ** 2) * rel_freq[i] for i in range(l))
    corrected_var = (n / (n - 1)) * sample_var
    corrected_std = math.sqrt(corrected_var)

    # Теоретические частоты для каждого интервала
    expected_freq = [n * h * normal_pdf(midpoint, sample_mean, corrected_std) for midpoint in midpoints]

    # Выводим ожидаемые частоты
    print("\nОжидаемые частоты для каждого интервала:")
    for i, ef in enumerate(expected_freq, 1):
        print(f"Е{i} = {ef:.3f}")

    # --- Критерий Пирсона ---
    chi_square_stat = sum(((freq[i] - expected_freq[i]) ** 2) / expected_freq[i] for i in range(l))
    degrees_of_freedom = l - 1 - 2  # Степени свободы (l-1-2 для нормального распределения)
    chi_square_critical = chi2.ppf(0.95, degrees_of_freedom)  # 95% уровень значимости

    print(f"\nКритерий Пирсона: Статистика χ² = {chi_square_stat:.3f}, критическое значение = {chi_square_critical:.3f}")
    if chi_square_stat > chi_square_critical:
        print("Гипотеза отклоняется (распределение не нормальное).")
    else:
        print("Гипотеза не отклоняется (распределение нормальное).")

    # --- Критерий Колмогорова ---
    # Эмпирическая и теоретическая функции распределения
    empirical_cdf = np.cumsum(rel_freq)
    theoretical_cdf = [norm.cdf(midpoint, sample_mean, corrected_std) for midpoint in midpoints]

    # Статистика Колмогорова
    sorted_data = sorted(data)
    empirical_cdf = [i / n for i in range(1, n + 1)]  # Эмпирическая CDF
    mean = sum(sorted_data) / n  # Выборочное среднее
    stddev = math.sqrt(sum((x - mean) ** 2 for x in sorted_data) / n)  # Выборочное стандартное отклонение
    theoretical_cdf = [0.5 * (1 + math.erf((x - mean) / (stddev * math.sqrt(2)))) for x in sorted_data]

    # Статистика D
    D_stat = max(abs(empirical_cdf[i] - theoretical_cdf[i]) for i in range(l))

    # Критическое значение D
    D_critical = 1.36 / math.sqrt(n)

    # Вывод результатов
    print(f"Статистика D: {D_stat:.3f}")
    print(f"Критическое значение D (для уровня значимости 0.05): {D_critical:.3f}")

    if D_stat > D_critical:
        print("Гипотеза о нормальности отвергается.")
    else:
        print("Гипотеза о нормальности не отвергается.")

    print(f"\nКритерий Колмогорова: Статистика D = {D_stat:.3f}, критическое значение = {D_critical:.3f}")
    if D_stat > D_critical:
        print("Гипотеза отклоняется (распределение не нормальное).")
    else:
        print("Гипотеза не отклоняется (распределение нормальное).")

    # --- Построение графиков ---
    # (Этот блок остается таким же, как и у вас в коде)
    plt.figure(figsize=(8, 5))
    plt.step([-math.inf] + midpoints, [0] + cum_freq, where='post', label="Эмпирическая функция $F_n^*(x)$", linewidth=2)
    plt.scatter(midpoints, cum_freq, color='red', zorder=3)
    plt.xlabel("x")
    plt.ylabel("$F_n^*(x)$")
    plt.title("Эмпирическая функция распределения")
    plt.grid()
    plt.legend()    
    plt.show()

    heights = [rel_freq[i] / h for i in range(l)]
    plt.figure(figsize=(8, 5))
    plt.bar(boundaries[:-1], heights, width=np.diff(boundaries), align='edge', edgecolor='black', alpha=0.6, label="Гистограмма")
    plt.plot(midpoints, heights, marker='o', color='red', label="Полигон частот", linewidth=2)
    plt.xlabel("x")
    plt.ylabel("$f_n^*(x)$")
    plt.title("Гистограмма и полигон частот")
    plt.grid()
    plt.legend()
    plt.show()

    # Теоретическая плотность нормального распределения для гладкой кривой
    x_grid = np.linspace(min_val, max_val, 200)
    y_grid = [normal_pdf(x, sample_mean, corrected_std) for x in x_grid]

    # Построим график теоретической плотности поверх гистограммы
    plt.figure(figsize=(8, 5))
    plt.bar(boundaries[:-1], heights, width=np.diff(boundaries), align='edge', edgecolor='black', alpha=0.6, label="Гистограмма")
    plt.plot(midpoints, heights, marker='o', color='red', linewidth=2, label="Полигон частот")
    plt.plot(x_grid, y_grid, 'g-', linewidth=2, label="Теоретическая кривая N( x̄ , s̄ )")
    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.title("Гистограмма, полигон частот и теоретическая кривая N")
    plt.grid()
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()
