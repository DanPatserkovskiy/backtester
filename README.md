# SMA Backtester

Тестер стратегии с расчётом PnL, позиции и метрик риска.
[![CI/CD Pipeline](https://github.com/DanPatserkovskiy/backtester/actions/workflows/ci.yml/badge.svg)](https://github.com/DanPatserkovskiy/backtester/actions/workflows/ci.yml)

## Описание
На данный момент проект представляет собой следующее: программа читает ряд цен, генерирует сигналы на основе пересечения короткой и длинной скользящих средних (SMA), симулирует торговлю по правилу "next open" и рассчитывает метрики эффективности. По сути — это тренажёр, на котором можно тестировать стратегию для торговли.
В данный момент выборка значений вшита в исходный код (в main.cpp):

```cpp
std::vector<double> prices = {110, 105, 100, 95, 90, 85, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 120, 115, 110, 105, 100, 95, 90};
```

Точно так же вшита длина кривой SMA (короткое и длинное окно):

```cpp
auto signals = backtest::sma_crossover_signals(prices, 3, 5);
```

## Структура проекта
- `include/backtest/` — заголовочные файлы (API)
- `src/` — реализация логики и CLI
- `tests/` — unit-тесты (doctest)
- `benchmarks/` — замеры производительности (Google Benchmark)

## Сборка и запуск

Требования: CMake >= 3.14, компилятор C++17.

```bash
# Конфигурация и сборка
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Запуск тестов
ctest --test-dir build --output-on-failure

# Запуск бенчмарка
./build/bench_backtest

# Запуск самого бэктестера (CLI)
./build/backtest_cli

## Документация
Автоматически сгенерированная документация (Doxygen) доступна по ссылке:
👉 **[https://danpatserkovskiy.github.io/backtester/](https://danpatserkovskiy.github.io/backtester/)**