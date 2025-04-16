from collections import defaultdict

def network_analysis(works):
    # Определяем все события
    events = sorted(set([work[0] for work in works] + [work[1] for work in works]))
    
    # Проверяем, что событие 1 существует
    if 1 not in events:
        raise ValueError("Событие 1 должно присутствовать в списке работ")
    
    # Инициализация
    t_early = defaultdict(int)
    t_late = defaultdict(lambda: float('inf'))
    predecessors = defaultdict(list)
    successors = defaultdict(list)
    
    # Строим связи
    for from_event, to_event, duration in works:
        successors[from_event].append((to_event, duration))
        predecessors[to_event].append((from_event, duration))
    
    # Проверка, что событие 1 - исходное
    if predecessors[1]:
        raise ValueError("Событие 1 должно быть исходным (не иметь входящих работ)")
    
    # Прямой проход
    t_early[1] = 0
    for event in sorted(events):
        for pred, dur in predecessors[event]:
            t_early[event] = max(t_early[event], t_early[pred] + dur)
    
    # Обратный проход
    t_late[max(events)] = t_early[max(events)]
    for event in sorted(events, reverse=True):
        for succ, dur in successors[event]:
            t_late[event] = min(t_late[event], t_late[succ] - dur)
    
    # Резервы
    R = {e: t_late[e] - t_early[e] for e in events}
    
    # Критический путь
    critical_path = [1]
    current = 1
    while current != max(events):
        for succ, dur in successors[current]:
            if t_early[succ] == t_early[current] + dur and R[succ] == 0:
                current = succ
                critical_path.append(current)
                break
    
    return t_early, t_late, R, critical_path, t_early[max(events)]

# Данные графа (только события 1-9)
works = [
    (1, 2, 8),   # 1 → 2 (длительность 8)
    (2, 3, 6),    # 2 → 3 (6)
    (2, 4, 9),    # 2 → 4 (9)
    (2, 5, 3),    # 2 → 5 (3)
    (3, 6, 4),    # 3 → 6 (4)
    (4, 7, 5),    # 4 → 7 (5)
    (5, 8, 7),    # 5 → 8 (7)
    (6, 9, 3),    # 6 → 9 (3)
    (7, 9, 4),    # 7 → 9 (4)
    (8, 9, 3)     # 8 → 9 (3)
]

# Анализ
t_early, t_late, R, critical_path, duration = network_analysis(works)

# Формируем строки для вывода
output_lines = [
    "Анализ сетевого графика (события 1-9)",
    "\nРанние сроки наступления событий:",
    *[f"Событие {e}: {t_early[e]}" for e in sorted(t_early)],
    "\nПоздние сроки наступления событий:",
    *[f"Событие {e}: {t_late[e]}" for e in sorted(t_late)],
    "\nРезервы времени:",
    *[f"Событие {e}: {R[e]}" for e in sorted(R)],
    f"\nКритический путь: {' → '.join(map(str, critical_path))}",
    f"Длина критического пути: {duration}"
]

# Сохраняем в файл
with open('network_analysis_results.txt', 'w', encoding='utf-8') as f:
    f.write('\n'.join(output_lines))

# Выводим в консоль
print('\n'.join(output_lines))
