// Statistics.cpp
#include "../include/Statistics.h"

void Min::update(double value) {
    if (value < min_) {
        min_ = value;
    }
}

double Min::result() const {
    return min_;
}

void Max::update(double value) {
    if (value > max_) {
        max_ = value;
    }
}

double Max::result() const {
    return max_;
}

void Mean::update(double value) {
    sum_ += value;
    ++count_;
}

double Mean::result() const {
    return sum_ / count_;
}

void Std::update(double value) {
    values_.push_back(value);
}

double Std::result() const {
    if (values_.empty()) {
        throw std::logic_error("No values");
    }
    double mean = std::accumulate(values_.begin(), values_.end(), 0.0) / values_.size();
    double sq_sum = std::inner_product(values_.begin(), values_.end(), values_.begin(), 0.0, std::plus<double>(), 
                                       [mean](double a, double b) { return (a - mean) * (b - mean); });
    return std::sqrt(sq_sum / values_.size());
}

void Percentile::update(double value) {
    values_.push_back(value);
}

double Percentile::result() const {
    if (values_.empty()) {
        throw std::logic_error("No values");
    }
    std::sort(values_.begin(), values_.end());
    size_t index = static_cast<size_t>(percentile_ * values_.size() / 100.0);
    return values_[index];
}
