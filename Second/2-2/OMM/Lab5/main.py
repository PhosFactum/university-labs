def find_optimal_route(costs):
    n = 10  # Количество пунктов
    F = [float('inf')] * (n + 1)  # Минимальные затраты
    F[10] = 0  # База: конечный пункт
    
    # Обратный проход
    for i in range(9, 0, -1):
        for j in range(i + 1, n + 1):
            if (i, j) in costs:
                F[i] = min(F[i], costs[(i, j)] + F[j])
    
    # Восстановление маршрута
    route = []
    current = 1
    while current != 10:
        route.append(current)
        next_node = min(
            ((j, costs[(current, j)] + F[j]) for j in range(current + 1, n + 1) if (current, j) in costs),
            key=lambda x: x[1]
        )[0]
        current = next_node
    route.append(10)
    
    return route, F[1]

# Пример данных (вариант 1)
costs = {
    (1, 2): 7, (1, 3): 3, (1, 4): 5,
    (2, 5): 2, (2, 7): 7,
    (3, 5): 9, (3, 6): 3, (3, 7): 1,
    (4, 5): 8, (4, 6): 4, (4, 7): 5,
    (5, 8): 2, (5, 9): 6,
    (6, 8): 1, (6, 9): 9,
    (7, 9): 4,
    (8, 10): 3,
    (9, 10): 8
}

route, total_cost = find_optimal_route(costs)
print(f"Оптимальный маршрут: {route}")
print(f"Минимальные затраты: {total_cost}")
