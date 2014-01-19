#include "OrderedSet.hpp"

OrderedSet::OrderedSet(void) {
    // Assume the linked list is empty: empty set.
    numElements = 0;
    head = tail = NULL;
}

OrderedSet::~OrderedSet(void) {
    struct nodeStruct *temp = head;
    // Destroy the linked list.
    if (numElements == 0)
        return;
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int OrderedSet::getNumElements(void) {
    return numElements;
}

bool OrderedSet::isElement(int landmark) {
    struct nodeStruct *temp;
    for (temp = head; temp != NULL; temp = temp->next)
        if (temp->element == landmark)
            return true; // Yes, it is an element.
    return false; // Nope, not an element.
}

int OrderedSet::insert(int landmark) {
    struct nodeStruct *temp;

    if (head == NULL) { // Linked list is empty.
        head = new struct nodeStruct;
        head->element = landmark;
        head->next = NULL;
        head->prev = NULL;
        tail = head;
    } else {
        // Linked list not empty. Check if the landmark is already present.
        for (temp = head; temp != NULL; temp = temp->next)
            if (temp->element == landmark)
                return REPEATED_ITEM_IN_SET;

        // No repetition detected.
        temp = new struct nodeStruct;
        temp->element = landmark;
        temp->next = NULL;
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }

    ++numElements;
    return 0;
}

int OrderedSet::remove(int landmark) {
    struct nodeStruct *temp;

    // Search for the linked list node that represents the landmark.
    for (temp = head; temp != NULL; temp = temp->next)
        // Landmark found; remove it.
        if (temp->element == landmark) {
            // Is the linked list node the head, tail or intermediate?
            if (temp == head) {
                // Is this the only element?
                if (head == tail)
                    head = tail = NULL;
                else {
                    head->next->prev = NULL;
                    head = head->next;
                }
            } else if (temp == tail) {
                tail->prev->next = NULL;
                tail = tail->prev;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            delete temp;
            --numElements;
            return SUCCESS;
        }
    return LMARK_NOT_FOUND;
}

void OrderedSet::print(bool printForward) {
    struct nodeStruct *temp;

    cout << numElements << " : { ";
    if (printForward)
        for (temp = head; temp != NULL; temp = temp->next)
            cout << temp->element << " ";
    else
        for (temp = tail; temp != NULL; temp = temp->prev)
            cout << temp->element << " ";

    cout << "}" << endl;
}

void OrderedSet::printNames(MapManager *map, bool printForward) {
    struct nodeStruct *temp;
    int i, cost, totalCost = 0;

    if (printForward) {
        cout << "From : " << map->getLandmarkName(head->element) << endl;
        cout << "  To : " << map->getLandmarkName(tail->element) << endl << endl;
    } else {
        cout << "From : " << map->getLandmarkName(tail->element) << endl;
        cout << "  To : " << map->getLandmarkName(head->element) << endl;
    }

    cout << "----------------------------------------------" << endl;
    cout << "#  Cost  From-To" << endl;
    cout << "----------------------------------------------" << endl;

    if (printForward)
        for (temp = head, i = 1; temp->next != NULL; temp = temp->next, ++i) {
            cost = map->getWeight(temp->element, temp->next->element);
            totalCost += cost;
            cout << i << " | "
                    << (cost > 9 ? "" : " ")
                    << cost << " | "
                    << map->getLandmarkName(temp->element)
                    << " -> "
                    << map->getLandmarkName(temp->next->element)
                    << endl;
        } else
        for (temp = tail, i = 1; temp->prev != NULL; temp = temp->prev, ++i) {
            cost = map->getWeight(temp->element, temp->prev->element);
            totalCost += cost;
            cout << i << " | "
                    << (cost > 9 ? "" : " ")
                    << cost << " | "
                    << map->getLandmarkName(temp->element)
                    << " -> "
                    << map->getLandmarkName(temp->prev->element)
                    << endl;
        }

    cout << "----------------------------------------------" << endl;
    cout << "Total cost of the route: " << totalCost << endl;
    cout << "----------------------------------------------" << endl;
}

int OrderedSet::nthElement(int n, bool searchForward) {
    struct nodeStruct *temp;

    if (n <= numElements) {
        if (searchForward) {
            for (temp = head; temp != NULL; temp = temp->next)
                if (--n == 0)
                    return temp->element;
        } else {
            for (temp = tail; temp != NULL; temp = temp->prev)
                if (--n == 0)
                    return temp->element;
        }
    }

    return NOT_ENOUGH_ELEMENTS;
}

