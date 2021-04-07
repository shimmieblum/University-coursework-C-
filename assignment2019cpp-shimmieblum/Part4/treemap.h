#ifndef TREEMAP_H
#define TREEMAP_H

#include "tree.h"

template<typename Key, typename Value>
class KeyValuePair {
    
public:
    
    const Key k;
    Value v;
    
    // TODO your code for KeyValuePair goes here
    
    KeyValuePair(Key key, Value value)
    :k(key), v(value){}

    KeyValuePair(Key key):k(key){}

    bool operator<(const KeyValuePair & other) const{
        return k < other.k;
    }

    const Value & getValue(){
        return v;
    }
    
    
};



template<typename Key, typename Value>
ostream & operator<< (ostream & o, const KeyValuePair<Key,Value> & kv){
    o << kv.k << "," << kv.v;
    return o;
}



template<typename Key, typename Value>
class TreeMap {
  
private:
    BinarySearchTree<KeyValuePair<Key,Value> > tree;
    
public:
    
    KeyValuePair<Key,Value> * insert(const Key & k, const Value & v) {
        return &(tree.insert(KeyValuePair<Key,Value>(k,v))->data);
    }
    
    void write(ostream & o)const {
        tree.write(o);
    }

    KeyValuePair<Key,Value> * find(Key key){
        KeyValuePair<Key,Value> pair(key);
        TreeNode<KeyValuePair<Key,Value>> * node = tree.getRoot();
        while(node){
            if(!(node->data < pair || pair < node->data)){
                return &node->data;
            }
            else if(pair < node->data){
                node = node->leftChild.get();
            }
            else{
                node = node->rightChild.get();
            }
        }
        return &node->data;

    }
    
    // TODO your code for TreeMap goes here:
    
    
    
    
};


// do not edit below this line

#endif
