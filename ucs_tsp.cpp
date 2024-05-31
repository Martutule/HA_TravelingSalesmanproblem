// ucs_tsp.cpp
#include "ucs_tsp.h"
#include <algorithm>
#include <queue>

UCSTSPSolver::UCSTSPSolver(int numCities, const vector<vector<int>>& distances)
    : numCities(numCities), distances(distances) {}

int UCSTSPSolver::findMinCostUCS() {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    for (int i = 0; i < numCities; ++i) {
        pq.push({ i, 0, {i} });
    }

    int minCost = numeric_limits<int>::max();

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.path.size() == numCities) {
            int returnCost = current.cost + distances[current.city][current.path[0]];
            if (returnCost < minCost) {
                minCost = returnCost;
            }
            continue;
        }

        for (int nextCity = 0; nextCity < numCities; ++nextCity) {
            if (find(current.path.begin(), current.path.end(), nextCity) == current.path.end()) {
                int nextCost = current.cost + distances[current.city][nextCity];
                vector<int> nextPath = current.path;
                nextPath.push_back(nextCity);
                pq.push({ nextCity, nextCost, nextPath });
            }
        }
    }

    return minCost;
}
