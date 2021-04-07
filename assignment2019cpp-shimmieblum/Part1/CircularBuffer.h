#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

// NB: Do not add any extra #include statements to this file
#include "SimpleVector.h"
#include <iostream>


/** TODO: complete the definition of the class CircularBuffer here
 *
 * Its constructor should take the size of the buffer as an argument
 *
 * It needs to have the functions:
 * - count() which returns how many things are in the buffer
 * - full() which returns true iff the buffer is full
 * - add() which takes an element and adds it to the buffer (you can assume the buffer is not full)
 * - remove() which removes the next element from the buffer (you can assume the buffer is not empty)
 */
class CircularBuffer {
    SimpleVector<char> vector;
    int first;
    int last;

    public:
    CircularBuffer(const int capacity)
    : vector(capacity), first(0), last(0) 
    {}

    int count() {
        if(first <= last) {
            return last - first; 
        }
        else{
            return vector.size() - first + last;
        }
    }

    bool full() {
          return count() == vector.size();
    }

    void add(char c) { 
        vector[last] = c;
        last = next(last);
        }

    char remove() {
        char c = vector[first];
        first = next(first);
        return c;
    }

    private:

    int next(int value) {
        
        return ++value % vector.size();
    }    


};


// don't write any code below this line

#endif
