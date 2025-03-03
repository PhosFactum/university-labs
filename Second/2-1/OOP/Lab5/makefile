# Компилятор и его флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Название выходного файла
TARGET = main

# Список исходных файлов
SRCS = main.cpp StaticArray.h Rational.h

# Правило сборки
$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

# Очистка скомпилированных файлов
clean:
	rm -f $(TARGET)

