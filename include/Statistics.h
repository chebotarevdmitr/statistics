#ifndef STATISTICS_H
#define STATISTICS_H

#include "IStatistics.h"  // Подключаем интерфейс
#include <vector>        // Для хранения значений
#include <cmath>        // Для математических функций
#include <algorithm>   // Для сортировки
#include <limits>     // Для бесконечности
#include <stdexcept> // Для исключений

// 1. Расчет минимального значения
class Min : public IStatistics {
public:
    Min() : m_min(std::numeric_limits<double>::infinity()) {} // Инициализация "бесконечностью"

    void update(double value) override {
        if (value < m_min) m_min = value; // Обновляем минимум
    }

    double eval() const override {
        // Возвращаем NaN если значений не было
        return std::isinf(m_min) ? std::numeric_limits<double>::quiet_NaN() : m_min;
    }

private:
    double m_min;  // Хранение минимума
};

// 2. Расчет максимального значения
class Max : public IStatistics {
public:
    Max() : m_max(-std::numeric_limits<double>::infinity()) {} // Инициализация "-бесконечностью"

    void update(double value) override {
        if (value > m_max) m_max = value; // Обновляем максимум
    }

    double eval() const override {
        return std::isinf(m_max) ? std::numeric_limits<double>::quiet_NaN() : m_max;
    }

private:
    double m_max;
};

// 3. Расчет среднего арифметического
class Mean : public IStatistics {
public:
    Mean() : m_sum(0.0), m_count(0) {}

    void update(double value) override {
        m_sum += value;  // Накопление суммы
        ++m_count;       // Увеличение счетчика
    }

    double eval() const override {
        return m_count ? m_sum / m_count : 0.0; // Защита от деления на ноль
    }

private:
    double m_sum;
    size_t m_count;   // Хранение количества значений
};

// 4. Расчет стандартного отклонения
class Std : public IStatistics {
public:
    explicit Std(const IStatistics& mean_ref) 
        : m_mean_ref(mean_ref) {} // Инъекция зависимости

    void update(double value) override {
        m_sum_sq += value * value; // Накопление суммы квадратов
        ++m_count;
    }

    double eval() const override {
        if (m_count < 2) return 0.0; // Минимум 2 значения для расчета
        
        const double mean = m_mean_ref.eval();
        // Формула несмещенной дисперсии:
        const double variance = (m_sum_sq - m_count * mean * mean) / (m_count - 1);
        return std::sqrt(variance);
    }

private:
    const IStatistics& m_mean_ref; // Ссылка на объект среднего
    double m_sum_sq = 0.0;
    size_t m_count = 0;
};

// 5. Расчет процентиля
class Percentile : public IStatistics {
public:
    explicit Percentile(double percentile) 
        : m_percentile(percentile) {
        if (percentile < 0 || percentile > 100) {
            throw std::invalid_argument("Percentile must be 0-100");
        }
    }

    void update(double value) override {
        m_values.push_back(value); // Сохраняем все значения
    }

    double eval() const override {
        if (m_values.empty()) return std::numeric_limits<double>::quiet_NaN();
        
        std::vector<double> sorted = m_values; // Копия для сортировки
        std::sort(sorted.begin(), sorted.end());
        
        // Формула линейной интерполяции
        const double index = (sorted.size() - 1) * m_percentile / 100.0;
        const size_t lower = static_cast<size_t>(index);
        
        if (lower + 1 >= sorted.size()) return sorted.back();
        
        const double fraction = index - lower;
        return sorted[lower] + fraction * (sorted[lower + 1] - sorted[lower]);
    }

private:
    double m_percentile;
    mutable std::vector<double> m_values; // mutable для кеширования
};

#endif