% Лабораторная работа 5 - Вариант 8
% Задача оптимизации методом динамического программирования

nodes = 10;
graph = inf(nodes); % Инициализация матрицы стоимостей

% Заполнение матрицы по варианту 8
graph(1,2) = 6;
graph(1,3) = 2;
graph(1,4) = 6;

graph(2,5) = 7;
graph(2,7) = 3;

graph(3,5) = 9;
graph(3,6) = 2;
graph(3,7) = 8;

graph(4,5) = 5;
graph(4,6) = 2;
graph(4,7) = 9;

graph(5,8) = 4;
graph(5,9) = 6;

graph(6,8) = 7;
graph(6,9) = 4;

graph(7,9) = 6;

graph(8,10) = 7;
graph(9,10) = 6;

% Обратный проход — инициализация
cost = inf(1, nodes);
cost(10) = 0;
path = cell(1, nodes);
path{10} = [10];

% Обратный динамический проход: двигаемся от конца к началу
for node = nodes-1:-1:1
    for next = node+1:nodes
        if graph(node, next) < inf
            temp_cost = graph(node, next) + cost(next);
            if temp_cost < cost(node)
                cost(node) = temp_cost;
                path{node} = [node, path{next}];
            end
        end
    end
end

% Вывод в файл
output_file = fopen("results.txt", "w");

fprintf(output_file, "Оптимальный маршрут из пункта 1 в 10:\n");
fprintf("Оптимальный маршрут из пункта 1 в 10:\n");
if ~isempty(path{1})
    disp(path{1});
    fprintf(output_file, "%s\n", mat2str(path{1}));
    fprintf(output_file, "Минимальная стоимость: %d д.е.\n\n", cost(1));
    fprintf("Минимальная стоимость: %d д.е.\n\n", cost(1));
else
    fprintf(output_file, "Нет пути\n");
    fprintf("Нет пути\n");
end

fprintf(output_file, "Маршруты из всех пунктов в 10:\n");
fprintf("Маршруты из всех пунктов в 10:\n");

for i = 1:nodes
    fprintf(output_file, "Пункт %d: ", i);
    fprintf("Пункт %d: ", i);
    if isempty(path{i})
        fprintf(output_file, "Нет пути\n");
        fprintf("Нет пути\n");
    else
        fprintf(output_file, "%s\n", mat2str(path{i}));
        fprintf(output_file, "Стоимость: %d д.е.\n", cost(i));
        fprintf("Стоимость: %d д.е.\n", cost(i));
    end
end

fclose(output_file);

