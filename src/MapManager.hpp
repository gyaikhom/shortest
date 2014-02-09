#ifndef MAP_MANAGER_HPP
#define MAP_MANAGER_HPP

#include "Settings.hpp"

/**
 * The MapManager class manages user supplied locations map.
 */
class MapManager {
private:
    // Number of landmarks in locations map.
    unsigned int numLandmarks;

    // Head and tail pointers to the linked list of landmarks.
    landmarkStructType *head, *tail;

    // Adjacency matrix of inter-landmark weights.
    int weight[MAX_LMARKS][MAX_LMARKS];

public:
    MapManager(void);
    ~MapManager(void);
    int readInputFile(char *fname);
    void print();

    // Landmark linked list.
    int getNumLandmarks(void);
    int insertLandmark(int index, const char *name);
    int getLandmarkIndex(const char *name);
    char *getLandmarkName(unsigned int index);
    void destroyLandmarkList(void);

    // Inter-landmark weights.
    void setWeight(int row, int col, int value);
    int getWeight(int row, int col);
};

#endif /* MAP_MANAGER_HPP */

