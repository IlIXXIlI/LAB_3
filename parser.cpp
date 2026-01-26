#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

// std::vector<std::pair<double, double>>

std::sregex_token_iterator splitLine(const std::string& line, const std::string& pat) {
    std::regex pattern(pat);
    std::sregex_token_iterator result(line.begin(), line.end(), pattern, -1);
    std::sregex_token_iterator end;
    return result, end;
}

// example: 0,1111 to 0.1111
double convertingStringToDouble (const std::string& token) {
    try {
        std::replace_if(token.begin(), token.end(), [](wchar_t c){return c == L',';}, L'.');
        double value = std::stod(token);
        return value;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid number: " << token << std::endl;
    }
}




std::vector<std::pair<double, double>> parseCvv(const std::string &path) {
    std::ifstream file(path.c_str());
    std::string line;
    std::vector<std::pair<double, double>> result; 
    size_t count = 0;
    while (std::getline(file, line))
    {
        std::sregex_token_iterator it, end = splitLine(line, ";");
        
        double x = 0.0, y = 0.0;
       
        for (; it != end; ++it) {
            std::string token = it->str();
            
            if (count >= 2) {
                double value = convertingStringToDouble(token);
                if (count % 2) {
                    x = value;
                } else {
                    y = value; 
                    result.push_back({x, y});
                }

            }
            count++;
        }
       
    }
    return result;

   
}


int main() {
    auto result = parseCvv("dataset_02.csv");
    for (auto i : result) {
        std::cout << i.first << " " << i.second << std::endl;
    }
}