// astar_tsp.cpp
#include "astar_tsp.h"
#include <algorithm>
#include <numeric>

ASTAR_TSPSolver::ASTAR_TSPSolver(int numCities, const vector<vector<int>>& distances)
    : numCities(numCities), distances(distances) {}

int ASTAR_TSPSolver::findMinCostAStar() {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    for (int i = 0; i < numCities; ++i) {
        vector<int> path = { i };
        int heuristic = calculateHeuristic(path);
        pq.push({ i, 0, heuristic, path });
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
                int heuristic = calculateHeuristic(nextPath);
                pq.push({ nextCity, nextCost, heuristic, nextPath });
            }
        }
    }

    return minCost;
}

int ASTAR_TSPSolver::calculateHeuristic(const vector<int>& path) {
    vector<int> remaining;
    for (int i = 0; i < numCities; ++i) {
        if (find(path.begin(), path.end(), i) == path.end()) {
            remaining.push_back(i);
        }
    }

    if (remaining.empty()) {
        return distances[path.back()][path.front()];
    }

    int nearestToLast = numeric_limits<int>::max();
    int nearestToFirst = numeric_limits<int>::max();
    for (int city : remaining) {
        nearestToLast = min(nearestToLast, distances[path.back()][city]);
        nearestToFirst = min(nearestToFirst, distances[city][path.front()]);
    }

    return nearestToLast + nearestToFirst;
}
