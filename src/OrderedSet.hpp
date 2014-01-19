#ifndef ORDEREDSET_HPP
#define ORDEREDSET_HPP

#include "MapManager.hpp"

/**
 * The OrderedSet class implements an ordered set of landmarks as a linked list.
 */
class OrderedSet {
private:

    struct nodeStruct {
        int element; // The index of the landmark.
        struct nodeStruct *next, *prev;
    } *head, *tail; // Head and tail of the linked list.
    int numElements; // Number of landmarks in the set.

public:
    OrderedSet(void);
    ~OrderedSet(void);

    // Returns the number of landmarks in the set.
    int getNumElements(void);

    // Is the given landmark in the set?
    bool isElement(int landmark);

    // Inserts a new landmark into the set. Always inserts new nodes at
    // the end of the linked list.
    int insert(int landmark);

    // Removes a landmark from the set.
    int remove(int landmark);

    // Prints landmarks in the set. If printForward flag is true, the
    // landmarks are printed in forward order (head to tail); otherwise,
    // they are printed in the reverse order (tail to head), otherwise.
    void print(bool printForward);

    // Prints the named of landmarks in the supplied map. If printForward
    // flag is true, the landmarks are printed in forward order
    // (head to tail); otherwise, they are printed in the
    // reverse order (tail to head).
    void printNames(MapManager *map, bool printForward);

    // Returns the nth element in the landmark set. If searchForward
    // flag is true, counting begins at the head; otherwise, counting
    // begins at the tail.
    int nthElement(int n, bool searchForward);
};

#endif /* ORDEREDSET_HPP */

