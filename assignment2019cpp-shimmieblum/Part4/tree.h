#ifndef TREE_H
#define TREE_H

#include "treenode.h"





// TODO your code goes here:
template<typename T>
class BinarySearchTree{
    private:
    
    unique_ptr<TreeNode<T>> root;

    bool areEqual(T t1, T t2){
        return !(t1 < t2 || t2 < t1);
    }
    
    public:
    
    BinarySearchTree<T>(){}
    BinarySearchTree<T>(const BinarySearchTree<T> & other){
        TreeNode<T> * oldRoot = other.getRoot();
     
        root = unique_ptr<TreeNode<T>>(new TreeNode<T>(*oldRoot));
    }

    BinarySearchTree<T> & operator=(const BinarySearchTree<T> & other){
        TreeNode<T> * oldRoot = other.getRoot();
        root = unique_ptr<TreeNode<T>>(new TreeNode<T>(*oldRoot));
        return *this;
    }

    void write(ostream & o)const{
        root->write(o);
    }

    TreeNode<T> * insert(T data){
        if(!root){
            root = unique_ptr<TreeNode<T>>(new TreeNode<T>(data));
            return root.get();
        }

        bool found = false;
        TreeNode<T> * node = root.get();
        TreeNode<T> * child = nullptr;


        while(!found){
            if(areEqual(node->data, data)){
                found = true;
                return node;
            }
            else if(data < node -> data){
                if(node->leftChild){
                    node = node->leftChild.get();
                }
                else{
                    node->setLeftChild(new TreeNode<T>(data));
                    node = node->leftChild.get();
                    found = true;
                }
            }
            else {
                if(node->rightChild){
                    node = node->rightChild.get();
                }
                else{
                    node->setRightChild(new TreeNode<T>(data));
                    node = node->rightChild.get();
                    found = true;
                }
            }
        }
        
        node = balance(node);
        return node;
    }

    TreeNode<T> * balance(TreeNode<T> * a){
        TreeNode<T> * node = a;
        if(node->parent && node->parent->parent){
            TreeNode<T> * parent = node->parent;
            TreeNode<T> * pparent = parent->parent;
            unique_ptr<TreeNode<T>> newNode = unique_ptr<TreeNode<T>>(nullptr);
            
            if(parent->leftChild && parent->rightChild){
                return node;
            }
            else if(pparent->leftChild && pparent->rightChild){
                return node;
            }
            else if(parent->leftChild){
                if(pparent->leftChild){
                    newNode = std::move(rightRotation(pparent));    
                }
                if(pparent->rightChild){
                    newNode = std::move(rightLeftRotation(pparent));
                   
                }
            }
            else if(parent->rightChild){
                if(pparent->rightChild){
                    newNode = std::move(leftRotation(pparent));
                 
                }
                if(pparent->leftChild){
                    newNode = std::move(leftRightRotation(pparent));  
                }
            }
            newNode->parent = pparent->parent;
            
            if(newNode){ // we've performed a switch
                if(!pparent->parent){ // dealing with root
                    root = std::move(newNode);
                    node = root.get();
                }
                else if(pparent == pparent->parent->rightChild.get() ){
                    pparent->parent->rightChild = std::move(newNode);
                }
                else{
                    pparent->parent->leftChild = std::move(newNode);
                }
            }
        }   
        
        return node;
    }

    

    TreeNode<T> * find(T data){
        TreeNode<T> * node = root.get();
        while(node){
            if(areEqual(node->data, data)){
                return node;
            }
            else if(data < node->data){
                node = node->leftChild.get();
            }
            else{
                node = node->rightChild.get();
            }
        }
        return node;
    }

    TreeNode<T> * getRoot() const{
        return root.get();
    } 


    TreeNodeIterator<T> begin(){
        if(!root){
            return TreeNodeIterator<T>(nullptr);
        }

        TreeNode<T> * node = root.get();
        while(node->leftChild){
            node = node->leftChild.get();
        }

        TreeNodeIterator<T> it(node);
        return it;
        
    }

    TreeNodeIterator<T> end(){
        TreeNodeIterator<T> it(nullptr);
        return it;
    }

    int maxDepth(){
        int depth = root->maxDepth();
        return depth;
    }

    unique_ptr<TreeNode<T>> leftRotation(TreeNode<T> * node){
        TreeNode<T> * newNode = new TreeNode<T>(node->data);
        node->rightChild->setLeftChild(newNode);
        unique_ptr<TreeNode<T>> newRoot = move(node->rightChild);
        return newRoot;
    }

    unique_ptr<TreeNode<T>> rightRotation(TreeNode<T> * node){
        TreeNode<T> * newNode = new TreeNode<T>(node->data);
        node->leftChild->setRightChild(newNode);
        unique_ptr<TreeNode<T>> newRoot = move(node->leftChild);
        return newRoot;
    }

    
    unique_ptr<TreeNode<T>> rightLeftRotation(TreeNode<T> * node){
        unique_ptr<TreeNode<T>> C = move(rightRotation(node->rightChild.get()));
        node->rightChild = move(C);
        node->rightChild->parent = node;
        unique_ptr<TreeNode<T>> newRoot = move(leftRotation(node));
        return newRoot;
    }

    unique_ptr<TreeNode<T>> leftRightRotation(TreeNode<T> * node){
        unique_ptr<TreeNode<T>> C = move(leftRotation(node->leftChild.get()));
        node->leftChild = move(C);
        node->leftChild->parent = node;
        unique_ptr<TreeNode<T>> newRoot = move(rightRotation(node));
        return newRoot;
    }


};





// do not edit below this line

#endif
