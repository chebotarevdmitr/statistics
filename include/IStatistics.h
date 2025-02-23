// IStatistics.h
#ifndef ISTATISTICS_H
#define ISTATISTICS_H

class IStatistics {
public:
    virtual void update(double value) = 0;
    virtual double result() const = 0;
    virtual ~IStatistics() = default;
};

#endif // ISTATISTICS_H
