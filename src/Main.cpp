#include "MapManager.hpp"

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

void runDijkstra(MapManager *map, int src, int dest) {
}

void runFloydWarshall(MapManager *map) {
}

int main(int argc, char *argv[]) {
    MapManager map;
    int src, dest;
    
    src = dest = LMARK_UNDEFINED;
    
    if (argc == 2) {
        map.readInputFile(argv[1]);
        runFloydWarshall(&map);
    } else if (argc == 4) {
        map.readInputFile(argv[1]);
        runDijkstra(&map, src, dest);
    } else
        cout << helpMessage << endl;
    map.print();
    return 0;
}
