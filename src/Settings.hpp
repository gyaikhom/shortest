#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <iostream>
#include <cstdlib>

using namespace std;

const unsigned int INFINITY = 999999; // Assumed value of infinity.
const unsigned int MAX_LMARKS = 100; // Maximum number of landmarks.
const unsigned int MAX_LMARK_NAME = 256; // Maximum length of landmark names.
const int UNDEFINED_LMARK = -1;

/**
 * Stores information about a landmark.
 */
typedef struct landmarkStruct {
    unsigned int index;
    char name[MAX_LMARK_NAME];
    struct landmarkStruct *next, *prev;
} landmarkStructType;

/**
 * Error codes.
 */
const int SUCCESS = 0;
const int NAME_TOO_LONG = -1;
const int NAME_REPEATED = -2;
const int FAILED_TO_OPEN_FILE = -3;
const int INVALID_NUM_LMARKS = -4;
const int INVALID_EDGE_WEIGHT = -5;
const int REPEATED_ITEM_IN_SET = -6;
const int LMARK_NOT_FOUND = -7;
const int NOT_ENOUGH_ELEMENTS = -8;

#endif /* SETTINGS_HPP */

