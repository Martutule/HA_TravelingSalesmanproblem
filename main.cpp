#include <iostream>
#include "dfs_tsp.h"
#include "ucs_tsp.h"
#include "astar_tsp.h"
#include "tsplib_parser.h"
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void runTestCases(const vector<vector<int>>& distances) {
    // Run DFS and measure the time
    auto startDFS = high_resolution_clock::now();
    DFSTSPSolver dfsSolver(distances.size(), distances);
    int minCostDFS = dfsSolver.findMinCostDFS();
    auto endDFS = high_resolution_clock::now();
    duration<double> elapsedDFS = endDFS - startDFS;
    cout << "Minimum cost (DFS): " << minCostDFS << endl;
    cout << "DFS Runtime: " << elapsedDFS.count() << " seconds" << endl << endl;

    // Run UCS and measure the time
    auto startUCS = high_resolution_clock::now();
    UCSTSPSolver ucsSolver(distances.size(), distances);
    int minCostUCS = ucsSolver.findMinCostUCS();
    auto endUCS = high_resolution_clock::now();
    duration<double> elapsedUCS = endUCS - startUCS;
    cout << "Minimum cost (UCS) " << minCostUCS << endl;
    cout << "UCS Runtime " << elapsedUCS.count() << " seconds" << endl << endl;

    // Run A* and measure the time
    auto startAStar = high_resolution_clock::now();
    ASTAR_TSPSolver astarSolver(distances.size(), distances);
    int minCostAStar = astarSolver.findMinCostAStar();
    auto endAStar = high_resolution_clock::now();
    duration<double> elapsedAStar = endAStar - startAStar;
    cout << "Minimum cost (A*) " << minCostAStar << endl;
    cout << "A* Runtime " << elapsedAStar.count() << " seconds" << endl << endl;
}

vector<vector<int>> calculate_distances(const vector<pair<int, int>>& city_coordinates) {
    int n = city_coordinates.size();
    vector<vector<int>> distances(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                distances[i][j] = 0;
            }
            else {
                int dx = city_coordinates[j].first - city_coordinates[i].first;
                int dy = city_coordinates[j].second - city_coordinates[i].second;
                distances[i][j] = static_cast<int>(round(sqrt(dx * dx + dy * dy)));
            }
        }
    }
    return distances;
}

int main() {
    
    // Insert the .tsp file
    string filename = "ulysses16.tsp";

    try {
        // Parse the TSP file
        std::vector<std::pair<int, int>> city_coordinates = TSPLIBParser::parse_tsp_file(filename);

        // Print the city coordinates with city number
        std::cout << "City Coordinates:" << std::endl;
        int city_number = 1;
        for (const auto& coord : city_coordinates) {
            std::cout << "City " << city_number++ << ": (" << coord.first << ", " << coord.second << ")" << std::endl;
        }
        cout << endl;

        // Calculate distance matrix
        std::vector<std::vector<int>> distance_matrix = calculate_distances(city_coordinates);

        // Print the distance matrix
        cout << "Distance Matrix:" << endl;
        // Print column headers
        cout << setw(4) << "    |";
        for (int i = 1; i <= city_coordinates.size(); ++i) {
            cout << setw(3) << i;
        }
        cout << endl;
        // Print separator line
        cout << "----+";
        for (int i = 0; i < city_coordinates.size() - 2; ++i) {
            cout << "----";
        }
        cout << endl;
        // Print matrix contents
        for (int i = 0; i < distance_matrix.size(); ++i) {
            cout << setw(3) << i + 1 << " |";
            for (int j = 0; j < distance_matrix[i].size(); ++j) {
                cout << setw(3) << distance_matrix[i][j];
            }
            cout << endl;
        }
        cout << endl;
        // Run the test cases
        runTestCases(distance_matrix);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}