#include "tsplib_parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <limits>

std::vector<std::pair<int, int>> TSPLIBParser::parse_tsp_file(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::pair<int, int>> city_coordinates;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    bool reading_coords_section = false;

    while (std::getline(file, line)) {
        if (line.find("NODE_COORD_SECTION") != std::string::npos) {
            reading_coords_section = true;
            continue;
        }

        if (reading_coords_section) {
            if (line.find("EOF") != std::string::npos) {
                break;
            }

            std::istringstream iss(line);
            int city_id;
            double x, y;
            if (iss >> city_id >> x >> y) {
                city_coordinates.push_back({ static_cast<int>(x), static_cast<int>(y) });
            }
        }
    }

    if (!reading_coords_section) {
        throw std::runtime_error("Invalid TSP file format: Missing NODE_COORD_SECTION.");
    }

    if (city_coordinates.empty()) {
        throw std::runtime_error("No city coordinates found in the TSP file.");
    }

    return city_coordinates;
}
