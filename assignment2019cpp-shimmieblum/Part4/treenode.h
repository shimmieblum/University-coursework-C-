#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:
template<typename T>
class TreeNode{
    public:
    T data;
    unique_ptr<TreeNode> leftChild;
    unique_ptr<TreeNode> rightChild;
    TreeNode<T> * parent;
    
    TreeNode<T>(T inData)
    :data(inData), parent(nullptr), leftChild(nullptr), rightChild(nullptr)
    {}

    TreeNode<T>(const TreeNode<T> & other):
    data(other.data), leftChild(nullptr), rightChild(nullptr) 
    {
        if(other.leftChild.get()){
            TreeNode<T>* left = new TreeNode<T>(*other.leftChild.get());
            setLeftChild(left);
        }
        if(other.rightChild.get()){
            TreeNode<T>* right = new TreeNode<T>(*other.rightChild.get());    
            setRightChild(right);
        }
    }

    


    void setLeftChild(TreeNode<T>* child){
        leftChild = unique_ptr<TreeNode<T>>(child);
        leftChild->parent = this;
    }

    void setRightChild(TreeNode<T>* child){
        rightChild = unique_ptr<TreeNode<T>>(child);
        rightChild->parent = this;
    }

    void write(ostream & out) const {
        if(leftChild){
            leftChild->write(out);    
        }
        out<<" "<<data<<" ";
        if(rightChild){
            rightChild->write(out);
        }
    }

    int maxDepth(){

        if(!leftChild && !rightChild){
            return 1;
        }

        int right = 0;
        int left = 0;
        
        if(rightChild)  right = rightChild.get()->maxDepth();
        if(leftChild) left = leftChild.get()->maxDepth();

        if(right<left){
            return 1 + left;
        }
        
        return 1 + right;
    }

    private:

    int max(int int1, int int2){
            if(int1<int2){
                return int2;
            }
            return int1;
    }

};


template<typename T>
class TreeNodeIterator{
    
    private:
    TreeNode<T> * current;

    public:
    TreeNodeIterator<T>(TreeNode<T> * other):current(other){}

    T & operator*(){
        return current->data;
    }

    TreeNode<T> * getCurrent() const{
        return current;
    }

    bool operator==(const TreeNodeIterator<T> & other){
        return current == other.getCurrent();
    }

    bool operator!=(const TreeNodeIterator<T> & other)
    {
        return current != other.getCurrent();
    }

    void operator++(){
        TreeNode<T> * parent = current->parent;
        
        if(!parent){
            if(current->rightChild){
                current = current->rightChild.get();
                while(current->leftChild){
                    current = current->leftChild.get();
                }
            }
            else {
                current = nullptr;
            }
        }
        else if(current == parent->leftChild.get()){
            if(current->rightChild){
                current = current->rightChild.get();
                while(current->leftChild){
                    current = current->leftChild.get();
                }
            }
            else{
                current = parent;
            }
        }
        else if(current == parent->rightChild.get()){
            if(!current->rightChild){
                current = parent;
                parent = current->parent;
                while(parent && current == parent->rightChild.get()){
                    current = parent;
                    parent = current->parent;
                }
                current = parent;
                
                
            }
            else{
                current = current->rightChild.get();
                while(current->leftChild){
                    current = current->leftChild.get();
                }
            }
        }
    }



    
};


// do not edit below this line

#endif
