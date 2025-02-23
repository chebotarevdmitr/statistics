// Statistics.h
#ifndef STATISTICS_H
#define STATISTICS_H

#include "IStatistics.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>

class Min : public IStatistics {
public:
    void update(double value) override;
    double result() const override;

private:
    double min_ = std::numeric_limits<double>::max();
};

class Max : public IStatistics {
public:
    void update(double value) override;
    double result() const override;

private:
    double max_ = std::numeric_limits<double>::lowest();
};

class Mean : public IStatistics {
public:
    void update(double value) override;
    double result() const override;

private:
    double sum_ = 0;
    size_t count_ = 0;
};

class Std : public IStatistics {
public:
    void update(double value) override;
    double result() const override;

private:
    std::vector<double> values_;
};

class Percentile : public IStatistics {
public:
    Percentile(double percentile) : percentile_(percentile) {}
    void update(double value) override;
    double result() const override;

private:
    std::vector<double> values_;
    double percentile_;
};

#endif // STATISTICS_H
