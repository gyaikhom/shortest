#ifndef FLOYD_WARSHALL_HPP
#define	FLOYD_WARSHALL_HPP

#include "MapManager.hpp"

// This class implements the Floyd-Warshll algorithm, which generates
// the all-pair shortest paths between all vertex pairs. We assume that
// the maximum number of vertices is always less than MAX_LMARKS.

class FloydWarshall {
private:
    unsigned int count;
    unsigned int numVertices;

    // Distance between vertex pairs.
    int distance[MAX_LMARKS][MAX_LMARKS];

    // Predecessor of the vertex which has the column number as index.
    int predecessor[MAX_LMARKS][MAX_LMARKS];

    // Print the path recursively.
    void printPath(MapManager *map, int source, int destination);

    // Display path header and related information.
    void displayPath(MapManager *map, int source, int destination);

public:
    FloydWarshall(void);
    int solve(MapManager *map);
    int displayPaths(MapManager *map);
};

#endif	/* FLOYD_WARSHALL_HPP */

