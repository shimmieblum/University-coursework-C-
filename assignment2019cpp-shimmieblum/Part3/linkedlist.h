#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>
#include <initializer_list>

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:

template<typename T>
class LinkedList{
    private:
    Node<T> * head;
    Node<T> * tail;
    int count;

    public:
    LinkedList<T>()
    : head(nullptr), tail(nullptr), count(0)
    {}

    LinkedList<T>(std::initializer_list<T> l)
    :head(nullptr), tail(nullptr), count(0){
        for(auto t:l){
            push_back(t);
        }
    }

    ~LinkedList<T>(){
        Node<T> * temp = nullptr;
        while(head){
            temp = head;
            head = temp -> next;
            delete temp;
        }
    }

    void push_front(T item){
        Node<T> * node = new Node<T>(item);
        if(!head){
            head = node;
            tail = node;
            
        }
        else{
            node -> next = head;
            head -> previous = node;
            head = node;
        }
        count++;

    }

    T & front(){
        return head -> data;
    }

    void push_back(T item){
        Node<T> * node = new Node<T>(item);
        if(tail == nullptr){
            tail = node;
            head = node;
        }
        else{
            node -> previous = tail;
            tail -> next = node;
            tail = node;
        }
        count++;
    } 

    T & back(){
        return tail -> data;
    }
    int size(){
        return count;
    }

    NodeIterator<T> begin(){
        NodeIterator<T> it(head);
        return it;
    }
    
    NodeIterator<T> end(){
        NodeIterator<T> it(nullptr);
        return it;
    }

    void reverse(){
        Node<T> * node1 = head;
        Node<T> * node2 = tail;

        T temp = node1->data;
        for(int i = 0; i < (count/2); ++i){
            node1->data = node2->data;
            node2->data = temp;
            node1 = node1->next;
            node2 = node2->previous;
            temp = node1->data;  
        }
    }

    NodeIterator<T> insert(const NodeIterator<T> & it, T data){ 
        
        if(it.getCurrent() == head){
            push_front(data);
            return begin();
        }
        else if(it.getCurrent() == tail){
            push_back(data);
            return NodeIterator<T>(tail);
        }

        else {
            count++;
            Node<T> * node = new Node<T>(data);
            node->next = it.getCurrent();
            node->previous = it.getCurrent()->previous;
            it.getCurrent()-> previous -> next = node;
            it.getCurrent()-> previous = node; 
            
            NodeIterator<T> newIt(node);
            return newIt;
        }

    }

    NodeIterator<T> erase(const NodeIterator<T> & it){
        count--;
        if(it.getCurrent() == head){
            head = head -> next;
            delete it.getCurrent();
            return begin();
        }
        else if(it.getCurrent() == tail){
            tail = tail->previous;
            delete it.getCurrent();
            return end();
        }
        else{
            it.getCurrent()->previous->next = it.getCurrent()->next;
            it.getCurrent()->next->previous =it.getCurrent()->previous;
            NodeIterator<T> newIt(it.getCurrent()->next);
            delete it.getCurrent();
            return newIt;
        }
        
    }
};



// do not edit below this line

#endif
