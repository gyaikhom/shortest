#include "Dijkstra.hpp"
#include "OrderedSet.hpp"

Dijkstra::Dijkstra(void) {
    unsigned int i;
    numVertices = -1;
    for (i = 0; i < MAX_LMARKS; ++i) {
        distance[i] = INFINITY;
        predecessor[i] = UNDEFINED_LMARK;
    }
}

int Dijkstra::displayPath(MapManager *map, int destination) {
    OrderedSet shortestPath;
    do {
        shortestPath.insert(destination);
        if (predecessor[destination] == UNDEFINED_LMARK)
            break;
        destination = predecessor[destination];
    } while (1);
    shortestPath.printNames(map, 0);
    return 0;
}

int Dijkstra::solve(MapManager *map, int source, int destination) {
    OrderedSet S; // Set of visited vertices.
    OrderedSet Q; // Set of vertices yet to be visited.
    int i, temp, minDistanceVertex;
    int totalDistance, tempDistance;

    numVertices = map->getNumLandmarks();

    // Initialise: Assume that all choices lead to extremely long paths.
    for (i = 0; i < numVertices; ++i) {
        // All paths are infinitely long at the beginning of the
        // algorithm. We assume that the length of the longest path
        // possible is always less than INFINITY.
        distance[i] = INFINITY;

        // I have no predecessor yet. Once the path has been
        // determined, these values will be set to the correct
        // predecessor in the shortest path determined.
        predecessor[i] = UNDEFINED_LMARK;
    }

    // Length of path from source to itself is zero.
    distance[source] = 0;

    // Initialise the 'yet to be visited' set.
    for (i = 0; i < numVertices; ++i)
        Q.insert(i);

    // The main loop of the algorithm:
    // We execute the algorithm until all the vertices in Q has been
    // visited, or the destination vertex has been reached.
    while (Q.getNumElements() > 0) {

        // Extract vertex with minimum total distance from source.
        // To do this, first assume that the first vertex in the set
        // has the least total distance.
        minDistanceVertex = Q.nthElement(1, 1);
        totalDistance = distance[minDistanceVertex];

        // Now find the vertex which actually has the least total
        // distance from the source.
        for (i = 1; i < Q.getNumElements(); ++i) {
            // We have found a vertex which has total distance less
            // than the current minimum.
            temp = Q.nthElement(i + 1, 1);
            if (totalDistance > distance[temp]) {
                minDistanceVertex = temp;
                totalDistance = distance[minDistanceVertex];
            }
        }

        // We have found the next vertex with minimum total
        // distance. Remove this vertex from the 'yet to be visited'
        // set, and insert it in the visited set.
        Q.remove(minDistanceVertex);
        S.insert(minDistanceVertex);

        // Have we reached the destination?
        if (destination > -1 && minDistanceVertex == destination)
            return 0;

        // We have not reached the destination, so continue finding
        // the next vertex with the minimum total distance from the
        // source. In order to do this, we have to update the distance
        // on each of the vertices which is the outgoing vertex from
        // the current minDistanceVertex.
        for (i = 0; i < numVertices; ++i) {
            // Check if there is an outgoing edge from the current
            // minDistanceVertex to the ith vertex. If there is an edge, the
            // weight of this edge must be greater than zero.
            if (map->getWeight(minDistanceVertex, i) > 0) {
                // Now find the total length once this edge is added to
                // the set of visited edges. To do this, we add the
                // edge weight to the current totalDistance, and see if the
                // distance is less than the current distance from
                // source to this vertex.
                tempDistance = totalDistance
                        + map->getWeight(minDistanceVertex, i);
                if (tempDistance < distance[i]) {
                    distance[i] = tempDistance;
                    predecessor[i] = minDistanceVertex;
                }
            }
        }
    }
    return 0;
}

