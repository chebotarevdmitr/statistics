// main.cpp
#include <iostream>
#include <vector>
#include <memory>
#include "../include/Statistics.h"

int main() {
    std::vector<std::unique_ptr<IStatistics>> statistics;
    statistics.emplace_back(std::make_unique<Min>());
    statistics.emplace_back(std::make_unique<Max>());
    statistics.emplace_back(std::make_unique<Mean>());
    statistics.emplace_back(std::make_unique<Std>());
    statistics.emplace_back(std::make_unique<Percentile>(90)); // 90th percentile
    statistics.emplace_back(std::make_unique<Percentile>(95)); // 95th percentile

    double value;
    while (std::cin >> value) {
        for (auto& stat : statistics) {
            stat->update(value);
        }
    }

    std::cout << "min = " << statistics[0]->result() << std::endl;
    std::cout << "max = " << statistics[1]->result() << std::endl;
    std::cout << "mean = " << statistics[2]->result() << std::endl;
    std::cout << "std = " << statistics[3]->result() << std::endl;
    std::cout << "pct90 = " << statistics[4]->result() << std::endl;
    std::cout << "pct95 = " << statistics[5]->result() << std::endl;

    return 0;
}
