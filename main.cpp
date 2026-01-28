#include <functional>
#include "utils/parser.h"


std::function<double(double)> createLagrangeInterpolator(const std::vector<std::pair<double, double>>& data) {
    size_t n = data.size();
    std::vector<double> denominators(n, 1.0);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                denominators[i] *= (data[i].first - data[j].first);
            }
        }
    }

    return [data, denominators](double x) -> double {
        double result = 0.0;
        size_t n = data.size();
        for (size_t i = 0; i < n; ++i) {
            double numerator = 1.0;
            for (size_t j = 0; j < n; ++j) {
                if (i != j) {
                    numerator *= (x - data[j].first);
                }
            }
            result += data[i].second * (numerator / denominators[i]);
        }
        return result;
    };
}

double q(const std::vector<std::pair<double, double>>& data) {
    size_t n = data.size();
    return (data[n - 1].first - data[0].first)/ (data[1].first - data[0].first );
}

std::vector<std::vector<double>> getDiffTable(const std::vector<std::pair<double, double>>& data) {
    std::vector<std::vector<double>> result;
    result.reserve(data.size());
    for (auto i : data) {
        result[0].push_back(i.second);
    }

    for (size_t i = 1; i < data.size(); i++) {
        result[i].push_back({});
        for (size_t j = 0, szi = result[i-1].size(); j < szi; j++) {
            result[i].push_back(result[i-1][j] - result[i-1][j-1]);
        }
    }

    return result;
}

int main() {
    auto func = createLagrangeInterpolator(parseCvv("/Users/dima.../CLionProjects/LAB_3/dataset_02.csv"));
    std::cout<< "Point 0.1: " << func(0.1) << std::endl;
    std::cout<< "Point 0.6: " << func(0.6) << std::endl;
    std::cout<< "Point 1.2: " << func(1.2) << std::endl;
    // std::cout<< "Point 1.2: " <<  << std::endl;
    for (auto s : getDiffTable(parseCvv("/Users/dima.../CLionProjects/LAB_3/dataset_02.csv"))) {
        for (auto g : s) {
            std::cout<< "table: " << g << std::endl;
        }
    }
    return 0;
}
