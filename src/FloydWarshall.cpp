#include "FloydWarshall.hpp"

FloydWarshall::FloydWarshall(void) {
    numVertices = -1;
    count = 0;
}

int FloydWarshall::solve(MapManager *map) {
    unsigned int i, j, k;
    int temp;

    numVertices = map->getNumLandmarks();

    // Initialise the distance and predecessor matrices.
    for (i = 0; i < numVertices; ++i)
        for (j = 0; j < numVertices; ++j) {
            predecessor[i][j] = -1;
            temp = map->getWeight(i, j);
            if (temp == 0) distance[i][j] = INFINITY;
            else distance[i][j] = temp;
        }

#ifdef __DEBUG
    // Print the matrices.
    cout << "Distance:" << endl;
    for (i = 0; i < numVertices; ++i) {
        for (j = 0; j < numVertices; ++j)
            cout << distance[i][j] << " ";
        cout << endl;
    }
    cout << "Predecessor:" << endl;
    for (i = 0; i < numVertices; ++i) {
        for (j = 0; j < numVertices; ++j)
            cout << predecessor[i][j] << " ";
        cout << endl;
    }
#endif

    // The main loop with dynamic programming.
    for (k = 0; k < numVertices; ++k)
        for (i = 0; i < numVertices; ++i)
            for (j = 0; j < numVertices; ++j) {
                temp = distance[i][k] + distance[k][j];
                if (distance[i][j] > temp) {
                    distance[i][j] = temp;
                    predecessor[i][j] = k;
                }
            }

#ifdef __DEBUG
    // Print the matrices.
    cout << "Distance:" << endl;
    for (i = 0; i < numVertices; ++i) {
        for (j = 0; j < numVertices; ++j)
            cout << distance[i][j] << " ";
        cout << endl;
    }
    cout << "Predecessor:" << endl;
    for (i = 0; i < numVertices; ++i) {
        for (j = 0; j < numVertices; ++j)
            cout << predecessor[i][j] << " ";
        cout << endl;
    }
#endif
    return 0;
}

void FloydWarshall::printPath(MapManager *map, int source, int destination) {
    if (predecessor[source][destination] == -1) {
        count++;
        cout << count << " | "
                << (map->getWeight(source, destination) > 9 ? "" : " ")
                << map->getWeight(source, destination)
                << " | "
                << map->getLandmarkName(source)
                << " -> "
                << map->getLandmarkName(destination)
                << endl;
    } else {
        FloydWarshall::printPath(map, source,
                predecessor[source][destination]);
        FloydWarshall::printPath(map,
                predecessor[source][destination], destination);
    }
}

void FloydWarshall::displayPath(MapManager *map,
        int source, int destination) {
    count = 0;
    cout << endl
            << "From : " << map->getLandmarkName(source) << endl
            << "  To : " << map->getLandmarkName(destination) << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "#  Cost  From-To" << endl;
    cout << "--------------------------------------------------------" << endl;
    FloydWarshall::printPath(map, source, destination);
    cout << "--------------------------------------------------------" << endl;
    cout << "Total cost of the route: " <<
            distance[source][destination] << endl;
    cout << "--------------------------------------------------------" << endl;
}

int FloydWarshall::displayPaths(MapManager *map) {
    unsigned int i, j;

    if (numVertices < 0 || numVertices > MAX_LMARKS)
        return -1;

    for (i = 0; i < numVertices; ++i)
        for (j = 0; j < numVertices; ++j)
            if (i != j)
                displayPath(map, i, j);
    return 0;
}

