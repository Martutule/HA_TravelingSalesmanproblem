#ifndef DFS_TSP_H
#define DFS_TSP_H

#include <vector>
#include <limits>

using namespace std;

class DFSTSPSolver {
public:
    DFSTSPSolver(int numCities, const vector<vector<int>>& distances);
    int findMinCostDFS();

private:
    int numCities;
    vector<vector<int>> distances;
    int minCost;
    vector<bool> visited;

    void dfs(int currentCity, int startCity, int currentCost, int count);
};

#endif // DFS_TSP_H
