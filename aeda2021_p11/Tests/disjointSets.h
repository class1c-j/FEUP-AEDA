#ifndef DISJOINTSETS_H
#define DISJOINTSETS_H

#include <vector>
#include <algorithm>

class DisjointSets {
    std::vector<int> set;
public:
    DisjointSets();

    explicit DisjointSets(int n);

    int find(int v) const;

    void unionSets(int root1, int root2);

    int getNumberOfSets() const;
};

#endif
