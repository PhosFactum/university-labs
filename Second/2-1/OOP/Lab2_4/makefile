# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Названия файлов и папки
TARGET = main
TEST_TARGET = test_classes
SOURCES = main.cpp classes.cpp
TEST_SOURCES = test_classes.cpp classes.cpp
INCLUDES = classes.h

# Основные цели
all: $(TARGET) $(TEST_TARGET)

# Сборка основного приложения
$(TARGET): $(SOURCES) $(INCLUDES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Сборка тестов
$(TEST_TARGET): $(TEST_SOURCES) $(INCLUDES)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SOURCES) -lgtest -lgtest_main -pthread

# Запуск основного приложения
run: $(TARGET)
	./$(TARGET)

# Запуск тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Очистка скомпилированных файлов
clean:
	rm -f $(TARGET) $(TEST_TARGET)

