#ifndef ISTATISTICS_H
#define ISTATISTICS_H

// Абстрактный базовый класс для всех статистических расчетов
class IStatistics {
public:
    virtual ~IStatistics() = default; // Виртуальный деструктор для корректного удаления потомков
    
    // Основной интерфейс:
    virtual void update(double value) = 0; // Метод для обновления данных
    virtual double eval() const = 0;       // Метод для получения результата
};

#endif