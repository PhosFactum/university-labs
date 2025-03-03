import random

# Количество чисел
n = 305
# Диапазон чисел
d = 0
c = 20000

# Генерация случайных чисел в заданном диапазоне
numbers = [random.randint(d, c) for _ in range(n)]

# Запись в файл в правильном формате (через запятую)
with open('input.txt', 'w') as f:
    f.write(",".join(map(str, numbers)) + "\n")

