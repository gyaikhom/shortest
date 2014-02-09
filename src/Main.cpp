#include "MapManager.hpp"
#include "Dijkstra.hpp"
#include "FloydWarshall.hpp"

const char helpMessage[] =
        "USAGE: \n\n"
        "  shortest locations.map [source] [destination]\n\n"
        "Display this help message if no arguments are provided.\n\n"
        "This application implements two approaches to finding out the\n"
        "shortest path between two landmarks on a locations map:\n\n"
        "1) Dijkstra's shortest path algorithm:\n"
        "   This algorithm allows us to find the shortest path\n"
        "   between two landmarks: the source and the destination.\n\n"
        "   To use this approach, provide four arguments to this\n"
        "   application, as follows:\n\n"
        "       shortest locations.map 2 3\n\n"
        "   where, 2 and 3 are respectively the indices of the source\n"
        "   and the destination landmarks in locations.map. Note that\n"
        "   indexing beings at zero, and not at one).\n\n"
        "   Alternatively, the user may also specify the landmarks by name.\n"
        "   For instance,\n\n"
        "       shortest locations.map \"Edinburgh\" \"Oxford\"\n\n"
        "2) Floyd-Warshall's all-pair shortest paths algorithm:\n"
        "   This algorithm allows us to find all of the shortest paths\n"
        "   between every landmark on the locations.map. It is particularly\n"
        "   useful when we wish to generate all of the paths for display\n"
        "   at each of the landmarks.\n\n"
        "   To use this approach, invoke the application as follows:\n\n"
        "       shortest locations.map\n\n"
        ;

void runDijkstra(MapManager *map, int source, int destination) {
    Dijkstra djtra;

    djtra.solve(map, source, destination);
    djtra.displayPath(map, destination);
}

void runFloydWarshall(MapManager *map) {
    FloydWarshall fw;

    fw.solve(map);
    fw.displayPaths(map);
}

int getLandmarkIndex(MapManager *map, const char *str) {
    int i, landmarkIndex;
    bool flag = false;
    for (i = 0; str[i] != '\0'; ++i) {
        if (isalpha(str[i])) {
            flag = true;
            break;
        }
    }
    if (flag == true)
        landmarkIndex = map->getLandmarkIndex(str);
    else
        landmarkIndex = atoi(str);
    return landmarkIndex;
}

int main(int argc, char *argv[]) {
    MapManager map;
    int source, destination;

    source = destination = UNDEFINED_LMARK;

    if (argc == 2) {
        map.readInputFile(argv[1]);
        runFloydWarshall(&map);
    } else if (argc == 4) {
        map.readInputFile(argv[1]);
        source = getLandmarkIndex(&map, argv[2]);
        destination = getLandmarkIndex(&map, argv[3]);
        if (source == destination) {
            cout << "Error: Source and destination must be different.\n";
            exit(1);
        }
        runDijkstra(&map, source, destination);
    } else
        cout << helpMessage << endl;
    return 0;
}
