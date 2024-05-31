#pragma once
// astar_tsp.h
#ifndef ASTAR_TSP_H
#define ASTAR_TSP_H

#include <vector>
#include <limits>
#include <queue>

using namespace std;

class ASTAR_TSPSolver {
public:
    ASTAR_TSPSolver(int numCities, const vector<vector<int>>& distances);
    int findMinCostAStar();

private:
    int numCities;
    vector<vector<int>> distances;

    struct Node {
        int city;
        int cost;
        int heuristic;
        vector<int> path;
        bool operator>(const Node& other) const {
            return cost + heuristic > other.cost + other.heuristic;
        }
    };

    int calculateHeuristic(const vector<int>& path);
};

#endif // ASTAR_TSP_H
