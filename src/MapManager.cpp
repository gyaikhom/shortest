#include "MapManager.hpp"

#include <cstring>
#include <cstdio>

MapManager::MapManager(void) {
    unsigned int i, j;
    numLandmarks = 0;
    head = tail = NULL;
    for (i = 0; i < MAX_LMARKS; ++i)
        for (j = 0; j < MAX_LMARKS; ++j)
            weight[i][j] = 0;
}

MapManager::~MapManager(void) {
    destroyLandmarkList();
}

void MapManager::destroyLandmarkList(void) {
    landmarkStructType *x, *y = head;
    while (y != NULL) {
        x = y;
        y = y->next;
        delete x;
    }
}

int MapManager::insertLandmark(int index, const char *name) {
    landmarkStructType *temp;

    // Is the name too long?
    if (strlen(name) > MAX_LMARK_NAME)
        return NAME_TOO_LONG;

    // Is the name repeated?
    for (temp = head; temp != NULL; temp = temp->next)
        if (strcmp(temp->name, name) == 0)
            return NAME_REPEATED;

    // Create a new index.
    temp = new landmarkStructType;
    temp->index = index;
    strcpy(temp->name, name);
    temp->next = NULL; // Always insert new nodes at the end.

    // Check if the linked list is empty.
    if (head == NULL) {
        // Linked list is empty.
        temp->prev = NULL;
        head = temp;
        tail = temp;
    } else {
        // No, insert new node at the tail.
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    return SUCCESS;
}

char *MapManager::getLandmarkName(unsigned int index) {
    landmarkStructType *x;

    if (index > numLandmarks)
        return NULL;

    for (x = head; x != NULL; x = x->next)
        if (x->index == index)
            return x->name;

    return NULL;
}

int MapManager::getLandmarkIndex(const char *name) {
    landmarkStructType *x;
    if (strlen(name) > MAX_LMARK_NAME)
        return -1;

    for (x = head; x != NULL; x = x->next)
        if (strcmp(x->name, name) == 0)
            return x->index;

    return UNDEFINED_LMARK; // Not found. something is wrong.
}

int MapManager::readInputFile(char *fname) {
    FILE *f = NULL;
    char temp, name[MAX_LMARK_NAME];
    unsigned int i, j;

    if ((f = fopen(fname, "r")) == NULL) {
        cerr << "Could not open input file '" << fname << "'..." << endl;
        return FAILED_TO_OPEN_FILE;
    }

    // Read in the landmark list.
    fscanf(f, "%d", &numLandmarks);
    if ((numLandmarks <= 0) || (numLandmarks > MAX_LMARKS)) {
        cout << "Invalid number of landmarks: " << numLandmarks << endl;
        return INVALID_NUM_LMARKS;
    }

    // Read in the landmark names.
    for (i = 0; i < numLandmarks; ++i) {
        // Ignore all preceding blank spaces.
        do {
            fscanf(f, "%c", &temp);
        } while (isspace(temp));

        // Start taking in the name.
        for (j = 0; j < MAX_LMARK_NAME; ++j) {
            fscanf(f, "%c", &name[j]);
            if (name[j] == '"') {
                name[j] = '\0'; // End of name.
                break;
            }
        }

        // Insert a new node.
        if (insertLandmark(i, name) == NAME_REPEATED) {
            destroyLandmarkList();
            return NAME_REPEATED;
        }
    }

    // Read in the adjacency matrix giving the inter-landmark weights.
    for (i = 0; i < numLandmarks; ++i)
        for (j = 0; j < numLandmarks; ++j) {
            fscanf(f, "%d", &weight[i][j]);
            if (weight[i][j] < 0) {
                destroyLandmarkList();
                return INVALID_EDGE_WEIGHT;
            }
        }

    fclose(f);
    return SUCCESS;
}

void MapManager::setWeight(int row, int col, int value) {
    weight[row][col] = value;
}

int MapManager::getNumLandmarks(void) {
    return numLandmarks;
}

int MapManager::getWeight(int row, int col) {
    return weight[row][col];
}

void MapManager::print() {
    landmarkStructType *x;
    unsigned int i, j;

    cout << "Number of landmarks: " << numLandmarks << endl;
    cout << "List of landmarks: " << endl;
    for (x = head; x != NULL; x = x->next)
        cout << "    " << x->name << endl;
    cout << "Inter-landmark weights: " << endl;
    for (i = 0; i < numLandmarks; ++i) {
        for (j = 0; j < numLandmarks; ++j)
            cout << weight[i][j] << " ";
        cout << endl;
    }
}
