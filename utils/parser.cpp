//
// Created by Дима … on 28.01.2026.
//
#include "parser.h"

// example: 0,1111 to 0.1111
double convertingStringToDouble (const std::string& token) {
    try {
        std::string tmp(token);
        std::replace_if(tmp.begin(), tmp.end(), [](char c){return c == ',';}, '.');
        return std::stod(tmp);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid number: " << token << std::endl;
    }
}




std::vector<std::pair<double, double>> parseCvv(const std::string &path) {
    std::ifstream file(path.c_str());
    std::string line;
    std::pair<double, double> tmp;
    std::vector<std::pair<double, double>> result;
    size_t count = 0;

    while (std::getline(file, line))
    {
        std::regex pattern(";");
        std::sregex_token_iterator it(line.begin(), line.end(), pattern, -1);
        std::sregex_token_iterator end;

        for (; it != end; ++it) {
            std::string token = it->str();
            if (count >= 2) {
                double value = convertingStringToDouble(token);

                if (count % 2 == 0) {
                    tmp.first = value;
                } else {
                    tmp.second = value;
                    result.push_back(tmp);
                }

            }
            count++;
        }

    }
    return result;


}

