#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code for the Node class goes here:
// (Note the 'NodeIterator' class will report lots of errors until Node exists

template<typename T>
class Node{
    public:
    T data;
    Node<T> * next;
    Node<T> * previous;

    Node(T dataObject)
    : next(nullptr), previous(nullptr), data(dataObject)
    {}
    
};


template<typename T>
class NodeIterator {
  
private:
    
    Node<T>* current;
    
public:
    

    NodeIterator(Node<T>* currentIn)
        : current(currentIn) {        
    }

    T & operator*() {
        return current->data;
    }

    // TODO: complete the code for NodeIterator here

    Node<T> * getCurrent() const{
        return current;
    }

    void operator++(){
        current = current -> next;
    }

    void operator++(int){
        current = current -> next;
    }

    bool operator==(const NodeIterator<T> & other){
        return current == other.getCurrent();
    }    

    bool operator!=(const NodeIterator<T> & other){
        return current != other.getCurrent();
    }
    
};

// do not edit below this line

#endif
