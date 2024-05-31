#pragma once
// ucs_tsp.h
#ifndef UCS_TSP_H
#define UCS_TSP_H

#include <vector>
#include <limits>
#include <utility>
#include <queue>

using namespace std;

class UCSTSPSolver {
public:
    UCSTSPSolver(int numCities, const vector<vector<int>>& distances);
    int findMinCostUCS();

private:
    int numCities;
    vector<vector<int>> distances;

    struct Node {
        int city;
        int cost;
        vector<int> path;
        bool operator>(const Node& other) const {
            return cost > other.cost;
        }
    };
};

#endif // UCS_TSP_H
