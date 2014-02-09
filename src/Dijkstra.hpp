#ifndef DIJKSTRA_HPP
#define	DIJKSTRA_HPP

#include "MapManager.hpp"

class Dijkstra {
private:
	int numVertices;

	// The distance between vertex pairs.
	int distance[MAX_LMARKS];

	// The predecessor of the vertex which has the column number as
	// index.
	int predecessor[MAX_LMARKS];
	
public:
	Dijkstra(void);
	int solve(MapManager *map, int source, int destination);
	int displayPath(MapManager *map, int destination);
};

#endif	/* DIJKSTRA_HPP */

