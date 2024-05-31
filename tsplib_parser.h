#ifndef TSPLIB_PARSER_H
#define TSPLIB_PARSER_H

#include <vector>
#include <string>
#include <utility>

class TSPLIBParser {
public:
    static std::vector<std::pair<int, int>> parse_tsp_file(const std::string& filename);
};

#endif // TSPLIB_PARSER_H
