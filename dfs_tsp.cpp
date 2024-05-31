#include "dfs_tsp.h"
#include <algorithm>

DFSTSPSolver::DFSTSPSolver(int numCities, const vector<vector<int>>& distances)
    : numCities(numCities), distances(distances), minCost(numeric_limits<int>::max()), visited(numCities, false) {}

int DFSTSPSolver::findMinCostDFS() {
    for (int i = 0; i < numCities; ++i) {
        fill(visited.begin(), visited.end(), false);
        dfs(i, i, 0, 1);
    }
    return minCost;
}

void DFSTSPSolver::dfs(int currentCity, int startCity, int currentCost, int count) {
    if (currentCost >= minCost) {
        return;
    }

    if (count == numCities) {
        currentCost += distances[currentCity][startCity]; // Complete the circuit
        if (currentCost < minCost) {
            minCost = currentCost;
        }
        return;
    }

    visited[currentCity] = true;

    for (int nextCity = 0; nextCity < numCities; ++nextCity) {
        if (!visited[nextCity] && distances[currentCity][nextCity] != 0) {
            int nextCost = currentCost + distances[currentCity][nextCity];
            dfs(nextCity, startCity, nextCost, count + 1);
        }
    }

    visited[currentCity] = false;
}
